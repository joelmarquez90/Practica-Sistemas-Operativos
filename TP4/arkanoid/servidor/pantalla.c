#include "pantalla.h"
#include <curses.h>

void pintar_pantalla(void)
{
	int i,j;
	for(i=0;i<ALTO;i++)
		for(j=0;j<ANCHO;j++)
		{
			if(i==0||((i>0&&i<=ALTO-8)&&((j>=0&&j<4)||(j>=ANCHO-4&&j<ANCHO)))||i>ALTO-8)//pinto las partes del tablero (bordes) en negro
				MATRIZ[i][j]=BORDE;
			else if(i>=1&&i<ALTO-7&&j>=4&&j<ANCHO-4)//pinta las partes de la pantalla que van en blanco
				MATRIZ[i][j]=FONDO;
		}	
}

void pintar_nivel(int nivel)
{
	int i,j;
	if(nivel==0)
	{
		for(i=ALTO/2-9;i<ALTO/2+1;i++)//pinta los bloques y el exit nivel 1
			for(j=ANCHO/2-24;j<ANCHO/2+24;j++)
			{
				if(j>=ANCHO/2-16&&j<ANCHO/2+16)
				{
					MATRIZ[i][j]=BLOQUE2;
					encolar(i,j,BLOQUE2);
				}
				else
				{
					MATRIZ[i][j]=FONDO;
					encolar(i,j,FONDO);
				}
			}
		for(i=ALTO/2-7;i<ALTO/2-1;i++)
			for(j=ANCHO/2-12;j<ANCHO/2+12;j++)
			{
				MATRIZ[i][j]=BLOQUE1;
				encolar(i,j,BLOQUE1);
			}
		for(i=ALTO/2-5;i<ALTO/2-3;i++)
			for(j=ANCHO/2-4;j<ANCHO/2+4;j++)
			{
				MATRIZ[i][j]=ZEXIT;
				encolar(i,j,ZEXIT);
			}
	}
	else
	{
		for(i=ALTO/2-9;i<ALTO/2+1;i++)//pinta los bloques y el exit nivel 2
			for(j=ANCHO/2-24;j<ANCHO/2+24;j++)
			{
				if(j<ANCHO/2-4||j>=ANCHO/2+4)
				{
					MATRIZ[i][j]=BLOQUE2;
					encolar(i,j,BLOQUE2);
				}
				else
				{
					MATRIZ[i][j]=FONDO;
					encolar(i,j,FONDO);
				}
			}
		for(i=ALTO/2-7;i<ALTO/2-1;i++)
			for(j=ANCHO/2-20;j<ANCHO/2+20;j++)
				if(j<ANCHO/2-8||j>=ANCHO/2+8)	
				{
					MATRIZ[i][j]=BLOQUE1;
					encolar(i,j,BLOQUE1);
				}
		for(i=ALTO/2-5;i<ALTO/2-3;i++)
			for(j=ANCHO/2-16;j<ANCHO/2+16;j++)
				if(j<ANCHO/2-12||j>=ANCHO/2+12)
				{
					MATRIZ[i][j]=ZEXIT;
					encolar(i,j,ZEXIT);
				}
	}
	/*for(j=ANCHO/2-16;j<ANCHO/2+16;j++)
	{
		MATRIZ[ALTO-11][j]=ZEXIT;
		encolar(ALTO-11,j,ZEXIT);
	}*/		
}

int encolar(int x,int y,int valor)
{
	t_dato dato;
	dato.pint.x=x;
	dato.pint.y=y;
	dato.pint.valor=valor;
	devolverSemaforo(idMatriz);
	return poner_en_cola(&cola,&dato);
}

void pieza_barra(int rot,int x,int y,int col) //dibuja la barra del color col en la pantalla con las coordenadas x e y y si esta rotada o no
{
   int j;
   if(rot==1)
	  	for(j=0;j<8;j++)
	  	{  
			MATRIZ[x][y+j]=col;
			encolar(x,y+j,col);
		}
   else
    	for(j=0;j<4;j++)
	  	{ 
			MATRIZ[x+j][y]=col; 
			encolar(x+j,y,col);
			MATRIZ[x+j][y+1]=col;
			encolar(x+j,y+1,col);
		}
}


void pieza_pelota(int x,int y, int col) //pinta la pelota en la pantalla
{	
	MATRIZ[x][y]=col;
	encolar(x,y,col);
}

void dibujar_pieza(t_pieza pie)
{
	switch(pie.cod)
	{
		case 1:	pieza_barra(pie.rot,pie.x,pie.y,pie.col);
					break;
		case 2:	pieza_pelota(pie.x,pie.y,pie.col);
					break;	
	} 
}

