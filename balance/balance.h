#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifndef BANK_MANAGEMENT_SYSTEM_BALANCE_H
#define BANK_MANAGEMENT_SYSTEM_BALANCE_H

/*
 * Get balance for user with provided ID
 *
 * Return values:
 *  user balance on success
 *  -1 on error
 * */

double get_balance(const int id){
    char line[255];
    int file_user_id;
    FILE * pFile = fopen("data/balance.txt", "r");
    int result = fscanf(pFile, "%s", line);
    while(result != EOF){
        file_user_id = strtol(line, NULL, 0);
        if(file_user_id == id){
            fscanf(pFile, "%s", line); // get next line: balance
            fclose(pFile);
            int balance = strtol(line, NULL, 0);
            // check for conversion errors
            if (balance != LONG_MIN && balance != LONG_MAX)
                return balance;
            return -1;

        }
        fscanf(pFile, "%s", line); // skip next line: balance
        result = fscanf(pFile, "%s", line);
    }
    fclose(pFile);
    return 1;
}
#endif //BANK_MANAGEMENT_SYSTEM_BALANCE_H
