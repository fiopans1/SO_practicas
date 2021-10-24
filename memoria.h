#ifndef __MEMORIA_H
#define __MEMORIA_H
//VARIABLES
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h> 
#include <errno.h>
#include <sys/file.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include "memoria_list.h"



typedef char *cadena;
#define LEERCOMPLETO ((ssize_t)-1)


//definicion de funcines:
void malloc1(cadena trozos,int n);


#endif