void mover_barra(t_pieza *barra, int mov,t_pieza *pel,int soltar) //mueve y pinta la barra en la pantalla 
{
	if(mov==CONFIG.tecla_izq)
	{
		switch(barra->col) //switchea dependiendo del color de la barra
		{
			case BAZUL:	//barra azul
					if (barra->y>6) //si puede moverse a la izquierda, despinta el bloque derecho y pinta uno hacia la izquierda, actualizando la matriz
					{	
						if(soltar==0)
						{
							MATRIZ[pel->x][pel->y]=FONDO;
							encolar(pel->x,pel->y,FONDO);
							pel->y-=2;
							MATRIZ[pel->x][pel->y]=pel->col;
							encolar(pel->x,pel->y,pel->col);
						}
						barra->y-=2;
						MATRIZ[barra->x][barra->y+8]=FONDO;
						encolar(barra->x,barra->y+8,FONDO);
						MATRIZ[barra->x][barra->y+9]=FONDO;
						encolar(barra->x,barra->y+9,FONDO);
						dibujar_pieza(*barra);
					}
					break;
			case BVERDE:	//barra verde
					if (barra->y>(ANCHO/2)+5)	//igual que la anterior
					{
						if(soltar==0)
						{
							MATRIZ[pel->x][pel->y]=FONDO;
							encolar(pel->x,pel->y,FONDO);
							pel->y-=2;
							MATRIZ[pel->x][pel->y]=pel->col;
							encolar(pel->x,pel->y,pel->col);
						}
						barra->y-=2;
						MATRIZ[barra->x][barra->y+8]=FONDO;
						encolar(barra->x,barra->y+8,FONDO);
						MATRIZ[barra->x][barra->y+9]=FONDO;
						encolar(barra->x,barra->y+9,FONDO);
						dibujar_pieza(*barra);
					}						
					break;
		}
	}
	else if(mov==CONFIG.tecla_der)//si tecleo hacia la derecha 
	{
		switch(barra->col)     		
		{
			case BAZUL:	//barra azul
					if (barra->y<(ANCHO/2)-12) //si puede moverse a la der, despinta el bloque izq y pinta uno hacia la der, actualizando la matriz
					{
						if(soltar==0)
						{
							MATRIZ[pel->x][pel->y]=FONDO;
							encolar(pel->x,pel->y,FONDO);
							pel->y+=2;
							MATRIZ[pel->x][pel->y]=pel->col;
							encolar(pel->x,pel->y,pel->col);
						}
						barra->y+=2;
						MATRIZ[barra->x][barra->y-1]=FONDO;
						encolar(barra->x,barra->y-1,FONDO);
						MATRIZ[barra->x][barra->y-2]=FONDO;
						encolar(barra->x,barra->y-2,FONDO);
						dibujar_pieza(*barra);
					}
					break;
			case BVERDE:	//barra verde
					if (barra->y<ANCHO-14)	//igual que la anterior
					{		
						if(soltar==0)
						{
							MATRIZ[pel->x][pel->y]=FONDO;
							encolar(pel->x,pel->y,FONDO);
							pel->y+=2;
							MATRIZ[pel->x][pel->y]=pel->col;
							encolar(pel->x,pel->y,pel->col);
						}		
						barra->y+=2;
						MATRIZ[barra->x][barra->y-1]=FONDO;
						encolar(barra->x,barra->y-1,FONDO);
						MATRIZ[barra->x][barra->y-2]=FONDO;
						encolar(barra->x,barra->y-2,FONDO);
						dibujar_pieza(*barra);
					}
					break;
		}
	}
	else if(mov==CONFIG.tecla_arr)
	{
		switch(barra->col) 
		{
			case BMAGEN:	//barra amarilla
					if (barra->x>2)	//si puede moverse hacia arriba, despinta el bloque de abajo y pinta uno hacia arriba, actualizando la matriz
					{					
						if(soltar==0)
						{
							MATRIZ[pel->x][pel->y]=FONDO;
							encolar(pel->x,pel->y,FONDO);
							pel->x--;
							MATRIZ[pel->x][pel->y]=pel->col;
							encolar(pel->x,pel->y,pel->col);
						}
						barra->x--;			
						MATRIZ[barra->x+4][barra->y]=FONDO;
						encolar(barra->x+4,barra->y,FONDO);
						MATRIZ[barra->x+4][barra->y+1]=FONDO;
						encolar(barra->x+4,barra->y+1,FONDO);
						dibujar_pieza(*barra);
					}
					break;
			case BROJA:	//barra roja
					if (barra->x>2)	//si puede moverse hacia arriba, despinta el bloque de abajo y pinta uno hacia arriba, actualizando la matriz
					{					
						if(soltar==0)
						{
							MATRIZ[pel->x][pel->y]=FONDO;
							encolar(pel->x,pel->y,FONDO);
							pel->x--;
							MATRIZ[pel->x][pel->y]=pel->col;
							encolar(pel->x,pel->y,pel->col);
						}
						barra->x--;			
						MATRIZ[barra->x+4][barra->y]=FONDO;
						encolar(barra->x+4,barra->y,FONDO);
						MATRIZ[barra->x+4][barra->y+1]=FONDO;
						encolar(barra->x+4,barra->y+1,FONDO);
						dibujar_pieza(*barra);
					}
					break;
		}
	}
	else if(mov==CONFIG.tecla_aba)
	{
		switch(barra->col) 				
		{
			case BMAGEN:	//barra amarilla
					if (barra->x<ALTO-12)	//si puede moverse hacia abajo, despinta el bloque de arriba y pinta uno hacia abajo, actualizando la matriz
					{
						if(soltar==0)
						{
							MATRIZ[pel->x][pel->y]=FONDO;
							encolar(pel->x,pel->y,FONDO);
							pel->x++;
							MATRIZ[pel->x][pel->y]=pel->col;
							encolar(pel->x,pel->y,pel->col);
						}
						barra->x++;		
						MATRIZ[barra->x-1][barra->y]=FONDO;
						encolar(barra->x-1,barra->y,FONDO);
						MATRIZ[barra->x-1][barra->y+1]=FONDO;
						encolar(barra->x-1,barra->y+1,FONDO);
						dibujar_pieza(*barra);
					}
					break;
			case BROJA:	//barra roja
					if (barra->x<ALTO-12)	//si puede moverse hacia abajo, despinta el bloque de arriba y pinta uno hacia abajo, actualizando la matriz
					{
						if(soltar==0)
						{
							MATRIZ[pel->x][pel->y]=FONDO;
							encolar(pel->x,pel->y,FONDO);
							pel->x++;
							MATRIZ[pel->x][pel->y]=pel->col;
							encolar(pel->x,pel->y,pel->col);
						}
						barra->x++;		
						MATRIZ[barra->x-1][barra->y]=FONDO;
						encolar(barra->x-1,barra->y,FONDO);
						MATRIZ[barra->x-1][barra->y+1]=FONDO;
						encolar(barra->x-1,barra->y+1,FONDO);
						dibujar_pieza(*barra);
					}
					break;
		}
	}
}

void cambiar_trayectoria(t_pieza *pelota,int tra,int x,int y) //cambia la trayectoria de la pelota
{
	pelota->tra=tra;
	MATRIZ[pelota->x][pelota->y]=FONDO;
	encolar(pelota->x,pelota->y,FONDO);
	pelota->x+=x;
	pelota->y+=y;
	MATRIZ[pelota->x][pelota->y]=pelota->col;
	encolar(pelota->x,pelota->y,pelota->col);
}

