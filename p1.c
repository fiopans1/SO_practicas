/*
 * TITLE: P0 SISTEMAS OPERATIVOS
 * SUBTITLE: Practica 0
 * AUTHOR 1: Diego Suárez Ramos LOGIN 1: diego.suarez.ramos@udc.es
 * AUTHOR 2: Ander Varela Martin LOGIN 2: ander.varela@udc.es
 * GROUP: 2.3
 * DATE: 21/09/2021
 */


//LIBRERIAS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <time.h>
#include "dynamic_list.c"
#include "dynamic_list.h"
#include <ctype.h> 
#include <errno.h>
#include <sys/file.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

//
//TIPOS DE DATOS Y VARIABLES
#define MAX_PARAM 5
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"
typedef char *cadena;
#define MAX_PALABRAS 200
#define MAX_RUTA 256

//CABECERAS P0
void imprimirPrompt();
void leerEntrada(cadena N);
void procesarEntrada(cadena N,tList *L);
void readtask();
void crearfichero();
void autores(cadena param1, int n);
void pid(cadena param1, int n);
void carpeta(cadena param1, int n);
void fecha(cadena param1, int n);
void infosis();
void hist(cadena param1, tList *L, int n);
void comandoN(cadena param1,tList L, int n);
void ayuda(cadena param1, int n);
int TrocearCadena(char * cadena, char * trozos[]);
//CABECERAS P1
void crear(cadena trozos[], int n);
void listfich(cadena trozos[],int n);
void listdir(cadena trozos[],int n);
void borrar(cadena trozos[],int n);
void borrar_rec(cadena trozos[],int n);



//CABECERAS FUNCIONES AUXILIARES
bool isNumber(cadena param1);
char LetraTF (mode_t m);
char * ConvierteModo2 (mode_t m);
void listar_long(bool acc1, bool link1,bool long1, cadena name);
void directorio();
void recura_directorios(bool long1,bool hid1,bool acc1, bool link1,bool reca1,bool recb1, tList *directorios);
void borrar1_directorios(cadena directorio);


