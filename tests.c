#include <stdio.h>
#include "users/users.h"

// data
char *authentication_true_cases[39][2] = {
        {"Liam",      "oD5Mm6r#vw"},
        {"Noah",      "kM1L5K6e7g"},
        {"Oliver",    "ToBEdd#ohX"},
        {"Elijah",    "J)YlEvNzVA"},
        {"William",   "3!aEuFEmSX"},
        {"James",     "LbmxIF9I&m"},
        {"Benjamin",  "9#5#%2(TF@"},
        {"Lucas",     "RwX0g&VvP*"},
        {"Henry",     "%odn0@@NCD"},
        {"Alexander", "IrI*ST@EM2"},
        {"Mason",     "9jNocX@$%&"},
        {"Michael",   "NFakNBq(Xx"},
        {"Ethan",     "f9KE1Z62BZ"},
        {"Daniel",    "YRVXt6utGf"},
        {"Jacob",     "pcuM6MaZUq"},
        {"Logan",     "HTN$Aeqc^9"},
        {"Jackson",   ")T*7MAevTo"},
        {"Levi",      "GkrqOjyyY!"},
        {"Sebastian", "9lGUrxEaNH"},
        {"Mateo",     "UmcdQX^rOa"},
        {"Jack",      "oLxwSjDdGi"},
        {"Owen",      "U8hqlrJPKl"},
        {"Theodore",  "S@mJXvBjsU"},
        {"Aiden",     "^XV@F!md&@"},
        {"Samuel",    "6mCys1M&zf"},
        {"Joseph",    "svGsV1VTK)"},
        {"John",      "&TABrS8%%i"},
        {"David",     "FLiz^N@At6"},
        {"Wyatt",     "^qQB&nVdvS"},
        {"Matthew",   "7GQiJ$vxCX"},
        {"Luke",      "9TqXncUyYH"},
        {"Asher",     "wm4Ug9Jsjl"},
        {"Carter",    "gH%!^*&d&#"},
        {"Julian",    "eW2m9dS8U1"},
        {"Grayson",   "SZIXH9iDVU"},
        {"Leo",       "OK2WhG3DEm"},
        {"Jayden",    "$f%Nre3Z@G"},
        {"Gabriel",   "uu#%gQkieN"},
        {"Isaac",     "R!1rE!Bs(@"},
};
char *authentication_false_cases[7][2] = {
        {"John",    "123"},
        {"Bob",     "1"},
        {"3",       "Liam"},
        {"sdsJohn", "123"},
        {"Basdob",  "1"},
        {"sd3",     "Lia2m"},
        {"",        "s"},
};


// Tests
int main() {
    for (int i = 0; i < 39; i++) {
        if (authentication(authentication_true_cases[i][0], authentication_true_cases[i][1]) == 0) {
            printf("Auth true case failed for: %s %s\n", authentication_true_cases[i][0],
                   authentication_true_cases[i][1]);
            break;
        }
    }
    for (int i = 0; i < 7; i++) {
        if (authentication(authentication_false_cases[i][0], authentication_false_cases[i][1]) >= 1) {
            printf("Auth false case failed for: %s %s\n", authentication_false_cases[i][0],
                   authentication_false_cases[i][1]);
            break;
        }
    }
    return 0;
}