int puede_mover(t_pieza *pelota) //valida los movimientos de la pelota
{
	int ret=-1;
	switch(pelota->tra) //switchea con la trayectoria que viene teniendo la pelota
	{
		case 0:	ret=0;
					break;
		case 1:	//60° abajo derecha
					if(MATRIZ[pelota->x+1][pelota->y+1]==BORDE) //si hay un borde negro
					{
						if(pelota->y+1==ANCHO-4&&pelota->x+1==ALTO-7) //si es una esquina
						{
							cambiar_trayectoria(pelota,4,-1,-1);
						}                                           
						else if(pelota->y+1==ANCHO-4&&pelota->x+1!=ALTO-7)	//si es la pared
						{
							cambiar_trayectoria(pelota,2,1,-1);
						}
						else if(pelota->x+1==ALTO-7&&pelota->y+1!=ANCHO-4)	//si es el piso
						{
							cambiar_trayectoria(pelota,3,-1,1);	
						}
						else if(MATRIZ[pelota->x+1][pelota->y]==ZAZUL&&MATRIZ[pelota->x][pelota->y+1]==BORDE)//si es zona azul y borde
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;
							encolar(pelota->x,pelota->y,FONDO);
							ret=1;	
						}
						else if(MATRIZ[pelota->x+1][pelota->y]==ZVERDE&&MATRIZ[pelota->x][pelota->y+1]==BORDE)//si es zona verde y borde
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;
							encolar(pelota->x,pelota->y,FONDO);
							ret=2;	
						}
						else if((MATRIZ[pelota->x][pelota->y+1]==ZROJA||MATRIZ[pelota->x][pelota->y+2]==ZROJA)&&MATRIZ[pelota->x+1][pelota->y]==BORDE)//si es zona roja y borde
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;
							encolar(pelota->x,pelota->y,FONDO);
							ret=4;	
						}
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==BAZUL||MATRIZ[pelota->x+1][pelota->y+1]==BVERDE) //si es barra azul o verde
					{
						if(MATRIZ[pelota->x+1][pelota->y+1]==BAZUL)
						{
							pelota->col=PAZUL;
							calcular_rebote(BAZUL,pelota);							
						}
						else
						{
							pelota->col=PVERDE;	
							calcular_rebote(BVERDE,pelota);
						}
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==BROJA) //si es barra roja
					{
						pelota->col=PROJA;
						calcular_rebote(BROJA,pelota);
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==ZAZUL)//si es zona azul
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=1;
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==ZVERDE)//si es zona verde
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=2;	
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==ZROJA) //si es zona roja
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=4;
					}
					
					else if(MATRIZ[pelota->x+1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota arriba
					{
						MATRIZ[pelota->x+1][pelota->y]=BLOQUE1;	
						encolar(pelota->x+1,pelota->y,BLOQUE1);
						if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE2)
						 	cambiar_trayectoria(pelota,4,-1,-1);
						else	
							cambiar_trayectoria(pelota,3,-1,1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota arriba
					{
						MATRIZ[pelota->x+1][pelota->y]=FONDO;	
						encolar(pelota->x+1,pelota->y,FONDO);						
						if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE2)
						 	cambiar_trayectoria(pelota,4,-1,-1);
						else	
							cambiar_trayectoria(pelota,3,-1,1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==ZEXIT) //si es exit y rebota en la arriba
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE2) //si es un bloque 2 y rebota en la izquierda
					{
						MATRIZ[pelota->x][pelota->y+1]=BLOQUE1;	
						encolar(pelota->x,pelota->y+1,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
						 	cambiar_trayectoria(pelota,4,-1,-1);
						else	
							cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE1) //si es un bloque 1 y rebota en la izquierda
					{
						MATRIZ[pelota->x][pelota->y+1]=FONDO;	
						encolar(pelota->x,pelota->y+1,FONDO);						
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
						 	cambiar_trayectoria(pelota,4,-1,-1);
						else	
							cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==ZEXIT) //si es exit y rebota en la izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2) //si es un bloque 2 y rebota en la esquina arriba izquierda
					{
						MATRIZ[pelota->x+1][pelota->y+1]=BLOQUE1;		
						encolar(pelota->x+1,pelota->y+1,BLOQUE1);
						cambiar_trayectoria(pelota,4,-1,-1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1) //si es un bloque 1 y rebota en la esquina arriba izquierda
					{
						MATRIZ[pelota->x+1][pelota->y+1]=FONDO;	
						encolar(pelota->x+1,pelota->y+1,FONDO);
						cambiar_trayectoria(pelota,4,-1,-1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==ZEXIT) //si es exit y rebota en la esquina arriba izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else //sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x+=1;
						pelota->y+=1;
						MATRIZ[pelota->x][pelota->y]=pelota->col;	
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
		case 2:	//60° abajo izquierda
					if(MATRIZ[pelota->x+1][pelota->y-1]==BORDE)	//si hay un borde negro
					{	
						if(pelota->y-1==3&&pelota->x+1!=ALTO-7)	//si es la pared
						{
							cambiar_trayectoria(pelota,1,1,1);	
						}
						else if(pelota->x+1==ALTO-7&&pelota->y-1!=3)	//si es el piso
						{
							cambiar_trayectoria(pelota,4,-1,-1);
						}											
						else if(pelota->y-1==3&&pelota->x+1==ALTO-7)//si es una esquina
						{
							cambiar_trayectoria(pelota,3,1,-1);
						}
						else if(MATRIZ[pelota->x+1][pelota->y]==ZAZUL&&MATRIZ[pelota->x][pelota->y-1]==BORDE)//si es zona azul y borde
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;	
							encolar(pelota->x,pelota->y,FONDO);
							ret=1;
						}
						else if(MATRIZ[pelota->x+1][pelota->y]==ZVERDE&&MATRIZ[pelota->x][pelota->y-1]==BORDE)//si es zona verde y borde
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;	
							encolar(pelota->x,pelota->y,FONDO);
							ret=2;
						}
						else if((MATRIZ[pelota->x][pelota->y-1]==ZMAGEN||MATRIZ[pelota->x][pelota->y-2]==ZMAGEN)&&MATRIZ[pelota->x+1][pelota->y]==BORDE)//si es zona magenta y borde
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;	
							encolar(pelota->x,pelota->y,FONDO);
							ret=3;
						}
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==BAZUL||MATRIZ[pelota->x+1][pelota->y-1]==BVERDE) //si es barra azul o verde
					{
						if(MATRIZ[pelota->x+1][pelota->y-1]==BAZUL)
						{
							pelota->col=PAZUL;
							calcular_rebote(BAZUL,pelota);
						}
						else
						{
							pelota->col=PVERDE;
							calcular_rebote(BVERDE,pelota);						
						}
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==BMAGEN)	 //si es barra magenta
					{						
						pelota->col=PMAGEN;
						calcular_rebote(BMAGEN,pelota);
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==ZAZUL)//si es zona azul
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=1;
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==ZVERDE)//si es zona verde
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=2;	
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==ZMAGEN) //si es zona magenta
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=3;
					}
					
					else if(MATRIZ[pelota->x+1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota arriba
					{
						MATRIZ[pelota->x+1][pelota->y]=BLOQUE1;	
						encolar(pelota->x+1,pelota->y,BLOQUE1);
						if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE2)
						 	cambiar_trayectoria(pelota,3,-1,1);
						else	
							cambiar_trayectoria(pelota,4,-1,-1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota arriba
					{
						MATRIZ[pelota->x+1][pelota->y]=FONDO;	
						encolar(pelota->x+1,pelota->y,FONDO);
						if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,3,-1,1);
						else
							cambiar_trayectoria(pelota,4,-1,-1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==ZEXIT) //si es exit y rebota arriba
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);	
						ret=0;		
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE2) //si es un bloque 2 y rebota en la derecha
					{
						MATRIZ[pelota->x][pelota->y-1]=BLOQUE1;	
						encolar(pelota->x,pelota->y-1,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2)
							cambiar_trayectoria(pelota,3,-1,1);
						else
							cambiar_trayectoria(pelota,1,1,1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE1) //si es un bloque 1 y rebota en la derecha
					{
						MATRIZ[pelota->x][pelota->y-1]=FONDO;	
						encolar(pelota->x,pelota->y-1,FONDO);						
						if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2)
							cambiar_trayectoria(pelota,3,-1,1);
						else
							cambiar_trayectoria(pelota,1,1,1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==ZEXIT) //si es exit y rebota en la derecha
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2) //si es un bloque 2 y rebota en la esquina arriba derecha
					{
						MATRIZ[pelota->x+1][pelota->y-1]=BLOQUE1;	
						encolar(pelota->x+1,pelota->y-1,BLOQUE1);
						cambiar_trayectoria(pelota,3,-1,1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1) //si es un bloque 1 y rebota en la esquina arriba derecha
					{
						MATRIZ[pelota->x+1][pelota->y-1]=FONDO;	
						encolar(pelota->x+1,pelota->y-1,FONDO);
						cambiar_trayectoria(pelota,3,-1,1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==ZEXIT) //si es exit y rebota en la esquina arriba derecha
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);	
						ret=0;	
					}
					else
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;	//sino, sigue su curso normal	
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x+=1;
						pelota->y-=1;
						MATRIZ[pelota->x][pelota->y]=pelota->col;	
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
		case 3:	//60° arriba derecha
					if(MATRIZ[pelota->x-1][pelota->y+1]==BORDE)	//si hay un borde negro
					{
						if(pelota->y+1==ANCHO-4&&pelota->x-1==0)	//si es una esquina
						{
							cambiar_trayectoria(pelota,2,1,-1);
						}
						if(pelota->y+1==ANCHO-4&&pelota->x-1!=0)	//si es la pared
						{
							cambiar_trayectoria(pelota,4,-1,-1);
						}
						if(pelota->x-1==0&&pelota->y+1!=ANCHO-4)	//si es el techo
						{
							cambiar_trayectoria(pelota,1,1,1);
						}
						else if((MATRIZ[pelota->x][pelota->y+1]==ZROJA||MATRIZ[pelota->x][pelota->y+2]==ZROJA)&&MATRIZ[pelota->x-1][pelota->y]==BORDE)//si es zona roja y borde
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;	
							encolar(pelota->x,pelota->y,FONDO);
							ret=4;
						}	
					}
					else if(MATRIZ[pelota->x-1][pelota->y+1]==BROJA) //si es barra roja
					{					
						pelota->col=PROJA;
						calcular_rebote(BROJA,pelota);
					}
					else if(MATRIZ[pelota->x-1][pelota->y+1]==ZROJA||MATRIZ[pelota->x-1][pelota->y+2]==ZROJA) //si es zona roja
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=4;
					}					
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=BLOQUE1;	
						encolar(pelota->x-1,pelota->y,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2)
							cambiar_trayectoria(pelota,2,1,-1);
						else
							cambiar_trayectoria(pelota,1,1,1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=FONDO;	
						encolar(pelota->x-1,pelota->y,FONDO);						
						if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2)
							cambiar_trayectoria(pelota,2,1,-1);
						else
						cambiar_trayectoria(pelota,1,1,1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==ZEXIT) //si es exit y rebota abajo
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE2) //si es un bloque 2 y rebota en la izquierda
					{
						MATRIZ[pelota->x][pelota->y+1]=BLOQUE1;	
						encolar(pelota->x,pelota->y+1,BLOQUE1);						
						if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,2,1,-1);
						else
							cambiar_trayectoria(pelota,4,-1,-1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE1) //si es un bloque 1 y rebota en la izquierda
					{
						MATRIZ[pelota->x][pelota->y+1]=FONDO;	
						encolar(pelota->x,pelota->y+1,FONDO);						
						if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,2,1,-1);
						else
							cambiar_trayectoria(pelota,4,-1,-1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==ZEXIT) //si es exit y rebota en la izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);	
						ret=0;	
					}
					else if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE2) //si es un bloque 2 y rebota en la esquina abajo izquierda
					{
						MATRIZ[pelota->x-1][pelota->y+1]=BLOQUE1;	
						encolar(pelota->x-1,pelota->y+1,BLOQUE1);
						cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE1) //si es un bloque 1 y rebota en la esquina abajo izquierda
					{
						MATRIZ[pelota->x-1][pelota->y+1]=FONDO;	
						encolar(pelota->x-1,pelota->y+1,FONDO);
						cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x-1][pelota->y+1]==ZEXIT) //si es exit y rebota en la esquina abajo izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);	
						ret=0;
					}
					else	//sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x-=1;
						pelota->y+=1;
						MATRIZ[pelota->x][pelota->y]=pelota->col;	
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
		case 4:	//60° arriba izquierda
					if(MATRIZ[pelota->x-1][pelota->y-1]==BORDE)	//si hay un borde negro
					{
						if(pelota->y-1==3&&pelota->x-1==0)	//si es una esquina
						{
							cambiar_trayectoria(pelota,1,1,1);
						}
						if(pelota->y-1==3&&pelota->x-1!=0)	//si es la pared
						{
							cambiar_trayectoria(pelota,3,-1,1);
						}
						if(pelota->x-1==0&&pelota->y-1!=3)	//si es el techo
						{
							cambiar_trayectoria(pelota,2,1,-1);	
						}
						else if((MATRIZ[pelota->x][pelota->y-1]==ZMAGEN||MATRIZ[pelota->x][pelota->y-2]==ZMAGEN)&&MATRIZ[pelota->x-1][pelota->y]==BORDE)//si es zona magenta y borde
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;	
							encolar(pelota->x,pelota->y,FONDO);
							ret=3;
						}
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==BMAGEN)	//si es barra magenta
					{
						pelota->col=PMAGEN;
						calcular_rebote(BMAGEN,pelota);
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==ZMAGEN) //si es zona magenta
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=3;
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=BLOQUE1;	
						encolar(pelota->x-1,pelota->y,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,1,1,1);
						else
							cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=FONDO;	
						encolar(pelota->x-1,pelota->y,FONDO);						
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,1,1,1);
						else
							cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==ZEXIT) //si es exit y rebota abajo
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE2) //si es un bloque 2 y rebota en la derecha
					{
						MATRIZ[pelota->x][pelota->y-1]=BLOQUE1;	
						encolar(pelota->x,pelota->y-1,BLOQUE1);						
						if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE2)
							cambiar_trayectoria(pelota,1,1,1);
						else
							cambiar_trayectoria(pelota,3,-1,1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE1) //si es un bloque 1 y rebota en la derecha
					{
						MATRIZ[pelota->x][pelota->y-1]=FONDO;	
						encolar(pelota->x,pelota->y-1,FONDO);						
						if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE2)
							cambiar_trayectoria(pelota,1,1,1);
						else
							cambiar_trayectoria(pelota,3,-1,1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==ZEXIT) //si es exit y rebota en la derecha
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}					
					else if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE2) //si es un bloque 2 y rebota en la esquina abajo derecha
					{
						MATRIZ[pelota->x-1][pelota->y-1]=BLOQUE1;	
						encolar(pelota->x-1,pelota->y-1,BLOQUE1);
						cambiar_trayectoria(pelota,1,1,1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1) //si es un bloque 1 y rebota en la esquina abajo derecha
					{
						MATRIZ[pelota->x-1][pelota->y-1]=FONDO;	
						encolar(pelota->x-1,pelota->y-1,FONDO);
						cambiar_trayectoria(pelota,1,1,1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==ZEXIT) //si es exit y rebota en la esquina abajo derecha
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else	//sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x-=1;
						pelota->y-=1;
						MATRIZ[pelota->x][pelota->y]=pelota->col;	
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
		case 5:	//45° abajo derecha
					if(MATRIZ[pelota->x+1][pelota->y+2]==BORDE||MATRIZ[pelota->x+1][pelota->y+1]==BORDE) //si hay un borde negro
					{
						if((pelota->y+2==ANCHO-4||pelota->y+2==ANCHO-3)&&pelota->x+1==ALTO-7) //si es una esquina
						{
							cambiar_trayectoria(pelota,8,-1,-2);
						}		                                  
						else if((pelota->y+2==ANCHO-4||pelota->y+2==ANCHO-3)&&pelota->x+1!=ALTO-7)	//si es la pared
						{
							cambiar_trayectoria(pelota,6,1,-2);
						}
						else if(MATRIZ[pelota->x+1][pelota->y]==ZAZUL&&(MATRIZ[pelota->x][pelota->y+1]==BORDE||MATRIZ[pelota->x][pelota->y+2]==BORDE))
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;		
							encolar(pelota->x,pelota->y,FONDO);
							ret=1;
						}	
						else if(MATRIZ[pelota->x+1][pelota->y]==ZVERDE&&(MATRIZ[pelota->x][pelota->y+1]==BORDE||MATRIZ[pelota->x][pelota->y+2]==BORDE))
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;		
							encolar(pelota->x,pelota->y,FONDO);
							ret=2;
						}						
						else	//si es el piso
						{
							cambiar_trayectoria(pelota,7,-1,2);	
						}
					}
					else if(MATRIZ[pelota->x+1][pelota->y+2]==BAZUL||MATRIZ[pelota->x+1][pelota->y+2]==BVERDE) //si es barra azul o verde
					{
						if(MATRIZ[pelota->x+1][pelota->y+2]==BAZUL)
						{	
							pelota->col=PAZUL;
							calcular_rebote(BAZUL,pelota);
						}
						else
						{
							pelota->col=PVERDE;
							calcular_rebote(BVERDE,pelota);
						}						
					}
					else if(MATRIZ[pelota->x+1][pelota->y+2]==BROJA||MATRIZ[pelota->x+1][pelota->y+1]==BROJA) //si es barra roja
					{
						pelota->col=PROJA;
						calcular_rebote(BROJA,pelota);
					}
					else if(MATRIZ[pelota->x+1][pelota->y+2]==ZAZUL||MATRIZ[pelota->x+1][pelota->y+1]==ZAZUL||MATRIZ[pelota->x+1][pelota->y]==ZAZUL)//si es zona azul
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=1;
					}
					else if(MATRIZ[pelota->x+1][pelota->y+2]==ZVERDE||MATRIZ[pelota->x+1][pelota->y+1]==ZVERDE||MATRIZ[pelota->x+1][pelota->y]==ZVERDE)//si es zona verde
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=2;	
					}
					else if(MATRIZ[pelota->x+1][pelota->y+2]==ZROJA||MATRIZ[pelota->x][pelota->y+1]==ZROJA) //si es zona roja
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=4;
					}
					
					else if(MATRIZ[pelota->x+1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota arriba
					{
						MATRIZ[pelota->x+1][pelota->y]=BLOQUE1;	
						encolar(pelota->x+1,pelota->y,BLOQUE1);						
						if(MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE2)
							cambiar_trayectoria(pelota,8,-1,-2);
						else
							cambiar_trayectoria(pelota,7,-1,2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota arriba
					{
						MATRIZ[pelota->x+1][pelota->y]=FONDO;	
						encolar(pelota->x+1,pelota->y,FONDO);						
						if(MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE2)
							cambiar_trayectoria(pelota,8,-1,-2);
						else
						cambiar_trayectoria(pelota,7,-1,2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==ZEXIT) //si es exit y rebota arriba
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;		
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE1) //si es un bloque 1 y rebota en la izquierda
					{
						if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE1)
						{
							MATRIZ[pelota->x][pelota->y+1]=FONDO;	
							encolar(pelota->x,pelota->y+1,FONDO);
						}
						else
						{
							MATRIZ[pelota->x+1][pelota->y+2]=FONDO;
							encolar(pelota->x+1,pelota->y+2,FONDO);	
						}								
						if(MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE2)
							cambiar_trayectoria(pelota,8,-1,-2);
						else
							cambiar_trayectoria(pelota,6,1,-2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE2||MATRIZ[pelota->x][pelota->y+1]==BLOQUE2) //si es un bloque 2 y rebota en la izquierda
					{
						if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE2)
						{
							MATRIZ[pelota->x][pelota->y+1]=BLOQUE1;	
							encolar(pelota->x,pelota->y+1,BLOQUE1);
						}
						else
						{
							MATRIZ[pelota->x+1][pelota->y+2]=BLOQUE1;			
							encolar(pelota->x+1,pelota->y+2,BLOQUE1);				
						}
						if(MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE2)
							cambiar_trayectoria(pelota,8,-1,-2);
						else
							cambiar_trayectoria(pelota,6,1,-2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==ZEXIT) //si es exit y rebota en la izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE1) //si es un bloque 1 y rebota en la esquina arriba izquierda
					{
						if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1)
						{
							MATRIZ[pelota->x+1][pelota->y+1]=FONDO;
							encolar(pelota->x+1,pelota->y+1,FONDO);
						}
						else
						{
							MATRIZ[pelota->x+1][pelota->y+2]=FONDO;
							encolar(pelota->x+1,pelota->y+2,FONDO);
						}
						cambiar_trayectoria(pelota,8,-1,-2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2||MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE2) //si es un bloque 2 y rebota en la esquina arriba izquierda
					{
						if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2)
						{
							MATRIZ[pelota->x+1][pelota->y+1]=BLOQUE1;
							encolar(pelota->x+1,pelota->y+1,BLOQUE1);
						}
						else
						{
							MATRIZ[pelota->x+1][pelota->y+2]=BLOQUE1;
							encolar(pelota->x+1,pelota->y+2,BLOQUE1);
						}
						cambiar_trayectoria(pelota,8,-1,-2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x+1][pelota->y+1]==ZEXIT) //si es exit y rebota en la esquina arriba izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else //sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x+=1;
						pelota->y+=2;
						MATRIZ[pelota->x][pelota->y]=pelota->col;
						encolar(pelota->x,pelota->y,pelota->col);
					} 
					break;
		case 6:	//45° abajo izquierda
					if(MATRIZ[pelota->x+1][pelota->y-2]==BORDE||MATRIZ[pelota->x+1][pelota->y-1]==BORDE)	//si hay un borde negro
					{
						if((pelota->y-2==3||pelota->y-2==2)&&pelota->x+1==ALTO-7)	//si es una esquina
						{
							cambiar_trayectoria(pelota,7,-1,2);
						}
						else if((pelota->y-2==3||pelota->y-2==2)&&pelota->x+1!=ALTO-7)	//si es la pared
						{
							cambiar_trayectoria(pelota,5,1,2);	
						}
						else if(MATRIZ[pelota->x+1][pelota->y]==ZAZUL&&(MATRIZ[pelota->x][pelota->y-1]==BORDE||MATRIZ[pelota->x][pelota->y-2]==BORDE))
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;		
							encolar(pelota->x,pelota->y,FONDO);
							ret=1;
						}	
						else if(MATRIZ[pelota->x+1][pelota->y]==ZVERDE&&(MATRIZ[pelota->x][pelota->y-1]==BORDE||MATRIZ[pelota->x][pelota->y-2]==BORDE))
						{
							cambiar_trayectoria(pelota,0,0,0);
							MATRIZ[pelota->x][pelota->y]=FONDO;		
							encolar(pelota->x,pelota->y,FONDO);
							ret=2;
						}
						else //si es el piso
						{
							cambiar_trayectoria(pelota,8,-1,-2);
						}
					}
					else if(MATRIZ[pelota->x+1][pelota->y-2]==BAZUL||MATRIZ[pelota->x+1][pelota->y-2]==BVERDE) //si es barra azul o verde
					{
						if(MATRIZ[pelota->x+1][pelota->y-2]==BAZUL)
						{
							pelota->col=PAZUL;
							calcular_rebote(BAZUL,pelota);
						}
						else
						{
							pelota->col=PVERDE;
							calcular_rebote(BVERDE,pelota);
						}													
					}
					else if(MATRIZ[pelota->x+1][pelota->y-2]==BMAGEN||MATRIZ[pelota->x+1][pelota->y-1]==BMAGEN)	 //si es barra magenta
					{
						pelota->col=PMAGEN;
						calcular_rebote(BMAGEN,pelota);
					}
					else if(MATRIZ[pelota->x+1][pelota->y-2]==ZAZUL||MATRIZ[pelota->x+1][pelota->y-1]==ZAZUL||MATRIZ[pelota->x+1][pelota->y]==ZAZUL)//si es zona azul
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						ret=1;
					}
					else if(MATRIZ[pelota->x+1][pelota->y-2]==ZVERDE||MATRIZ[pelota->x+1][pelota->y-1]==ZVERDE||MATRIZ[pelota->x+1][pelota->y]==ZVERDE)//si es zona verde
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						ret=2;	
					}
					else if(MATRIZ[pelota->x+1][pelota->y-2]==ZMAGEN||MATRIZ[pelota->x][pelota->y-1]==ZMAGEN) //si es zona magenta
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=3;
					}
						
					else if(MATRIZ[pelota->x+1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota arriba
					{
						MATRIZ[pelota->x+1][pelota->y]=BLOQUE1;
						encolar(pelota->x+1,pelota->y,BLOQUE1);						
						if(MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE2)
							cambiar_trayectoria(pelota,7,-1,2);
						else
						cambiar_trayectoria(pelota,8,-1,-2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota arriba
					{
						MATRIZ[pelota->x+1][pelota->y]=FONDO;	
						encolar(pelota->x+1,pelota->y,FONDO);					
						if(MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE2)
							cambiar_trayectoria(pelota,7,-1,2);
						else
						cambiar_trayectoria(pelota,8,-1,-2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==ZEXIT) //si es exit y rebota arriba
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);	
						ret=0;	
					}
					else if(MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x][pelota->y-1]==BLOQUE1) //si es un bloque 1 y rebota en la derecha
					{
						if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE1)
						{
							MATRIZ[pelota->x][pelota->y-1]=FONDO;
							encolar(pelota->x,pelota->y-1,FONDO);
						}
						else
						{	
							MATRIZ[pelota->x+1][pelota->y-2]=FONDO;
							encolar(pelota->x+1,pelota->y-2,FONDO);
						}
						if(MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE2)
							cambiar_trayectoria(pelota,7,-1,2);
						else
							cambiar_trayectoria(pelota,5,1,2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE2||MATRIZ[pelota->x][pelota->y-1]==BLOQUE2) //si es un bloque 2 y rebota en la derecha
					{
						if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE2)
						{
							MATRIZ[pelota->x][pelota->y-1]=BLOQUE1;
							encolar(pelota->x,pelota->y-1,BLOQUE1);
						}
						else
						{
							MATRIZ[pelota->x+1][pelota->y-2]=BLOQUE1;
							encolar(pelota->x+1,pelota->y-2,BLOQUE1);
						}
						if(MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE2)
							cambiar_trayectoria(pelota,7,-1,2);
						else
						cambiar_trayectoria(pelota,5,1,2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==ZEXIT) //si es exit y rebota en la izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE1) //si es un bloque 1 y rebota en la esquina arriba derecha
					{
						if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1)
						{
							MATRIZ[pelota->x-1][pelota->y-1]=FONDO;
							encolar(pelota->x-1,pelota->y-1,FONDO);
						}
						else
						{
							MATRIZ[pelota->x-1][pelota->y-2]=FONDO;
							encolar(pelota->x-1,pelota->y-2,FONDO);
						}
						cambiar_trayectoria(pelota,7,-1,2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2||MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE2) //si es un bloque 2 y rebota en la esquina arriba derecha
					{
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
						{
							MATRIZ[pelota->x+1][pelota->y-1]=BLOQUE1;
							encolar(pelota->x+1,pelota->y-1,BLOQUE1);
						}
						else
						{
							MATRIZ[pelota->x+1][pelota->y-2]=BLOQUE1;
							encolar(pelota->x+1,pelota->y-2,BLOQUE1);
						}
						cambiar_trayectoria(pelota,7,-1,2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==ZEXIT) //si es exit y rebota en la esquina arriba izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else //sino, sigue su curso normal.
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x+=1;
						pelota->y-=2;
						MATRIZ[pelota->x][pelota->y]=pelota->col;
						encolar(pelota->x,pelota->y,pelota->col);
					} 
					break; 
		case 7:	//45° arriba derecha
					if(MATRIZ[pelota->x-1][pelota->y+2]==BORDE||MATRIZ[pelota->x-1][pelota->y+1]==BORDE)	//si hay un borde negro
					{
						if((pelota->y+2==ANCHO-4||pelota->y+2==ANCHO-3)&&pelota->x-1==0)	//si es una esquina
						{
							cambiar_trayectoria(pelota,6,1,-2);
						}
						else if((pelota->y+2==ANCHO-4||pelota->y+2==ANCHO-3)&&pelota->x-1!=0)	//si es la pared
						{
							cambiar_trayectoria(pelota,8,-1,-2);
						}
						else	//si es el techo
						{
							cambiar_trayectoria(pelota,5,1,2);
						}
					}
					else if(MATRIZ[pelota->x-1][pelota->y+2]==BROJA||MATRIZ[pelota->x-1][pelota->y+1]==BROJA) //si es barra roja
					{	
						pelota->col=PROJA;
						calcular_rebote(BROJA,pelota);						
					}
					else if(MATRIZ[pelota->x-1][pelota->y+2]==ZROJA||MATRIZ[pelota->x][pelota->y+1]==ZROJA) //si es zona roja
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=4;
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=BLOQUE1;
						encolar(pelota->x-1,pelota->y,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE2)
							cambiar_trayectoria(pelota,6,1,-2);
						else
							cambiar_trayectoria(pelota,5,1,2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=FONDO;
						encolar(pelota->x-1,pelota->y,FONDO);						
						if(MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+2]==BLOQUE2)
							cambiar_trayectoria(pelota,6,1,-2);
						else
							cambiar_trayectoria(pelota,5,1,2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==ZEXIT) //si es exit y rebota abajo
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE1) //si es un bloque 1 y rebota en la izquierda
					{
						if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE1)
						{
							MATRIZ[pelota->x][pelota->y+1]=FONDO;
							encolar(pelota->x,pelota->y+1,FONDO);
						}
						else
						{	
							MATRIZ[pelota->x-1][pelota->y+2]=FONDO;
							encolar(pelota->x-1,pelota->y+2,FONDO);
						}
						if(MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE2)
							cambiar_trayectoria(pelota,6,1,-2);
						else
							cambiar_trayectoria(pelota,8,-1,-2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE2||MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE2) //si es un bloque 2 y rebota en la izquierda
					{
						if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE2)
						{
							MATRIZ[pelota->x][pelota->y+1]=BLOQUE1;
							encolar(pelota->x,pelota->y+1,BLOQUE1);
						}
						else
						{
							MATRIZ[pelota->x-1][pelota->y+2]=BLOQUE1;
							encolar(pelota->x-1,pelota->y+2,BLOQUE1);
						}
						if(MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE2)
							cambiar_trayectoria(pelota,6,1,-2);
						else
							cambiar_trayectoria(pelota,8,-1,-2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==ZEXIT) //si es exit y rebota en la izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;		
					}
					else if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE1) //si es un bloque 1 y rebota en la esquina abajo izquierda
					{
						if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE1)
						{
							MATRIZ[pelota->x-1][pelota->y+1]=FONDO;
							encolar(pelota->x-1,pelota->y+1,FONDO);
						}
						else
						{
							MATRIZ[pelota->x-1][pelota->y+2]=FONDO;
							encolar(pelota->x-1,pelota->y+2,FONDO);
						}
						cambiar_trayectoria(pelota,6,1,-2);	
						sumar_puntaje(pelota,BLOQUE1);
					}					
					else if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE2||MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE2) //si es un bloque 2 y rebota en la esquina abajo izquierda
					{
						if(MATRIZ[pelota->x-1][pelota->y+1]==BLOQUE2)
						{
							MATRIZ[pelota->x-1][pelota->y+1]=BLOQUE1;
							encolar(pelota->x-1,pelota->y+1,BLOQUE1);
						}
						else
						{
							MATRIZ[pelota->x-1][pelota->y+2]=BLOQUE1;
							encolar(pelota->x-1,pelota->y+2,FONDO);
						}
						cambiar_trayectoria(pelota,6,1,-2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y+1]==ZEXIT) //si es exit y rebota en la esquina abajo izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else	//sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x-=1;
						pelota->y+=2;
						MATRIZ[pelota->x][pelota->y]=pelota->col;
						encolar(pelota->x,pelota->y,pelota->col);
					} 
					break;
		case 8:	//45° arriba izquierda
					if(MATRIZ[pelota->x-1][pelota->y-2]==BORDE||MATRIZ[pelota->x-1][pelota->y-1]==BORDE)	//si hay un borde negro
					{
						if((pelota->y-2==3||pelota->y-2==2)&&pelota->x-1==0)	//si es una esquina
						{
							cambiar_trayectoria(pelota,5,1,2);
						}
						else if((pelota->y-2==3||pelota->y-2==2)&&pelota->x-1!=0)	//si es la pared
						{
							cambiar_trayectoria(pelota,7,-1,2);
						}
						else	//si es el techo
						{
							cambiar_trayectoria(pelota,6,1,-2);	
						}
					}
					else if(MATRIZ[pelota->x-1][pelota->y-2]==BMAGEN||MATRIZ[pelota->x-1][pelota->y-1]==BMAGEN)	//si es barra magenta
					{
						pelota->col=PMAGEN;
						calcular_rebote(BMAGEN,pelota);
					}
					else if(MATRIZ[pelota->x-1][pelota->y-2]==ZMAGEN||MATRIZ[pelota->x][pelota->y-1]==ZMAGEN) //si es zona magenta
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=3;
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=BLOQUE1;
						encolar(pelota->x-1,pelota->y,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE2)
							cambiar_trayectoria(pelota,5,1,2);
						else
						cambiar_trayectoria(pelota,6,1,-2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=FONDO;	
						encolar(pelota->x-1,pelota->y,FONDO);					
						if(MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-2]==BLOQUE2)
							cambiar_trayectoria(pelota,5,1,2);
						else
						cambiar_trayectoria(pelota,6,1,-2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==ZEXIT) //si es exit y rebota abajo
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE1) //si es un bloque 1 y rebota en la derecha
					{
						if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE1)
						{
							MATRIZ[pelota->x][pelota->y-1]=FONDO;
							encolar(pelota->x,pelota->y-1,FONDO);
						}
						else
						{
							MATRIZ[pelota->x-1][pelota->y-2]=FONDO;
							encolar(pelota->x-1,pelota->y-2,FONDO);
						}						
						if(MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE2)
							cambiar_trayectoria(pelota,5,1,2);
						else
						cambiar_trayectoria(pelota,7,-1,2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE2||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE2) //si es un bloque 2 y rebota en la derecha
					{
						if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE2)
						{
							MATRIZ[pelota->x][pelota->y-1]=BLOQUE1;
							encolar(pelota->x,pelota->y-1,BLOQUE1);
						}
						else
						{
							MATRIZ[pelota->x-1][pelota->y-2]=BLOQUE1;
							encolar(pelota->x-1,pelota->y-2,BLOQUE1);
						}						
						if(MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y+2]==BLOQUE2)
							cambiar_trayectoria(pelota,5,1,2);
						else
						cambiar_trayectoria(pelota,7,-1,2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==ZEXIT) //si es exit y rebota en la derecha
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);	
						ret=0;	
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE1) //si es un bloque 1 y rebota en la esquina abajo derecha
					{
						if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE1)
						{
							MATRIZ[pelota->x-1][pelota->y-1]=FONDO;
							encolar(pelota->x-1,pelota->y-1,FONDO);
						}
						else
						{
							MATRIZ[pelota->x-1][pelota->y-2]=FONDO;
							encolar(pelota->x-1,pelota->y-2,FONDO);
						}
						cambiar_trayectoria(pelota,5,1,2);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE2||MATRIZ[pelota->x-1][pelota->y-2]==BLOQUE2) //si es un bloque 2 y rebota en la esquina abajo derecha
					{
						if(MATRIZ[pelota->x-1][pelota->y-1]==BLOQUE2)
						{
							MATRIZ[pelota->x-1][pelota->y-1]=BLOQUE1;
							encolar(pelota->x-1,pelota->y-1,BLOQUE1);
						}
						else
						{
							MATRIZ[pelota->x-1][pelota->y-2]=BLOQUE1;
							encolar(pelota->x-1,pelota->y-2,BLOQUE1);
						}
						cambiar_trayectoria(pelota,5,1,2);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y-1]==ZEXIT) //si es exit y rebota en la esquina abajo derecha
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else	//sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x-=1;
						pelota->y-=2;
						MATRIZ[pelota->x][pelota->y]=pelota->col;
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
		case 9:	//90° abajo 
					if(MATRIZ[pelota->x+1][pelota->y]==BORDE) //si hay un borde negro
					{		                                  
						if(pelota->x+1==ALTO-7&&pelota->y+1!=ANCHO-4)	//si es el piso y no es la esquina derecha
						{
							cambiar_trayectoria(pelota,4,-1,-1);
						}
						else
						{
							cambiar_trayectoria(pelota,3,-1,1);	
						}
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==BAZUL||MATRIZ[pelota->x+1][pelota->y]==BVERDE) //si es barra azul o verde
					{
						if(MATRIZ[pelota->x+1][pelota->y]==BAZUL)
						{
							pelota->col=PAZUL;
							calcular_rebote(BAZUL,pelota);	
						}
						else
						{
							pelota->col=PVERDE;
							calcular_rebote(BVERDE,pelota);
						}	
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==ZAZUL)//si es zona azul
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=1;
					}
					else if(MATRIZ[pelota->x+1][pelota->y]==ZVERDE)//si es zona verde
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						ret=2;	
					}
					else //sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x+=1;
						pelota->y+=0;
						MATRIZ[pelota->x][pelota->y]=pelota->col;
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
		case 10:	//90° arriba
					if(MATRIZ[pelota->x-1][pelota->y]==BORDE)	//si hay un borde negro
					{
						if(pelota->y-1!=3&&pelota->x-1==0)	//si es el techo y no es la esquina izquierda
						{
							cambiar_trayectoria(pelota,2,1,-1);
						}
						else //si la esquina izquierda
						{
							cambiar_trayectoria(pelota,1,1,1);
						}
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE2) //si es un bloque 2 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=BLOQUE1;
						encolar(pelota->x-1,pelota->y,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,9,1,0);
						else
							cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==BLOQUE1) //si es un bloque 1 y rebota abajo
					{
						MATRIZ[pelota->x-1][pelota->y]=FONDO;
						encolar(pelota->x-1,pelota->y,FONDO);						
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,9,1,0);
						else
							cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x-1][pelota->y]==ZEXIT) //si es exit y rebota abajo
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}	
					else
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;	//sino, sigue su curso normal
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x-=1;
						pelota->y-=0;
						MATRIZ[pelota->x][pelota->y]=pelota->col;
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
		case 11:	//90°  derecha
					if(MATRIZ[pelota->x][pelota->y+1]==BORDE)	//si hay un borde negro
					{
						if(pelota->y+1==ANCHO-4&&pelota->x-1!=0)	//si es la pared y no es la esquina de arriba
						{
							cambiar_trayectoria(pelota,8,-1,-2);
						}
						else	//si es la esquina de arriba
						{
							cambiar_trayectoria(pelota,6,1,-2);	
						}
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BROJA) //si es barra roja
					{
						pelota->col=PROJA;
						calcular_rebote(BROJA,pelota);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==ZROJA) //si es zona roja
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=4;
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE2) //si es un bloque 2 y rebota en la izquierda
					{
						MATRIZ[pelota->x][pelota->y+1]=BLOQUE1;
						encolar(pelota->x,pelota->y+1,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,12,0,-1);
						else
							cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==BLOQUE1) //si es un bloque 1 y rebota en la izquierda
					{
						MATRIZ[pelota->x][pelota->y+1]=FONDO;
						encolar(pelota->x,pelota->y+1,FONDO);						
						if(MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y-1]==BLOQUE2)
							cambiar_trayectoria(pelota,12,0,-1);
						else
							cambiar_trayectoria(pelota,2,1,-1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x][pelota->y+1]==ZEXIT) //si es exit y rebota en la izquierda
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else	//sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x+=0;
						pelota->y+=1;
						MATRIZ[pelota->x][pelota->y]=pelota->col;
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
		case 12:	//90° izquierda
					if(MATRIZ[pelota->x][pelota->y-1]==BORDE)	//si hay un borde negro
					{
						if(pelota->y-1==3&&pelota->x-1!=0)	//si es la pared y no es la esquina de arriba
						{
							cambiar_trayectoria(pelota,7,-1,2);
						}
						else //si es la esquina de arriba
						{
							cambiar_trayectoria(pelota,5,1,2);
						}
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BMAGEN) //si es barra magenta
					{
						pelota->col=PMAGEN;	
						calcular_rebote(BMAGEN,pelota);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==ZMAGEN) //si es zona magenta
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						ret=3;
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE2) //si es un bloque 2 y rebota en la derecha
					{
						MATRIZ[pelota->x][pelota->y-1]=BLOQUE1;
						encolar(pelota->x,pelota->y-1,BLOQUE1);						
						if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2)
							cambiar_trayectoria(pelota,11,0,1);
						else
						cambiar_trayectoria(pelota,1,1,1);	
						sumar_puntaje(pelota,BLOQUE2);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==BLOQUE1) //si es un bloque 1 y rebota en la derecha
					{
						MATRIZ[pelota->x][pelota->y-1]=FONDO;
						encolar(pelota->x,pelota->y-1,FONDO);						
						if(MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE1||MATRIZ[pelota->x+1][pelota->y+1]==BLOQUE2)
							cambiar_trayectoria(pelota,11,0,1);
						else
							cambiar_trayectoria(pelota,1,1,1);	
						sumar_puntaje(pelota,BLOQUE1);
					}
					else if(MATRIZ[pelota->x][pelota->y-1]==ZEXIT) //si es exit y rebota en la derecha
					{
						cambiar_trayectoria(pelota,0,0,0);
						MATRIZ[pelota->x][pelota->y]=FONDO;	
						encolar(pelota->x,pelota->y,FONDO);
						ret=0;	
					}
					else	//sino, sigue su curso normal
					{
						MATRIZ[pelota->x][pelota->y]=FONDO;
						encolar(pelota->x,pelota->y,FONDO);
						pelota->x+=0;
						pelota->y-=1;
						MATRIZ[pelota->x][pelota->y]=pelota->col;
						encolar(pelota->x,pelota->y,pelota->col);
					}
					break;
	}
	return ret;
}

