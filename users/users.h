#ifndef BANK_USERS_H
#define BANK_USERS_H

#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "../crypto/sha-256.c"
#include "../balance/balance.h"

const char password_symbols[31] = {'~', '`', '!', ' ', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=',
                                   '{',
                                   '[', '}', ']', '|', '\\', ':', ';', '<', ',', '>', '.', '?', '/'};

const char uppercase_letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                    'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";

/*
 * Generate random string
 * */
char * generate_salt(size_t length) { // const size_t length, supra
    int seed;
    time_t tt;
    seed = time(&tt);
    srand(seed);
    char *randomString = NULL;

    if (length) {
        randomString = malloc(length +1); // sizeof(char) == 1, cf. C99

        if (randomString) {
            int l = (int) (sizeof(charset) -1);
            int key;  // one-time instantiation (static/global would be even better)
            for (int n = 0;n < length;n++) {
                key = rand() % l;   // no instantiation, just assignment, no overhead from sizeof
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}
/*
 * Converts uint8_t hash to string
 * */
static void hash_to_string(char string[65], const uint8_t hash[32])
{
    size_t i;
    for (i = 0; i < 32; i++) {
        string += sprintf(string, "%02x", hash[i]);
    }
}

/*
 * Returns char pointer with password + salt hash
 *
 * */
char * generate_password_hash(char password[], char salt[]){
    struct Sha_256 sha_256;
    char * hash_string = malloc(sizeof(char) * 64);
    uint8_t hash[32];
    sha_256_init(&sha_256, hash);
    sha_256_write(&sha_256, password, strlen(password));
    sha_256_write(&sha_256, salt, 16);
    sha_256_close(&sha_256);
    hash_to_string(hash_string, hash);
    return hash_string;
}
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
            char salt[17]; // 16 (salt size) + 1 (\0)
            fscanf(pFile, "%s", line); // gets next line (hash password)
            fscanf(pFile, "%s", salt); // gets next line (salt)
            fclose(pFile);
            if (strcmp(generate_password_hash(password, salt), line) == 0){
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
        fscanf(pFile, "%s",
               line);

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
int check_user_by_login(FILE *pFile, char login[]) {
    char line[255];
    char user_id[255]; //  for storing each user id value. final value is id of last user
    fscanf(pFile, "%s", line);
    int result = fscanf(pFile, "%s", line);
    while (result != EOF) {
        if (strcmp(line, login) == 0) {
            return 0;
        }
        fscanf(pFile, "%s", line); // hash
        fscanf(pFile, "%s", line); // salt
        fscanf(pFile, "%s", user_id); // id

        result = fscanf(pFile, "%s", line); // NEXT user password

    }
    int last_id = strtol(user_id, NULL, 0); // convert to int
    if (last_id != LONG_MIN && last_id != LONG_MAX)
        return last_id;

    return -1;
}

int get_user_id(char username[]){
    char line[255];
    char string_user_id[255];
    FILE * pFile = fopen("data/db.txt", "r");
    fscanf(pFile, "%s", string_user_id);
    int result = fscanf(pFile, "%s", line);
    while(result != EOF){
        if(strcmp(line, username) == 0){
            int user_id = strtol(string_user_id, NULL, 0);
            if(user_id != LONG_MAX && user_id != LONG_MIN)
                return user_id;
            return -1;
        }


        // skip 2 lines which are not username nor id
        fscanf(pFile, "%s", line);
        fscanf(pFile, "%s", line);

        fscanf(pFile, "%s", string_user_id);

        result = fscanf(pFile, "%s", line);
    }

    return 0;

}
/*
 * Creates user if user with provided login doesn't exist
 *
 * Return value:
 *      user_id if user is created
 *      0 if user is not created
 *
 * */

unsigned int create_user(char login[], char password[]) {
    FILE *pFile = fopen("data/db.txt", "a+");
    unsigned int last_user_id = check_user_by_login(pFile, login); // see check_user return values
    if (last_user_id >= 1) {
        FILE *pBalance = fopen("data/balance.txt", "a");
        char * salt = generate_salt(16);
        char * hash = generate_password_hash(password, salt);
        fprintf(pFile, "%d\n%s\n%s\n%s\n\n", (last_user_id + 1), login, hash, salt);
        fprintf(pBalance, "%d\n%d\n\n", (last_user_id + 1), 0);
        fclose(pBalance);
    } else {
        fclose(pFile);
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

unsigned int account_creation_dialog(char * login, char * password){
    puts("\nEnter login: ");
    scanf("%s", login);
    while(strlen(login) < 6){
        puts("\nLogin must be at least 6 letters long\nEnter login: ");
        scanf("%s", login);
    }
    puts("\nEnter password: ");
    scanf("%s", password);

    int password_validation = validate_password(password);
    while(password_validation != 1){
        switch(password_validation){
            case -1:
                puts("Password must be at least 10 characters long");
                break;
            case -2:
                puts("Password must have at least 1 uppercase letter");
                break;
            case -3:
                puts("Password must have at least 1 special symbol");
                break;
        }
        puts("\nEnter password: ");
        scanf("%s", password);
        password_validation = validate_password(password);
    }

    return create_user(login, password);
}

int logged_user_choice_dialog(){
    long dialog_value;
    char dialog_buf[128];
    puts("\nAvailable options\n"
         "1) Deposit\n"
         "2) Withdraw\n"
         "3) Send\n"
         "4) Log out\n"
         "\nSelect option: ");

    scanf("%c", (char *) stdin); // clear stdin from trailing '\n'

    fgets(dialog_buf, 128, stdin);
    dialog_value = strtol(dialog_buf, NULL, 0);
    if (dialog_value == LONG_MIN || dialog_value == LONG_MAX)
        return -1;

    if (dialog_value != 1 && dialog_value != 2 && dialog_value != 3)
        return 0;

    return dialog_value;
}
/*
 * Return code meanings:
 *  1: puts "Deposit successful"
 * -1: puts "There was an error"
 *
 * */
int deposit_dialog(int user_id){
    double amount;
    char dialog_buf[128];

    puts("Enter amount: ");

    fgets(dialog_buf, 128, stdin);
    amount = strtod(dialog_buf, NULL);
    if (amount == HUGE_VAL)
        return -1;

    if (amount <= 0){
        puts("Amount has to be larger than 0");
        return -1;
    }



    return update_balance(-1, user_id, amount);
}

/*
 * Return code meanings:
 *  1: puts "Withdrawal successful"
 *  0: puts "Not enough credits"
 * -1: puts "There was an error"
 *
 * */
int withdraw_dialog(int user_id){
    double amount;
    char dialog_buf[128];

    puts("Enter amount: ");

    fgets(dialog_buf, 128, stdin);
    amount = strtod(dialog_buf, NULL);
    if (amount == HUGE_VAL)
        return -1;

    if( amount <= 0) {
        puts("Amount has to be larger than 0");
        return -1;
    }

    if(get_balance(user_id) >= amount)
        return update_balance(-1, user_id, -amount);
    return 0;
}
/*
 * Return code meanings:
 * -1: puts "There was an error"
 * every other message is displayed in this function (not main.c)
 * */
int transaction_dialog(int user_id){
    char other_user_name[255];
    int other_user_id;

    // Get username from input
    puts("Enter user name: ");
    scanf("%s", other_user_name);

    // Get user id
    other_user_id = get_user_id(other_user_name);
    if(other_user_id == 0){
        printf("User %s doesn't exist\n", other_user_name);
        return -1;
    }
    else if(other_user_id == -1) {
        puts("There was an error");
        return -1;
    }

    // Get amount and finish transaction
    double amount;
    char dialog_buf[255];

    // Get amount from input and check for conversion errors
    puts("\nEnter amount: ");

    scanf("%c", (char *) stdin); // clear stdin from trailing '\n'
    fgets(dialog_buf, 128, stdin);
    amount = strtod(dialog_buf, NULL);
    if (amount == HUGE_VAL)
        return -1;

    if(amount <= 0){
        puts("Amount has to be larger than 0");
        return 0;
    }

    if(get_balance(user_id) <= amount){
        puts("Not enough credits");
        return 0;
    }

    if(create_transaction(user_id, other_user_id, amount) == 1){
        printf("Successfully sent %f to %s", amount, other_user_name);
        return 1;
    }
    return -1;

}
#endif
