#include <stdio.h>
#include "users/users.h"

char * authentication_true_cases[39][2] = {
        {"Liam", "%r7l@bM#Jf"}, {"Noah", "r!w(8Q1Su5"}, {"Oliver", "ZZph3JUu*)"},
        {"Elijah", "gDxhef9FGZ"}, {"William", "JYPC@oKnV!"}, {"James", "e3ARa6mhxJ"},
        {"Benjamin", "P!Zz6cToJ&"}, {"Lucas", "vNra#q$1SA"}, {"Henry", "eOPu0uBTVO"},
        {"Alexander", "%IKjdH)EwI"}, {"Mason", "geCHA6Wj)e"}, {"Michael", "vmDfxul(s#"},
        {"Ethan", "wUApfj$DYC"}, {"Daniel", "rLM(yhSMRU"}, {"Jacob", "W6KjnJWdtA"},
        {"Logan", "QndJ(Z9FRV"}, {"Jackson", "x!4jjZTL^S"}, {"Levi", "YmFcPDzmt0"},
        {"Sebastian", "ihZOC(UR@T"}, {"Mateo", "0lgn4feBqk"}, {"Jack", "ulfaoDum$E"},
        {"Owen", "**JA@Ml2P1"}, {"Theodore", "CKqnFVpD5#"}, {"Aiden", "irFd9D%Z0x"},
        {"Samuel", "wEIrNsU71("}, {"Joseph", "d3F@sF&^Y@"}, {"John", "FzESXEMNhq"},
        {"David", "wBSYo1Seww"}, {"Wyatt", "g6f6w4Mgmy"}, {"Matthew", "1G!fWt&*0o"},
        {"Luke", "PUfOmGgrBl"}, {"Asher", "!tDMgwmE1S"}, {"Carter", "Cqk^lP9aPr"},
        {"Julian", "CtOaU3WJYk"}, {"Grayson", "43DBb&lX0q"}, {"Leo", "v79265QC1n"},
        {"Jayden", "Oy3TmsP2mg"}, {"Gabriel", "PpT7c^9hx^"}, {"Isaac", "@k(PEK2%d*"}
};
char * authentication_false_cases[7][2] = {
        {"John", "123"},
        {"Bob", "1"},
        {"3", "Liam"},
        {"sdsJohn", "123"},
        {"Basdob", "1"},
        {"sd3", "Lia2m"},
        {"", "s"},
};

int main() {
    for (int i = 0; i < 39; i++) {
        if (authentication(authentication_true_cases[i][0], authentication_true_cases[i][1]) == 0) {
            printf("Auth true case failed for: %s %s\n", authentication_true_cases[i][0], authentication_true_cases[i][1]);
            break;
        }
    }
    for (int i = 0; i < 7; i++) {
        if (authentication(authentication_false_cases[i][0], authentication_false_cases[i][1]) >= 1) {
            printf("Auth false case failed for: %s %s\n", authentication_false_cases[i][0], authentication_false_cases[i][1]);
            break;
        }
    }
    return 0;
}