void calcular_rebote(int bar,t_pieza *pelota)
{
	int r;
	srand(time(NULL));
	switch(bar)
	{
		case BAZUL:
		case BVERDE:		
						do 
						{
							r=rand()%12+1;	 	
						}while(r==1||r==2||r==5||r==6||r==9||r==11||r==12);//5 aleatorias
						break;
		case BMAGEN:
						do 
						{
							r=rand()%12+1;	 	
						}while(r==2||r==4||r==6||r==8||r==9||r==10||r==12);//5 aleatorias
						break;
		case BROJA:
						do 
						{
							r=rand()%12+1;	 	
						}while(r==1||r==3||r==5||r==7||r==9||r==10||r==11);//5 aleatorias
						break;		
	}		
	switch(r)
	{
		case 1: cambiar_trayectoria(pelota,r,1,1);
			break;
		case 2: cambiar_trayectoria(pelota,r,1,-1);
			break;
		case 3: cambiar_trayectoria(pelota,r,-1,1);
			break;
		case 4: cambiar_trayectoria(pelota,r,-1,-1);
			break;
		case 5: cambiar_trayectoria(pelota,r,1,2);
			break;
		case 6: cambiar_trayectoria(pelota,r,1,-2);
			break;
		case 7: cambiar_trayectoria(pelota,r,-1,2);
			break;
		case 8: cambiar_trayectoria(pelota,r,-1,-2);
			break;
		case 9: cambiar_trayectoria(pelota,r,1,0);
			break;
		case 10: cambiar_trayectoria(pelota,r,-1,0);
			break;
		case 11: cambiar_trayectoria(pelota,r,0,1);
			break;
		case 12: cambiar_trayectoria(pelota,r,0,-1);		
	}
}

