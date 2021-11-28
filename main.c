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

    puts("Enter login");
    scanf("%s", login);
    puts("Enter password");
    scanf("%s", password);

    if (dialog_value == 1) {
        if (authentication(login, password))
            puts("\nAuthentication successful");
        else
            puts("\nAuthentication failed");
    } else {
        if (create_user(login, password)) {
            puts("\nAccount successfully created");
        } else {
            puts("\nUsername is already taken");
        }
    }

    return 0;

}
