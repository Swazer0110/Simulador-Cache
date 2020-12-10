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
    int etiqueta[11], linea[11], palabra[11];
    int i = 0, j = 0, k = 0;
    int ascii;
    char texto[100];
    T_LINEA_CACHE lineas_cache[4];

    int tiempo_global = 0, num_fallos = 0;
    for (i = 0; i < 4; ++i)
    {
        lineas_cache[i].ETQ = 0;
        for (j = 0; j < 8; ++j)
            lineas_cache[i].Datos[j] = 0xFF;
    }

    //leer ram
    if (access("RAM.bin", F_OK) == 0)
    {
        FILE *fp = fopen("RAM.bin", "r");
        fscanf(fp, "%s", RAM);
        fclose(fp);
    }
    else
    {
        printf("Falta archivo: RAM.bin");
        exit(-1);
    }

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
    if (access("accesos_memoria.txt", F_OK) == 0)
    {
        FILE *fd = fopen("accesos_memoria.txt", "r");
        fread(acceso_memoria, 60, 1, fd);
        acceso_memoria[59] = '\0';
        fclose(fd);
    }
    else
    {
        printf("Falta archivo: accesos_memoria.txt");
        exit(-1);
    }

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
        etiqueta[k] = getEtiqueta(accesos_memoria_bin[k]);
        linea[k] = getLinea(accesos_memoria_bin[k]);
        palabra[k] = getPalabra(accesos_memoria_bin[k]);
        k++;
    }

    // DESCOMENTAR PARA DEBUGGING
    /*
    printf("VALORES ACCESOS MEMORIA:\n\n");
    for (k = 0; k < 11; k++){
        printf("Decimal: %d\tHexadecimal: %04X\tBinario: %016d\nEtiqueta: %02d\tLinea: %d\t\tPalabra: %d\n",
        accesos_memoria_dec[k], accesos_memoria_hex[k], accesos_memoria_bin[k], etiqueta[k], linea[k], palabra[k]);
        printf("\n\n");
    }
    printf("VALORES RAM EN HEXADECIMAL POR BLOQUES:\n\n");
    for (i = 0; i < 128; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            printf("%X\t", hexRAMbloques[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    */

    for (i = 0; i < 11; ++i)
    {
        if (etiqueta[i] == lineas_cache[linea[i]].ETQ)
        {
            printf("T: %d, Acierto de CACHE, ADDR %04X ETQ %X linea %02X palabra %02X DATO %02X\n", tiempo_global, "ADDR",
                   etiqueta[i], linea[i], palabra[i], "DATO");
            for (j = 0; j < 4; ++j)
            {
                printf("ETQ: %X\tDatos: %X %X %X %X %X %X %X %X\n", lineas_cache[j].ETQ, lineas_cache[j].Datos[7],
                       lineas_cache[j].Datos[6], lineas_cache[j].Datos[5], lineas_cache[j].Datos[4], lineas_cache[j].Datos[3],
                       lineas_cache[j].Datos[2], lineas_cache[j].Datos[1], lineas_cache[j].Datos[0]);
            }
            //añadir dato a texto
            sleep(2);
        }
        else
        {
            num_fallos++;
            printf("T:  %d,  Fallo  de  CACHE  %d,  ADDR  %04X  ETQ  %X  linea  %02X palabra %02Xbloque %02X\n",
                   tiempo_global, num_fallos, "addr", etiqueta[i], linea[i], palabra[i], "bloque");
            tiempo_global += 9;
            printf("Cargando el bloque %02X en la linea %02X\n", "bloque", linea[i]);
            lineas_cache[linea[i]].ETQ = etiqueta[i];
            // meter datos de ram(no se como va) en lineas_cache[linea[i]].Datos[]
            i--; // esto es para q vuelva a hacerlo con el mismo i y de el acierto, asi te ahorras tener el acierto simulado dentro del fallo(creo)
        }
        tiempo_global++;
    }
}