//EMPIEZA EL CODIGO
int main(){
readtask();
return 0;
}
void readtask(){//funcion general
    bool terminado;
    cadena N;
    tList L;
    createList(&L);
    //reservamos memoria para N
    N=malloc(200*sizeof(char));
    terminado=false;
    if(N!=NULL){
    while(!terminado){
        imprimirPrompt();
        leerEntrada(N);
        procesarEntrada(N, &L);
    }
    free(N);
    }else{
        printf(RED "MEMORIA LLENA\n" COLOR_RESET); 
    }
}
void imprimirPrompt(){//imprimimos prompt
    printf(GREEN "<user@udcsystem>" COLOR_RESET);
}
void leerEntrada(cadena N){//leemos el stdin
    char error[100];
    fflush(stdin);
    if(fgets(N,200,stdin)==NULL){
        perror( error );
    }
    fflush(stdin);
}
void procesarEntrada(cadena N, tList *L){//procesamos la entrada
    //COSAS DE LISTA Y VARIABLES
    tItemL informacion;
    char *trozos[MAX_PALABRAS];//reservamos memoria par 200 palabras, si se introducen mas de 200 el programa peta
    char N2[200];
    int n;


    //VAMOS A TROCEAR COMANDO
    strcpy(N2,N);
    n=TrocearCadena(N,trozos);
   if(n>=1){
        //VAMOS A GUARDAR COMANDO EN HISTORIAL
        if(strcmp(trozos[0],"comando")!=0){
            strcpy(informacion.command,N2);
            if(isEmptyList(*L)){
                informacion.numcode=0;
            }else{
                informacion.numcode=getItem(last(*L),*L).numcode+1;
            }
            if(!(insertElement(informacion,LNULL,L))){
                printf(RED "El comando no se pudo guardar en el historial\n" COLOR_RESET); 
            }
        }
        

        //VAMOS A ELEGIR COMANDO:
        
            if(strcmp(trozos[0],"autores")==0){ //AUTORES
                if(n==2){
                    autores(trozos[1],n);
                }else if(n==1){
                    autores(NULL,n);
                }else{
                   printf(RED "This command doesn't exist\n" COLOR_RESET); 
                }
            }else if(strcmp(trozos[0],"pid")==0){ //PID
                if(n==2){
                    pid(trozos[1],n);
                }else if(n==1){
                    pid(NULL,n);
                }else{
                   printf(RED "This command doesn't exist\n" COLOR_RESET); 
                }
            }else if(strcmp(trozos[0],"carpeta")==0){ //CARPETA
                if(n==2){
                    carpeta(trozos[1],n);
                }else if(n==1){
                    carpeta(NULL,n);
                }else{
                   printf(RED "This command doesn't exist\n" COLOR_RESET); 
                }
            }else if(strcmp(trozos[0],"fecha")==0){ //FECHA
                if(n==2){
                    fecha(trozos[1],n);
                }else if(n==1){
                    fecha(NULL,n);
                }else{
                   printf(RED "This command doesn't exist\n" COLOR_RESET); 
                }
            }else if(strcmp(trozos[0],"hist")==0){ //HIST
                if(n==2){
                    hist(trozos[1],L,n);
                }else if(n==1){
                    hist(NULL,L,n);
                }else{
                   printf(RED "This command doesn't exist\n" COLOR_RESET); 
                }
            }else if(strcmp(trozos[0],"comando")==0){ //COMANDO
                if(n==2){
                    comandoN(trozos[1],*L,n);
                }else if(n==1){
                    comandoN(NULL,*L,n);
                }else{
                   printf(RED "This command doesn't exist\n" COLOR_RESET); 
                }
            }else if(strcmp(trozos[0],"infosis")==0){ //INFOSIS
                if(n==1){
                    infosis();
                }else{
                   printf(RED "This command doesn't exist\n" COLOR_RESET); 
                }
                
            }else if(strcmp(trozos[0],"ayuda")==0){ //AYUDA
                if(n==2){
                    ayuda(trozos[1],n);
                }else if(n==1){
                    ayuda(NULL,n);
                }else{
                   printf(RED "This command doesn't exist\n" COLOR_RESET); 
                }
            }else if(strcmp(trozos[0],"salir")==0 || strcmp(trozos[0],"fin")==0 || strcmp(trozos[0],"bye")==0){ //SALIR
                for(int i=0;i<n;i++){
                    free(trozos[i]);
                }
                deleteList(L);
                exit(1);
            }else if(strcmp(trozos[0],"crear")==0){
                crear(trozos,n);

            }else if(strcmp(trozos[0],"borrar")==0){
                borrar(trozos,n);
            }else if(strcmp(trozos[0],"borrarrec")==0){
                borrar_rec(trozos,n);
            }else if(strcmp(trozos[0],"listfich")==0){
                listfich(trozos,n);
            }else if(strcmp(trozos[0],"listdir")==0){
                listdir(trozos,n);
            }else{
                printf(RED "This command doesn't exist\n" COLOR_RESET);
            }
    }
}
int TrocearCadena(char * cadena, char * trozos[]){ //troceamos la cadena en palabras
    int i=1;
    if ((trozos[0]=strtok(cadena," \n\t"))==NULL){
        return 0;
    }
    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL){
        i++;
        
    }
        
    return i;
}

