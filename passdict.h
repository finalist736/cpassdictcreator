#ifndef PASSDICT_H
#define PASSDICT_H

#include <stdlib.h>

struct PDConfig {
    int isAlpha;
    int isDigit;

    int minLength;
    int maxLength;
};

typedef struct PDConfig PassDictionaryConfig;

errno_t PassDictGenerate(const PassDictionaryConfig* c);

#endif // PASSDICT_H
