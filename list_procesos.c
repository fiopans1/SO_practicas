/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander.varela@udc.es
 * GROUP: 2.3
 * DATE: 21/09/2021
 */

#include "list_procesos.h"


static struct SEN sigstrnum[] = {
	{"HUP", SIGHUP},
	{"INT", SIGINT},
	{"QUIT", SIGQUIT},
	{"ILL", SIGILL},
	{"TRAP", SIGTRAP},
	{"ABRT", SIGABRT},
	{"IOT", SIGIOT},
	{"BUS", SIGBUS},
	{"FPE", SIGFPE},
	{"KILL", SIGKILL},
	{"USR1", SIGUSR1},
	{"SEGV", SIGSEGV},
	{"USR2", SIGUSR2},
	{"PIPE", SIGPIPE},
	{"ALRM", SIGALRM},
	{"TERM", SIGTERM},
	{"CHLD", SIGCHLD},
	{"CONT", SIGCONT},
	{"STOP", SIGSTOP},
	{"TSTP", SIGTSTP},
	{"TTIN", SIGTTIN},
	{"TTOU", SIGTTOU},
	{"URG", SIGURG},
	{"XCPU", SIGXCPU},
	{"XFSZ", SIGXFSZ},
	{"VTALRM", SIGVTALRM},
	{"PROF", SIGPROF},
	{"WINCH", SIGWINCH},
	{"IO", SIGIO},
	{"SYS", SIGSYS},
	/*senales que no hay en todas partes*/
	#ifdef SIGPOLL
		{"POLL", SIGPOLL},
	#endif

	#ifdef SIGPWR
		{"PWR", SIGPWR},
	#endif

	#ifdef SIGEMT
		{"EMT", SIGEMT},
	#endif

	#ifdef SIGINFO
		{"INFO", SIGINFO},
	#endif

	#ifdef SIGSTKFLT
		{"STKFLT", SIGSTKFLT},
	#endif

	#ifdef SIGCLD
		{"CLD", SIGCLD},
	#endif

	#ifdef SIGLOST
		{"LOST", SIGLOST},
	#endif

	#ifdef SIGCANCEL
		{"CANCEL", SIGCANCEL},
	#endif

	#ifdef SIGTHAW
		{"THAW", SIGTHAW},
	#endif

	#ifdef SIGFREEZE
		{"FREEZE", SIGFREEZE},
	#endif

	#ifdef SIGLWP
		{"LWP", SIGLWP},
	#endif

	#ifdef SIGWAITING
		{"WAITING", SIGWAITING},
	#endif

	{NULL,-1},

};
/*fin array sigstrnum */
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

int Senal1(char * sen) /*devuel el numero de senial a partir del nombre*/ {
	int i;
	for (i=0; sigstrnum[i].nombre!=NULL; i++)
	if (!strcmp(sen, sigstrnum[i].nombre))
	return sigstrnum[i].senal;
	return -1;
}
char *NombreSenal1(int sen) /*devuelve el nombre senal a partir de la senal*/ {
/* para sitios donde no hay sig2str*/
	int i;
	for (i=0; sigstrnum[i].nombre!=NULL; i++)
	if (sen==sigstrnum[i].senal)
	return sigstrnum[i].nombre;
	return ("SIGUNKNOWN");
}


void actualizar_list(tListP *P) {
    tItemP item;
    tPosP pos;
    int id, estado;
    pos=firstP(*P);
    while (pos != NULL) {
        item=getItemP(pos,*P);
        estado = 0;
        if (item.estado != TERMINADO) {item.prioridad = getpriority(PRIO_PROCESS, item.pid);}
        id = waitpid(item.pid, &estado, WNOHANG | WUNTRACED | WCONTINUED);
        if (id == item.pid) {
            if (WIFEXITED(estado)) {
                item.estado = TERMINADO;
                item.final = WEXITSTATUS(estado);
                item.prioridad=-1;
            } else if (WIFSIGNALED(estado)) {
                item.estado = SIGNAL;
                item.final = WTERMSIG(estado);
                item.prioridad=-1;
            } else if (WIFSTOPPED(estado)) {
                item.estado = PARADO;
                item.final = WSTOPSIG(estado);
            } else if (WIFCONTINUED(estado)) {
                item.estado = ACTIVO;
                item.final = SIGCONT;
            } else {
                item.estado = ACTIVO;
                item.final = -1;
            }
        }
        updateItemP(item,pos,P);
        pos=nextP(pos,*P);
    }
    
}
void listar_p(tListP P){
    tItemP item;
    tPosP pos;
    printf("LISTANDO PROCESOS SEGUNDO PLANO:\n");
    pos=firstP(P);
    while (pos != NULL) {
        item=getItemP(pos,P);
            for(int i=0;i<strlen(item.hora);i++){if(item.hora[i]=='\n'){item.hora[i]=' ';}}
            printf("%d %s p=%d %s ",item.pid,item.user,item.prioridad,item.hora);
            if(item.estado==TERMINADO){
                printf("TERMINADO ");
            }else if(item.estado==PARADO){
                printf("PARADO ");
            }else if(item.estado==SIGNAL){
                printf("SIGNAL ");
            }else{
                printf("ACTIVO ");
            }
            printf("(%d) %s\n",item.final, item.comando);
        pos=nextP(pos,P);
    }
}

tPosP findpid(int pid, tListP L){

    //declaramos la variable "p" que recorrerá la lista
    tItemP item;
    tPosP p;
    for(p=L;(p!=NULL);p=p->next){
        item=getItemP(p,L);
        if(item.pid==pid){
            return p;
        }
    }
    
    return p;

}
void listar_item(tItemP item){
    for(int i=0;i<strlen(item.hora);i++){if(item.hora[i]=='\n'){item.hora[i]=' ';}}
    printf("%d %s p=%d %s ",item.pid,item.user,item.prioridad,item.hora);
    if(item.estado==TERMINADO){
        printf("TERMINADO ");
    }else if(item.estado==PARADO){
        printf("PARADO ");
    }else{
        printf("ACTIVO ");
    }
    printf("(%d) %s\n",item.final, item.comando);
}
void borrartem(tListP *P){
    actualizar_list(P);
    tItemP item;
    tPosP pos;
    pos=firstP(*P);
    while (pos != NULL) {
        item=getItemP(pos,*P);
        if(item.estado==TERMINADO){
            pos=deleteynext(pos,P,true);
        }else{
            pos=deleteynext(pos,P,false);
        }
    }
}
void borrarsig(tListP *P){
    actualizar_list(P);
    tItemP item;
    tPosP pos;
    pos=firstP(*P);
    while (pos != NULL) {
        item=getItemP(pos,*P);
        if(item.estado==SIGNAL){
            pos=deleteynext(pos,P,true);
        }else{
            pos=deleteynext(pos,P,false);
        }
    }
}
tPosP deleteynext(tPosP p, tListP *L,bool borrar){
    tPosP  q;
    tPosP  z;
    if(borrar){
        if(p==*L) {//borrar 1er elemento
            *L = (*L)->next;
            z=(*L)->next;
        }else if(p->next == LNULL){ //borrar último elemento
            for(q=*L;q->next!=p;q=q->next);
            q->next = LNULL;
            z=q->next;
            //es lo mismo que hacer q=previous(q,L);
        }else{//borrar en intermedio
            q=p->next;
            p->data = q->data;
            p->next = q->next;
            z=p;
            p=q;
        }
        //liberaramos la variable
        free(p);
        return z;
    }else{
        return p->next;        
    }
}