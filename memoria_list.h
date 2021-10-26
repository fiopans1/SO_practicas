/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos
 * AUTHOR 2: Alejandro Ariza Abaña LOGIN 2: alejandro.ariza
 * GROUP: 1.3
 * DATE: 08/04/2021
 */

#ifndef __MEMORIA_H_
#define __MEMORIA_H_
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MALLOC 0
#define MMAP 1
#define SHARED 2

/* Definicion de tipos */
#define LNULL NULL //DEFINIMOS UN LNULL PORQUE EN EL CODIGO PRINCIPAL NO TIENEN QUE SABER DE QUE MANERA LO IMPLEMENTAMOS
typedef struct tNodeM *tPosM;//aquí enlazamos unas con otras
typedef int elemento;
typedef struct{
    void* dir_malloc;
    int key;
    char nome_ficheiro[256];
    unsigned long int tam;
    char hora[256];
    int tipo;
}tItemM;
struct tNodeM {
    tItemM data;
    tPosM next;
};
typedef tPosM tListM;
//el último elemento de la lista no tiene next(no apunta a otro, apunta a un nulo el último)

/* prototipos de funciones */
void createEmptyListM (tListM*);
bool insertItemM(tItemM, tPosM, tListM*);
void updateItemM(tItemM, tPosM, tListM*);
void deleteAtPositionM(tPosM, tListM*);
tPosM findtamM(unsigned long int, tListM);
bool isEmptyListM(tListM);
tItemM getItemM(tPosM, tListM);
tPosM firstM(tListM);
tPosM lastM(tListM);
tPosM previousM(tPosM, tListM);
tPosM nextM(tPosM, tListM);
bool createNodeM(tPosM *p);
void deleteListM(tListM *L);
void imprimir_malloc(tListM M);

#endif
