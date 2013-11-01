#include "pantalla.h"
#include "estructuras.h"
#include <curses.h>
#include <string.h>

void inicializar_pantalla(void)
{ 
	initscr();
	keypad(stdscr,TRUE); 
	nonl();
	cbreak();
	start_color();
	curs_set(0);
	noecho(); 
	getmaxyx(stdscr,ALTO,ANCHO);
	
	init_pair(BLOQUE2,COLOR_WHITE,COLOR_CYAN);
	init_pair(BLOQUE1,COLOR_WHITE,COLOR_YELLOW);
	init_pair(BORDE,COLOR_WHITE,COLOR_BLACK);
	init_pair(FONDO,COLOR_BLACK,COLOR_WHITE);
	init_pair(ZEXIT,COLOR_BLACK,COLOR_WHITE);
	init_pair(BAZUL,COLOR_WHITE,COLOR_BLUE);
	init_pair(BVERDE,COLOR_WHITE,COLOR_GREEN);
	init_pair(BMAGEN,COLOR_WHITE,COLOR_MAGENTA);
	init_pair(BROJA,COLOR_WHITE,COLOR_RED);
	init_pair(PAZUL,COLOR_BLUE,COLOR_WHITE);
	init_pair(PVERDE,COLOR_GREEN,COLOR_WHITE);
	init_pair(PMAGEN,COLOR_MAGENTA,COLOR_WHITE);
	init_pair(PROJA,COLOR_RED,COLOR_WHITE);
}	

void presentacion() //muestra en pantalla ARKANOID
{
	int i, x=(ANCHO-72)/2,y=ALTO/2-2; //X=4,Y=11
	attron(COLOR_PAIR(BAZUL));
	for(i=x+2;i<x+6;i++) //palos horizontales primer A
	{
		mvaddch(y-2,i,' ');
		mvaddch(y+1,i,' ');
	}
	for(i=x+12;i<x+16;i++) //palos horizontales R
	{
		mvaddch(y-2,i,' ');
		mvaddch(y+1,i,' ');
	}
	for(i=x+32;i<x+36;i++)//palos horizontales segunda A
	{
		mvaddch(y-2,i,' ');
		mvaddch(y+1,i,' ');
	}
	for(i=x+52;i<x+56;i++)////palos horizontales O
	{
		mvaddch(y-2,i,' ');
		mvaddch(y+3,i,' ');
	}
	for(i=x+66;i<x+70;i++)//palos horizontales D
	{
		mvaddch(y-2,i,' ');
		mvaddch(y+3,i,' ');
	}
	for(i=y-1;i<y+4;i++)//palos verticales cortos R
	{
		if (i!=y+1)
		{
			mvaddch(i,x+17,' ');
			mvaddch(i,x+16,' ');
		}
	}
	for(i=y;i<y+2;i++)//palos verticales cortos principio K
	{
		mvaddch(i,x+23,' ');
		mvaddch(i,x+22,' ');	
	}
	for(i=y-1;i<y+3;i++)//palos verticales cortos medio K
	{
		mvaddch(i,x+25,' ');
		mvaddch(i,x+24,' ');
	}
	for(i=y-2;i<y+4;i++)//palos verticales cortos fin K
	{
		if (i!=y&&i!=y+1)
		{
			mvaddch(i,x+27,' ');
			mvaddch(i,x+26,' ');
		}
	}
	mvaddch(y+2,x+15,' ');//cuadrado medio R
	mvaddch(y+2,x+14,' ');
	for(i=y-1;i<y+1;i++)//palos verticales cortos medio arriba N
	{
		mvaddch(i,x+43,' ');
		mvaddch(i,x+42,' ');
	}
	for(i=y+1;i<y+3;i++)//palos verticales cortos medio abajo N
	{
		mvaddch(i,x+45,' ');
		mvaddch(i,x+44,' ');
	}
	for(i=y-1;i<y+3;i++)//palo vertical corto D
	{
		mvaddch(i,x+71,' ');
		mvaddch(i,x+70,' ');
	}
	for(i=y-2;i<y+4;i++) //palos largos
	{
		mvaddch(i,x,' ');
		mvaddch(i,x+1,' ');
		mvaddch(i,x+6,' ');
		mvaddch(i,x+7,' ');
		mvaddch(i,x+10,' ');
		mvaddch(i,x+11,' ');
		mvaddch(i,x+20,' ');
		mvaddch(i,x+21,' ');
		mvaddch(i,x+30,' ');
		mvaddch(i,x+31,' ');
		mvaddch(i,x+36,' ');
		mvaddch(i,x+37,' ');
		mvaddch(i,x+40,' ');
		mvaddch(i,x+41,' ');
		mvaddch(i,x+46,' ');
		mvaddch(i,x+47,' ');
		mvaddch(i,x+50,' ');
		mvaddch(i,x+51,' ');
		mvaddch(i,x+56,' ');
		mvaddch(i,x+57,' ');
		mvaddch(i,x+60,' ');
		mvaddch(i,x+61,' ');
		mvaddch(i,x+64,' ');
		mvaddch(i,x+65,' ');
	}
	attroff(COLOR_PAIR(BAZUL));
	attron(A_BOLD);
	attron(A_BLINK);	
	mvprintw(ALTO/2+7,(ANCHO-strlen("Cargando.."))/2,"Cargando..");
	refresh();
	clear();
}	

