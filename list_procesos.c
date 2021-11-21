/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander.varela@udc.es
 * GROUP: 2.3
 * DATE: 21/09/2021
 */

#include "list_procesos.h"
void createEmptyListP(tListP *L){
    *L= LNULL;
}
bool createNodeP(tPosP *p){

    //si malloc no es capaz de crear la variable porque no hay memoria en el heap y devuelve nulo
    *p= malloc(sizeof(struct tNodeP));
    return *p != NULL;
}
bool insertItemP(tItemP d, tPosP p, tListP* L){

    tPosP q,r;
    if(!createNodeP(&q)){
        return false;//si no hay memoria para meter el item devuelve false
    }else{
        q->data = d;
        q->next =LNULL;
        if(*L == LNULL){
            *L =q;
        }else if(p==LNULL){//insertar al final de lista no vacia
            for(r=*L; r->next!= LNULL; r=r->next);
            r->next = q;
        }else if(p==*L){ //insertar cabeza, si p apunta al primer elemento de la lista
            q->next =p;//antes p era el primero, y ahora q hacemos que sea el primero diciendo que p sea el siguiente
            *L = q;//y ahora decimos que el contenido de p será el contenido de q
        }else{//insertar en posicion anterior(mirar esta parte)
            q->data =p->data;
            p->data = d;
            q->next = p->next;
            p->next = q;
        }
        return true;
    }
}
void updateItemP(tItemP d, tPosP p, tListP* L ){
    p->data=d;
}

bool isEmptyListP(tListP L){
    return(L==LNULL);
}
tItemP getItemP(tPosP p, tListP L){
    //aqui ponemos tlista porque para arrays hace falta
    return p->data;//nos devuelve el campo data del elemento apuntado por p
}
tPosP  firstP(tListP L){
    return L;
}
tPosP lastP(tListP L){

    //declaramos "p" que recorerá la lista hasta llegar al último elemento
    tPosP p;
    for(p=L;p->next != LNULL;p = p->next);
    return p;

}
tPosP previousP(tPosP p, tListP L){
    tPosP q;
    if(p==L) { //caso de la 1era posición
        return LNULL;
    }else{
        //se recorre la lista con la variable "p"
        for(q=L;q->next!=p;q=q->next);
        return q;
    }
}
tPosP nextP(tPosP p, tListP L){
    return p->next;
}
void deleteAtPositionP(tPosP p, tListP *L){
    tPosP  q;
    if(p==*L) {//borrar 1er elemento
        *L = (*L)->next;
    }else if(p->next == LNULL){ //borrar último elemento
        for(q=*L;q->next!=p;q=q->next);
        q->next = LNULL;
        //es lo mismo que hacer q=previous(q,L);
    }else{//borrar en intermedio
        q=p->next;
        p->data = q->data;
        p->next = q->next;
        p=q;
    }
    //liberaramos la variable
    free(p);
}
void deleteListP(tListP *L){
    tPosP p;
    while(*L != LNULL) {
        p = *L;
        *L = (*L)->next;
        free(p);
    }
}