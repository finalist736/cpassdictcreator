#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "passdict.h"

errno_t PassDictGenerate(const PassDictionaryConfig *c)
{
    int i, n, m, q;
    char *buffer = (char*)malloc(c->maxLength + 1);

    FILE *f = fopen("dictionary.txt", "w");
    if (f == NULL)
    {
        return -1;
    }

    for (i=c->minLength; i<=c->maxLength; i++)
    {
        memset(buffer, '0', i);
        buffer[i] = '\0';
        n = i - 1;
        m = 0;
        for (;;)
        {
            while (buffer[n] < '9')
            {
                fprintf(f, "%s\n", buffer);
                buffer[n]++;
            }
            for(;;)
            {
                n--;
                if (n == -1)
                {
                    m = 1;
                    break;
                }
                if (buffer[n] < '9')
                {
                    fprintf(f, "%s\n", buffer);
                    buffer[n]++;
                    for (q = n+1; q< i; q++)
                    {
                        buffer[q] = '0';
                    }
                    n = i - 1;
                    break;
                }

            }
            if (m == 1)
            {
                fprintf(f, "%s\n", buffer);
                break;
            }
        }
    }
    fclose(f);
    free(buffer);
    return 0;
}

