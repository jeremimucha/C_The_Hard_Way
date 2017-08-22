#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../debug.h"

#define SIZE 255
#define LOGFIND_FILE "logfind.txt"

void iter_logfiles(char* logfind_file, int nwords, char* words[],
                    bool(*fp)(char*fname, int nwords, char* words[]));
bool scanfile_and(char* fname, int nwords, char* words[]);
bool scanfile_or(char* fname, int nwords, char* words[]);
/*char* s_gets(char buf[], int lim);*/
char* s_fgets(char buf[], int lim, FILE* fp);


int main(int argc, char* argv[])
{
    int nwords = argc - 1;
    char** words = argv + 1;

    if(argc < 2){
        printf("Usage: %s  [word1, word2, ..., wordn]", __FILE__);
        return 1;
    }
    iter_logfiles(LOGFIND_FILE, nwords, words, scanfile_and);

    return 0;
}

char* s_fgets(char buf[], int lim, FILE* fp)
{
    char* ret_val;

    ret_val = fgets(buf, lim, fp);
    if(ret_val){
        while(*buf != '\n' && *buf != '\0')
            ++buf;
        if(*buf == '\n')
            *buf = '\0';
    }
    return ret_val;
}

#define FNAMESIZE 255
void iter_logfiles(char* logfind_file, int nwords, char* words[], bool(*cmp_f)(char*, int, char**))
{
    FILE* fp;
    char fname[FNAMESIZE];
    if((fp = fopen(logfind_file, "r")) != NULL)
        while(s_fgets(fname, FNAMESIZE, fp)){
            if((*cmp_f)(fname, nwords, words)){
                printf("%s\n", fname);
            }
        }
}


bool scanfile_and(char* fname, int nwords, char* words[])
{
    FILE* fp;
    bool res[nwords];
    memset(res, false, nwords);
    char buf[SIZE];
    int i = 0;
    if((fp = fopen(fname, "r")) == NULL){
        fprintf(stderr, "Failed to open the file -> %s", fname);
        return false;
    }

    for(i = 0; i < nwords; ++i){
        while(s_fgets(buf, SIZE, fp))
            if(strstr(buf, words[i])){
                res[i] = true;
                break;
            }
        rewind(fp);
    }

    for(i = 0; i<nwords; ++i){
        if(res[i] == false)
            return false;
    }
    return true;
}

bool scanfile_or(char* fname, int nwords, char* words[])
{
    FILE* fp;
    bool res[nwords];
    memset(res, false, nwords);
    char buf[SIZE];
    int i = 0;
    if((fp = fopen(fname, "r")) == NULL){
        fprintf(stderr, "Failed to open the file -> %s", fname);
        return false;
    }

    for(i = 0; i < nwords; ++i){
        while(s_fgets(buf, SIZE, fp))
            if(strstr(buf, words[i])){
                res[i] = true;
                break;
            }
        rewind(fp);
    }

    for(i = 0; i<nwords; ++i){
        if(res[i] == true)
            return true;
    }
    return false;
}
