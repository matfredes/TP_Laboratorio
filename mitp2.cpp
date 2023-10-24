#include <iostream>
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/**
 * Dado el archivo binario generado en el ejercicio 7, que contiene todas las inscripciones del día, y
otro con el mismo diseño que contiene las inscripciones anteriores (FINALES.DAT), desarrolle un programa
que agregue al archivo de inscripciones anteriores el contenido del archivo del día. Al final del
proceso emita un listado del archivo de los registros agregados al archivo.

Abrir archivo Finales.DAT en modo append o lectura/escritura
Posicionarnos al final del archivo
Abrir archivo del dia DIAFINALES.DAT en modo lectura

Recorrer secuencialmente DIAFINALES.DAT
 - Escribir cada registro en FINALES.DAT

Cerrar archivos


*/

struct Inscripcion
{
    int legajo;
    int codMateria;
    int dia;
    int mes;
    int anio;
    char nombre[26];
};

void leer(Inscripcion *ptrRegistro, FILE *file)
{
    fread(ptrRegistro, sizeof(Inscripcion), 1, file);
    return;
}

void escribir(Inscripcion *ptrRegistro, FILE *file)
{
    fwrite(ptrRegistro, sizeof(Inscripcion), 1, file);
    return;
}

int main()
{
    // Abrir archivos para leer y actualizar
    FILE *finales = fopen("FINALES.dat", "rb+");
    if (finales == NULL)
    {
        exit(EXIT_FAILURE);
    }

    FILE *diaFinales = fopen("DIAFINALES.dat", "rb");
    if (diaFinales == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // Ubicarse al final del archivo de inscripciones anteriores (MATFINALES.dat) y guardar posición
    fseek(finales, 0, SEEK_END);
    int posEscritura = ftell(finales);

    Inscripcion registro;
    leer(&registro, diaFinales);

    // Recorrer secuencialmente el archivo de inscripciones del día
    while (!feof(diaFinales))
    {
        // Grabar registro en archivo de inscripciones anteriores
        escribir(&registro, finales);
        // Leer registro archivo de inscripciones del día
        leer(&registro, diaFinales);
    }

    // Ubicarse en el primer registro de los agregados
    fseek(finales, posEscritura, SEEK_SET);
    leer(&registro, finales);

    // Recorrer secuencialmente el archivo de inscripciones anteriores desde donde fue ubicado
    while (!feof(finales))
    {
        // Listar datos del registro
        printf("%d;%d;%2d/%2d/%4d;%s\n", registro.legajo, registro.codMateria, registro.dia, registro.mes, registro.anio, registro.nombre);
        // Leer registro archivo de inscripciones anteriores
        leer(&registro, finales);
    }

    // Cerrar archivos
    fclose(diaFinales);
    fclose(finales);

    system("pause");
    return 0;
}