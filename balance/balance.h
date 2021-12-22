#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#ifndef BANK_MANAGEMENT_SYSTEM_BALANCE_H
#define BANK_MANAGEMENT_SYSTEM_BALANCE_H

/*
 * Get balance for user with provided ID
 *
 * Return values:
 *  user balance on success
 *  -1 on error
 * */

double get_balance(const int id) {
    char line[255];
    unsigned int file_user_id;
    FILE *pFile = fopen("data/balance.txt", "r");
    int result = fscanf(pFile, "%s", line);
    while (result != EOF) {
        file_user_id = strtol(line, NULL, 0);
        if (file_user_id == id) {
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
    return -1;
}
/*
 * Updates balance of both: payer, payee with amount argument
 *
 * Return values:
 * 1: success
 * -1: error
 * */
int update_balance(int payer_id, int payee_id, double amount) {
    char line[255];
    double line_double; // contains converted line to double so function can make calculations
    unsigned int line_id; // contains id of current user in loop (updated in every iteration)

    FILE * pFile = fopen("data/balance.txt", "r+");
    // create balance_temp.txt file
    FILE * pFileTemp = fopen("data/balance_temp.txt", "w");

    // scan first line: id
    int result = fscanf(pFile, "%s", line);

    // convert id to long and check for conversion errors
    line_id = strtol(line, NULL, 0);
    if(line_id == LONG_MAX || line_id == LONG_MIN){
        fclose(pFile);
        fclose(pFileTemp);
        return -1;
    }
    while(result != EOF){
        fprintf(pFileTemp, "%d\n", line_id);

        if(line_id == payer_id || line_id == payee_id){
            // get next line: user balance
            fscanf(pFile, "%s", line);

            // convert balance line to double and check for conversion errors
            line_double = strtod(line, NULL);
            if(line_double == HUGE_VAL){
                fclose(pFile);
                fclose(pFileTemp);

                // remove temporary file because it wasn't completed due to conversion error
                remove("data/balance_temp.txt");
                return -1;
            }


            if(line_id == payer_id)
                fprintf(pFileTemp, "%f\n", (line_double - amount));
            else
                fprintf(pFileTemp, "%f\n", (line_double + amount));

        }
        else {
            fscanf(pFile, "%s", line);
            fprintf(pFileTemp, "%s\n", line);
        }
        result = fscanf(pFile, "%s", line);

        // convert id to long and check for conversion errors
        line_id = strtol(line, NULL, 0);
        if(line_id == LONG_MAX || line_id == LONG_MIN){
            fclose(pFile);
            fclose(pFileTemp);
            return -1;
        }


    }

    fclose(pFile);
    fclose(pFileTemp);

    // Replace original file with temporary one
    remove("data/balance.txt");
    rename("data/balance_temp.txt", "data/balance.txt");
    return 1;
}


/* Creates new transaction in transactions.txt
 *
 * Return values:
 * 1: success
 * -1: error
 *
 * */
int create_transaction(int payer_id, int payee_id, double amount) {
    FILE *pFile = fopen("data/transactions.txt", "a");
    int result =  fprintf(pFile, "%d\n%d\n%f\n\n", payer_id, payee_id, amount);
    fclose(pFile);
    if(result < 0)
        return -1;
    return 1;
}

#endif //BANK_MANAGEMENT_SYSTEM_BALANCE_H