//P0
void autores(cadena param1, int n){                //AUTORES
     if(n==1 && param1==NULL){//imprimimos solo autores
        puts("********************");
        puts("NOMBRE Y LOGIN DE LOS AUTORES:");
        puts("-> Diego Suarez Ramos: diego.suarez.ramos@udc.es");
        puts("-> Ander Varela Martin: ander.varela@udc.es");
        puts("********************"); 
     }else  if(strcmp("-l",param1)==0){//imprimimos autores -l
        puts("********************");
        puts("LOGIN DE LOS AUTORES:");
        puts("-> diego.suarez.ramos@udc.es");
        puts("-> ander.varela@udc.es");
        puts("********************");
    }else if(strcmp("-n",param1)==0){//imprimimos autores -l
        puts("********************");
        puts("NOMBRE DE LOS AUTORES");
        puts("-> Diego Suarez Ramos");
        puts("-> Ander Varela Martin");
        puts("********************");
    }else{
        printf(RED "This command doesn't exist\n" COLOR_RESET);
    }
}
void pid(cadena param1,int n){                     //PID
    pid_t id;
    if(n==1 && param1==NULL){//imprimimos pid
        id=getpid();//esta funcion nunca falla
        puts("********************");
        printf("-> El pid del shell es: %d\n", id);
        puts("********************");
    }else if(strcmp(param1,"-p")==0){//imprimimos pid padre
        id=getppid();//esta funcion nunca falla
        puts("********************");
        printf("-> El pid del padre del shell es: %d\n",id);
        puts("********************");
    }else{
        printf(RED "This command doesn't exist\n" COLOR_RESET);
    }
}
void carpeta(cadena param1,int n){                 //CARPETA
    char error[100];

    if(n==1 && param1==NULL){//obtenemos carpeta
        directorio();
    }else if(n==2){//cambiamos carpeta
        if(chdir(param1)!=0){
          perror( error );   
        }
    }else{
        printf(RED "This command doesn't exist\n" COLOR_RESET);
    }
}
void fecha(cadena param1, int n){                  //FECHA
    time_t tiempo = time(0);
    char error[100];
    struct tm *tiempolocal;
    char time[50];
    tiempolocal = localtime(&tiempo);
    if(tiempolocal==NULL){
        perror( error );
    }else{
        if(n==1 && param1==NULL){//fecha
            strftime(time,50,"%d/%m/%y %H:%M:%S",tiempolocal);
            puts("********************");
            printf("-> %s\n",time);
            puts("********************");
        }else if(strcmp(param1,"-d")==0){//fecha -d
        
            strftime(time,50,"%d/%m/%y",tiempolocal);
            puts("********************");
            printf("-> %s\n",time);
            puts("********************");
        }else if(strcmp(param1,"-h")==0){//fecha -h
        
            strftime(time,50,"%H:%M:%S",tiempolocal);
            puts("********************");
            printf("-> %s\n",time);
            puts("********************");
        }else{
            printf(RED "This command doesn't exist\n" COLOR_RESET);
        }
    }
}
void hist(cadena param1, tList *L, int z) {        //HIST
    tPosL p;
    tItemL items;
    tNumCode n;

    puts("********************");
    if(z==1 && param1==NULL){//hist
        if (!isEmptyList(*L)) {//miramos si el historial esta vacio o no
            p = first(*L);
            //recorremos la lista monstrando los datos y actualizando contadores
            while (p != LNULL) {
                items = getItem(p, *L);
                printf("%d - %s\n", items.numcode, items.command);
                p = next(p, *L);
            }
        }else{
            puts("Historial vacio");
        }
    }else if (strcmp("-c", param1) == 0) {//hist -cincludePa
        deleteList(L); //borramos historial
        puts("Historial borrado");


    } else if (isNumber(param1)) {//necesitamos ver que sea numero hist N
        tPosL pos;
        n= (tNumCode) strtol(param1, NULL, 10);
        pos=findItem(n,*L);
        if(pos!=LNULL){
        items= getItem(pos,*L);
        printf("%d - %s\n", items.numcode, items.command);
        }else{
            printf(RED "No se encontro el comando en el historial\n" COLOR_RESET);
        }

    }else{
        printf(RED "Error con el historial\n" COLOR_RESET);
    }
    puts("********************");
}
void comandoN(cadena param1,tList L, int z){       //COMANDO N
    if(z==2 && isNumber(param1)){//comando N
    //tPosL p;
    tItemL items;
    tNumCode n;
    tPosL pos;
    n= (tNumCode) strtol(param1, NULL, 10);
    pos=findItem(n,L);
        if(pos!=LNULL){
            items= getItem(pos,L);
            printf("%d - %s\n", items.numcode, items.command);
            procesarEntrada(items.command, &L);
        }else{
            printf(RED "-> No se encontro el comando en el historial\n" COLOR_RESET);
        }
    }else{
        printf(RED "This command doesn't exist\n" COLOR_RESET);
    }

}
void infosis() {               //INFOSIS
        struct utsname uts;

        if (uname(&uts) < 0)//caso error
            perror("uname() error");
        else{//infosis
            puts("********************");
            printf("Sysname:  %s\n", uts.sysname);
            printf("Nodename: %s\n", uts.nodename);
            printf("Release:  %s\n", uts.release);
            printf("Version:  %s\n", uts.version);
            printf("Machine:  %s\n", uts.machine);
            puts("********************");
        }

}
void ayuda(cadena param1, int n){    //terminar de añadir las nuevas funciones              //AYUDA

    puts("********************");
    if(n==1 && param1==NULL) {//ayuda general

       puts("->'ayuda [cmd]' donde cmd es uno de los siguientes comandos:\nfin\tsalir\tbye\tcarpeta\tpid\n\nautores\thist\tcomando\tfecha\ninfosis\tayuda");

    }else if(n==2){//ayuda especifico
        if(strcmp(param1,"autores")==0){
            printf("autores [-n|-l]	Muestra los nombres y logins de los autores\n");

        }else if(strcmp(param1,"pid")==0){
            printf("pid [-p]	Muestra el pid del shell o de su proceso padre\n");
        }else if(strcmp(param1,"carpeta")==0){
            printf("carpeta [dir]	Cambia (o muestra) el directorio actual del shell\n");
        }else if(strcmp(param1,"fecha")==0){
            printf("fecha [-d|-h]	Muestra la fecha y o la hora actual\n");
        }else if(strcmp(param1,"hist")==0){
            printf("hist [-c|-N]	Muestra el historico de comandos, con -c lo borra\n");
        }else if(strcmp(param1,"comando")==0){
            printf("comando [-N]	Repite el comando N (del historico)\n");
        }else if(strcmp(param1,"infosis")==0){
            printf("infosis 	Muestra informacion de la maquina donde corre el shell");
        }else if(strcmp(param1,"ayuda")==0){
            printf("ayuda [cmd]	Muestra ayuda sobre los comandos\n");
        }else if(strcmp(param1,"salir")==0 || strcmp(param1,"fin")==0 || strcmp(param1,"bye")==0){
            printf("bye/salir/fin 	Termina la ejecucion del shell\n");

        }else{
            printf(RED "This command doesn't exist\n" COLOR_RESET);
        }
    }else{
        printf(RED "This command doesn't exist\n" COLOR_RESET);
    }
    puts("********************");
}


