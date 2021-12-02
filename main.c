#include <stdio.h>
#include <stdlib.h>
#include "users/users.h"
#include <limits.h>

int main() {
    char dialog_buf[128];
    char login[255], password[255];

    puts("1) Login to account\n2) Create account");

    // Get value from stdin and check for errors
    fgets(dialog_buf, 128, stdin);
    long dialog_value = strtol(dialog_buf, NULL, 0);
    if (dialog_value == LONG_MIN || dialog_value == LONG_MAX) {
        exit(-1);
    }
    if (dialog_value != 1 && dialog_value != 2) {
        puts("\nQuitting...");
        exit(0);
    }


    if (dialog_value == 1) {
        puts("Enter login: ");
        scanf("%s", login);
        puts("Enter password: ");
        scanf("%s", password);
        if (authentication(login, password))
            puts("\nAuthentication successful");
        else
            puts("\nAuthentication failed");
    } else {
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

        if (create_user(login, password) ) {
            puts("\nAccount successfully created");
        } else {
            puts("\nUsername is already taken");
        }
    }

    return 0;

}
