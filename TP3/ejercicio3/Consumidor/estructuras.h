#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

typedef struct {key_t keylimite1, keylimite2, keymem;
		int memid, limiteid2, limiteid1;
}t_mensaje;
		

