#!/bin/bash

########################################
#NOMBRE DEL SCRIPT:Ejercicio2.sh			#				
#TRABAJO PRACTICO N°1                  #
#EJERCICIO 2.	                        #
#INTEGRANTES:                          #
#Joel Marquez             35.367.125   #
#Maria Eugenia Brea       35.272.169   #
#Maria Victoria Trimboli  35.723.767  	#
#Soledad Suarez           35.387.379   #
#Marlene Lauria           35.423.458  	#
#PRIMERA ENTREGA								#				
########################################


###############################################################################################
#Funcion que imprime mensaje de error. Si el script recibio como parametro el nombre del archivo, la salida se direcciona
#automaticamente a otro archivo de logs. De lo contrario se informa por pantalla.
################################################################################################

Error()
{
if [ $1 -eq 1 ] ; 
then
	echo "Error. Debe ingresarse un parametro numerico y opcionalmente --log=archivo: '$0' 'parametro' '--log=archivo'" >  ./log
	echo
else
	echo "Error. Debe ingresarse un parametro numerico y opcionalmente --log=archivo: '$0' 'parametro' '--log=archivo'"
	echo
fi
}

################################################################################################
#Procedemos a verificar que se haya enviado el parametro adecuado, en caso contrario
#se informa por pantalla.
#################################################################################################

if [[ ! ( $1 = *[[:digit:]]* ) ]];then
	if [ $# -eq 2 ];then
		Error 1
		exit 1
	else
		Error 2
		exit 1
	fi
else
	if [ $# -eq 2 ];then
		archivo=`echo $2 | sed -e 's/\([a-zA-Z]*\)=\([a-zA-Z.]*\)/\1/'`
		if test $archivo = "--log" ; then
			archivo=""
		else
  			Error 2
			exit 1			
  		fi
	fi
fi
NUM=$1
SUMA=0
i=0
RES=`expr $NUM % 10`

#################################################################################################
#Se realizan divisiones sucesivas para descomponer el numero en todas sus cifras. Los restos son guardados
#en vectores para luego utilizarlos. 
################################################################################################

while ((test $RES -ne 0 && test `expr $NUM / 10` -ge 0) || (test $RES -eq 0 && test `expr $NUM / 10` -ne 0))
do
	SUMA=`expr $SUMA + $RES`
	vector[$i]=$RES
	i=`expr $i + 1`
	NUM=`expr $NUM / 10`
	RES=`expr $NUM  % 10`
done

#################################################################################################
#Se recorre el array en sentido inverso para mostrar el numero en orden. (Con el algoritmo anterior queda al revés, 
#con lo cual es necesario acomodarlo.)
#################################################################################################

if [ $# -eq 2 ];then
	archivo=`echo $2 | sed -e 's/--log=//'`
	printf "" > ./$archivo
fi
for((j=$i ; j >= 0 ; j-- ))
do
	if [ $# -eq 2 ] ; 
	then
		printf "${vector[$j]}" >> ./$archivo
	else
		printf "${vector[$j]}" 
	fi
	if [[ ($j -lt $i) && ($j -gt 0) ]] ; 
	then
		if [ $# -eq 2 ] ; 
		then
			printf " + " >> ./$archivo
		else
			printf " + "
		fi
	fi
done

######################################################################################################
#IMPRIME EN PANTALLA SI NO SE PASO PARAMETRO O EN ARCHIVO SI ESTE HUBIERA SIDO PASADO.
#####################################################################################################

if [ $# -eq 2 ] ; 
then
	printf " = " >> ./$archivo
	printf "$SUMA" >> ./$archivo
	echo
else
	printf " = "
	printf "$SUMA"
	echo
fi



