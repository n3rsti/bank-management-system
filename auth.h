#ifndef BANK_AUTH_H
#define BANK_AUTH_H
#include <string.h>

/*
 Authenticate user using db.txt file and provided arguments

 Arguments: char login[], char password[]
 Return value:
    1 if provided data is matching db.txt data
    0 if provided data is not matching db.txt data

 */

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
