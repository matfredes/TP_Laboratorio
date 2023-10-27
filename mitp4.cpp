#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct STR_NODO
{
    int dato;
    STR_NODO *ste;
};

void create(STR_NODO **pila)
{
    *pila = NULL;
}

bool isEmpty(STR_NODO *pila)
{
    return pila == NULL;
}

void push(STR_NODO **pila, int valor)
{
    STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    nodo->ste = *pila;
    *pila = nodo;
    return;
}

int pop(STR_NODO **pila)
{
    int dato = (*pila)->dato;
    STR_NODO *aux = *pila;
    *pila = (*pila)->ste;

    free(aux);
    return dato;
}

void clear(STR_NODO **pila)
{
    while (!isEmpty(*pila))
    {
        printf("%d->", pop(pila));
    }
    printf("NULL");
}

char pushEnPosicion(STR_NODO **pila, int valor, int posicion)
{
    STR_NODO *aux = NULL;
    int eliminados = 0;
    while (!isEmpty(*pila) && eliminados < (posicion - 1))
    {
        push(&aux, pop(pila));
        eliminados++;
    }

    push(pila, valor);

    while (!isEmpty(aux))
    {
        push(pila, pop(&aux));
    }

    if (eliminados == (posicion - 1))
    {
        return 'S';
    }
    else
    {
        return 'N';
    }
}

int main()
{

    STR_NODO *pila = NULL;

    create(&pila);

    push(&pila, 1);
    push(&pila, 2);
    push(&pila, 3);
    push(&pila, 4);
    push(&pila, 5);
    push(&pila, 6);

    clear(&pila);
    system("pause");
    return 0;
}