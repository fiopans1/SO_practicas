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
    if(n==1){
        if(oldfd!=0){

        }else{

        }
    }else if(n>=2){//FUNCIONA
        if(strcmp(trozos[1],"-reset")==0){//funciona
            close(2);
            dup(oldfd);
            close(oldfd);
        }else{//abrir antes, cerrar stderr y luego hacer el dup FUNCIONA!!!
            /*oldfd=dup(2);
            close(2);
            n1=open (trozos[1],O_WRONLY | O_CREAT | O_APPEND,0600);
            printf("%d\n",n1);*/
            oldfd=dup(STDERR_FILENO);
            close(STDERR_FILENO);
            open (trozos[1],O_WRONLY | O_CREAT | O_APPEND,0600);
            dup(STDERR_FILENO);
            
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
            perror("Con env:");
        }else{
            printf("Con arg3 main: %s(%p) @%p\n", env[pos], env[pos], &env);
        }
        if((pos=BuscarVariable (trozos[1],environ))==-1){
            perror("Con environ:");
            return;
        }else{
            printf("Con environ: %s(%p) @%p\n", environ[pos], environ[pos], &environ);
        }
        if((punt=getenv(trozos[1]))==NULL){
            errno=ENOENT;
            perror("Con getenv");
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
            if ((aux=(char *)malloc(strlen(trozos[2])+strlen(trozos[3])+2))==NULL){
                perror("error");
            }else{
                strcpy(aux,trozos[2]);
                strcat(aux,"=");
                strcat(aux,trozos[3]);
                strcat(aux,"\0");
                if(putenv(aux)==-1){
                    printf(RED "No se pudo cambiar la varible\n" COLOR_RESET);
                }else{
                    printf("Se cambió el valor de %s a %s a través de putenv\n",trozos[2], trozos[3]);
                }
                free(aux);
            }
        }
    }
}
void uid1(cadena trozos[], int n){
    if(n==1){
        MostrarUidsProceso();
    }else if(n>=2){
        if(strcmp(trozos[1],"-get")==0){
            MostrarUidsProceso();
        }else if(strcmp(trozos[1],"-set")==0){
            if(n==2){
                MostrarUidsProceso();
            }else{
                if(n==3){
                    if(strcmp(trozos[2],"-l")==0){
                        MostrarUidsProceso();
                    }else{
                        CambiarUidLogin2(trozos[2]);

                    }
                }else if(n>=4){
                    if(strcmp(trozos[2],"-l")==0){
                        CambiarUidLogin1(trozos[3]);
                    }else{
                        CambiarUidLogin2(trozos[2]);
                    }
                }

            }

        }
    }
}
void fork1(){
    pid_t id;
    if((id=fork())==-1){
        perror("error");
    }else if(id>0){
        waitpid (id,NULL,0);
    }else{
        printf("EJECUTANDO PROCESO %d\n",getpid());
    }
}
void ejec(cadena trozos[], int n){
    if(n>=2){
        cadena argv[n];
        for(int i=1;i<n;i++){
            argv[i-1]=trozos[i];
        }
        argv[n-1]=NULL;
        if(execvp(argv[0], argv)==-1){
            perror("error");
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar\n" COLOR_RESET);
    }
}
/*        id= strtol(trozos[1],NULL,10);
        prio= strtol(trozos[2],NULL,10);
        if(setpriority(PRIO_PROCESS,id,prio)==-1){
            perror("error");
        }else{
            printf("Se estableció la prioridad del proceso %d en %d\n", (int) id, prio);
        }
*/
void ejecprio(cadena trozos[], int n){
    if(n>=3){
        pid_t id=getpid();
        int prio= strtol(trozos[1],NULL,10);
        cadena argv[n-1];
        for(int i=2;i<n;i++){
            argv[i-2]=trozos[i];
        }
        argv[n-2]=NULL;
        if(setpriority(PRIO_PROCESS,id,prio)==-1){
            perror("error");
        }else{
            if(execvp(argv[0], argv)==-1){
                perror("error");
            }
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar y la prioridad\n" COLOR_RESET);
    }
}
void fg(cadena trozos[], int n){//funcion para segundo plano
    if(n>=2){
        pid_t id;
        cadena argv[n];
        for(int i=1;i<n;i++){
            argv[i-1]=trozos[i];
        }
        argv[n-1]=NULL;
        if((id=fork())==-1){
            perror("error");
        }else if(id>0){
            waitpid (id,NULL,0);
        }else if(id==0){
            if(execvp(argv[0], argv)==-1){
                perror("error");
            }
            exit(0);
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar\n" COLOR_RESET);
    }
}
void fg1(cadena trozos[], int n){//funcion para segundo plano
    if(n>=1){
        pid_t id;
        cadena argv[n+1];
        for(int i=0;i<n;i++){
            argv[i]=trozos[i];
        }
        argv[n]=NULL;
        if((id=fork())==-1){
            perror("error");
        }else if(id>0){
            waitpid (id,NULL,0);
        }else if(id==0){
            if(execvp(argv[0], argv)==-1){
                perror("error");
            }
            exit(0);
        }
    }else{
        printf(RED "Introduzca algún comando\n" COLOR_RESET);
    }
}
void fgprio(cadena trozos[], int n){//funcion para segundo plano
        pid_t id;
        int prio= strtol(trozos[1],NULL,10);
        cadena argv[n-1];
        for(int i=2;i<n;i++){
            argv[i-2]=trozos[i];
        }
        argv[n-2]=NULL;
        if((id=fork())==-1){
            perror("error");
        }else if(id>0){
            waitpid (id,NULL,0);
        }else if(id==0){
            if(setpriority(PRIO_PROCESS,id,prio)==-1){
                perror("error");
            }else{            
                if(execvp(argv[0], argv)==-1){
                    perror("error");
                }
                exit(0);
            }
        }
}
void back(cadena trozos[], int n,tListP *P,char cad[]){//funcion para segundo plano
    if(n>=2){
        char * trozos1;
        bool t=false;
        for(int i=0;i<strlen(cad);i++){if(cad[i]==' ' && !t){trozos1=&cad[i];t=true;}}//cambiar por break
        tItemP item;
        pid_t id;
        cadena argv[n];
        for(int i=1;i<n;i++){
            argv[i-1]=trozos[i];
        }
        argv[n-1]=NULL;
        if((id=fork())==-1){
            perror("error");
        }else if(id>0){
            item.pid=id;
            item.prioridad=getpriority(PRIO_PROCESS,id);
            obt_hora1(item.hora);
            strcpy(item.user,NombreUsuario(getuid()));
            item.estado=ACTIVO;
            item.final=000;
            strcpy(item.comando,trozos1);
            insertItemP(item,NULL,P);

        }else if(id==0){
            if(execvp(argv[0], argv)==-1){
                perror("error");
            }
            exit(0);
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar\n" COLOR_RESET);
    }
}
void back1(cadena trozos[], int n,tListP *P,char cad[]){//funcion para segundo plano
    if(n>=2){
        char * trozos1=strtok(cad,"&");
        tItemP item;
        pid_t id;
        cadena argv[n];
        for(int i=0;i<(n-1);i++){
            argv[i]=trozos[i];
        }
        argv[n-1]=NULL;
        if((id=fork())==-1){
            perror("error");
        }else if(id>0){
            item.pid=id;
            item.prioridad=getpriority(PRIO_PROCESS,id);
            obt_hora1(item.hora);
            strcpy(item.user,NombreUsuario(getuid()));
            item.estado=ACTIVO;
            item.final=000;
            strcpy(item.comando,trozos1);
            insertItemP(item,NULL,P);

        }else if(id==0){
            if(execvp(argv[0], argv)==-1){
                perror("error");
            }
            exit(0);
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar\n" COLOR_RESET);
    }
}

void backprio(cadena trozos[], int n,tListP *P,char cad[]){//funcion para segundo plano
    if(n>=3){
        char * trozos1;
        bool t=false;
        int j=0;
        for(int i=0;i<strlen(cad);i++){if(cad[i]==' ' && !t && j==1){trozos1=&cad[i];t=true;}else if(cad[i]==' '){j++;}}//cambiar por break

        tItemP item;
        pid_t id;
        int prio= strtol(trozos[1],NULL,10);
        cadena argv[n-1];
        for(int i=2;i<n;i++){
            argv[i-2]=trozos[i];
        }
        argv[n-2]=NULL;
        if((id=fork())==-1){
            perror("error");
        }else if(id>0){
            item.pid=id;
            item.prioridad=getpriority(PRIO_PROCESS,id);
            obt_hora1(item.hora);
            strcpy(item.user,NombreUsuario(getuid()));
            item.estado=ACTIVO;
            item.final=000;
            strcpy(item.comando,trozos1);
            insertItemP(item,NULL,P);

        }else if(id==0){
            if(setpriority(PRIO_PROCESS,id,prio)==-1){
                perror("error");
            }else{            
                if(execvp(argv[0], argv)==-1){
                    perror("error");
                }
                exit(0);
            }
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar\n" COLOR_RESET);
    }
}
void ejecas(cadena trozos[], int n){
    if(n>=3){
        cadena argv[n-1];
        for(int i=2;i<n;i++){
            argv[i-2]=trozos[i];
        }
        argv[n-2]=NULL;
        if(CambiarUidLogin1(trozos[1])==-1){
            perror("error");
        }else{
            if(execvp(argv[0], argv)==-1){
                perror("error");
            }
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar y el login\n" COLOR_RESET);
    }
}
void fgas(cadena trozos[], int n){//funcion para segundo plano
    if(n>=3){
        pid_t id;
        cadena argv[n-1];
        for(int i=2;i<n;i++){
            argv[i-2]=trozos[i];
        }
        argv[n-2]=NULL;
        if((id=fork())==-1){
            perror("error");
        }else if(id>0){
            waitpid (id,NULL,0);
        }else if(id==0){
            if(CambiarUidLogin1(trozos[1])==-1){
                perror("error");
            }else{            
                if(execvp(argv[0], argv)==-1){
                    perror("error");
                }
                exit(0);
            }
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar y el login\\n" COLOR_RESET);
    }
}
void backas(cadena trozos[], int n,tListP *P,char cad[]){//funcion para segundo plano
    if(n>=3){
        char * trozos1;
        bool t=false;
        int j=0;
        for(int i=0;i<strlen(cad);i++){if(cad[i]==' ' && !t && j==1){trozos1=&cad[i];t=true;}else if(cad[i]==' '){j++;}}//cambiar por break

        tItemP item;
        pid_t id;
        cadena argv[n-1];
        for(int i=2;i<n;i++){
            argv[i-2]=trozos[i];
        }
        argv[n-2]=NULL;
        if((id=fork())==-1){
            perror("error");
        }else if(id>0){
            item.pid=id;
            item.prioridad=getpriority(PRIO_PROCESS,id);
            obt_hora1(item.hora);
            strcpy(item.user,trozos[1]);
            item.estado=ACTIVO;
            item.final=000;
            strcpy(item.comando,trozos1);
            insertItemP(item,NULL,P);

        }else if(id==0){
            if(CambiarUidLogin1(trozos[1])==-1){
                perror("error");
            }else{            
                if(execvp(argv[0], argv)==-1){
                    perror("error");
                }
                exit(0);
            }
        }
    }else{
        printf(RED "Debe poner el nombre del programa a ejecutar\n" COLOR_RESET);
    }
}
void listjobs(tListP *P){
    actualizar_list(P);
    listar_p(*P);
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
    free(aux);
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
int CambiarUidLogin1 (char * login){
    uid_t uid;
    if ((uid=UidUsuario(login))==(uid_t) -1){
        printf("login no valido: %s\n", login);
        return -1;
    }
    if (setuid(uid)==-1){
        printf ("Imposible cambiar credencial: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}
int CambiarUidLogin2 (char * idlogin){
    uid_t uid;
    char *login;
    uid=(uid_t) strtol(idlogin,NULL,10);
    if (strcmp((login=NombreUsuario(uid))," ??????")==0){
        printf("Usuario no valido: %d\n", uid);
        return -1;
    }
    if (setuid(uid)==-1){
        printf ("Imposible cambiar credencial: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}


//FUNCIONES AUXILIARES
void obt_hora1(char hora[]){
    time_t now;
    time(&now);
    strcpy(hora,ctime(&now));
}