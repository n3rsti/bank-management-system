#include <stdio.h>
#include "auth.h"

int main()
{
    printf("%d\n", authentication("n3rsti", "123"));
    printf("%d\n", authentication("bob", "123"));
    printf("%d\n", authentication("maria", "dog123"));
    printf("%d\n", authentication("n3rsasati", "123"));

    return 0;

}
