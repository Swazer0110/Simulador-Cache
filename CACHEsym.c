#include "func.h"



typedef struct
{
    short int ETQ;
    short int Datos[8];
} T_LINEA_CACHE;

int main(void)
{
    int i, j, counter = 0;
    int k = 0, r = 0;
    unsigned char RAM[1023];
    char acceso_memoria[59];
    int tiempoglobal = 0;
    int numfallos = 0;
    char aux[4];
    int a[16];
    int memoria[12][16];
    unsigned char hexRAM[2047];
    int linea = 0, palabra = 0, etiqueta = 0;

    T_LINEA_CACHE lineas[4];
    for (i = 0; i < 4; ++i)
    {
        lineas[i].ETQ = 0xFF;

        for (j = 0; j < 4; ++j)
            lineas[i].Datos[j] = 0;
    }

    // lectura de archivos
    FILE *fp = fopen("RAM.bin", "r");
    fscanf(fp, "%s", RAM);
    //printf("%s",RAM);
    fclose(fp);

    FILE *fd = fopen("accesos_memoria.txt", "r");
    fread(acceso_memoria, 60, 1, fd);
    acceso_memoria[59] = '\0';
    fclose(fd);
    //printf("%s",acceso_memoria);

    // conversion de RAM a hexadecimal y division por bloques
    for (i = 0; i < 1024; ++i)
    {
        sprintf(hexRAM + (i * 2), "%02X", RAM[i]);
    }
    // printf("%s",hexRAM);

    unsigned char hex_bloques_RAM[200][17];

    for (i = 0, k = 0; i < 2047; i++)
    {

        for (j = 0; j < 16; j++)
        {
            hex_bloques_RAM[k][j] = hexRAM[i];
            i++;
        }
        i--;
        hex_bloques_RAM[k][16] = '\0';
        k++;
    }

    /*for(i=0;i<128;i++){
        printf("%c%c %c%c %c%c %c%c %c%c %c%c %c%c %c%c %c%c \n", hex_bloques_RAM[i][0], hex_bloques_RAM[i][1], hex_bloques_RAM[i][2], hex_bloques_RAM[i][3],
        hex_bloques_RAM[i][4], hex_bloques_RAM[i][5], hex_bloques_RAM[i][6], hex_bloques_RAM[i][7], hex_bloques_RAM[i][8], hex_bloques_RAM[i][9],
        hex_bloques_RAM[i][10], hex_bloques_RAM[i][11], hex_bloques_RAM[i][12], hex_bloques_RAM[i][13], hex_bloques_RAM[i][14], hex_bloques_RAM[i][15]);
    }*/

    // conversion accesos_memoria a binario

    for (j = 0; j < 59; ++j)
    {
        for (i = 0; i < 4; ++i)
        {
            aux[i] = acceso_memoria[j];
            ++j;
        }

        for (i = 0, k = 0; i < 4; ++i)
        {
            switch (aux[i])
            {
            case '0':
                a[k] = 0;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 0;
                break;
            case '1':
                a[k] = 0;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 1;
                break;
            case '2':
                a[k] = 0;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 0;
                break;
            case '3':
                a[k] = 0;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 1;
                break;
            case '4':
                a[k] = 0;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 0;
                break;
            case '5':
                a[k] = 0;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 1;
                break;
            case '6':
                a[k] = 0;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 0;
                break;
            case '7':
                a[k] = 0;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 1;
                break;
            case '8':
                a[k] = 1;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 0;
                break;
            case '9':
                a[k] = 1;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 1;
                break;
            case 'A':
                a[k] = 1;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 0;
                break;
            case 'B':
                a[k] = 1;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 1;
                break;
            case 'C':
                a[k] = 1;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 0;
                break;
            case 'D':
                a[k] = 1;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 0;
                ++k;
                a[k] = 1;
                break;
            case 'E':
                a[k] = 1;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 0;
                break;
            case 'F':
                a[k] = 1;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 1;
                ++k;
                a[k] = 1;
                break;
            default:
                printf("Invalid input.");
                break;
            }
            k++;
        }
        for (i = 0; i < 17; ++i)
        {
            memoria[r][i] = a[i];
        }
        r++;
        //printf("%s\n", a);
    }

    for (i = 0; i < 12; ++i)
    {
        printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", memoria[i][0], memoria[i][1], memoria[i][2], memoria[i][3], memoria[i][4], memoria[i][5],
               memoria[i][6], memoria[i][7], memoria[i][8], memoria[i][9], memoria[i][10], memoria[i][11], memoria[i][12], memoria[i][13], memoria[i][14], memoria[i][15]);
    }

    //bucle principal
    for (i = 0; i < 12; ++i)
    {
        //etiqueta
        etiqueta = convert(memoria[i][6] * 10000 + memoria[i][7] * 1000 + memoria[i][8] * 100 + memoria[i][9] * 10 + memoria[i][10]);
        //linea
        linea = convert(memoria[i][11] * 10 + memoria[i][12]);
        //palabra
        palabra = convert(memoria[i][13] * 100 + memoria[i][14] * 10 + memoria[i][15]);
        printf("%d %d %d", etiqueta, linea, palabra);
        getchar();
    }

    return 0;
}