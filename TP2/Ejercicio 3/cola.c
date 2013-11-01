#include <stdio.h>
#include <stdlib.h>
#include "cola.h"


void crear_cola (t_lista *pl)
{
    *pl=NULL;
}

int cola_vacia(t_lista *pl)
{
    return *pl==NULL;
}

int poner_en_cola(t_lista *pl, const t_dato *d)
{
    t_nodo* pn=(t_nodo*)malloc(sizeof(t_nodo));
    if(!pn)
    return NO_MEM;
    pn->info=*d;

    if(!*pl)
    {
        pn->psig=pn;
        *pl=pn;
        return TODO_OK;
    }

    pn->psig=(*pl)->psig;
    (*pl)->psig=pn;
    *pl=pn;
    return TODO_OK;
}



int frente_de_cola(const t_lista * pl, t_dato *d)
{
    if(!*pl)
    return COLA_VACIA;

    *d=(*pl)->psig->info;
    return TODO_OK;
}


int sacar_de_cola (t_lista *pl, t_dato *d)
{t_nodo *aux;

    if(!*pl)
    return COLA_VACIA;

    if(*pl != (*pl)->psig)
    {
    aux=(*pl)->psig;
    (*pl)->psig=aux->psig;
    *d=aux->info;
     free(aux);
    return TODO_OK;
    }

    aux=*pl;
    *d=aux->info;
    *pl=NULL;
    free(aux);
    return TODO_OK;

}


int vaciar_cola (t_lista*pl)
{t_nodo* aux;
    if(!*pl)
    return COLA_VACIA;

    while(*pl!=(*pl)->psig)
    {
        aux=(*pl)->psig;
        (*pl)->psig=aux->psig;
        free(aux);
    }
    *pl=NULL;
    return TODO_OK;
}





