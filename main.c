#include <stdio.h>
#include "auth.h"

/*
 Authenticate user using db.txt file and provided arguments

 Arguments: char login[], char password[]
 Return value:
    1 if provided data is matching db.txt data
    0 if provided data is not matching db.txt data

 */

int main()
{
    printf("%d\n", authentication("n3rsti", "123"));
    printf("%d\n", authentication("bob", "123"));
    printf("%d\n", authentication("maria", "dog123"));
    printf("%d\n", authentication("n3rsasati", "123"));

    return 0;

}
