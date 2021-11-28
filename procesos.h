/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander.varela@udc.es
 * GROUP: 2.3
 * DATE: 21/09/2021
 */
#ifndef __PROCESOS_H
#define __PROCESOS_H
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
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "list_procesos.h"

#define MAXVAR 256
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"
typedef char *cadena;
int oldfd;
extern char ** environ;





//FUNCIONES:
void priority(cadena trozos[], int n);
void rederr(cadena trozos[], int n);
void entorno(cadena trozos[], int n, char *env[]);
void mostrarvar(cadena trozos[],int n, char *env[]);
void cambiarvar(cadena trozos[], int n, char *env[]);
void uid1(cadena trozos[], int n);
void fork1();
void ejec(cadena trozos[], int n);
void ejecprio(cadena trozos[], int n);
void fg(cadena trozos[], int n);
void fgprio(cadena trozos[], int n);
void back(cadena trozos[], int n,tListP *P,char cad[]);
void backprio(cadena trozos[], int n,tListP *P,char cad[]);
void listjobs(tListP *P);
void ejecas(cadena trozos[], int n);
void fgas(cadena trozos[], int n);
void backas(cadena trozos[], int n,tListP *P,char cad[]);
void back1(cadena trozos[], int n,tListP *P,char cad[]);
void fg1(cadena trozos[], int n);

//FUNCIONES QUE NOS DAN:
void MostrarEntorno (char **entorno, char * nombre_entorno);
int BuscarVariable (char * var, char *e[]);
int CambiarVariable(char * var, char * valor, char *e[]);
char * NombreUsuario (uid_t uid);
uid_t UidUsuario (char * nombre);
void MostrarUidsProceso (void);
int CambiarUidLogin1 (char * login);
int CambiarUidLogin2 (char * idlogin);
//FUNCIONES AUXILIARES
void obt_hora1(char hora[]);
#endif