#ifndef BANK_USERS_H
#define BANK_USERS_H

#include <string.h>

const char password_symbols[31] = {'~', '`', '!', ' ', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=',
                                   '{',
                                   '[', '}', ']', '|', '\\', ':', ';', '<', ',', '>', '.', '?', '/'};

const char uppercase_letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                    'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

/*
 Authenticate user using db.txt file and provided arguments

 Arguments: char login[], char password[]
 Return value:
    user_id if provided data is matching db.txt data
    0 if provided data is not matching db.txt data

 */
int authentication(char login[], char password[]) {
    char line[255];
    int result, id;
    FILE *pFile = fopen("db.txt", "r");
    id = fscanf(pFile, "%s", line); // 1st line is id
    result = fscanf(pFile, "%s", line); // 2nd line is username
    while (result != EOF) {
        if (strcmp(line, login) == 0) {
            fscanf(pFile, "%s", line); // gets next line (password)
            fclose(pFile);
            if (strcmp(line, password) == 0)
                return id;
            return 0;
        }
        fscanf(pFile, "%s",
               line); // this line is password, it gets skipped because we don't need it if login is incorrect
        
        
        // id: id of NEXT user, result: username of NEXT user
        id = fscanf(pFile, "%s",
                    line);
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
int check_user(FILE *pFile, char login[]) {
    char line[255];
    int result = fscanf(pFile, "%s", line);
    while (result != EOF) {
        if (strcmp(line, login) == 0)
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

int create_user(char login[], char password[]) {
    FILE *pFile = fopen("db.txt", "a+");
    if (check_user(pFile, login) == 0) {
        fprintf(pFile, "%s\n%s\n\n", login, password);
    } else {
        return 0;
    }
    fclose(pFile);
    return 1;
}

/* Validate password from input
 * Password rules:
 *  - at least 10 characters
 *  - at least 1 special symbol from password_symbols
 *  - at least 1 uppercase letter
 *
 *  Return value:
 *  1: password meets requirements
 *  -1: password is too short
 *  -2: password doesn't have any uppercase letter
 *  -3: password doesn't have any special symbol
 *
 * */
int validate_password(char password[]) {
    int containsUppercaseLetter = 0;
    if (strlen(password) < 10)
        return -1;
    for (int i = 0; i < 26; i++) {
        if (strchr(password, uppercase_letters[i]) != NULL) {
            containsUppercaseLetter = 1;
            break;
        }
    }
    if (!containsUppercaseLetter) {
        return -2;
    }
    for (int i = 0; i < 31; i++) {
        if (strchr(password, password_symbols[i]) != NULL)
            return 1;
    }
    return -3;
}

#endif
