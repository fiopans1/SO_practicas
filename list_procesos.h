/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander.varela@udc.es
 * GROUP: 2.3
 */

#ifndef __PROCESOS_LIST_
#define __PROCESOS_LIST_


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <pwd.h>
#include <sys/utsname.h>
#define TAM_M 256
#define VACIA 0
#define ERR -1
#define TERM 1
#define SIGNAL 2
#define ACTIVO 0
#define PARADO 1
#define TERMINADO 2
struct SEN{
    char *nombre;
    int senal;
};
/* Definicion de tipos */
#define LNULL NULL //DEFINIMOS UN LNULL PORQUE EN EL CODIGO PRINCIPAL NO TIENEN QUE SABER DE QUE MANERA LO IMPLEMENTAMOS
typedef struct tNodeP *tPosP;//aquí enlazamos unas con otras
typedef int elemento;
typedef struct{
    pid_t pid;
    int prioridad;
    char user[TAM_M];
    char comando[TAM_M];
    char hora[TAM_M];
    int estado;
    int final;
}tItemP;
struct tNodeP {
    tItemP data;
    tPosP next;
};
typedef tPosP tListP;
//el último elemento de la lista no tiene next(no apunta a otro, apunta a un nulo el último)

/* prototipos de funciones */
void createEmptyListP (tListP*);
bool insertItemP(tItemP, tPosP, tListP*);
void updateItemP(tItemP, tPosP, tListP*);
void deleteAtPositionP(tPosP, tListP*);
bool isEmptyListP(tListP);
tItemP getItemP(tPosP, tListP);
tPosP firstP(tListP);
tPosP lastP(tListP);
tPosP previousP(tPosP, tListP);
tPosP nextP(tPosP, tListP);
bool createNodeP(tPosP *p);
void deleteListP(tListP *L);
void actualizar_list(tListP *P);
void listar_p(tListP P);
tPosP findpid(int pid, tListP L);
void listar_item(tItemP item);
void borrarsig(tListP *P);
void borrartem(tListP *P);
#endif
