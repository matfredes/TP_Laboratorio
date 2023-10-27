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
        printf("%d,", pop(pila));
    }
}
int main()
{

    system("cls");

    STR_NODO *pila = NULL;
    create(&pila);

    STR_NODO *aux = NULL;
    create(&aux);

    int valorI = 22;

    push(&pila, 1);
    push(&pila, 2);
    push(&pila, 3);
    push(&pila, 4);
    push(&pila, 5);

    while (!isEmpty(pila))
    {
        push(&aux, pop(&pila));
    }

    int i = 0;
    while (!isEmpty(aux))
    {
        if (i < 2)
        {
            push(&pila, pop(&aux));
        }
        else if (i == 2)
        {
            push(&pila, valorI);
        }
        else
        {
            push(&pila, pop(&aux));
        }
        i++;
    }

    clear(&pila);
    system("pause");
    return 0;
}