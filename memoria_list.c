/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos
 * AUTHOR 2: Alejandro Ariza Abaña LOGIN 2: alejandro.ariza
 * GROUP: 1.3
 * DATE: 08/04/2021
 */

#include "memoria_list.h"
void createEmptyListM(tListM *L){
    *L= LNULL;
}
bool createNodeM(tPosM *p){

    //si malloc no es capaz de crear la variable porque no hay memoria en el heap y devuelve nulo
    *p= malloc(sizeof(struct tNodeM));
    return *p != NULL;
}
bool insertItemM(tItemM d, tPosM p, tListM* L){

    tPosM q,r;
    if(!createNodeM(&q)){
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
void updateItemM(tItemM d, tPosM p, tListM* L ){
    p->data=d;
}
tPosM findtamM(unsigned long int tam, tListM L){

    //declaramos la variable "p" que recorrerá la lista
    tPosM p;
    for(p=L;(p!=NULL) && (p->data.tam==tam) && (p->data.tipo=MALLOC);p=p->next);
    return p;

}

bool isEmptyListM(tListM L){
    return(L==LNULL);
}
tItemM getItemM(tPosM p, tListM L){
    //aqui ponemos tlista porque para arrays hace falta
    return p->data;//nos devuelve el campo data del elemento apuntado por p
}
tPosM  firstM(tListM L){
    return L;
}
tPosM lastM(tListM L){

    //declaramos "p" que recorerá la lista hasta llegar al último elemento
    tPosM p;
    for(p=L;p->next != LNULL;p = p->next);
    return p;

}
tPosM previousM(tPosM p, tListM L){
    tPosM q;
    if(p==L) { //caso de la 1era posición
        return LNULL;
    }else{
        //se recorre la lista con la variable "p"
        for(q=L;q->next!=p;q=q->next);
        return q;
    }
}
tPosM nextM(tPosM p, tListM L){
    return p->next;
}
void deleteAtPositionM(tPosM p, tListM *L){
    tPosM  q;
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

void imprimir_malloc(tListM M){

    for(tPosM p; p!=NULL; p=nextM(p,M)){
        if(p->data.tipo==MALLOC){
            //printf("%p: size:%ld. malloc %s",p->data.dir_malloc,p->data.tam,p->data.hora);
        }
    }
}

