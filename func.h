#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int dec_to_hex(int dec)
{
    char hex_char[1000];
    int hex = 0x0;
    sprintf(hex_char, "%X", dec);
    sscanf(hex_char, "%X", &hex);
    return hex;
}

int char_to_ascii(char character)
{
    int ascii = (int)character;
    return ascii;
}

int charhex_to_dec(char hex[])
{
    int i = 0;
    int val = 0;
    int decimal = 0;
    int len = strlen(hex);
    len--;
    for (i = 0; hex[i] != '\0'; i++)
    {
        if (hex[i] >= '0' && hex[i] <= '9')
        {
            val = hex[i] - 48;
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f')
        {
            val = hex[i] - 97 + 10;
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            val = hex[i] - 65 + 10;
        }

        decimal += val * power(16, len);
        len--;
    }
    return decimal;
}

int dec_to_binaryint(int k)
{
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * dec_to_binaryint(k / 2)));
}

int binary_to_dec(int n)
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

int chardec_to_intdec(char c)
{
    int num = 0;
    num = c - '0';
    return num;
}

int getEtiqueta(int binary_int)
{
    char binary[16];
    int etiqueta_bin[5];
    int etiqueta_binint;
    int i = 0;
    sprintf(binary, "%016d", binary_int);
    for (i = 0; i < 5; ++i)
    {
        etiqueta_bin[i] = chardec_to_intdec(binary[i + 6]);
    }
    etiqueta_binint = etiqueta_bin[0] * 10000 + etiqueta_bin[1] * 1000 + etiqueta_bin[2] * 100 + etiqueta_bin[3] * 10 + etiqueta_bin[4];
    return binary_to_dec(etiqueta_binint);
}

int getLinea(int binary_int)
{
    char binary[16];
    int linea_bin[2];
    int linea_binint;
    int i = 0;
    sprintf(binary, "%016d", binary_int);
    for (i = 0; i < 2; ++i)
    {
        linea_bin[i] = chardec_to_intdec(binary[i + 11]);
    }
    linea_binint = linea_bin[0] * 10 + linea_bin[1];
    return binary_to_dec(linea_binint);
}

int getPalabra(int binary_int)
{
    char binary[16];
    int palabra_bin[3];
    int palabra_binint;
    int i = 0;
    sprintf(binary, "%016d", binary_int);
    for (i = 0; i < 3; ++i)
    {
        palabra_bin[i] = chardec_to_intdec(binary[i + 13]);
    }
    palabra_binint = palabra_bin[0] * 10 + palabra_bin[1];
    return binary_to_dec(palabra_binint);
}

typedef struct
{
    short int ETQ;
    short int Datos[8];
} T_LINEA_CACHE;