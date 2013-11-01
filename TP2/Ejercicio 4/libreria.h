#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void NuevaAlarma(int,pid_t,int);

void handler(int, siginfo_t *, void *);
void CancelarAlarma(pid_t);
void SetearActYConjSen(struct sigaction *);

