#include <stdio.h>

int power(int base, int exp)
{
    if (exp < 0)
        return -1;

    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

int convert(int n)
{
    int dec = 0, i = 0, rem;
    while (n != 0)
    {
        rem = n % 10;
        n /= 10;
        dec += rem * power(2, i);
        ++i;
    }
    return dec;
}

int file_size(FILE *fp){
    char ch = ' ';
    int count = 0;
     while (1) {
        ch = fgetc(fp);
        if (ch == EOF)
            break;
        ++count;
    }
    return count;
}