//P1
void crear(cadena trozos[], int n){//declararlo de manera 
    char error[100];
    struct stat st;
    int fd;//puntero que apunta a la direccion del fichero
    //FILE *fd;
    if(n==1){//obtenemos carpeta
        directorio();
    }else if(n==2 && strcmp(trozos[1],"-f")!=0){
        if(stat(trozos[1], &st)== -1){
            if(mkdir(trozos[1],0700)==-1){//el 0700 es para darle los permisos
                perror( error );
            }
        }else{
            printf(RED "Ese directorio ya existe\n" COLOR_RESET);
        }
    }else if(n==3 && strcmp(trozos[1],"-f")==0){
        fd=open(trozos[2],O_CREAT, 0700);
        if(fd==-1){
            perror( error );
        }
        /*fd=fopen(trozos[2], "w");//nose si será esta función o otro tipo, mejor preguntar
        if(fd==NULL){
            perror( error );
        }
        fclose(fd);  */  
    }else{
        printf(RED "This command doesn't exist\n" COLOR_RESET);
    }
}
void borrar(cadena trozos[],int n){
    if(n==1){
        directorio();
    }else if(n>1){
        struct stat *st=malloc(sizeof(struct stat));
        char error[100];

        for(int i=1; i<n && i<MAX_PALABRAS; i++){
            lstat (trozos[i], st);

            if(S_ISDIR (st->st_mode)){//miramos si es directorio
                
                /*if(st.st_size==0){
                    rmdir(trozos[i]);
                    puts("The directory has been deleted");
                }*/ //No funciona
                
                if(rmdir(trozos[i])==0){
                    puts("********************");
                    printf("-> The directory '%s' has been deleted\n", trozos[i]);
                    puts("********************");
                }else{
                    puts("********************");
                    perror( error );
                    printf("-> No se ha podido borrar '%s'\n", trozos[i]);
                    puts("********************");
                }
            }else{
                if(S_ISREG (st->st_mode) || S_ISLNK (st->st_mode)){
                    if(unlink(trozos[i])==0){
                        puts("********************");
                        printf("-> The file '%s' has been deleted\n", trozos[i]);
                        puts("********************");
                    }else{
                        puts("********************");
                        perror( error );
                        printf("-> No se ha podido borrar '%s'\n", trozos[i]);
                        puts("********************");
                    }
                }else{
                    puts("********************");
                    printf("-> '%s' is not a file or a directory\n", trozos[i]);
                    puts("********************");
                }
            }

        }
        free(st);
    }else{
        printf(RED "This command doesn't exist\n" COLOR_RESET);

    }
    
}
void listfich(cadena trozos[],int n){
    //VARIABLES
    bool long1=false, link1=false, acc1=false;
    tList M;
    tItemL nombres, items;
    tPosL p;
    //CODIGO
    if(n==1){
        directorio();
    }else if(n>1){
        createList(&M);
        //hacer lo de la parte anterior de manera bucle
        for(int i=1;i<n && i<MAX_PALABRAS;i++){//nos aseguramos que nunca se pase del numero maximo de palabras
            if(strcmp(trozos[i],"-long")==0){
                long1=true;
            }else if(strcmp(trozos[i],"-link")==0){
                link1=true;
            }else if(strcmp(trozos[i],"-acc")==0){
                acc1=true;
            }else{

                strcpy(nombres.command,trozos[i]);
                if(isEmptyList(M)){
                    nombres.numcode=0;
                }else{
                    nombres.numcode=getItem(last(M),M).numcode+1;
                }
                if(!(insertElement(nombres,LNULL,&M))){
                    printf(RED "MEMORIA LLENA PARA INTRODUCIR EN LISTA\n" COLOR_RESET); 
                }
                    
            }
        }
            if (!isEmptyList(M)) {//miramos si el historial esta vacio o no
                p = first(M);
                //recorremos la lista monstrando los datos y actualizando contadores
                while (p != LNULL) {
                    items = getItem(p, M);
                    listar_long(acc1,link1,long1,items.command);//lista el fichero

                    p = next(p, M);
                }
            }
        deleteList(&M);
        

    }else{
        printf(RED "Opción no valida\n" COLOR_RESET);
    }
    //free(st);
}
void listdir(cadena trozos[],int n){//hacer que funcione -hid y dejarlo bonito(y poner lo de reca y recb)
    char ruta[MAX_RUTA];
    char ruta_actual[MAX_RUTA];
    char error[100];
    struct stat *st=malloc(sizeof(struct stat));//preguntar como es que entra memoria ya reservada para st
    bool long1=false, link1=false, acc1=false, reca1=false, recb1=false, hid1=false;
    tList dirs,ficheros,M;
    tItemL nombres, items, Ificheros;
    tPosL p,q;
    DIR *dir;
    struct dirent *rdir;
    //CODIGO
    if(n==1){
        directorio();
    }else if(n>1){
        getcwd(ruta,MAX_RUTA);
        createList(&ficheros);
        createList(&dirs);
        createList(&M);
        //hacer lo de la parte anterior de manera bucle
        for(int i=1;i<n && i<MAX_PALABRAS;i++){//nos aseguramos que nunca se pase del numero maximo de palabras
            if(strcmp(trozos[i],"-long")==0){
                long1=true;
            }else if(strcmp(trozos[i],"-link")==0){
                link1=true;
            }else if(strcmp(trozos[i],"-acc")==0){
                acc1=true;
            }else if(strcmp(trozos[i],"-reca")==0){
                reca1=true;
            }else if(strcmp(trozos[i],"-recb")==0){
                recb1=true;
            }else if(strcmp(trozos[i],"-hid")==0){
                hid1=true;
            }else{
                if(lstat(trozos[i],st)==-1){
                    perror( error );
                }else{
                //*********************************************ALMACENADO******************************+
                    if(S_ISDIR (st->st_mode)){//miramos si es directorio y guardamos en lista de directorios
                        strcpy(nombres.command,trozos[i]);
                        if(isEmptyList(dirs)){
                            nombres.numcode=0;
                        }else{
                            nombres.numcode=getItem(last(dirs),dirs).numcode+1;
                        }
                            if(strncmp(trozos[i],".",1)!=0 || (hid1 || strncmp(trozos[i],"./",2)==0)){
                            if(!(insertElement(nombres,LNULL,&dirs))){
                                printf(RED "MEMORIA LLENA PARA INTRODUCIR EN LISTA DE DIRECTORIOS\n" COLOR_RESET); 
                            }
                            }
                        
                     
                    }else if(S_ISREG (st->st_mode) || S_ISLNK (st->st_mode)){//sino miramos si es un fichero y guardamos en lista de ficheros
                        strcpy(nombres.command,trozos[i]);
                        if(isEmptyList(ficheros)){
                            nombres.numcode=0;
                        }else{
                            nombres.numcode=getItem(last(ficheros),ficheros).numcode+1;
                        }
                        if(strncmp(trozos[i],".",1)!=0 || (hid1 || strncmp(trozos[i],"./",2)==0)){
                            if(!(insertElement(nombres,LNULL,&ficheros))){
                                printf(RED "MEMORIA LLENA PARA INTRODUCIR EN LISTA DE FICHEROS\n" COLOR_RESET); 
                            } 
                        }
                        


                    }else{
                        printf(RED "Lo introducido no es ni fichero ni directorio\n" COLOR_RESET); 
                                        
                    }
                    //almacenamos para el método no recursivo
                    strcpy(nombres.command,trozos[i]);
                    if(isEmptyList(M)){
                    nombres.numcode=0;
                    }else{
                    nombres.numcode=getItem(last(M),M).numcode+1;
                    }
                    if(strncmp(trozos[i],".",1)!=0 || (hid1 || strncmp(trozos[i],"./",2)==0)){
                        if(!(insertElement(nombres,LNULL,&M))){
                        printf(RED "MEMORIA LLENA PARA INTRODUCIR EN LISTA\n" COLOR_RESET); 
                        }
                    }
                   //*********************************************ALMACENADO******************************+

                    
            }
        }
        }
        if((reca1==true || recb1==true) && reca1!=recb1){
            if(reca1){
            if (!isEmptyList(ficheros)) {//miramos si el historial esta vacio o no
                q = first(ficheros);
                //recorremos la lista monstrando los datos y actualizando contadores
                while (q != LNULL) {
                    Ificheros = getItem(q, ficheros);
                    listar_long(acc1,link1,long1,Ificheros.command);//lista el fichero

                    q = next(q, ficheros);
                }
            } 
            //***********************************
            if(!isEmptyList(dirs)){                                            
                recura_directorios(long1,hid1,acc1,link1,reca1,recb1,&dirs);  
                            
            } 
            }else if(recb1){
                if(!isEmptyList(dirs)){                                            
                recura_directorios(long1,hid1,acc1,link1,reca1,recb1,&dirs);  
                            
                }
                //***********************************
                if (!isEmptyList(ficheros)) {//miramos si el historial esta vacio o no
                    q = first(ficheros);
                    //recorremos la lista monstrando los datos y actualizando contadores
                    while (q != LNULL) {
                        Ificheros = getItem(q, ficheros);
                        listar_long(acc1,link1,long1,Ificheros.command);//lista el fichero

                        q = next(q, ficheros);
                    }
                }   
            }

        }else if(reca1==true && recb1==true){
          printf(RED "No puedes activar -reca y -recb a la vez\n" COLOR_RESET);   
        }else{//caso no reca ni recb
            if (!isEmptyList(M)) {//miramos si el historial esta vacio o no
                p = first(M);
                //recorremos la lista monstrando los datos y actualizando contadores
                while (p != LNULL) {
                    items = getItem(p, M); 
                    listar_long(acc1,link1,long1,items.command);
                    if(S_ISDIR (st->st_mode)){
                        dir=opendir(items.command);
                        getcwd(ruta_actual,MAX_RUTA);
                        strcpy(ruta_actual,"/");
                        strcpy(ruta_actual,items.command);
                        if(chdir(ruta_actual)==0){
                            printf("+++++++++++++++++++++++++ABRIENDO %s+++++++++++++++++++++++++++++++++\n", items.command);
                            if(dir==NULL){
                                perror( error );
                            }else{

                            while((rdir = readdir(dir)) != NULL){
                                if(strncmp(rdir->d_name,".\0",2)!=0 && strncmp(rdir->d_name,"..\0",3)!=0){
                                    if(strncmp(rdir->d_name,".",1)!=0 || (hid1 || strncmp(rdir->d_name,"./",2)==0)){
                                        listar_long(acc1,link1,long1,rdir->d_name);
                                    }
                                }                            
                            } 
                            closedir(dir);

                            } 
                        printf("+++++++++++++++++++++++++CERRANDO %s+++++++++++++++++++++++++++++++++\n", items.command);  
                        }

                    }

                    p = next(p, M);
                }
            }


        }
        chdir(ruta);
        deleteList(&M);
        deleteList(&ficheros);
        deleteList(&dirs);
    }
    free(st);
    
    
}
void borrar_rec(cadena trozos[],int n){
    char error[200];
    struct stat *st=malloc(sizeof(struct stat));

    if(n==1){
        directorio();
    }else if(n>1){
        for(int i=1; i<n && i<MAX_PALABRAS;i++){
            if(lstat(trozos[i],st)==-1){
                perror( error );
            }else{
                if(S_ISDIR (st->st_mode)){
                    if(strncmp(trozos[i],".\0",2)!=0 && strncmp(trozos[i],"..\0",3)!=0){
                        borrar1_directorios(trozos[i]);
                    }
                }else if(S_ISREG (st->st_mode) || S_ISLNK (st->st_mode)){
                    if(unlink(trozos[i])!=0){
                        perror( error );
                    }
                }else{

                }
            }
        }
    }
    free(st);
}


