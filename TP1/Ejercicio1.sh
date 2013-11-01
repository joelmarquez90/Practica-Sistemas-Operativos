#!/bin/bash

########################################
#NOMBRE DEL SCRIPT:Ejercicio1.sh			#				
#TRABAJO PRACTICO N°1                  #
#EJERCICIO 1.	                        #
#INTEGRANTES:                          #
#Joel Marquez             35.367.125   #
#Maria Eugenia Brea       35.272.169   #
#Maria Victoria Trimboli  35.723.767  	#
#Soledad Suarez           35.387.379   #
#Marlene Lauria           35.423.458  	#
#PRIMERA ENTREGA								#				
########################################


#a) Tomando en cuenta el siguiente script responda las preguntas. Importante: cómo parte del
#resultado se deberá entregar el script en un archivo tipo sh y las respuestas en el mismo código
#1- ¿Cuál es el objetivo de este script?
#2- ¿Qué parámetros recibe?
#3- Comentar línea a línea especificando qué hace cada sentencia (no describa los comandos,
#indique la lógica de cada línea completa)
#4- Completar los “echo” con el mensaje correspondiente.

Error()
{
	echo "Error. Sintaxis de uso: $0/ archivo | directorio"
}
if test $# -lt 1
then   #SI LA CANTIDAD DE PARAMETROS PASADOS POR EL SCRIPT ES MENOR A UNO, ENTONCES NO SE ENVIO NADA. DE SER ASI 
	Error  #SE PROCEDE A LLAMAR A LA FUNCION ERROR. 
elif test -d $1 #DE SER FALSO SE PREGUNTA SI EL PARAMETRO REFIERE A UN DIRECTORIO
then
	echo "$1 es un directorio"  
elif test -f $1 ##POR FALSO SE PREGUNTA POR ARCHIVO COMUN.
then
	echo "$1 es un archivo regular" 
else   #POR ULTIMO SE INFORMA, DE SER FALSO LO ANTERIOR, QUE NO CORRESPONDE A DIRECTORIO NI ARCHIVO.
	echo "$1 No se reconoce como archivo ni como directorio" 
fi


#1- El objetivo de este script es determinar si un determinado parámetro que recibe es un directorio, o un archivo común y corriente (con test -d y -f respectivamente). 

#2- El parametro que recibe es el archivo/directorio/objeto que se desea evaluar.El $0 al que se refiere es el nombre
#del script ($0 refiere al nombre del Script siempre)


##################################################################################################################
##################################################################################################################

#b) De acuerdo al siguiente script responda las siguientes preguntas:
#1- ¿Cuál es el objetivo de este script?
#2- ¿Qué parámetros recibe?
#3- Comentar línea a línea especificando qué hace cada sentencia. Describir el uso del
#comando sort y grep especificando qué opciones permiten.

#!/bin/bash
Error()
{
	echo "Error. La sintaxis del script es la siguiente:"
	echo "Para orden ascendente: $0 nombre_archivo A"
	echo "Para orden descendente: $0 nombre_archivo Z"
}
if test $# -lt 2 #SI LA CANTIDAD DE ELEMENTOS RECIBIDOS ES MENOR A 2, SE LLAMA A LA FUNCION ERROR.
then
	Error
elif test -f $1 && (test $2 = "A" || test $2 = "Z") ##SI LA CONDICION DE ERROR DA FALSO, EVALUA QUE SEA UN ARCHIVO
then    			    #CORRIENTE. POR FALSA ALGUNACONDICION SE INVOCA A  
	if test $2 = "A"		    #ERROR NUEVAMENTE. SI ES VERDADERA SE PREGUNTA SI EL 2DO PARAMETRO
	then				    #ES LA LETRA A Y DE SER ASI SE MUESTRA EL CONTENIDO DEL FICHERO ASCENDENTEMENTE
		cat $1 | sort -d
	elif test $2 = "Z"                  #SI ES FALSO QUEDA UNA SOLA OPCION, LA Z, QUE ES PARA DESCENDENTE.
	then
		cat $1 | sort -r
	fi
else
	Error
fi

#1- El script tiene como objetivo mostrar el contenido de un archivo en orden, sea descendente (-r) o ascendente (-d)


#2- Los parametros que recibe son el primero, que es el archivo que se evalua y el segundo una letra, un caracter.


#3- Se usa sort (y en este caso conectado por medio del pipe a cat), para ordenar la salida de un comando
#según lo que indique el parametro enviado, en este caso -r o -d. Como indica su nombre, entonces, sort ordena la 
#salida de algún comando. Sort también nos permite ordenar por comparaciones numericas, ignorando espacios en blanco, #etc.

#Ejemplo: ls -l | sort -r

#nos estaría mostrando en orden reverso al alfabético lo arrojado por ls.
#Por otro lado el comando grep es usado para establecer filtros. Normalmente se usa en las salidas de lo que arroja 
#otro comando, conectando con pipes (|), ejemplo:

#Ejemplo:  ls -l | grep txt 

#Estaría mostrandome  información detallada sobre los documentos en un directorio (por default el que estemos), filtra#ando por los que contienen 'txt' en sus nombres. 


