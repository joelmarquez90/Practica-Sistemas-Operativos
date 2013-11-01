#!/bin/bash

########################################
#NOMBRE DEL SCRIPT:Ejercicio4.sh			#				
#TRABAJO PRACTICO N°1                  #
#EJERCICIO 24	                        #
#INTEGRANTES:                          #
#Joel Marquez             35.367.125   #
#Maria Eugenia Brea       35.272.169   #
#Maria Victoria Trimboli  35.723.767  	#
#Soledad Suarez           35.387.379   #
#Marlene Lauria           35.423.458  	#
#PRIMERA ENTREGA								#				
########################################

####################################################################################################################
#En el comienzo del comando awk, especialmente en el begin inicializamos tres vectores asociados al código de producto,
#uno para guardar el stock recibido del proveedor y luego actualizar estos datos al leer el archivo de ventas. De esta
#manera el vector stock contendrá el stock resultante de la recepción y venta de cada producto que ingresó al almacen.
#El otro vector guarda los precios nuevos y el último las descripciones de los productos.
#El archivo stock.in tiene como formato: código descripción stock precio(opcional)
#El archivo stock.out tiene como formato: código descripción stock
##################################################################################################################### 

if [ $# -eq 1 ];then
  if [[ $1=="-?" ]];then
    echo "       Versión 1
       Parámetros:No recibe parámetros.Se actualiza una base de datos existente."
    exit 1
  fi
fi

awk '	BEGIN {
			while(getline < "stock.in" > 0) {
				stock[$1]=$3
				if(NF>3)
					precios[$1]=$4
				descripcion[$1]=$2 
			}

			while(getline < "stock.out" > 0) {
				if($1 in stock)
					stock[$1]-=$3
				else
					stock[$1]=-$3	
			}
		} 
#####################################################################################################################
#Leyendo la base de datos, se busca el código de cada producto en el vector de stock, si se encuentra en el mismo se 
#actualiza el stock en la base de datos,lo mismo se hace con el vector precios y se eliminan del vector de stock. 
#Al ir eliminando los datos que se actualizan, cuando se termina de leer la base de datos, en el vector stock
#se contiene información solo de los productos nuevos que ingresaron y no están registrados en la base de datos.
######################################################################################################################4
		{
			if($1 in stock) {
				$3+=stock[$1]
				delete stock[$1]
			}	
			if($1 in precios)
				$4=precios[$1]
			printf $0 "\n" > "stockDonCarlos.dat"
		}

#######################################################################################################################
#Por último se graba al final de la base de datos las lineas correspondientes a los productos nuevos que contiene
#el vector stock, extrayendo el precio y la descripcion correspondiente de los otros vectores.
#######################################################################################################################
 
		END {
			for(p in stock)
				printf p " " descripcion[p] " " stock[p] " " precios[p] "\n" >> "stockDonCarlos.dat"				
		}' stockDonCarlos.dat
