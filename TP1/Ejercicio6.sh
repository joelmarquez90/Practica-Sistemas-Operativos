#!/bin/bash

########################################
#NOMBRE DEL SCRIPT:Ejercicio6.sh			#				
#TRABAJO PRACTICO N°1                  #
#EJERCICIO 6.	                        #
#INTEGRANTES:                          #
#Joel Marquez             35.367.125   #
#Maria Eugenia Brea       35.272.169   #
#Maria Victoria Trimboli  35.723.767  	#
#Soledad Suarez           35.387.379   #
#Marlene Lauria           35.423.458  	#
#PRIMERA ENTREGA								#				
########################################

#####################################################################################################################
#Primero seteamos una  bandera en 1 para verificar luego si la validación fue adecuada y no entrar al ciclo posterior
#La validación consiste en ver que se haya pasado un numero único, en KB, correspondientes al tamaño que ocupa
# en disco el archivo encontrado.
######################################################################################################################

bandera=1
if (test $# -eq 1) then
	if [[ $1=="-?" ]]; then
		bandera=1
	else 
		if [[ ! ( $1 = *[[:digit:]]* ) ]]; then
			echo "El parametro ingresado debe ser numerico puro"
			bandera=0
		fi
	fi
else
	echo "Debe ingresarse como unico parámetro el espacio ocupado por el archivo en disco, expresado en Bytes"
	bandera=0 
fi

###################################################################################################################
# De "pasarse" la marca, se ingresa a un ciclo que evalúa todas las salidas del find, que se correspondan con
# el patrón usado. Luego obtenemos cuánto ocupan los mismos (de a uno por vez)
# Se extrae con el comando sed el campo que nos  interesa y adelante, evaluamos que la longitud de los archivos traidos coincida con la pasada por parametro. 
###################################################################################################################

if (test $bandera -eq 1) then
	for archivo in `find ./ -iname 'PELICULAS[0-9][0-9][0-9][0-9]'`
	do
		VAR=`stat -c %s $archivo`
		if (test $VAR -ge $1) then

##################################################################################################################
#Ingresamos a un bloque de comando awk para pasar a mayusculas unicamente los titulos, y guardar lo realizado en un
#archivo auxiliar.
##################################################################################################################

			awk ' BEGIN{ CONTADOR=0}
			{
				if( $0!="----------" )
				{    
				 	if(CONTADOR==0)
					{	
						print toupper($0) > "archivoaux.txt"
						CONTADOR=1
					}
					else
						printf $0 "\n" > "archivoaux.txt"
				}
				else
				{
					CONTADOR=0
					printf $0 "\n" > "archivoaux.txt"	
				}		
			}' $archivo

##################################################################################################################### 
#Se copian los archivos auxiliares para no permitir pérdida de ningún dato y modificar el mismo archivo.
#############################################################################################################	

		 	cp ./archivoaux.txt $archivo
			sed 's/[a-z]\+/\u&/gi' $archivo > archivoaux.txt
			cp ./archivoaux.txt $archivo
   	fi

######################################################################################################################
#Con el comando sed, se pasa a mayúscula la primer letra de cada palabra del archivo que tenemos ya modificado.
#Se guardan los nuevos datos en el archivo auxiliar para no perder la información y luego se reemplaza el archivo original por este. 
######################################################################################################################

	done

############################################################################################################
#Borramos el archivo auxiliar creado.
############################################################################################################

	rm -f "archivoaux.txt"
fi
