#include <stdio.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "printf_impl.h"

#define ASCII (256)

typedef void (*func_ptr_print)(char *temp, char *buff, int *i, va_list ap);
static void printInt(char *temp, char *buff, int *i, va_list ap);
static void printStr(char *temp, char *buff, int *i, va_list ap);
static void printChar(char *temp, char *buff, int *i, va_list ap);
static void copyBuff(char *buff, char *temp, int *i);
static void initLut();
static func_ptr_print lut[ASCII] = {0};

typedef void (*handle_characters)(char *temp, char **str, char *buff, int *i, va_list ap);
static void handleSpecialCharacter(char *temp, char **str, char *buff, int *i, va_list ap);
static void handleRecularCharacter(char *temp, char **str, char *buff, int *i, va_list ap);
static handle_characters lut_options[2] = {&handleRecularCharacter, &handleSpecialCharacter};

int print(char *str, ...)
{
    int i = 0;
    va_list ap;
    char buff[100] = {0}, temp[100] = {0};
    va_start(ap, str);

    initLut();

    for (; *str != '\0'; ++str)
    {
        lut_options[*str == '%'](temp, (char **)&str, buff, &i, ap);
    }

    buff[i] = '\n';

    fwrite(buff, strlen(buff), 1, stdout);

    va_end(ap);

    return strlen(buff);
}

static void initLut()
{
    int i = 0;
    for (; i < ASCII; ++i)
    {
        lut[i] = '\0';
    }

    lut['d'] = &printInt;
    lut['s'] = &printStr;
    lut['c'] = &printChar;
}

static void handleSpecialCharacter(char *temp, char **str, char *buff, int *i, va_list ap)
{
    ++*str;
    lut[(int)**str](temp, buff, i, ap);
}

static void handleRecularCharacter(char *temp, char **str, char *buff, int *i, va_list ap)
{
    (void)temp;
    (void)ap;

    *(buff + (*i)++) = **str;
}

static void printInt(char *temp, char *buff, int *i, va_list ap)
{
    sprintf(temp, "%d", va_arg(ap, int));
    copyBuff(buff, temp, i);
}

static void printChar(char *temp, char *buff, int *i, va_list ap)
{
    int res = va_arg(ap, int);
    (void)temp;
    buff[(*i)++] = (char)res;
}

static void printStr(char *temp, char *buff, int *i, va_list ap)
{
    sprintf(temp, "%s", va_arg(ap, char *));
    copyBuff(buff, temp, i);
}

static void copyBuff(char *buff, char *temp, int *i)
{
    strcpy(&buff[*i], temp);
    *i += strlen(temp);
}
