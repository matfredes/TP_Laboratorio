#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define MAX_BUFFER 255

struct Novedades
{
    char nombre[26];
    int size;
    int fecha;
    char autor[26];
};

struct Maestro
{
    char nombre[26];
    char status;
    char contenido[MAX_BUFFER];
};

// Abrir archivos
FILE *abrir(const char *path, const char *mode)
{
    FILE *file = fopen(path, mode);
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    return file;
}

// Leer archivo novedades.csv (txt)
void leerTxt(Novedades *novedades, FILE *file) // leo txt
{
    char buffer[MAX_BUFFER];
    if (fgets(buffer, MAX_BUFFER, file) != NULL)
    {
        strcpy(novedades->nombre, strtok(buffer, ","));
        strtok(NULL, ",");
        novedades->fecha = atoi(strtok(NULL, ","));
        strcpy(novedades->autor, strtok(NULL, "\n"));
    }
    // Cargo en size el tamaño correspondiente al archivo para cargar la estructura a novedades.bin
    FILE *archivoTratado = abrir(novedades->nombre, "r");
    fseek(archivoTratado, 0, SEEK_END);
    int cant = ftell(archivoTratado);
    novedades->size = cant;
    fclose(archivoTratado);
    return;
}

// Escribir novedades.dat (bin)
void escribirNovBin(Novedades novedades, FILE *file)
{
    fwrite(&novedades, sizeof(Novedades), 1, file);
    return;
}

// Escribir maestro.csv (txt)
void escribirMaeTxt(Maestro maestro, FILE *file) // escribo txt
{
    fprintf(file, "%s,%c,%s", maestro.nombre, maestro.status, maestro.contenido);
    return;
}

// Escribir maestro.dat (bin)
void escribirMaeBin(Maestro maestro, FILE *file) // escribo binario
{
    fwrite(&maestro, sizeof(Maestro), 1, file);
    return;
}

// Cargar 2 primeras lineas de codigo a contenido
void contenido(char contenido[MAX_BUFFER], FILE *file)
{
    char buffer[MAX_BUFFER];
    int i = 0;
    while (i < 2)
        if (fgets(buffer, MAX_BUFFER, file) != NULL)
        {
            // Encuentra la posición del carácter '\n' en el buffer
            size_t posicion = strcspn(buffer, "\n");

            // Si se encuentra un '\n', elimínalo
            if (buffer[posicion] == '\n')
            {
                buffer[posicion] = '\0'; // Reemplaza '\n' con el carácter nulo
            }

            // Concatenar las líneas en la misma cadena con un espacio entre ellas
            if (i == 0)
            {
                strcpy(contenido, buffer);
                i++;
            }
            else
            {
                strcat(contenido, " ");
                strcat(contenido, buffer);
                strcat(contenido, "\n");
                i++;
            }
        }
}

int main()
{
    system("cls");

    FILE *archivoNovedadesTXT = abrir("novedades.csv", "r");
    FILE *archivoNovedadesDAT = abrir("novedades.dat", "wb");
    FILE *archivoMaestroTXT = abrir("maestro.csv", "w");
    FILE *archivoMaestroDAT = abrir("maestro.dat", "wb");

    Novedades novedades;
    Maestro maestro;
    leerTxt(&novedades, archivoNovedadesTXT);
    // Creo archivo novedades.dat, maestro.csv y maestro.dat
    while (!feof(archivoNovedadesTXT))
    {
        escribirNovBin(novedades, archivoNovedadesDAT); // Cargo novedades.dat
        strcpy(maestro.nombre, novedades.nombre);
        FILE *archivoTratado = abrir(maestro.nombre, "r"); // abro archivo cpp para tomar las 2 primeras lineas de codigo
        maestro.status = '?';

        // En caso de encontrar las primeras lineas blancas, recorrera hasta poder imprimir 2 lineas con contenido
        char linea[256];
        bool primeraLineaEnBlanco = false;
        bool segundaLineaEnBlanco = false;
        if (fgets(linea, sizeof(linea), archivoTratado) != NULL)
        {
            if (strlen(linea) <= 1)
            {
                primeraLineaEnBlanco = true;
            }
        }
        if (fgets(linea, sizeof(linea), archivoTratado) != NULL)
        {
            if (strlen(linea) <= 1)
            {
                segundaLineaEnBlanco = true;
            }
        }

        if (primeraLineaEnBlanco == true && segundaLineaEnBlanco == true)
        {
            strcpy(maestro.contenido, "NOLINE");
        }

        contenido(maestro.contenido, archivoTratado);
        escribirMaeTxt(maestro, archivoMaestroTXT); // cargo maestro.csv
        escribirMaeBin(maestro, archivoMaestroDAT); // cargo maestro.dat
        leerTxt(&novedades, archivoNovedadesTXT);
        fclose(archivoTratado);
    }

    fclose(archivoNovedadesTXT);
    fclose(archivoNovedadesDAT);
    fclose(archivoMaestroTXT);
    fclose(archivoMaestroDAT);
    system("pause");
    return 0;
}