void pintar_zona(t_pintar pint)
{	
	if(pint.valor==20)
	{
		attron(COLOR_PAIR(BAZUL));
		mvprintw(ALTO-6,(ANCHO-8)/4-1,"PLAYER 1");
		attroff(COLOR_PAIR(BAZUL));					
	}
	if(pint.valor==21)
	{
		attron(COLOR_PAIR(BVERDE));
		mvprintw(ALTO-6,(3*ANCHO-8)/4-3,"PLAYER 2");
		attroff(COLOR_PAIR(BVERDE));
	}
	if(pint.valor==22)
	{
		attron(COLOR_PAIR(BMAGEN));
		mvprintw(ALTO/2-7,0,"P");
		mvprintw(ALTO/2-6,0,"L");
		mvprintw(ALTO/2-5,0,"A");
		mvprintw(ALTO/2-4,0,"Y");
		mvprintw(ALTO/2-3,0,"E");
		mvprintw(ALTO/2-2,0,"R");
		mvprintw(ALTO/2,0,"3"); 
		attroff(COLOR_PAIR(BMAGEN));
	}
	if(pint.valor==23)
	{
		attron(COLOR_PAIR(BROJA));
		mvprintw(ALTO/2-7,ANCHO-2,"P");
		mvprintw(ALTO/2-6,ANCHO-2,"L");
		mvprintw(ALTO/2-5,ANCHO-2,"A");
		mvprintw(ALTO/2-4,ANCHO-2,"Y");
		mvprintw(ALTO/2-3,ANCHO-2,"E");
		mvprintw(ALTO/2-2,ANCHO-2,"R");
		mvprintw(ALTO/2,ANCHO-2,"4");
		attroff(COLOR_PAIR(BROJA));
	}
	refresh();
}

void pintar_puntajes(t_pintar pint) //pinta la tabla de puntajes segun el numero
{
	attron(A_BOLD);
	attron(A_BLINK);
	mvprintw(ALTO-3,2,"PUNTOS");
	mvprintw(ALTO-2,2,"VIDAS");	
	if (pint.valor==40)
	{
		attron(COLOR_PAIR(BAZUL));
		mvprintw(ALTO-4,12,"PLAYER 1");
		attroff(COLOR_PAIR(BAZUL));			
		mvprintw(ALTO-4,22,"PLAYER 2");
		mvprintw(ALTO-4,32,"PLAYER 3");
		mvprintw(ALTO-4,42,"PLAYER 4");
	}
	if (pint.valor==41)
	{		
		attron(COLOR_PAIR(BVERDE));
		mvprintw(ALTO-4,22,"PLAYER 2");
		attroff(COLOR_PAIR(BVERDE));	
		mvprintw(ALTO-4,12,"PLAYER 1");
		mvprintw(ALTO-4,32,"PLAYER 3");
		mvprintw(ALTO-4,42,"PLAYER 4");
	}
	if (pint.valor==42)
	{
		attron(COLOR_PAIR(BMAGEN));
		mvprintw(ALTO-4,32,"PLAYER 3");
		attroff(COLOR_PAIR(BMAGEN));
		mvprintw(ALTO-4,12,"PLAYER 1");
		mvprintw(ALTO-4,22,"PLAYER 2");
		mvprintw(ALTO-4,42,"PLAYER 4");
	}
	if (pint.valor==43)
	{
		attron(COLOR_PAIR(BROJA));
		mvprintw(ALTO-4,42,"PLAYER 4");
		attroff(COLOR_PAIR(BROJA));	
		mvprintw(ALTO-4,12,"PLAYER 1");
		mvprintw(ALTO-4,22,"PLAYER 2");
		mvprintw(ALTO-4,32,"PLAYER 3");
	}			
	refresh();
}

