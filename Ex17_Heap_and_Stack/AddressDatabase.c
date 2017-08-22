#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MYBUF 1024
char BUF[MYBUF];

typedef struct address
{
    int id;
    int set;
    char* name;
    char* email;
} Address;

typedef struct database
{
    int size_db;
    int size_data;
    Address* rows;
} Database;

typedef struct Connection
{
    FILE* fh;
    Database* db;
} Connection;

void Database_close(Connection* conn);

void die(const char* message, Connection* conn)
{
    Database_close(conn);
    if(errno){
        perror(message);
    }else{
        fprintf(stderr, "ERROR: %s\n", message);
    }

    exit(EXIT_FAILURE);
}

void Address_print(Address* addr)
{
    printf("ID: %d\nName: %s\nemail: %s\n", addr->id, addr->name, addr->email);
}

void Database_load(Connection* conn)
{
    Database* db = conn->db;

    int rc = fread(db, sizeof(Database), 1, conn->fh);
    fprintf(stderr, "Database_load; db->size_db = %d, db->size_data = %d", db->size_db, db->size_data);
    if(rc != 1){
        fprintf(stderr, "rc = %d\n", rc);
        die("Failed to load database.", conn);
    }

    conn->db->rows = (Address*)malloc(sizeof(Address) * db->size_db);
    if(!conn->db->rows)
        die("Memory error", conn);

    // char buf[db->size_data];
    for(int i = 0; i < db->size_db; ++i){
        Address* addr = &db->rows[i];

        rc = fread(&addr->id, sizeof(int), 1, conn->fh);
        if(rc != 1)
            die("Failed to read Address record.", conn);
        
        rc = fread(&addr->set, sizeof(int), 1, conn->fh);
        if(rc != 1)
            die("Failed to read Address record.", conn);

        addr->name = (char*)malloc(db->size_data);
        if(!addr->name)
            die("Memory allocation error.", conn);
        
        addr->email = (char*)malloc(db->size_data);
        if(!addr->email)
            die("Memory allocation error.", conn);
        
        rc = fread(BUF, sizeof(char), db->size_data, conn->fh);
        if(rc != db->size_data)
            die("Failed to read a name record.", conn);
        memcpy(addr->name, BUF, db->size_data);

        BUF[db->size_data-1] = '\0';

        rc = fread(BUF, sizeof(char), db->size_data, conn->fh);
        if(rc != db->size_data)
            die("Failed to read a email record.", conn);
        BUF[db->size_data-1] = '\0';
        memcpy(addr->email, BUF, db->size_data);
        
    }
}

Connection* Database_open(const char* filename, char mode, size_t size_db)
{
    Connection* conn = (Connection*)malloc(sizeof(Connection));
    if(!conn)
        die("Memory error", conn);

    conn->db = (Database*)malloc(sizeof(Database));
    if(!conn->db)
        die("Memory error", conn);

    if(mode == 'c'){
        conn->fh = fopen(filename, "wb");
    }else{
        conn->fh = fopen(filename, "rb+");

        if(conn->fh){
            Database_load(conn);
        }
    }

    if(!conn->fh)
        die("Failed to open the file", conn);

    return conn;
}

static void free_address(Address* addr)
{
    if(addr->name)
        free(addr->name);
    if(addr->email)
        free(addr->email);
}

static void free_database(Database* db)
{
    if(db->rows){
        for(int i = db->size_db-1; i >= 0; --i)
            free_address(&db->rows[i]);

        free(db->rows);
    }

    free(db);
}

void Database_close(Connection* conn)
{
    if(conn){
        if(conn->fh)
            fclose(conn->fh);
        if(conn->db){
            free_database(conn->db);
        }
        free(conn);
    }
}


