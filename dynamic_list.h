/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander.varela@udc.es
 * GROUP: 2.3
 */
//LISTA PARA EL HIST
#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H


#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/* Definicion de tipos */
#define LNULL NULL //DEFINIMOS UN LNULL PORQUE EN EL CODIGO PRINCIPAL NO TIENEN QUE SABER DE QUE MANERA LO IMPLEMENTAMOS
typedef struct tNode *tPosL;//aquí enlazamos unas con otras
typedef int tNumCode;
typedef struct{
    tNumCode numcode;
    char command[200];
}tItemL;

struct tNode {
    tItemL data;
    tPosL next;
};
typedef tPosL tList;
//el último elemento de la lista no tiene next(no apunta a otro, apunta a un nulo el último)

/* prototipos de funciones */
void createList (tList*);
bool insertElement(tItemL, tPosL, tList*);
void updateItem(tItemL, tPosL, tList*);
void RemoveElement(tPosL, tList*);
tPosL findItem(tNumCode, tList);
bool isEmptyList(tList);
tItemL getItem(tPosL, tList);
tPosL first(tList);
tPosL last(tList);
tPosL previous(tPosL, tList);
tPosL next(tPosL, tList);
bool createNode(tPosL *p);
void deleteList(tList *L);

#endif