void actualizar_puntajes(t_pintar pint)
{
	char vidas[6], puntos[6];
	sprintf(vidas,"%d",pint.x);
	sprintf(puntos,"%d",pint.y);
	attron(COLOR_PAIR(BORDE));
	switch(pint.valor)
	{
		case 30:
		case 20:
			mvaddch(ALTO-3,12,' ');
			mvaddch(ALTO-3,13,' ');
			mvaddch(ALTO-3,14,' ');
			mvaddch(ALTO-3,15,' ');
			mvprintw(ALTO-3,12,"%s",puntos);
			mvaddch(ALTO-2,12,' ');
			mvprintw(ALTO-2,12,"%s",vidas);
			break;	
		case 31:
		case 21:
			mvaddch(ALTO-3,22,' ');
			mvaddch(ALTO-3,23,' ');
			mvaddch(ALTO-3,24,' ');
			mvaddch(ALTO-3,25,' ');
			mvprintw(ALTO-3,22,"%s",puntos);
			mvaddch(ALTO-2,22,' ');
			mvprintw(ALTO-2,22,"%s",vidas);
			break;	
		case 32:
		case 22:
			mvaddch(ALTO-3,32,' ');
			mvaddch(ALTO-3,33,' ');
			mvaddch(ALTO-3,34,' ');
			mvaddch(ALTO-3,35,' ');
			mvprintw(ALTO-3,32,"%s",puntos);
			mvaddch(ALTO-2,32,' ');
			mvprintw(ALTO-2,32,"%s",vidas);
			break;	
		case 33:
		case 23:
			mvaddch(ALTO-3,42,' ');
			mvaddch(ALTO-3,43,' ');
			mvaddch(ALTO-3,44,' ');
			mvaddch(ALTO-3,45,' ');
			mvprintw(ALTO-3,42,"%s",puntos);
			mvaddch(ALTO-2,42,' ');
			mvprintw(ALTO-2,42,"%s",vidas);
			break;	
	}
	attroff(COLOR_PAIR(BORDE));
}

void pintar(t_pintar pint)
{
	switch(pint.valor)
	{
		case 	BORDE:
							attron(COLOR_PAIR(BORDE));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BORDE));
							break;
		case	FONDO:
							attron(COLOR_PAIR(FONDO));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(FONDO));
							break;
		case	BAZUL:
							attron(COLOR_PAIR(BAZUL));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BAZUL));
							break;
		case	BVERDE:
							attron(COLOR_PAIR(BVERDE));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BVERDE));
							break;
		case	BMAGEN:
							attron(COLOR_PAIR(BMAGEN));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BMAGEN));
							break;
		case	BROJA:
							attron(COLOR_PAIR(BROJA));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BROJA));
							break;
		case	ZAZUL:
							attron(COLOR_PAIR(BAZUL));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BAZUL));
							break;
		case	ZVERDE:
							attron(COLOR_PAIR(BVERDE));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BVERDE));
							break;
		case	ZMAGEN:
							attron(COLOR_PAIR(BMAGEN));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BMAGEN));
							break;
		case	ZROJA:
							attron(COLOR_PAIR(BROJA));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BROJA));
							break;
		case	PAZUL:
							attron(COLOR_PAIR(PAZUL));
							mvaddch(pint.x,pint.y,'o');
							attroff(COLOR_PAIR(PAZUL));
							break;						
		case	PVERDE:							
							attron(COLOR_PAIR(PVERDE));
							mvaddch(pint.x,pint.y,'o');
							attroff(COLOR_PAIR(PVERDE));
							break;
		case	PMAGEN:
							attron(COLOR_PAIR(PMAGEN));
							mvaddch(pint.x,pint.y,'o');
							attroff(COLOR_PAIR(PMAGEN));
							break;
		case	PROJA:
							attron(COLOR_PAIR(PROJA));
							mvaddch(pint.x,pint.y,'o');
							attroff(COLOR_PAIR(PROJA));	
							break;
		case BLOQUE1: 	
							attron(COLOR_PAIR(BLOQUE1));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BLOQUE1));
							break;
		case BLOQUE2: 	
							attron(COLOR_PAIR(BLOQUE2));
							mvaddch(pint.x,pint.y,' ');
							attroff(COLOR_PAIR(BLOQUE2));
							break;
		case ZEXIT:				
							attron(COLOR_PAIR(ZEXIT));
							mvaddch(pint.x,pint.y,'X');
							attroff (COLOR_PAIR(ZEXIT));
							break;
	}
	refresh();
}
