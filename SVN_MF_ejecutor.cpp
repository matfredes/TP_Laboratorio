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

struct Status
{
    char tipo;
    char archivo[26];
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

// Leer archivo novedades.dat (bin)
void leerNovBin(Novedades *novedades, FILE *file)
{
    fread(novedades, sizeof(Novedades), 1, file);
    return;
}

// Leer archivos meastro.dat (bin)
void leerMaeBin(Maestro *maestro, FILE *file)
{
    fread(maestro, sizeof(Maestro), 1, file);
    return;
}

// Escribir logger.log (txt)
void escribirLoggerTxt(char archivo[26], FILE *file, char tipo)
{
    fprintf(file, "%c\t%s\n", tipo, archivo);
    return;
}

// escribir logger.log con 2 archivos
void escribirLoggerTxtx2(char archivo1[26], char archivo2[26], FILE *file, char tipo)
{
    fprintf(file, "%c\t%s\t%s\n", tipo, archivo1, archivo2);
}

// Escribir error.log (txt)
void escribirErrorTxt(char archivo[26], FILE *file)
{
    fprintf(file, "E\t%s\n", archivo);
    return;
}
// Escribir error.log con 2 archivos
void escribirErrorTxtx2(char archivo1[26], char archivo2[26], FILE *file)
{
    fprintf(file, "E\t%s\t%s\n", archivo1, archivo2);
}

// Vector para guardar valores a imprimir con status
void cargoVecStatus(Status vecStatus[MAX_BUFFER], char archivo[26], char tipo, int i)
{
    vecStatus[i].tipo = tipo;
    strcpy(vecStatus[i].archivo, archivo);
}

// Vector que guarda las propiedades que puedan tener los archivos (maestro.dat)
void cargoVecMaestro(Maestro vecMaestro[MAX_BUFFER], Maestro archivo, int &m)
{
    strcpy(vecMaestro[m].nombre, archivo.nombre);
    vecMaestro[m].status = archivo.status;
    strcpy(vecMaestro[m].contenido, archivo.contenido);
    m++;
}

// Vector que guarda las propiedades que puedan tener los archivos (novedades.dat)
void cargoVecNovedades(Novedades vecNovedades[MAX_BUFFER], Novedades archivo, int &n)
{
    strcpy(vecNovedades[n].nombre, archivo.nombre);
    vecNovedades[n].size = archivo.size;
    vecNovedades[n].fecha = archivo.fecha;
    strcpy(vecNovedades[n].autor, archivo.autor);
    n++;
}

// CARGA/MODIFICACIÓN DE vecMaestro

// nombre
void nombreVecMaestro(Maestro vecMaestro[MAX_BUFFER], char nombre[26], int &m)
{
    int cont = 0;
    for (int x = 0; x < m; x++)
    {
        if (strcmp(vecMaestro[x].nombre, nombre) == 0)
        {
            cont++;
            strcpy(vecMaestro[x].nombre, nombre);
        }
    }
    if (cont == 0)
    {
        strcpy(vecMaestro[m].nombre, nombre);
        m++;
    }
}

// CARGA/MODIFICACIÓN DE vecNovedades

// nombre
void nombreVecNovedades(Novedades vecNovedades[MAX_BUFFER], char nombre[26], int &n)
{
    int cont = 0;
    for (int x = 0; x < n; x++)
    {
        if (strcmp(vecNovedades[x].nombre, nombre) == 0)
        {
            cont++;
            strcpy(vecNovedades[x].nombre, nombre);
        }
    }
    if (cont == 0)
    {
        strcpy(vecNovedades[n].nombre, nombre);
        n++;
    }
}

int main()
{
    system("cls");

    FILE *archivoPropiedades = abrir("comandos_svn.properties", "r");
    FILE *archivoNovedades = abrir("novedades.dat", "rb");
    FILE *archivoMaestro = abrir("maestro.dat", "rb");
    FILE *logger = abrir("logger.log", "w");
    FILE *error = abrir("error.log", "w");

    // Leo la condición a ejecutar
    char condicion[26] = {0};
    char archivoTratado[26] = {0};

    Maestro vecMaestro[MAX_BUFFER] = {0}; // vector donde cargo propiedades maestro.dat
    int m = 0;                            // inicializo m para vecMaestro
    Novedades vecNovedades[MAX_BUFFER] = {0};
    int n = 0; // inicializo n para vecNovedades
    Maestro maestro;
    Novedades novedades;
    bool mitp1Exist = false;
    bool mitp2Exist = false;
    bool mitp3Exist = false;
    bool mitp4Exist = false;

    // Declaro que archivos existen en mi maestro.dat
    leerMaeBin(&maestro, archivoMaestro);
    while (!feof(archivoMaestro))
    {
        if (strcmp(maestro.nombre, "mitp1.cpp") == 0)
        {
            mitp1Exist = true;
            cargoVecMaestro(vecMaestro, maestro, m);
        }
        else if (strcmp(maestro.nombre, "mitp2.cpp") == 0)
        {
            mitp2Exist = true;
            cargoVecMaestro(vecMaestro, maestro, m);
        }
        else if (strcmp(maestro.nombre, "mitp3.cpp") == 0)
        {
            mitp3Exist = true;
            cargoVecMaestro(vecMaestro, maestro, m);
        }
        else if (strcmp(maestro.nombre, "mitp4.cpp") == 0)
        {
            mitp4Exist = true;
            cargoVecMaestro(vecMaestro, maestro, m);
        }
        leerMaeBin(&maestro, archivoMaestro);
    }

    // Declaro los archivos que existen en mi novedades.dat
    leerNovBin(&novedades, archivoNovedades);
    while (!feof(archivoNovedades))
    {
        if (strcmp(novedades.nombre, "mitp1.cpp") == 0)
        {
            mitp1Exist = true;
            cargoVecNovedades(vecNovedades, novedades, n);
        }
        else if (strcmp(novedades.nombre, "mitp2.cpp") == 0)
        {
            mitp2Exist = true;
            cargoVecNovedades(vecNovedades, novedades, n);
        }
        else if (strcmp(novedades.nombre, "mitp3.cpp") == 0)
        {
            mitp3Exist = true;
            cargoVecNovedades(vecNovedades, novedades, n);
        }
        else if (strcmp(novedades.nombre, "mitp4.cpp") == 0)
        {
            mitp4Exist = true;
            cargoVecNovedades(vecNovedades, novedades, n);
        }
        leerNovBin(&novedades, archivoNovedades);
    }

    int i = 0; // inicializo i para vecStatus
    Status vecStatus[MAX_BUFFER] = {0};
    char buffer[MAX_BUFFER];
    while (!feof(archivoPropiedades))
    {
        if (fgets(buffer, MAX_BUFFER, archivoPropiedades) != NULL)
        {
            if (buffer[0] != '#')
            {
                strtok(buffer, " ");
                strcpy(condicion, strtok(NULL, " "));       // defino la condicion a usar
                strcpy(archivoTratado, strtok(NULL, "\n")); // defino el archivo que trata la condicion
            }
        }

        if (strcmp(condicion, "add") == 0)
        {
            if (strcmp(archivoTratado, "mitp1.cpp") == 0)
            {
                if (mitp1Exist == true)
                {
                    escribirErrorTxt(archivoTratado, error);
                }
                else
                {
                    mitp1Exist = true;
                    escribirLoggerTxt(archivoTratado, logger, 'A');
                    cargoVecStatus(vecStatus, archivoTratado, 'A', i);
                    nombreVecMaestro(vecMaestro, archivoTratado, m);
                    nombreVecNovedades(vecNovedades, archivoTratado, n);
                    i++;
                }
            }
            else if (strcmp(archivoTratado, "mitp2.cpp") == 0)
            {
                if (mitp2Exist == true)
                {
                    escribirErrorTxt(archivoTratado, error);
                }
                else
                {
                    mitp2Exist = true;
                    escribirLoggerTxt(archivoTratado, logger, 'A');
                    cargoVecStatus(vecStatus, archivoTratado, 'A', i);
                    nombreVecMaestro(vecMaestro, archivoTratado, m);
                    nombreVecNovedades(vecNovedades, archivoTratado, n);
                    i++;
                }
            }
            else if (strcmp(archivoTratado, "mitp3.cpp") == 0)
            {
                if (mitp3Exist == true)
                {
                    escribirErrorTxt(archivoTratado, error);
                }
                else
                {
                    mitp3Exist = true;
                    escribirLoggerTxt(archivoTratado, logger, 'A');
                    cargoVecStatus(vecStatus, archivoTratado, 'A', i);
                    nombreVecMaestro(vecMaestro, archivoTratado, m);
                    nombreVecNovedades(vecNovedades, archivoTratado, n);
                    i++;
                }
            }
            else if (strcmp(archivoTratado, "mitp4.cpp") == 0)
            {
                if (mitp4Exist == true)
                {
                    escribirErrorTxt(archivoTratado, error);
                }
                else
                {
                    mitp4Exist = true;
                    escribirLoggerTxt(archivoTratado, logger, 'A');
                    cargoVecStatus(vecStatus, archivoTratado, 'A', i);
                    nombreVecMaestro(vecMaestro, archivoTratado, m);
                    nombreVecNovedades(vecNovedades, archivoTratado, n);
                    i++;
                }
            }
        }
        else if (strcmp(condicion, "del") == 0)
        {
            if (strcmp(archivoTratado, "mitp1.cpp") == 0)
            {
                if (mitp1Exist == true)
                {
                    mitp1Exist = false;
                    escribirLoggerTxt(archivoTratado, logger, 'D');
                    cargoVecStatus(vecStatus, archivoTratado, 'D', i);
                    i++;
                }
                else
                {
                    escribirErrorTxt(archivoTratado, error);
                }
            }
            else if (strcmp(archivoTratado, "mitp2.cpp") == 0)
            {
                if (mitp2Exist == true)
                {
                    mitp2Exist = false;
                    escribirLoggerTxt(archivoTratado, logger, 'D');
                    cargoVecStatus(vecStatus, archivoTratado, 'D', i);
                    i++;
                }
                else
                {
                    escribirErrorTxt(archivoTratado, error);
                }
            }
            else if (strcmp(archivoTratado, "mitp3.cpp") == 0)
            {
                if (mitp3Exist == true)
                {
                    mitp3Exist = false;
                    escribirLoggerTxt(archivoTratado, logger, 'D');
                    cargoVecStatus(vecStatus, archivoTratado, 'D', i);
                    i++;
                }
                else
                {
                    escribirErrorTxt(archivoTratado, error);
                }
            }
            else if (strcmp(archivoTratado, "mitp4.cpp") == 0)
            {
                if (mitp4Exist == true)
                {
                    mitp4Exist = false;
                    escribirLoggerTxt(archivoTratado, logger, 'D');
                    cargoVecStatus(vecStatus, archivoTratado, 'D', i);
                    i++;
                }
                else
                {
                    escribirErrorTxt(archivoTratado, error);
                }
            }
        }
        else if (strcmp(condicion, "status") == 0)
        {
            int contLogStatus = 0;
            for (int j = 0; j < i; j++)
            {
                if (strcmp(archivoTratado, vecStatus[j].archivo) == 0)
                {
                    printf("Status: El archivo %s se encontro/encuentra en estado %c\n", vecStatus[j].archivo, vecStatus[j].tipo);
                    contLogStatus++;
                    if (contLogStatus == 1)
                    {
                        escribirLoggerTxt(archivoTratado, logger, '?');
                    }
                }
            }
            if (contLogStatus == 0)
            {
                printf("Status: No se encontraron modificaciones del archivo en logger.log\n");
                escribirErrorTxt(archivoTratado, error);
            }
        }
        else if (strcmp(condicion, "diff") == 0)
        {
            bool cumpleCondicion = false;
            char archivo1[26] = {0};
            char archivo2[26] = {0};
            strcpy(archivo1, strtok(archivoTratado, " "));
            strcpy(archivo2, strtok(NULL, "\n"));

            for (int j = 0; j < n; j++)
            {
                if (strcmp(archivo1, vecNovedades[j].nombre) == 0)
                {
                    for (int p = 0; p < m; p++)
                    {
                        if (strcmp(archivo2, vecNovedades[p].nombre) == 0)
                        {
                            if (vecNovedades[j].size != 0 && vecNovedades[p].size != 0)
                            {
                                if (vecNovedades[j].fecha != 0 && vecNovedades[p].fecha != 0)
                                {
                                    if (strcmp(vecNovedades[j].autor, "") != 0 && strcmp(vecNovedades[p].autor, "") != 0)
                                    {
                                        printf("Diff: El archivo %s posee nombre: %s y el archivo %s posee nombre: %s\n", vecNovedades[j].nombre, vecNovedades[j].nombre, vecNovedades[p].nombre, vecNovedades[p].nombre);
                                        printf("el archivo %s posee un size de: %i y el archivo %s posee un size de: %i\n", vecNovedades[j].nombre, vecNovedades[j].size, vecNovedades[p].nombre, vecNovedades[p].size);
                                        printf("%s posee %i como fecha mientras que %s posee %i\n", vecNovedades[j].nombre, vecNovedades[j].fecha, vecNovedades[p].nombre, vecNovedades[p].fecha);
                                        printf("el autor de %s es %s y el de %s es %s\n", vecNovedades[j].nombre, vecNovedades[j].autor, vecNovedades[p].nombre, vecNovedades[p].autor);
                                        escribirLoggerTxtx2(archivo1, archivo2, logger, '?');
                                        cumpleCondicion = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (!cumpleCondicion)
            {
                printf("Diff: no se puede realizar una comparacion\n");
                escribirErrorTxtx2(archivo1, archivo2, error);
            }
        }
        else if (strcmp(condicion, "revert") == 0)
        {
            int contLogRevert = 0;
            for (int j = 0; j < i; j++)
            {
                if (strcmp(archivoTratado, vecStatus[j].archivo) == 0)
                {
                    contLogRevert++;
                    if (contLogRevert == 1)
                    {
                        escribirLoggerTxt(archivoTratado, logger, 'M');
                    }
                }
            }
            if (contLogRevert == 0)
            {
                printf("Revert: No se encontro el archivo mencionado\n");
                escribirErrorTxt(archivoTratado, error);
            }
        }
        else if (strcmp(condicion, "info") == 0)
        {
            int contLogInfo = 0;
            for (int j = 0; j < i; j++)
            {
                if (strcmp(archivoTratado, vecMaestro[j].nombre) == 0)
                {
                    contLogInfo++;

                    printf("Info: El archivo %s contiene lo siguiente: %s", vecMaestro[j].nombre, vecMaestro[j].nombre);

                    if (vecMaestro[j].status != '\0')
                    {
                        printf(",%c", vecMaestro[j].status);
                    }
                    else
                    {
                        printf("");
                    }
                    if (strcmp(vecMaestro[j].contenido, "") != 0)
                    {
                        printf(",%s", vecMaestro[j].contenido);
                    }
                    else
                    {
                        printf("");
                    }
                    printf("\n");
                    escribirLoggerTxt(archivoTratado, logger, '?');
                }
            }
            if (contLogInfo == 0)
            {
                printf("Info: No se encontro el archivo mencionado\n");
                escribirErrorTxt(archivoTratado, error);
            }
        }
        else if (strcmp(condicion, "blame") == 0)
        {
            int contLogBlame = 0;
            for (int j = 0; j < n; j++)
            {
                if (strcmp(archivoTratado, vecNovedades[j].nombre) == 0 && strcmp(vecNovedades[j].autor, "") != 0)
                {
                    printf("Blame: El archivo %s fue modificado por %s\n", vecNovedades[j].nombre, vecNovedades[j].autor);
                    contLogBlame++;
                    if (contLogBlame == 1)
                    {
                        escribirLoggerTxt(archivoTratado, logger, '?');
                    }
                }
            }
            if (contLogBlame == 0)
            {
                printf("Blame: El archivo consultado no posee la propiedad Autor cargada\n");
                escribirErrorTxt(archivoTratado, error);
            }
        }
        else if (strcmp(condicion, "cat") == 0)
        {
            int contLogCat = 0;
            for (int j = 0; j < i; j++)
            {
                if (strcmp(archivoTratado, vecMaestro[j].nombre) == 0)
                {
                    contLogCat++;
                    if (strcmp(vecMaestro[j].contenido, "") != 0)
                    {
                        printf("Cat: El contenido del archivo %s es: %s\n", vecMaestro[j].nombre, vecMaestro[j].contenido);
                        escribirLoggerTxt(archivoTratado, logger, '?');
                    }
                    else
                    {
                        printf("Cat: el archivo no contiene informacion detallada\n");
                        escribirErrorTxt(archivoTratado, error);
                    }
                }
            }
            if (contLogCat == 0)
            {
                printf("Cat: No se encontro el archivo mencionado\n");
                escribirErrorTxt(archivoTratado, error);
            }
        }
        else if (strcmp(condicion, "propget") == 0)
        {
            int contPropGet = 0;
            char propiedad[26] = {0};
            char archBuscado[26] = {0};
            strcpy(propiedad, strtok(archivoTratado, " "));
            strcpy(archBuscado, strtok(NULL, "\n"));
            bool encontradoEnNovedades = false; // Variable para seguimiento

            for (int z = 0; z < n; z++)
            {
                if (strcmp(archBuscado, vecNovedades[z].nombre) == 0)
                {
                    if (strcmp(propiedad, "nombre") == 0)
                    {
                        if (strcmp(vecNovedades[z].nombre, "") == 0)
                        {
                            escribirErrorTxt(archBuscado, error);
                        }
                        else
                        {
                            printf("Propget: El nombre del archivo es: %s\n", vecNovedades[z].nombre);
                            escribirLoggerTxt(archBuscado, logger, '?');
                            contPropGet++;
                        }
                        encontradoEnNovedades = true; // Marcamos que encontró en vecNovedades
                    }
                    else if (strcmp(propiedad, "size") == 0)
                    {
                        if (vecNovedades[z].size == 0)
                        {
                            escribirErrorTxt(archBuscado, error);
                        }
                        else
                        {
                            printf("Propget: El size del archivo es: %i\n", vecNovedades[z].size);
                            escribirLoggerTxt(archBuscado, logger, '?');
                            contPropGet++;
                        }
                        encontradoEnNovedades = true; // Marcamos que encontró en vecNovedades
                    }
                    else if (strcmp(propiedad, "fecha") == 0)
                    {
                        if (vecNovedades[z].fecha == 0)
                        {
                            escribirErrorTxt(archBuscado, error);
                        }
                        else
                        {
                            printf("Propget: La fecha del archivo es: %i\n", vecNovedades[z].fecha);
                            escribirLoggerTxt(archBuscado, logger, '?');
                            contPropGet++;
                        }
                        encontradoEnNovedades = true; // Marcamos que encontró en vecNovedades
                    }
                    else if (strcmp(propiedad, "autor") == 0)
                    {
                        if (strcmp(vecNovedades[z].autor, "") == 0)
                        {
                            escribirErrorTxt(archBuscado, error);
                        }
                        else
                        {
                            printf("Propget: El autor del archivo es: %s\n", vecNovedades[z].autor);
                            escribirLoggerTxt(archBuscado, logger, '?');
                            contPropGet++;
                        }
                        encontradoEnNovedades = true; // Marcamos que encontró en vecNovedades
                    }
                }
            }

            // Si no encontró en vecNovedades, recorre vecMaestro
            if (!encontradoEnNovedades)
            {
                for (int j = 0; j < m; j++)
                {
                    if (strcmp(archBuscado, vecMaestro[j].nombre) == 0)
                    {
                        if (strcmp(propiedad, "nombre") == 0)
                        {
                            if (strcmp(vecMaestro[j].nombre, "") == 0)
                            {
                                escribirErrorTxt(archBuscado, error);
                            }
                            else
                            {
                                printf("Propget: El nombre del archivo es: %s\n", vecMaestro[j].nombre);
                                escribirLoggerTxt(archBuscado, logger, '?');
                                contPropGet++;
                            }
                        }
                        else if (strcmp(propiedad, "status") == 0)
                        {
                            if (vecMaestro[j].status == '\0')
                            {
                                escribirErrorTxt(archBuscado, error);
                            }
                            else
                            {
                                printf("Propget: El status del archivo es: %c\n", vecMaestro[j].status);
                                escribirLoggerTxt(archBuscado, logger, '?');
                                contPropGet++;
                            }
                        }
                        else if (strcmp(propiedad, "contenido") == 0)
                        {
                            if (strcmp(vecMaestro[j].contenido, "") == 0)
                            {
                                escribirErrorTxt(archBuscado, error);
                            }
                            else
                            {
                                printf("Propget: El contenido del archivo es: %s\n", vecMaestro[j].contenido);
                                escribirLoggerTxt(archBuscado, logger, '?');
                                contPropGet++;
                            }
                        }
                    }
                }
            }

            if (contPropGet == 0)
            {
                printf("Propget: No se puede obtener la propiedad del archivo\n");
                escribirErrorTxt(archivoTratado, error);
            }
        }
        else if (strcmp(condicion, "propset") == 0)
        {
            bool encontrado = false;
            bool modificado = false;
            char propiedad[26] = {0};
            char valor[26] = {0};
            char archBuscado[26] = {0};
            strcpy(propiedad, strtok(archivoTratado, " "));
            strcpy(valor, strtok(NULL, " "));
            strcpy(archBuscado, strtok(NULL, "\n"));

            for (int i = 0; i < n; i++)
            {

                if (strcmp(archBuscado, vecNovedades[i].nombre) == 0)
                {
                    encontrado = true;
                    if (strcmp(propiedad, "nombre") == 0)
                    {
                        strcpy(vecNovedades[i].nombre, valor);
                        modificado = true;
                    }
                    else if (strcmp(propiedad, "size") == 0)
                    {
                        vecNovedades[i].size = atoi(valor);
                        modificado = true;
                    }
                    else if (strcmp(propiedad, "fecha") == 0)
                    {
                        vecNovedades[i].fecha = atoi(valor);
                        modificado = true;
                    }
                    else if (strcmp(propiedad, "autor") == 0)
                    {
                        strcpy(vecNovedades[i].autor, valor);
                        modificado = true;
                    }
                    printf("Propset: El archivo %s fue modificado\n", archBuscado);

                    escribirLoggerTxt(archBuscado, logger, 'M');

                    break;
                }
            }
            if (!modificado)
            {
                for (int j = 0; j < m; j++)
                {
                    if (strcmp(archBuscado, vecMaestro[j].nombre) == 0)
                    {
                        encontrado = true;
                        if (strcmp(propiedad, "nombre") == 0)
                        {
                            strcpy(vecMaestro[j].nombre, valor);
                        }
                        else if (strcmp(propiedad, "status") == 0)
                        {
                            vecMaestro[j].status = valor[0];
                        }
                        else if (strcmp(propiedad, "contenido") == 0)
                        {
                            strcpy(vecMaestro[j].contenido, valor);
                        }

                        printf("Propset: El archivo %s fue modificado\n", archBuscado);

                        escribirLoggerTxt(archBuscado, logger, 'M');

                        break;
                    }
                }
            }
            if (!encontrado)
            {
                escribirErrorTxt(archBuscado, error);
                printf("PropSet: No se encontro el archivo a modificar\n");
            }
        }
    }

    fclose(archivoPropiedades);
    fclose(archivoNovedades);
    fclose(archivoMaestro);
    fclose(logger);
    fclose(error);
    system("pause");
    return 0;
}