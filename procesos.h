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
#include "memoria_list.h"
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAXVAR 256
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"
typedef char *cadena;
int oldfd;
extern char ** environ;


struct SEN{
    char *nombre;
    int senal;
};
/*
static struct SEN sigstrnum[]={
"HUP", SIGHUP,
"INT", SIGINT,
"QUIT", SIGQUIT,
"ILL", SIGILL,
"TRAP", SIGTRAP,
"ABRT", SIGABRT,
"IOT", SIGIOT,
"BUS", SIGBUS,
"FPE", SIGFPE,
"KILL", SIGKILL,
"USR1", SIGUSR1,
"SEGV", SIGSEGV,
"USR2", SIGUSR2,
"PIPE", SIGPIPE,
"ALRM", SIGALRM,
"TERM", SIGTERM,
"CHLD", SIGCHLD,
"CONT", SIGCONT,
"STOP", SIGSTOP,
"TSTP", SIGTSTP,
"TTIN", SIGTTIN,
"TTOU", SIGTTOU,
"URG", SIGURG,
"XCPU", SIGXCPU,
"XFSZ", SIGXFSZ,
"VTALRM", SIGVTALRM,
"PROF", SIGPROF,
"WINCH", SIGWINCH,
"IO", SIGIO,
"SYS", SIGSYS,
//senales que no hay en todas partes
#ifdef SIGPOLL
"POLL", SIGPOLL,
#endif
#ifdef SIGPWR
"PWR", SIGPWR,
#endif
#ifdef SIGEMT
"EMT", SIGEMT,
#endif
#ifdef SIGINFO
"INFO", SIGINFO,
#endif
#ifdef SIGSTKFLT
"STKFLT", SIGSTKFLT,
#endif
#ifdef SIGCLD
"CLD", SIGCLD,
#endif
#ifdef SIGLOST
"LOST", SIGLOST,
#endif
#ifdef SIGCANCEL
"CANCEL", SIGCANCEL,
#endif
#ifdef SIGTHAW
"THAW", SIGTHAW,
#endif
#ifdef SIGFREEZE
"FREEZE", SIGFREEZE,
#endif
#ifdef SIGLWP
"LWP", SIGLWP,
#endif
#ifdef SIGWAITING
"WAITING", SIGWAITING,
#endif
NULL,-1,
}; //fin array sigstrnum
*/
//FUNCIONES:
void priority(cadena trozos[], int n);
void rederr(cadena trozos[], int n);
void entorno(cadena trozos[], int n, char *env[]);
void mostrarvar(cadena trozos[],int n, char *env[]);

//FUNCIONES QUE NOS DAN:
void MostrarEntorno (char **entorno, char * nombre_entorno);
int BuscarVariable (char * var, char *e[]);
int CambiarVariable(char * var, char * valor, char *e[]);
#endif