//FUNCIONES AUXILIARES
void recura_directorios(bool long1,bool hid1,bool acc1, bool link1,bool reca1,bool recb1, tList *directorios){//POÑER BEN O MOSTRAR(A RECURSIVIDAD FUNCION BEN)
    //VARIABLES
    char error[200];
    //char ruta_actual[MAX_RUTA];
    char ruta[MAX_RUTA];//sino para recorrer recursivamente el directorio dirá que no lo encuentra
    DIR *dir;
    struct dirent *rdir;
    struct stat *st=malloc(sizeof(struct stat));
    tItemL nombres, items, Ificheros;
    tPosL p,q;
    tList ficheros, dirs;
    //CODIGO
    //con esto hacer un bucle y mirar bien como es 
        if(!isEmptyList(*directorios)){
            getcwd(ruta,MAX_RUTA);
            p = first(*directorios);
            while (p != LNULL) {//recorremos la lista de directorios cada directorio
                createList(&ficheros);
                createList(&dirs);
                items = getItem(p, *directorios);
                listar_long(acc1,link1,long1,items.command);
                printf("+++++++++++++++++++++++++ABRIENDO %s+++++++++++++++++++++++++++++++++\n", items.command);
                dir=opendir(items.command); 
                    
                    if(dir==NULL){
                        perror( error );
                    }else{

                        if(chdir(items.command) == 0){
                        while((rdir = readdir(dir)) != NULL){
                        
                            if(strncmp(rdir->d_name,".\0",2)!=0 && strncmp(rdir->d_name,"..\0",3)!=0){

                                if(lstat(rdir->d_name,st)==-1){
                                    perror( error );
                                }else{
                                    //*********************************************ALMACENADO******************************+
                                    if(S_ISDIR (st->st_mode)){//miramos si es directorio y guardamos en lista de directorios
                                        strcpy(nombres.command,rdir->d_name);
                                        if(isEmptyList(dirs)){
                                            nombres.numcode=0;
                                        }else{
                                            nombres.numcode=getItem(last(dirs),dirs).numcode+1;
                                        }
                                        if(strncmp(rdir->d_name,".\0",2)!=0 && strncmp(rdir->d_name,"..\0",3)!=0){
                                            if(strncmp(rdir->d_name,".",1)!=0 || (hid1 || strncmp(rdir->d_name,"./",2)==0)){

                                            if(!(insertElement(nombres,LNULL,&dirs))){
                                                printf(RED "MEMORIA LLENA PARA INTRODUCIR EN LISTA DE DIRECTORIOS\n" COLOR_RESET); 
                                            }
                                            }
                                        }
                                     
                                    }else if(S_ISREG (st->st_mode) || S_ISLNK (st->st_mode)){//sino miramos si es un fichero y guardamos en lista de ficheros
                                        strcpy(nombres.command,rdir->d_name);
                                        if(isEmptyList(ficheros)){
                                            nombres.numcode=0;
                                        }else{
                                            nombres.numcode=getItem(last(ficheros),ficheros).numcode+1;
                                        }
                                        if(strncmp(rdir->d_name,".",1)!=0 || (hid1 || strncmp(rdir->d_name,"./",2)==0)){
                                            if(!(insertElement(nombres,LNULL,&ficheros))){
                                                printf(RED "MEMORIA LLENA PARA INTRODUCIR EN LISTA DE FICHEROS\n" COLOR_RESET); 
                                            } 
                                        }
                                        


                                    }else{
                                        printf(RED "Lo introducido no es ni fichero ni directorio\n" COLOR_RESET); 
                                        
                                    }
                                        //*********************************************ALMACENADO******************************+
                                    
                                }
                            }
                        }
                        }
                        closedir(dir);
                    }   

            //recura
        if(reca1){
            //***********************************
            if (!isEmptyList(ficheros)) {//miramos si el historial esta vacio o no
                q = first(ficheros);
                //recorremos la lista monstrando los datos y actualizando contadores
                while (q != LNULL) {
                    Ificheros = getItem(q, ficheros);
                    listar_long(acc1,link1,long1,Ificheros.command);//lista el fichero

                    q = next(q, ficheros);
                }
            }  
            //***********************************
            if(!isEmptyList(dirs)){                                            
                recura_directorios(long1,hid1,acc1,link1,reca1,recb1,&dirs);  
                            
            }
        }else if(recb1){
            if(!isEmptyList(dirs)){                                            
            recura_directorios(long1,hid1,acc1,link1,reca1,recb1,&dirs);  
                        
            }
            //***********************************
            if (!isEmptyList(ficheros)) {//miramos si el historial esta vacio o no
                q = first(ficheros);
                //recorremos la lista monstrando los datos y actualizando contadores
                while (q != LNULL) {
                    Ificheros = getItem(q, ficheros);
                    listar_long(acc1,link1,long1,Ificheros.command);//lista el fichero

                    q = next(q, ficheros);
                }
            } 
        }
        //recurb
        chdir(ruta);
        deleteList(&ficheros);
        deleteList(&dirs);
        printf("+++++++++++++++++++++++++CERRANDO %s+++++++++++++++++++++++++++++++++\n", items.command);
        p = next(p, *directorios);
        }
        free(st);
    }//falta mirar lo de las rutas a ver como hacer
}
void directorio(){//lista directorio actual
    char dir[200];
    char error[100];
    if(getcwd(dir, sizeof(dir))==NULL){
        perror( error );  
    }else{
        printf(BLUE "%s\n", dir);
    }    

}
bool isNumber(cadena param1) {//funcion para comprobar si una cadena es un numero
    int cnt=0;
    for(int i=0; i<strlen(param1); i++){
        if (isdigit(param1[i]))
            cnt++;
    }
    if(cnt == strlen(param1)) {
        return true;
    }
    else {
        return false;
    }
}
char LetraTF (mode_t m){
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }   
}
char * ConvierteModo2 (mode_t m){
static char permisos[12];
strcpy (permisos,"---------- ");
permisos[0]=LetraTF(m);//mira el tipo de fichero
if (m&S_IRUSR) permisos[1]='r'; /*propietario*/
if (m&S_IWUSR) permisos[2]='w';
if (m&S_IXUSR) permisos[3]='x';
if (m&S_IRGRP) permisos[4]='r'; /*grupo*/
if (m&S_IWGRP) permisos[5]='w';
if (m&S_IXGRP) permisos[6]='x';
if (m&S_IROTH) permisos[7]='r'; /*resto*/
if (m&S_IWOTH) permisos[8]='w';
if (m&S_IXOTH) permisos[9]='x';
if (m&S_ISUID) permisos[3]='s'; /*setuid, setgid y stickybit*/
if (m&S_ISGID) permisos[6]='s';
if (m&S_ISVTX) permisos[9]='t';
return (permisos);
}
void listar_long(bool acc1, bool link1,bool long1, cadena name){//lista datos del directorio
    char error[100];
    struct stat *st=malloc(sizeof(struct stat));//preguntar como es que entra memoria ya reservada para st
    struct tm *fecha;
    struct passwd *usr;
    struct group *grp;
    char time[50];
    char link[200];
    char* perm;
    if(long1){
        if(lstat(name,st)==-1){
            perror( error );
        }else{
    
            usr=getpwuid(st->st_uid);
            if(usr!=NULL){//comprobamos que se obtiee el user bien
                grp=getgrgid(st->st_gid);
                if(grp!=NULL){//comprobamos que se obtiene el grp bien
                    if(acc1){//convertimos las fechas a un formato accesible con la funcion localtime
                        fecha=localtime(&st->st_atime);//separamos el formato time_t en el struct tm
                        strftime(time,50,"%y/%m/%d-%H:%M:%S",fecha);//elegimos camposd e tm
                        printf("%s ", time);//imprimimos tm
                    }else{
                        fecha=localtime(&st->st_mtime);
                        strftime(time,50,"%y/%m/%d-%H:%M:%S",fecha);
                        printf("%s ", time);
                    } 
                    //listfich -long -acc -link dynamic_list.h p0.c dynamic_list.c prueba pad
                    perm=ConvierteModo2(st->st_mode);                               
                    printf("%ld (%ld) %s %s %s %ld %s", st->st_nlink, st->st_ino, usr->pw_name, grp->gr_name, perm, st->st_size, name);//ConvierteModo2(st.st_mode)
                    if(link1){//tenemos una llamada al sistema operativo que nos dice si un fichero es un link simbolico
                        if(S_ISLNK(st->st_mode)){
                            if(readlink(name,link,200)!=-1){
                                printf("-> %s",link);
                            }else{
                                perror( error );
                            }
                        }
                    } 
                }else{
                    perror( error );
                }
            }else{
                perror( error );
            }  
        printf("\n");
        }
    }else{
        if(lstat(name,st)==-1){
            perror( error );
        }else{
            printf("%ld %s\n",st->st_size ,name);
        }
    
    }
    free(st);
}
void borrar1_directorios(cadena directorio){
    char error[200];
    //char ruta_actual[MAX_RUTA];
    char ruta[MAX_RUTA];//sino para recorrer recursivamente el directorio dirá que no lo encuentra
    DIR *dir;
    struct dirent *rdir;
    struct stat *st=malloc(sizeof(struct stat));
    getcwd(ruta,MAX_RUTA);
    dir= opendir(directorio);
    if(dir==NULL){
        perror( error );
    }else{
        if(chdir(directorio)==0){
            while((rdir=readdir(dir))!=NULL){
                if(strncmp(rdir->d_name,".\0",2)!=0 && strncmp(rdir->d_name,"..\0",3)!=0){
                    if(lstat(rdir->d_name,st)==-1){
                        perror( error );
                    }else{
                        if(S_ISDIR (st->st_mode)){
                            if(strncmp(rdir->d_name,".\0",2)!=0 && strncmp(rdir->d_name,"..\0",3)!=0){
                                borrar1_directorios(rdir->d_name);
                            }


                        }else if(S_ISREG (st->st_mode) || S_ISLNK (st->st_mode)){
                            if(unlink(rdir->d_name)!=0){
                                perror( error );
                            }
                        }else{

                        }

                    }
                }
            }
            chdir(ruta);
            if(rmdir(directorio)!=0){
                perror( error );
            }
            closedir(dir);
        }else{
            perror( error );
        }
    }
    chdir(ruta);
    free(st);
}



