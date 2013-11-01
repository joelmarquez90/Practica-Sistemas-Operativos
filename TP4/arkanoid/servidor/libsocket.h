#ifndef LIBSOCKET_H
#define LIBSOCKET_H

int abrir_socket_escucha(int);
int conectar_al_server(int, char *);
int aceptar_conexion(int);

#endif