void agregar_jugador(int numJug,int socket,int vidas,int puntos) //agrega los jugadores en la pantalla según el número que sean
{
	int i,j;
 	jugadores[numJug].nro=numJug+1;
	jugadores[numJug].vidas=vidas;
	jugadores[numJug].puntos=puntos;
	jugadores[numJug].socket=socket;
	jugadores[numJug].soltar=0;
	jugadores[numJug].cayoPel=0;
	switch (numJug)
	{
		case 0:		
					jugadores[numJug].bar.x=ALTO-7;
					jugadores[numJug].bar.y=ANCHO/4-4;
					jugadores[numJug].bar.rot=1;
					jugadores[numJug].bar.col=BAZUL;
					jugadores[numJug].bar.cod=1;
					jugadores[numJug].pel.x=jugadores[numJug].bar.x-1;
					jugadores[numJug].pel.y=jugadores[numJug].bar.y+4;
					jugadores[numJug].pel.col=PAZUL;
					jugadores[numJug].pel.cod=2;
					jugadores[numJug].pel.tra=3;
					for(i=6;i<(ANCHO/2)-4;i++)
					{
						MATRIZ[ALTO-7][i]=FONDO;
						encolar(ALTO-7,i,FONDO);
						MATRIZ[ALTO-6][i]=ZAZUL;
						encolar(ALTO-6,i,ZAZUL);
					}
					break;
		case 1:  	
					jugadores[numJug].bar.x=ALTO-7;
					jugadores[numJug].bar.y=(3*ANCHO-16)/4;
					jugadores[numJug].bar.rot=1;
					jugadores[numJug].bar.col=BVERDE;
					jugadores[numJug].bar.cod=1;
					jugadores[numJug].pel.x=jugadores[numJug].bar.x-1;
					jugadores[numJug].pel.y=jugadores[numJug].bar.y+4;
					jugadores[numJug].pel.col=PVERDE;
					jugadores[numJug].pel.cod=2;
					jugadores[numJug].pel.tra=4;
					for(i=(ANCHO/2)+4;i<ANCHO-6;i++)
					{
						MATRIZ[ALTO-7][i]=FONDO;
						encolar(ALTO-7,i,FONDO);
						MATRIZ[ALTO-6][i]=ZVERDE;
						encolar(ALTO-6,i,ZVERDE);
					}
					break; 
		case 2:	
					jugadores[numJug].bar.x=(ALTO-6)/2-2;
					jugadores[numJug].bar.y=2;
					jugadores[numJug].bar.rot=2;
					jugadores[numJug].bar.col=BMAGEN;
					jugadores[numJug].bar.cod=1;
					jugadores[numJug].pel.x=jugadores[numJug].bar.x+2;
					jugadores[numJug].pel.y=jugadores[numJug].bar.y+2;
					jugadores[numJug].pel.col=PMAGEN;
					jugadores[numJug].pel.cod=2;
					jugadores[numJug].pel.tra=3;
					for(i=0;i<2;i++)
						for(j=2;j<ALTO-8;j++)
						{
							MATRIZ[j][i]=ZMAGEN;
							encolar(j,i,ZMAGEN);
						}
					for(i=2;i<4;i++)
						for(j=2;j<ALTO-8;j++)
						{
							MATRIZ[j][i]=FONDO;
							encolar(j,i,FONDO);
						}
					break;				
		case 3:
					jugadores[numJug].bar.x=(ALTO-6)/2-2;
					jugadores[numJug].bar.y=ANCHO-4;
					jugadores[numJug].bar.rot=2;
					jugadores[numJug].bar.col=BROJA;
					jugadores[numJug].bar.cod=1;
					jugadores[numJug].pel.x=jugadores[numJug].bar.x+2;
					jugadores[numJug].pel.y=jugadores[numJug].bar.y-1;
					jugadores[numJug].pel.col=PROJA;
					jugadores[numJug].pel.cod=2;
					jugadores[numJug].pel.tra=4;
					for(i=ANCHO-2;i<ANCHO;i++)
						for(j=2;j<ALTO-8;j++)
						{
							MATRIZ[j][i]=ZROJA;
							encolar(j,i,ZROJA);
						}
					for(i=ANCHO-4;i<ANCHO-2;i++)
						for(j=2;j<ALTO-8;j++)
						{
							MATRIZ[j][i]=FONDO;
							encolar(j,i,FONDO);
						}       
					break;
	}
	dibujar_pieza(jugadores[numJug].pel);
	dibujar_pieza(jugadores[numJug].bar);
}

