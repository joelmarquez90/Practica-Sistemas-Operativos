#include "arbol.h"

int comparar (const t_info *d, const t_info *dnodo)
{
	return d->dni-dnodo->dni;
}

void crearArbol (t_arbol *p)
{
	*p=NULL;
}

int cargarenArbol (t_arbol *p, const t_info *d)
{
	int cmp;
	if (*p)
	{
	   cmp=comparar (d, &(*p)->info);
	   if (!cmp)
	   {
			(*p)->info=*d;
			return TODO_BIEN;
		}
	   if (cmp<0)
	   	return cargarenArbol (&(*p)->izq, d);
	   else
	   	return cargarenArbol (&(*p)->der, d);
	}
	*p=(t_nodo *)malloc(sizeof (t_nodo));
	if (!*p)
		return SIN_MEMORIA;
	(*p)->info=*d;
	(*p)->izq=(*p)->der=NULL;
	return TODO_BIEN;
}

void eliminarArbol (t_arbol *p)
{
   if (*p)
   {
      eliminarArbol (&(*p)->izq);
      eliminarArbol (&(*p)->der);
      if (!(*p)->izq&&!(*p)->der)
      {
         free (*p);
         *p=NULL;
      }
   }
}

void grabarpreArbol (const t_arbol *p, FILE *pf)
{
   if (*p)
   { 
		fprintf(pf, "%s:%s:%ld:%.2f:%d:%s:%ld\n", (*p)->info.empresa, (*p)->info.apynom, (*p)->info.dni, (*p)->info.sueldo, (*p)->info.antiguedad, 
						(*p)->info.posee_tarjeta, (*p)->info.tel);
		grabarpreArbol (&(*p)->izq, pf);
      grabarpreArbol (&(*p)->der, pf);
   }
}
