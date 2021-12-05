#ifndef BANK_USERS_H
#define BANK_USERS_H

#include <string.h>
#include <limits.h>

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
    -1 id conversion error

 */
int authentication(char login[], char password[]) {
    char line[255];
    char user_id[255]; //  for storing each user id value. it's returned if username and password are correct
    int result;
    FILE *pFile = fopen("data/db.txt", "r");
    fscanf(pFile, "%s", user_id); // 1st line is id
    result = fscanf(pFile, "%s", line); // 2nd line is username
    while (result != EOF) {
        if (strcmp(line, login) == 0) {
            fscanf(pFile, "%s", line); // gets next line (password)
            fclose(pFile);
            if (strcmp(line, password) == 0){
                // convert user_id to int and return it
                int id = strtol(user_id, NULL, 0); // convert to int
                if (id != LONG_MIN && id != LONG_MAX)
                    return id;
                else
                    return -1;
            }
            return 0;
        }
        fscanf(pFile, "%s",
               line); // this line is password, it gets skipped because we don't need it if login is incorrect


        // id of NEXT user, result: username of NEXT user
        fscanf(pFile, "%s",
                    user_id);
        result = fscanf(pFile, "%s", line);
    }
    fclose(pFile);

    return 0;
}

/*
 * Check if user with provided login exists
 *
 * Return value:
 *      0 if user exists
 *      last user id if user doesn't exist
 *
 * */
int check_user(FILE *pFile, char login[]) {
    char line[255];
    char user_id[255]; //  for storing each user id value. final value is id of last user
    fscanf(pFile, "%s", line);
    int result = fscanf(pFile, "%s", line);
    while (result != EOF) {
        if (strcmp(line, login) == 0) {
            fclose(pFile);
            return 0;
        }
        fscanf(pFile, "%s", line); // password
        fscanf(pFile, "%s", user_id); // id

        result = fscanf(pFile, "%s", line); // NEXT user password

    }
    fclose(pFile);
    int last_id = strtol(user_id, NULL, 0); // convert to int
    if (last_id != LONG_MIN && last_id != LONG_MAX)
        return last_id;

    return -1;
}

/*
 * Creates user if user with provided login doesn't exist
 *
 * Return value:
 *      user_id if user is created
 *      0 if user is not created
 *
 * */

int create_user(char login[], char password[]) {
    FILE *pFile = fopen("data/db.txt", "a+");
    int last_user_id = check_user(pFile, login); // see check_user return values
    if (last_user_id >= 1) {
        fprintf(pFile, "%d\n%s\n%s\n\n", (last_user_id + 1), login, password);
    } else {
        return 0;
    }
    fclose(pFile);
    return (last_user_id + 1);
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
