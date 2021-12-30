#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "users/users.h"
#include "balance/balance.h"

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
        int user_id = authentication(login, password);
        if (user_id >= 1) {
            printf("\nSuccessfully logged in"
                   "\nUsername: %s"
                   "\nBalance: %.2f\n", login, get_balance(user_id));
            switch(logged_user_choice_dialog()){
                case 1:
                    dialog_value = deposit_dialog(user_id);
                    if(dialog_value)
                        printf("Deposit successful\n");
                    else
                        puts("There was an error\n");
                    break;
                case 2:
                    dialog_value = withdraw_dialog(user_id);
                    if(dialog_value == 1)
                        printf("Withdrawal successful\n");
                    else if(dialog_value == 0)
                        puts("Not enough credits\n");
                    else
                        puts("There was an error");
                    break;
                case 3:
                    dialog_value = transaction_dialog(user_id);
                    if(dialog_value == -1)
                        puts("There was an error");
                    break;
                case 4:
                    puts("Logging out");
                    exit(0);
                case -1:
                    break;
            }
        }
        else
            puts("\nAuthentication failed");
    } else {
        unsigned user_id = account_creation_dialog(login, password);
        if (user_id >= 1 ) {
            puts("\nAccount successfully created");
            printf("\nSuccessfully logged in"
                   "\nUsername: %s"
                   "\nBalance: 0\n", login);
        } else {
            puts("\nUsername is already taken");
        }
    }

    return 0;

}