void borrar_jugador(int numJug) //borra un jugador del tablero inicializando todos sus valores en 0
{
	int i,j;
 	jugadores[numJug].nro=0;
 	jugadores[numJug].socket=0;
	jugadores[numJug].vidas=0;
	jugadores[numJug].puntos=0;
	jugadores[numJug].soltar=0;
	jugadores[numJug].cayoPel=0;
	jugadores[numJug].bar.x=0;
	jugadores[numJug].bar.y=0;
	jugadores[numJug].bar.rot=0;
	jugadores[numJug].bar.col=0;
	jugadores[numJug].bar.cod=0;
	MATRIZ[jugadores[numJug].pel.x][jugadores[numJug].pel.y]=FONDO;
	encolar(jugadores[numJug].pel.x,jugadores[numJug].pel.y,FONDO);
	jugadores[numJug].pel.x=0;
	jugadores[numJug].pel.y=0;
	jugadores[numJug].pel.col=0;
	jugadores[numJug].pel.cod=0;
	jugadores[numJug].pel.tra=0;
	switch(numJug)
	{
		case 0:
				for(i=6;i<(ANCHO/2)-4;i++)
				{
					MATRIZ[ALTO-7][i]=BORDE;
					encolar(ALTO-7,i,BORDE);
					MATRIZ[ALTO-6][i]=BORDE;
					encolar(ALTO-6,i,BORDE);
				}
				break;
		case 1:
				for(i=(ANCHO/2)+4;i<ANCHO-6;i++)
				{
					MATRIZ[ALTO-7][i]=BORDE;
					encolar(ALTO-7,i,BORDE);
					MATRIZ[ALTO-6][i]=BORDE;
					encolar(ALTO-6,i,BORDE);
				}
				break;
		case 2:
				for(i=0;i<4;i++)
					for(j=2;j<ALTO-8;j++)
					{
						MATRIZ[j][i]=BORDE;
						encolar(j,i,BORDE);
					}
				break;
		case 3:
				for(i=ANCHO-4;i<ANCHO;i++)
					for(j=2;j<ALTO-8;j++)
					{
						MATRIZ[j][i]=BORDE;
						encolar(j,i,BORDE);
					}
				break;
	}
}

void sumar_puntaje(t_pieza * pelota,int bloque)	//suma los puntajes cuando la pelota toca un bloque
{
	if(bloque==BLOQUE1)
	{
		if(pelota->col==PAZUL)
			jugadores[0].puntos+=P5;
		else if(pelota->col==PVERDE)
			jugadores[1].puntos+=P5;
		else if(pelota->col==PMAGEN)
			jugadores[2].puntos+=P5;
		else if(pelota->col==PROJA)
			jugadores[3].puntos+=P5;
	}
	else if(bloque==BLOQUE2)
	{
		if(pelota->col==PAZUL)
			jugadores[0].puntos+=P10;
		else if(pelota->col==PVERDE)
			jugadores[1].puntos+=P10;
		else if(pelota->col==PMAGEN)
			jugadores[2].puntos+=P10;
		else if(pelota->col==PROJA)
			jugadores[3].puntos+=P10;
	}
}