void Database_write(Connection* conn)
{
    Database* db = conn->db;
    rewind(conn->fh);

    int rc = fwrite(db, sizeof(Database), 1, conn->fh);

    if(rc != 1)
        die("Failed to write database.", conn);

    for(int i = 0; i < db->size_db; ++i){
        rc = fwrite(&db->rows[i].id, sizeof(int), 1, conn->fh);
        if(rc != 1)
            die("Failed to write Address to database.", conn);

        rc = fwrite(&db->rows[i].set, sizeof(int), 1, conn->fh);
        if(rc != 1)
            die("Failed to write Address to database.", conn);

        rc = fwrite(db->rows[i].name, sizeof(char), db->size_data, conn->fh);
        if(rc != db->size_data)
            die("Failed to write Address.name to database.", conn);

        rc = fwrite(db->rows[i].email, sizeof(char), db->size_data, conn->fh);
        if(rc != db->size_data)
            die("Failed to write Address.email to database.", conn);
    }

    rc = fflush(conn->fh);
    if(rc == EOF)
        die("Could not flush database to file.", conn);
}

void Database_create(Connection* conn, size_t size_db, size_t size_data)
{
    int i;
    conn->db->size_db = size_db;
    conn->db->size_data = size_data;

    conn->db->rows = (Address*)malloc(sizeof(Address) * size_db);
    if(!conn->db->rows)
        die("Memory error", conn);

    for(i = 0; i<size_db; ++i){
        char* name = (char*)malloc(size_data);
        memset(name, 0, size_data);
        char* email = (char*)malloc(size_data);
        memset(email, 0, size_data);
        
        Address addr = {.id=i, .set=0, .name = name, .email = email};
        
        conn->db->rows[i] = addr;
        
    }
}

void Database_set(Connection* conn, int id,  char* name,  char* email)
{
    Address* addr = &conn->db->rows[id];
    if(addr->set)
        die("Already set, delete it first", conn);

    addr->set = 1;

    if(strlen(name) >= conn->db->size_data-1)
        name[conn->db->size_data-1] = '\0';
    if(strlen(email) >= conn->db->size_data-1)
        email[conn->db->size_data-1] = '\0';
    char* res = strncpy(addr->name, name, conn->db->size_data);
    if(!res)
        die("Name copy failed.", conn);
    // res[conn->db->size_data-1] = '\0';

    res = strncpy(addr->email, email, conn->db->size_data);
    if(!res)
        die("Email copy failed.", conn);
    // res[conn->db->size_data-1] = '\0';    
}

void Database_get(Connection* conn, int id)
{
    Address* addr = &conn->db->rows[id];

    if(addr->set){
        Address_print(addr);
    }else{
        die("ID is not set", conn);
    }
}

void Database_delete(Connection* conn, int id)
{
    Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(Connection* conn)
{
    int i;
    Database* db = conn->db;

    for(i = 0; i<db->size_db; ++i){
        Address* cur = &db->rows[i];
        if(cur->set){
            Address_print(cur);
        }
    }
}

int main(int argc, char* argv[])
{
    Connection* conn = NULL;
    if(argc < 5)
        die("USAGE: ex17 <dbfile> <action> <size_db> <size_data> [action params]", conn);

    char* filename = argv[1];
    char action = argv[2][0];
    size_t size_db = atoi(argv[3]);
    size_t size_data = atoi(argv[4]);
    printf("filename: %s\naction: %c\nsize_db: %d\nsize_data: %d\n",
        filename, action, size_db, size_data);
    conn = Database_open(filename, action, size_db);
    int id = 0;

    if(argc > 3 && strchr("dgs", argv[2][0]) != NULL)
        id = atoi(argv[5]);

    switch(action){
        case 'c':
            Database_create(conn, size_db, size_data);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 6)
                die("Need an id to get", conn);

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 8)
                die("Need id, name, email to set", conn);
            fprintf(stderr, "In case 's'.\nID: %d\nname: %s, email: %s\n",
                id, argv[6], argv[7]);
            Database_set(conn, id, argv[6], argv[7]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 6)
                die("Need id to delete", conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid action; c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);

    return 0;
}
