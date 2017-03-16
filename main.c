#include <stdio.h>
#include "passdict.h"

int main(int argc, char *argv[])
{
    PassDictionaryConfig config;

    char l;
    printf("need alpha? ");
    //scanf("%c", &l);
    if (l == 'y')
    {
        config.isAlpha = 1;
    }
    else
    {
        config.isAlpha = 0;
    }
    //scanf("%c", &l);
    printf("need digit? ");
    //scanf("%c", &l);
    if (l == 'y')
    {
        config.isDigit = 1;
    }
    else
    {
        config.isDigit = 0;
    }
    config.isDigit = 1;
    config.isAlpha = 1;
    config.minLength = 3;
    config.maxLength = 6;
    printf("min length: ");
    //scanf("%d", &config.minLength);
    printf("max length: ");
    //scanf("%d", &config.maxLength);

    // check data is correct?

    errno_t err =  PassDictGenerate(&config);
    if (err != 0)
    {
        printf("error was occured!\n");
    }
    else
    {
        printf("done!\n");
    }


    return 0;
}
