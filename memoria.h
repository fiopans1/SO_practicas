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
#include <sys/wait.h>



#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"
typedef char *cadena;
#define LEERCOMPLETO ((ssize_t)-1)//definimos LEERCOMPLETO como -1 y le hacemos el cast a tipo ssize_t
#define TAMANO 4096
int global1, global2, global3;


//definicion de funcines:
void malloc1(cadena trozos[],int n,tListM *M);
void mmap1(cadena trozos[],int n,tListM *M);
void doRecursiva (int n);
void dealloc(cadena trozos[], int n, tListM *M);
void shared1(cadena trozos[], int n, tListM *M);
void memoria(cadena trozos[], int n, tListM *M);
void volcarmem(cadena trozos[],int n);
void llenarmemoria(cadena trozos[], int n);
void esreadwrite(cadena trozos[], int n);
//funciones secundarias:
void obt_hora(char hora[]);
bool isNumber2(cadena param1); 


//funciones que nos dieron ellos:
void * ObtenerMemoriaShmget (key_t clave, size_t tam,tListM *M);
void SharedCreate (char *arg[],tListM *M);
void * MmapFichero (char * fichero, int protection, tListM *M);
void Mmap (char *arg[], tListM *M);
void SharedDelkey (char *args[]);
ssize_t LeerFichero (char *fich, void *p, ssize_t n);
ssize_t EscribirFichero (char *fich, void *p, ssize_t n, int sobreescritura);
void dopmap (void);
#endif