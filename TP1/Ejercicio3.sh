#!/bin/bash

########################################
#NOMBRE DEL SCRIPT:Ejercicio3.sh			#				
#TRABAJO PRACTICO N°1                  #
#EJERCICIO 3.	                        #
#INTEGRANTES:                          #
#Joel Marquez             35.367.125   #
#Maria Eugenia Brea       35.272.169   #
#Maria Victoria Trimboli  35.723.767  	#
#Soledad Suarez           35.387.379   #
#Marlene Lauria           35.423.458  	#
#PRIMERA ENTREGA								#				
########################################


##################################################################################################################
#Funciones
##################################################################################################################

##################################################################################################################
#Guardamos en un vector las variables ingresadas por el usuario. Despues se lo recorre para cargar el archivo. con
#las salidas de echo, que se direccionan al mismo.
##################################################################################################################
Agregar_Persona()
{
clear
echo " "
echo "****AGREGAR UNA PERSONA****"
echo
 printf "Nombre: " && read VAR
vec[0]=$VAR
 printf "Apellido: " && read VAR
vec[1]=$VAR
 printf "Telefono 'xx-xxxx-xxxx': " && read VAR
vec[2]=$VAR

for (( i=0 ; i<=2 ; i++ ))
do
printf "%-10s ${vec[$i]}	" >> ./agenda.txt
done 
echo  >> ./agenda.txt
}

Consultar_Clave()
{ 
  clear
  echo "*****CONSULTAR POR CLAVE*****" 
  if [ -e agenda.txt ]; then
  printf "Ingresar Palabra a buscar: " && read VAR
  clear
  echo " "
  echo "Coincidencias encontradas: "
  echo " "
  cat  agenda.txt | grep $VAR
  if [ $? -ne 0 ] ; then
  echo "No se encontraron coincidencias"
  fi
  echo " "
  echo "Presione 'ENTER' para continuar "
  read
  else
  printf "El archivo no existe, o esta vacio. Presione 'ENTER' para continuar "
  read
  fi
}




Mostrar_Agenda()
{
  clear
  if [ -e agenda.txt ]; then
  echo " "
  echo "***********************************************************************************************"
  sort agenda.txt
  echo "***********************************************************************************************"
  echo " "
  echo "Presione 'ENTER' para continuar "
  read
  else
  echo "El archivo de la agenda no existe, o esta vacio. Presione 'ENTER' para continuar "
  read
  fi
}



Borrar_Agenda()
{
 clear
  if [  -e "agenda.txt" ]; then
  rm -rf agenda.txt
  echo "Registros borrados. Presione 'ENTER' para continuar "
  read
  else
  echo "El archivo de la agenda no existe, o esta vacio. Presione 'ENTER' para continuar "
  read
  fi
}


##################################################################################################################
#Inicio del Programa
##################################################################################################################
if [ $# -eq 1 ];then
	if [[ $1=="-?" ]];then
	 echo "       Versión 1
       Parámetros:No recibe parámetros.Debe seleccionarse opción desde un menú"
 	exit 1
	fi
fi

 OP=2
 while ( test $OP -ne 5 ) 
 do
	clear
	echo "SELECCIONE SU OPCION: "
  	echo " "
	echo "[1]- Agregar Persona "
	echo "[2]- Consultar por Clave "
	echo "[3]- Mostrar Agenda "
	echo "[4]- Borrar Agenda "
	echo "[5]- Salir "
  	echo " "
        read OP
##################################################################################################################
#Verificamos que OP sea un numero
##################################################################################################################	
        while [[ ! ( $OP = *[[:digit:]]* ) ]]; do 
	printf "Debe Ingresarse un numero: " && read OP
	done        
	
        case $OP in 
	1) Agregar_Persona;;
	2) Consultar_Clave;;
        3) Mostrar_Agenda ;;
        4) Borrar_Agenda;;
         
        esac
 done
