/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander.varela@udc.es
 * GROUP: 2.3
 * DATE: 21/09/2021
 */
#include "procesos.h"

//FUNCIONES QUE NOS DAN:
void MostrarEntorno (char **entorno, char * nombre_entorno){
    int i=0;
    while (entorno[i]!=NULL) {
        printf ("%p->%s[%d]=(%p) %s\n", &entorno[i],
            nombre_entorno, i,entorno[i],entorno[i]);
        i++;
    }
}
int BuscarVariable (char * var, char *e[]){
    int pos=0;
    char aux[MAXVAR];

    strcpy (aux,var);
    strcat (aux,"=");

    while (e[pos]!=NULL)
        if (!strncmp(e[pos],aux,strlen(aux)))
            return (pos);
        else
            pos++;
    errno=ENOENT; /*no hay tal variable*/
    return(-1);
}

int CambiarVariable(char * var, char * valor, char *e[]){
    int pos;
    char *aux;
    if ((pos=BuscarVariable(var,e))==-1)
        return(-1);
    if ((aux=(char *)malloc(strlen(var)+strlen(valor)+2))==NULL)
        return -1;
    strcpy(aux,var);
    strcat(aux,"=");
    strcat(aux,valor);
    e[pos]=aux;
    return (pos);
}
//************************************************************************************
char * NombreUsuario (uid_t uid){
    struct passwd *p;
        if ((p=getpwuid(uid))==NULL)
    return (" ??????");
        return p->pw_name;
}
uid_t UidUsuario (char * nombre){
    struct passwd *p;
    if ((p=getpwnam (nombre))==NULL)
        return (uid_t) -1;
    return p->pw_uid;
}
void MostrarUidsProceso (void){
    uid_t real=getuid(), efec=geteuid();
    printf ("Credencial real: %d, (%s)\n", real, NombreUsuario (real));
    printf ("Credencial efectiva: %d, (%s)\n", efec, NombreUsuario (efec));
}
void CambiarUidLogin (char * login){
    uid_t uid;
    if ((uid=UidUsuario(login))==(uid_t) -1){
        printf("loin no valido: %s\n", login);
        return;
    }
    if (setuid(uid)==.1)
        printf ("Imposible cambiar credencial: %s\n", strerror(errno));
}

/*PUEDE SER IMPORTANTE:
if (waitpid (pid,&valor, WNOHANG |WUNTRACED |WIFCONTINUED)==pid){
the integer valor contains info on the status of process pid
}
else {
the integer valor contains NO VALID INFORMATION, process state has not changed
since we last checked 
}*/

/******************************SENALES ******************************************/

int Senal(char * sen){ /*devuel el numero de senial a partir del nombre*/

    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (!strcmp(sen, sigstrnum[i].nombre))
            return sigstrnum[i].senal;
    return -1;
}
char *NombreSenal(int sen){ /*devuelve el nombre senal a partir de la senal*/
 /* para sitios donde no hay sig2str*/
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (sen==sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");
}