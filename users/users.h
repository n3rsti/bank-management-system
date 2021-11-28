#ifndef BANK_USERS_H
#define BANK_USERS_H
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
        if(strcmp(line, login) == 0){
            fscanf(pFile, "%s", line); // gets next line (password)
            fclose(pFile);
            if(strcmp(line, password) == 0)
                return 1;
            return 0;
        }
        fscanf(pFile, "%s", line); // this line is password, it gets skipped because we don't need it if login is incorrect
        result = fscanf(pFile, "%s", line);
    }
    fclose(pFile);

    return 0;
}
/*
 * Check if user with provided login exists
 *
 * Return value:
 *      1 if user exists
 *      0 if user doesn't exist
 *
 * */
int check_user(FILE * pFile, char login[]){
    char line[255];
    int result = fscanf(pFile, "%s", line);
    while(result != EOF){
        if(strcmp(line, login) == 0)
            return 1;
        result = fscanf(pFile, "%s", line);
    }
    return 0;
}
/*
 * Creates user if user with provided login doesn't exist
 *
 * Return value:
 *      1 if user is created
 *      0 if user is not created
 *
 * */

int create_user(char login[], char password[]){
    FILE * pFile = fopen("db.txt", "a+");
    if(check_user(pFile, login) == 0){
        fprintf(pFile, "%s\n%s\n\n", login, password);
    }
    else {
        return 0;
    }
    fclose(pFile);
    return 1;
}


#endif
