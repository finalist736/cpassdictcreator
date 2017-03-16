#include <stdlib.h>
#include <string.h>
//#include <stdio.h>
#include "passdict.h"

static char startDigit = '0';
static char endDigit = '9';
static char startAlpha = 'a';
static char endAlpha = 'z';


char determineLastChar(const PassDictionaryConfig *c)
{
    if (c->isAlpha)
    {
        return endAlpha;
    }
    else
    {
        return endDigit;
    }
}

char getNextChar(const PassDictionaryConfig *c, char current)
{
    if (current < endDigit)
    {
        return current + 1;
    }
    else if (current == endDigit)
    {
        if (c->isAlpha)
        {
            return startAlpha;
        }
        else
        {
            return startDigit;
        }
    }
    else
    {
        if (current == endAlpha)
        {
            if (c->isDigit)
            {
                return startDigit;
            }
            else
            {
                return startAlpha;
            }
        }
        else
        {
            return current + 1;
        }
    }
}

errno_t PassDictGenerate(const PassDictionaryConfig *c)
{
    char startChar;
    int i, n, m, q;
    char *buffer = (char*)malloc(c->maxLength + 1);

    if (c->isDigit == 0 && c->isAlpha == 0)
    { // no chars to generate passwords
        return -1;
    }
    if (c->minLength <= 0 || c->maxLength < c->minLength)
    { // incorrect password length
        return -1;
    }


    //FILE *f = fopen("dictionary.txt", "w");
    //if (f == NULL)
    //{
    //    return -1;
    //}

    // determine first char
    if (c->isDigit)
    {
        startChar = startDigit;
    }
    else
    {
        startChar = startAlpha;
    }
    for (i=c->minLength; i<=c->maxLength; i++)
    {
        memset(buffer, startChar, i);
        buffer[i] = '\0';
        n = i - 1;
        m = 0;
        for (;;) // many many endless cycles
        {
            //fprintf(f, "%s\n", buffer);
            while (buffer[n] < determineLastChar(c))
            {
                //fprintf(f, "%s\n", buffer);
                buffer[n] = getNextChar(c, buffer[n]);
            }
            for(;;)
            {
                n--;
                if (n == -1)
                {
                    m = 1;
                    break;
                }
                if (buffer[n] < determineLastChar(c))
                {
                    //fprintf(f, "%s\n", buffer);
                    buffer[n] = getNextChar(c, buffer[n]);
                    for (q = n+1; q< i; q++)
                    {
                        buffer[q] = startChar;
                    }
                    n = i - 1;
                    break;
                }

            }
            if (m == 1)
            {
                //fprintf(f, "%s\n", buffer);
                break;
            }
        }
    }
    //fclose(f);
    free(buffer);
    return 0;
}

