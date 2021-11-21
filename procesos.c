/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander.varela@udc.es
 * GROUP: 2.3
 * DATE: 21/09/2021
 */
#include "procesos.h"
//FUNCIONES PRACTICA __PROCESOS

void priority(cadena trozos[], int n){
    pid_t id;
    int prio;
    if(n==1){
        id=getpid();
        if((prio=getpriority(PRIO_PROCESS,id))==-1){
            perror("error");
        }else{
            printf("Prioridad del proceso %d es %d\n", (int) id, prio);
        }
    }else if(n==2){
        id= strtol(trozos[1],NULL,10);
        if((prio=getpriority(PRIO_PROCESS,id))==-1){
            perror("error");
        }else{
            printf("Prioridad del proceso %d es %d\n", (int) id, prio);
        }
    }else if(n>=3){
        id= strtol(trozos[1],NULL,10);
        prio= strtol(trozos[2],NULL,10);
        if(setpriority(PRIO_PROCESS,id,prio)==-1){
            perror("error");
        }else{
            printf("Se estableció la prioridad del proceso %d en %d\n", (int) id, prio);
        }

    }
}
void rederr(cadena trozos[], int n){//PROXIMAMENTE
    int n1;
    if(n==1){
        if(oldfd!=0){

        }else{

        }
    }else if(n>=2){//FUNCIONA
        if(strcmp(trozos[1],"-reset")==0){//funciona
            close(2);
            dup(oldfd);
            close(oldfd);
        }else{//NO FUNCIONA
            oldfd=dup(2);
            close(2);
            n1=open (trozos[1],O_WRONLY | O_CREAT | O_APPEND,0600);
            printf("%d\n",n1);
        }

    }
}
void entorno(cadena trozos[], int n, char *env[]){
    if(n==1){
        MostrarEntorno(env,"main arg3");

    }else if(n>=2){
        if(strcmp(trozos[1],"-environ")==0){
            MostrarEntorno(environ,"env");
        }else if(strcmp(trozos[1],"-addr")==0){
            printf ("===========================================================\n");
            printf("environ: %p (almacenado en %p)\n",environ, &environ);
            printf("main arg3: %p (almacenado en %p)\n",env, &env);
            printf ("===========================================================\n");

        }else{
            printf(RED "Uso: entorno [-environ|-addr]\n" COLOR_RESET);
        }

    }
}
void mostrarvar(cadena trozos[],int n, char *env[]){
    int pos;
    cadena punt;
    if(n==1){
        MostrarEntorno(env,"main arg3");
    }else if(n>=2){
        if((pos=BuscarVariable (trozos[1],env))==-1){
            perror("error");
            return;
        }else{
            printf("Con arg3 main: %s(%p) @%p\n", env[pos], env[pos], &env);
        }
        if((pos=BuscarVariable (trozos[1],environ))==-1){
            perror("error");
            return;
        }else{
            printf("Con environ: %s(%p) @%p\n", environ[pos], environ[pos], &environ);
        }
        if((punt=getenv(trozos[1]))==NULL){
            errno=ENOENT;
            perror("error");
            return;
        }else{
            printf("Con getenv: %s(%p)\n",punt,punt);
        }

    }
}
void cambiarvar(cadena trozos[], int n, char *env[]){
    cadena aux;
    if(n<4){
       printf(RED "Uso: cambiarvar [-a|-e|-p] var valor\n" COLOR_RESET); 
    }else if(n>=4){
        if(strcmp(trozos[1],"-a")==0){
            if(CambiarVariable(trozos[2],trozos[3],env)==-1){
                printf(RED "No se pudo cambiar la varible\n" COLOR_RESET);

            }else{
                printf("Se cambió el valor de %s a %s a través del 3 argumento de main\n",trozos[2], trozos[3]);
            }

        }else if(strcmp(trozos[1],"-e")==0){
            if(CambiarVariable(trozos[2],trozos[3],environ)==-1){
                printf(RED "No se pudo cambiar la varible\n" COLOR_RESET);

            }else{
                printf("Se cambió el valor de %s a %s a través de environ\n",trozos[2], trozos[3]);
            }
        }else if(strcmp(trozos[1],"-p")==0){
                strcpy(aux,trozos[2]);
                strcat(aux,"=");
                strcat(aux,trozos[3]);
                if(putenv(aux)==-1){
                    printf(RED "No se pudo cambiar la varible\n" COLOR_RESET);
                }else{
                    printf("Se cambió el valor de %s a %s a través de environ\n",trozos[2], trozos[3]);
                }
            }
        }
    }
}

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
        printf("login no valido: %s\n", login);
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
/*
int Senal(char * sen){ //devuel el numero de senial a partir del nombre

    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (!strcmp(sen, sigstrnum[i].nombre))
            return sigstrnum[i].senal;
    return -1;
}
char *NombreSenal(int sen){ //devuelve el nombre senal a partir de la senal
 // para sitios donde no hay sig2str
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (sen==sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");
}*/