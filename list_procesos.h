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
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
/* Definicion de tipos */
#define LNULL NULL //DEFINIMOS UN LNULL PORQUE EN EL CODIGO PRINCIPAL NO TIENEN QUE SABER DE QUE MANERA LO IMPLEMENTAMOS
typedef struct tNodeP *tPosP;//aquí enlazamos unas con otras
typedef int elemento;
typedef struct{
    void* dir_malloc;
    int key;
    char nome_ficheiro[256];
    unsigned long int tam;
    char hora[256];
    int tipo;
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
#endif
