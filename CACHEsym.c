#include "func.h"

int main(void)
{

    char RAM[1024];
    int hexRAM[1024];
    int hexRAMbloques[128][8];
    int accesos_memoria_dec[11];
    int accesos_memoria_hex[11];
    int accesos_memoria_bin[11];
    char acceso_memoria[59];
    char aux[5];
    int i = 0, j = 0, k = 0, etiqueta = 0, linea = 0, palabra = 0;
    int ascii;

    //leer ram
    FILE *fp = fopen("RAM.bin", "r");
    fscanf(fp, "%s", RAM);
    fclose(fp);

    // convertir a una array de int hexadecimales
    for (i = 0; i < 1024; ++i)
    {
        ascii = char_to_ascii(RAM[i]);
        hexRAM[i] = dec_to_hex(ascii);
    }

    // convertir a un array bidimensional por bloques
    for (i = 0; i < 1024; ++i)
    {
        if (j == 8)
        {
            k++;
            j = 0;
        }
        hexRAMbloques[k][j] = hexRAM[i];
        j++;
    }

    //leer accesos de memoria
    FILE *fd = fopen("accesos_memoria.txt", "r");
    fread(acceso_memoria, 60, 1, fd);
    acceso_memoria[59] = '\0';
    fclose(fd);

    // DESCOMENTAR PARA DEBUGGING
    //printf("VALORES ACCESOS MEMORIA:\n\n");

    //convertir a array de hexadecimales
    k = 0;
    for (i = 0; acceso_memoria[i] != '\0'; i++)
    {
        for (j = 0; j < 4; ++j)
        {
            aux[j] = acceso_memoria[i];
            ++i;
        }
        accesos_memoria_dec[k] = charhex_to_dec(aux);
        accesos_memoria_hex[k] = dec_to_hex(accesos_memoria_dec[k]);
        accesos_memoria_bin[k] = dec_to_binaryint(accesos_memoria_dec[k]);
        etiqueta = getEtiqueta(accesos_memoria_bin[k]);
        linea = getLinea(accesos_memoria_bin[k]);
        palabra = getPalabra(accesos_memoria_bin[k]);

        // DESCOMENTAR PARA DEBUGGING
        /*printf("Decimal: %d\tHexadecimal: %04X\tBinario: %016d\nEtiqueta: %02d\tLinea: %d\t\tPalabra: %d\n",
        accesos_memoria_dec[k], accesos_memoria_hex[k], accesos_memoria_bin[k], etiqueta, linea, palabra);
        printf("\n\n"); */

        k++;
    }

    // DESCOMENTAR PARA DEBUGGING
    /*printf("VALORES RAM EN HEXADECIMAL POR BLOQUES:\n\n");
    for (i = 0; i < 128; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            printf("%X\t", hexRAMbloques[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");*/
}