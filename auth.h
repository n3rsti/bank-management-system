#ifndef BANK_AUTH_H
#define BANK_AUTH_H
#include <string.h>

int authentication(char login[], char password[]){
    char line[255];
    int result;
    FILE * pFile = fopen("db.txt", "r");
    result = fscanf(pFile, "%s", line);
    while(result != EOF){
        if(strcmp((const char *) line, login) == 0){
            fscanf(pFile, "%s", line);
            fclose(pFile);
            if(strcmp((char *) &line, password) == 0)
                return 1;
            return 0;
        }
        result = fscanf(pFile, "%s", line);
    }
    fclose(pFile);

    return 0;
}

#endif
