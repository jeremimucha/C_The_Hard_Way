#ifndef _DB_H_
#define _DB_H_

#define DB_FILE "data/db"
#define DB_DIR "data"

int DB_init();
int DB_list();
int DB_update(const char* url);
int DB_find(const char* url);

#endif
