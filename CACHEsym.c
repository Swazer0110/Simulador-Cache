#include "func.h"

int main(void)
{

    char RAM[1024];
    int hexRAM[1024];
    int hexRAMbloques[128][8];
    int accesos_memoria_dec[12];
    int accesos_memoria_bin[12];
    char acceso_memoria[59];
    char aux[5];
    int etiqueta[12], linea[12], palabra[12], bloque[12];
    int i = 0, j = 0, k = 0;
    int ascii;
    char texto[100];
    int vacio;
    T_LINEA_CACHE lineas_cache[4];
    int tiempo_global = 0, num_fallos = 0, num_aciertos = 0;

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
        accesos_memoria_bin[k] = dec_to_binaryint(accesos_memoria_dec[k]);
        etiqueta[k] = getEtiqueta(accesos_memoria_bin[k]);
        linea[k] = getLinea(accesos_memoria_bin[k]);
        palabra[k] = getPalabra(accesos_memoria_bin[k]);
        bloque[k] = etiqueta[k] * 4 + linea[k];
        k++;
    }

    for (i = 0; i < 12; ++i)
    {
        if (etiqueta[i] == lineas_cache[linea[i]].ETQ && checkEmptyLine(lineas_cache[linea[i]]) == 0)
        {
            num_aciertos++;
            int dato = hexRAMbloques[bloque[i]][palabra[i]];
            printf("T: %d, Acierto de CACHE, ADDR %04X ETQ %X linea %02X palabra %02X DATO %02X\n", tiempo_global, accesos_memoria_dec[i],
                   etiqueta[i], linea[i] + 1, palabra[i], dato);
            for (j = 3; j >= 0; --j)
            {
                printf("ETQ: %X\tDatos: %X %X %X %X %X %X %X %X\n", lineas_cache[j].ETQ, lineas_cache[j].Datos[7],
                       lineas_cache[j].Datos[6], lineas_cache[j].Datos[5], lineas_cache[j].Datos[4], lineas_cache[j].Datos[3],
                       lineas_cache[j].Datos[2], lineas_cache[j].Datos[1], lineas_cache[j].Datos[0]);
            }
            texto[i] = (char)dato;
            //sleep(2);
        }
        else
        {
            num_fallos++;
            printf("T:  %d,  Fallo  de  CACHE  %d,  ADDR  %04X  ETQ  %X  linea  %02X palabra %02X bloque %02X\n",
                   tiempo_global, num_fallos, accesos_memoria_dec[i], etiqueta[i], linea[i] + 1, palabra[i], bloque[i]);
            tiempo_global += 9;
            printf("Cargando el bloque %02X en la linea %02X\n", "bloque", linea[i] + 1);
            lineas_cache[linea[i]].ETQ = etiqueta[i];
            for (j = 0; j < 8; ++j)
            {
                lineas_cache[linea[i]].Datos[j] = hexRAMbloques[bloque[i]][j];
            }

            i--;
        }
        tiempo_global++;
    }

    printf("Numero de accesos: %d\tNumero de Fallos: %d\tTiempo medio de acceso: %f\n", num_aciertos + num_fallos, num_fallos, tiempo_global /(float)(num_aciertos + num_fallos));
    printf("Texto: %s", texto);
}