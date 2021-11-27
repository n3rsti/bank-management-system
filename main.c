#include <stdio.h>
#include "auth.h"

int main()
{
    char login[255], password[255];

    puts("Enter login");
    scanf("%s", login);
    puts("Enter password");
    scanf("%s", password);

    if(authentication(login, password))
        puts("\nAuthentication successful");
    else
        puts("\nAuthentication failed");
    return 0;

}
