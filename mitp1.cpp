#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct Inscripcion
{
    int legajo;
    int codigoMateria;
    char dia;
    char mes;
    int anio;
    char nombreApellido[26];
};

FILE *abrir(const char *path, const char *mode)
{
    FILE *file = fopen(path, mode);

    if (file == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo");
        exit(EXIT_FAILURE);
    }

    return file;
}

void escribir(Inscripcion registro, FILE *file)
{
    fwrite(&registro, sizeof(Inscripcion), 1, file);
    return;
}

void leer(const char *msg, int *val)
{
    printf(msg);
    scanf("%d", val);
    fflush(stdin);
}

void leer(const char *msg, char *val)
{
    printf(msg);
    scanf("%d", val);
    fflush(stdin);
}

// funcion para leer cadena con espacios (nombreApellido)
void leerCadena(const char *msg, char val[])
{
    printf(msg);
    gets(val);
    fflush(stdin);
}

int main()
{
    system("cls");

    Inscripcion inscripcion;
    FILE *finales = abrir("DIAFINALES.dat", "wb");

    leerCadena("Ingrese un apellido y nombre:", inscripcion.nombreApellido);
    while (strcmp(inscripcion.nombreApellido, " ") != 0)
    {
        leer("Nro legajo:", &inscripcion.legajo);
        leer("Codigo de Materia:", &inscripcion.codigoMateria);
        leer("Dia:", &inscripcion.dia);
        leer("Mes:", &inscripcion.mes);
        leer("Anio:", &inscripcion.anio);

        escribir(inscripcion, finales);
        leerCadena("Ingrese un apellido y nombre:", inscripcion.nombreApellido);
    }

    fclose(finales);
    finales = abrir("DIAFINALES.dat", "rb");
    fread(&inscripcion, sizeof(inscripcion), 1, finales);
    while (!feof(finales))
    {
        printf("Legajo: %d", inscripcion.legajo);
        fread(&inscripcion, sizeof(Inscripcion), 1, finales);
    }

    fclose(finales);
    system("pause");
    return 0;
}