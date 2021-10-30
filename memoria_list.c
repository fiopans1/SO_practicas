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
void deleteListM(tListM *L){
    tPosM p;
    while(*L != LNULL) {
        p = *L;
        *L = (*L)->next;
        free(p);
    }
}
//funciones especificas:
tPosM findtamM(unsigned long int tam, tListM L){

    //declaramos la variable "p" que recorrerá la lista
    tItemM item;
    tPosM p;
    for(p=L;(p!=NULL);p=p->next){
        item=getItemM(p,L);
        if(item.tam==tam && item.tipo==MALLOC){
            return p;
        }
    }
    
    return p;

}
tPosM findkeyM(int key, tListM L){

    //declaramos la variable "p" que recorrerá la lista
    tItemM item;
    tPosM p;
    for(p=L;(p!=NULL);p=p->next){
        item=getItemM(p,L);
        if(item.key==key && item.tipo==SHARED){
            return p;
        }
    }
    
    return p;

}

tPosM findfichM(char fich[], tListM L){

    //declaramos la variable "p" que recorrerá la lista
    tItemM item;
    tPosM p;
    for(p=L;(p!=NULL);p=p->next){
        item=getItemM(p,L);
        if(strcmp(item.nome_ficheiro,fich)==0 && item.tipo==MMAP){
            return p;
        }
    }
    
    return p;

}
tPosM finddirM(void *dir, tListM L){

    //declaramos la variable "p" que recorrerá la lista
    tItemM item;
    tPosM p;
    for(p=L;(p!=NULL);p=p->next){
        item=getItemM(p,L);
        if(item.dir_malloc==dir){
            return p;
        }
    }
    
    return p;

}

void imprimir_malloc(tListM M){
    tItemM item;
    for(tPosM p=M; p!=NULL; p=nextM(p,M)){
        item=getItemM(p,M);
        if(item.tipo==MALLOC){
            printf("%p: size:%ld. malloc %s\n",item.dir_malloc,item.tam,item.hora);
        }
    }
}
void imprimir_shared(tListM M){
    tItemM item;
    for(tPosM p=M; p!=NULL; p=nextM(p,M)){
        item=getItemM(p,M);
        if(item.tipo==SHARED){
            printf("%p: size:%ld. shared memory (fd:%d) %s\n",item.dir_malloc,item.tam,item.key,item.hora);
        }
    }
}
void imprimir_mmap(tListM M){
    tItemM item;
    for(tPosM p=M; p!=NULL; p=nextM(p,M)){
        item=getItemM(p,M);
        if(item.tipo==MMAP){
            printf("%p: size:%ld. mmap %s (fd:%d) %s\n",item.dir_malloc,item.tam,item.nome_ficheiro,item.key,item.hora);
        }
    }
}
void imprimir_listacompleta(tListM M){
        tItemM item;
    for(tPosM p=M; p!=NULL; p=nextM(p,M)){
        item=getItemM(p,M);
        if(item.tipo==MALLOC){
            printf("%p: size:%ld. malloc %s\n",item.dir_malloc,item.tam,item.hora);
        }else if(item.tipo==SHARED){
            printf("%p: size:%ld. shared memory (fd:%d) %s\n",item.dir_malloc,item.tam,item.key,item.hora);
        }else if(item.tipo==MMAP){
            printf("%p: size:%ld. mmap %s (fd:%d) %s\n",item.dir_malloc,item.tam,item.nome_ficheiro,item.key,item.hora);
        }
    }

}
