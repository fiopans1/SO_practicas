/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander,varela@udc.es
 * GROUP: 2.3
 * DATE: 21/09/2021
 */
//LISTA PARA EL HIST
#include "dynamic_list.h"
void createList(tList *L){
    /*objetivo: crear una lista vacía
      entradas: una lista
      salidas: devuelve una lista vacía
      precondiciones: la lista introducida no debe estar inicializada
      postcondiciones: La lista que queda inicializada y no contiene elementos */
    *L= LNULL;
}
bool createNode(tPosL *p){
    /*objetivo: crear una variable dinámica
  entradas: una posición
  salidas: una variable dinámica creada
  */

    //si malloc no es capaz de crear la variable porque no hay memoria en el heap y devuelve nulo
    *p= malloc(sizeof(struct tNode));
    return *p != NULL;
}
bool insertElement(tItemL d, tPosL p, tList* L){
    /*objetivo: Insertar un elemento en la lista
    entradas: un elemento, la posición en la que se desea añadir y la lista
    salidas: devuelve verdadero si la operación fue realizada con exito y falso en caso contrario
    precondiciones: la lista debe estar previamente inicializada
    postcondiciones: la lista se rellena con los datos dados y las posiciones anteriores
     a la del elemento pueden haber variado */

    tPosL q,r;
    if(!createNode(&q)){
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
void updateItem(tItemL d, tPosL p, tList* L ){
    /*objetivo: Actualizar un elemento
  entradas: n elemento, la posición que se desea actualizar y la lista
  salidas: devuelve la lista actualizada
  precondiciones: la lista debe estar previamente inicializada
  */
    p->data=d;
}
tPosL findItem(tNumCode d, tList L){
    /*objetivo: Encontrar la posición de un elemento
  entradas: eL elemento a buscar y una lista
  salidas: devuelve la posición del elemento
  precondiciones: la lista debe estar previamente incializada
  */

    //declaramos la variable "p" que recorrerá la lista
    tPosL p;
    for(p=L;(p!=NULL) && (p->data.numcode!=d);p=p->next);
    return p;

}

bool isEmptyList(tList L){
    /*objetivo: comprobar que la lista esté vacía
  entradas: una lista
  salidas: devuelve verdadero si la lista está vacía, falso en caso contrario
  precondiciones: la lista debe estar previamente inicializada
  */
    return(L==LNULL);
}
tItemL getItem(tPosL p, tList L){
    /*objetivo: Encontrar el elemento de una posición dada
  entradas: una posición y una lista
  salidas: devuelve el objeto de dicha posición
  precondiciones: la lista debe estar previamente inicializada
  */
    //aqui ponemos tlista porque para arrays hace falta
    return p->data;//nos devuelve el campo data del elemento apuntado por p
}
tPosL  first(tList L){
    /*objetivo: devuelver la posición del primer elemento
  entradas: una lista
  salidas: la primera posición
  precondiciones: la lista debe estar previamente inicializada
  */
    return L;
}
tPosL last(tList L){
    /*objetivo: devolver la posición del último elemento
  entradas: una lista
  salidas: la última posición
  precondiciones: la lista debe estar previamente inicializada
  */

    //declaramos "p" que recorerá la lista hasta llegar al último elemento
    tPosL p;
    for(p=L;p->next != LNULL;p = p->next);
    return p;

}
tPosL previous(tPosL p, tList L){
    /*objetivo: facilitar la posición anterior de un elemento
  entradas: una posición y una lista
  salidas: devuelve la posición anterior
  precondiciones: la lista debe estar previamente inicializada
  postcondiciones:si la posición dada es la primera retorna LNULL*/

    tPosL q;
    if(p==L) { //caso de la 1era posición
        return LNULL;
    }else{
        //se recorre la lista con la variable "p"
        for(q=L;q->next!=p;q=q->next);
        return q;
    }
}
tPosL next(tPosL p, tList L){
    /*objetivo: facilitar la posición siguiente de un elemento
  entradas: una posición y una lista
  salidas: devueve la siguiente posición
  precondiciones: la lista debe estar previamente inicializada
  postcondiciones: si la posición dada es la última retorna LNULL*/
    return p->next;
}
void RemoveElement(tPosL p, tList *L){
    /*objetivo: eliminar una posición
  entradas: una posición y una lista
  salidas: devulve la lista sin el elemeno
  precondiciones: la lista debe estar previamente inicializada
  postcondiciones: las posiciones de los elementos de posiciones
  posteriores a la eliminada pueden haber variado*/

    tPosL  q;
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
void deleteList(tList *L){
    tPosL p;
    while(*L != LNULL) {
        p = *L;
        *L = (*L)->next;
        free(p);
    }
}
