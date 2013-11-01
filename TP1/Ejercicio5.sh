#!/bin/bash

########################################
#NOMBRE DEL SCRIPT:Ejercicio5.sh			#				
#TRABAJO PRACTICO N°1                  #
#EJERCICIO 5.	                        #
#INTEGRANTES:                          #
#Joel Marquez             35.367.125   #
#Maria Eugenia Brea       35.272.169   #
#Maria Victoria Trimboli  35.723.767  	#
#Soledad Suarez           35.387.379   #
#Marlene Lauria           35.423.458  	#
#PRIMERA ENTREGA								#				
########################################

####################################################################################################################
#Con el comando sed, se identifican los bloques a invertir, el primero y el segundo (id,dni) solo números, el segundo 
#y tercero (apellido,nombre) solo letras mayúsculas o minúsculas y espacio, el cuarto (dirección) letras, números y espacio.
#Se especifica en el mismo comando el orden en que se desean los bloques.Con \u delante del bloque se indica que en el mismo
#se convierte la primer letra a mayúscula.
#####################################################################################################################


if [ $# -eq 1 ];then
  if [[ $1=="-?" ]];then
    echo "       Versión 1
       Parámetros:No recibe parámetros.Se genera un nuevo archivo a partir de uno existente."
    exit 1
  fi
fi

sed 's/\([0-9]*\),\([0-9]*\),\([a-zA-Z ]*\),\([a-zA-Z ]*\),\([a-zA-Z 0-9]*\)/\u\4:\u\3:\2:\5:\1/' Ejercicio5.in > Ejercicio5.out

