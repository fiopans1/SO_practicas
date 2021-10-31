#include "memoria.h"

//MEMORIA:
void doRecursiva (int n){
    char automatico[TAMANO];
    static char estatico[TAMANO];
    printf ("parametro n:%d en %p",n,&n);
    printf ("array estatico en:%p ",estatico);
    printf ("array automatico en %p\n",automatico);
    n--;
    if (n>0){
        doRecursiva(n);
    }
}
void malloc1(cadena trozos[],int n,tListM *M){
    tItemM items;
    tPosM pos;
    unsigned long int tam;
    if(n==1){
        imprimir_malloc(*M);
    
    }else if(n==2){
        if(strcmp(trozos[1], "-free")==0){
            imprimir_malloc(*M);
        }else{
            if(isNumber2(trozos[1])){
            tam=(unsigned long int) strtoul(trozos[1], NULL, 10);//es strtoul en vez de strtol porque la u significa unsigned
            items.dir_malloc=malloc(tam);
            obt_hora(items.hora);
            if(items.dir_malloc==NULL){
                printf("No se pudo reservar memoria\n");
            }else{
            strcpy(items.nome_ficheiro,"");
            items.tipo=MALLOC;
            items.key=0;
            items.tam=tam;
            insertItemM(items,NULL,M);
            printf("allocated %ld at %p\n", items.tam,items.dir_malloc);
            }
            }else{
                printf(RED "Valor no valido\n" COLOR_RESET);
            }
        }


    }else if(n>=3){
        if(strcmp(trozos[1], "-free")==0){
            if(isNumber2(trozos[2])){
                tam=(unsigned long int) strtoul(trozos[2], NULL, 10);
                pos=findtamM(tam, *M);
                if(pos!=NULL){
                    items=getItemM(pos,*M);
                    free(items.dir_malloc);
                    printf("deallocated %ld at %p\n",items.tam, items.dir_malloc);
                    deleteAtPositionM(pos,M);
                }else{
                    printf(RED "Tamaño no encontrado\n" COLOR_RESET);
                }
            }else{
            printf(RED "Valor no valido\n" COLOR_RESET); 
            }
        }else{
            if(isNumber2(trozos[1])){
                tam=(unsigned long int) strtoul(trozos[1], NULL, 10);//es strtoul en vez de strtol porque la u significa unsigned
                items.dir_malloc=malloc(tam);
                obt_hora(items.hora);
                if(items.dir_malloc==NULL){
                    printf("No se pudo reservar memoria\n");
                }else{
                strcpy(items.nome_ficheiro,"");
                items.tipo=MALLOC;
                items.key=0;
                items.tam=tam;
                insertItemM(items,NULL,M);
                printf("allocated %ld at %p\n", items.tam,items.dir_malloc);
                }
                }else{
                    printf(RED "Valor no valido\n" COLOR_RESET);
            }

        }
    
    
    
    }else{
        printf(RED "Opciones no validas para malloc\n" COLOR_RESET); 
    }  
}
void mmap1(cadena trozos[],int n,tListM *M){
    cadena args[2];
    tPosM pos;
    tItemM item;

    if(n==1){
        imprimir_mmap(*M);
    }else if(n==2){
        if(strcmp(trozos[1],"-free")!=0){
            args[0]=trozos[1];
            args[1]=NULL;
            Mmap(args,M);
        }else{
            imprimir_mmap(*M);
        }
        
    }else if(n>=3){
        if(strcmp(trozos[1],"-free")==0){
            pos=findfichM(trozos[2], *M);
            if(pos==NULL){
                printf("No se puede borrar el archivo porque no tiene permisos o no fue mapeado");
            }else{
                item=getItemM(pos,*M);
                if(munmap(item.dir_malloc,item.tam)==-1){
                    perror("error");
                }else{
                    printf("Se desalojo perfectamente la memoria reservada para %s\n", item.nome_ficheiro);
                    deleteAtPositionM(pos,M);                   
                }
            }            
        }else{
            args[0]=trozos[1];
            args[1]=trozos[2];
            Mmap(args,M);
    
        }
    }
}
void dealloc(cadena trozos[], int n, tListM *M){
    tItemM items;
    tPosM pos;
    long int tam;
    if(n==1){
        imprimir_listacompleta(*M);
    }else if(n==2){//por direcciones
        if(strcmp(trozos[1],"-malloc")==0){
            imprimir_malloc(*M);
        }else if(strcmp(trozos[1],"-mmap")==0){
            imprimir_mmap(*M);
        }else if(strcmp(trozos[1],"-shared")==0){
            imprimir_shared(*M);
        }else{
            pos=finddirM(((void *) strtoull(trozos[1], NULL, 16)),*M);
            if(pos==NULL){
                printf(RED "Direccion no encontrada en la lista\n" COLOR_RESET);
            }else{
                items=getItemM(pos,*M);
                if(items.tipo==MALLOC){
                    free(items.dir_malloc);
                    printf("deallocated %ld at %p\n",items.tam, items.dir_malloc);
                    deleteAtPositionM(pos,M);
                }else if(items.tipo==MMAP){
                    if(munmap(items.dir_malloc,items.tam)==-1){
                        perror("error");
                    }else{
                        printf("Se desalojo perfectamente la memoria reservada para %s\n", items.nome_ficheiro);
                        deleteAtPositionM(pos,M);                   
                    }
                }else if(items.tipo==SHARED){
                    //RELLENAR CUANDO TENGAMOS SHARED

                }
            }
        }

    }else if(n>=3){
        if(strcmp(trozos[1],"-malloc")==0){//caso malloc
            if(isNumber2(trozos[2])){
                tam=(long int) strtol(trozos[2], NULL, 10);
                pos=findtamM(tam, *M);
                if(pos!=NULL){
                    items=getItemM(pos,*M);
                    free(items.dir_malloc);
                    printf("deallocated %ld at %p\n",items.tam, items.dir_malloc);
                    deleteAtPositionM(pos,M);
                }else{
                    printf("No se puede borrar el archivo porque no tiene permisos o no fue mapeado");
                }
            }else{
                printf(RED "Tamaño no encontrado\n" COLOR_RESET);
            }

        }else if(strcmp(trozos[1],"-mmap")==0){//caso mmap
            pos=findfichM(trozos[2], *M);
            if(pos==NULL){
                printf("No se puede borrar el archivo porque no tiene permisos o no fue mapeado");
            }else{
                items=getItemM(pos,*M);
                if(munmap(items.dir_malloc,items.tam)==-1){
                    perror("error");
                }else{
                    printf("Se desalojo perfectamente la memoria reservada para %s\n", items.nome_ficheiro);
                    deleteAtPositionM(pos,M);                   
                }
            }  

        }else if(strcmp(trozos[1],"-shared")==0){//caso shared
            //RELLENAR CUANDO TENGAMOS SHARED
        }
    }
}

void shared1(cadena trozos[], int n, tListM *M){
    cadena args[2];
    if(n==1 || n==2){
        imprimir_shared(*M);
    }else if(n==3){
        if(strcmp(trozos[1],"-free")==0){

        }else if(strcmp(trozos[1],"-create")==0){
            imprimir_shared(*M);
        }else if(strcmp(trozos[1],"-delkey")==0){
            args[0]=trozos[2];
            args[1]=NULL;
            SharedDelkey(args,M);

        }else{
            imprimir_shared(*M);
        }

    }else if(n>=4){
        if(strcmp(trozos[1],"-free")==0){

        }else if(strcmp(trozos[1],"-create")==0){
            args[0]=trozos[2];
            args[1]=trozos[3];
            SharedCreate(args,M);
        }else if(strcmp(trozos[1],"-delkey")==0){
            args[0]=trozos[2];
            args[1]=NULL;
            SharedDelkey(args,M);

        }else{

        }

    }
}

void memoria(cadena trozos[], int n, tListM *M){
    static int st1,st2,st3;
    int loc1,loc2,loc3;
    if(n==1){
        printf("Estáticas: %p %p %p\n",&st1,&st2,&st3);
        printf("Locales: %p %p %p\n",&loc1,&loc2,&loc3);
        printf("Globales: %p %p %p\n",&global1,&global2,&global3);
        printf("Funciones programa: %p %p %p\n", (void *) memoria,(void *) MmapFichero,(void *) ObtenerMemoriaShmget);
        printf("Funciones C: %p %p %p\n", (void *) shmget,(void *) malloc,(void *) free);
        imprimir_listacompleta(*M);
    }else if(n>=2){
        if(strcmp(trozos[1],"-vars")==0){
            printf("Estáticas: %p %p %p\n",&st1,&st2,&st3);
            printf("Locales: %p %p %p\n",&loc1,&loc2,&loc3);
            printf("Globales: %p %p %p\n",&global1,&global2,&global3);

        }else if(strcmp(trozos[1],"-funcs")==0){
            printf("Funciones programa: %p %p %p\n", (void *) memoria,(void *) MmapFichero,(void *) ObtenerMemoriaShmget);
            printf("Funciones C: %p %p %p\n", (void *) shmget,(void *) malloc,(void *) free);
        }//terminar memoria
    }

}





//FUNCIONES QUE NOS DIERON ELLOS:
/*********************************************************/
/*********************************************************/
void * ObtenerMemoriaShmget (key_t clave, size_t tam,tListM *M){//aqui mandamos la clave
        /*Obtienen un puntero a una zaona de memoria compartida*/
    /*si tam >0 intenta crearla y si tam==0 asume que existe*/
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    tItemM item;
    if (tam){  /*si tam no es 0 la crea en modo exclusivo
        esta funcion vale para shared y shared -create*/

        flags=flags | IPC_CREAT | IPC_EXCL;//hace or bit a bit para que cree y no se que
        /*si tam es 0 intenta acceder a una ya creada*/
    }
    if (clave==IPC_PRIVATE){ /*no nos vale*/ //miramos que el arcivho no sea privado
        errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1){//con esto creamos la zona de memoria que queremos crear, clave es la clave de la zona de memoria, tma el numero de bits
    // a reservar(si es 0 es para acceder a una ya creada, y flag es los permisos que le damos para acceder), retorna id que es la clave de la zona de memoria a la que accedemos
        return (NULL);
    }
    obt_hora(item.hora);
    if ((p=shmat(id,NULL,0))==(void*) -1){//el id es el indentificador de la zona de memoria,  el NULL es la direccion concreta donde reside la memoria compartida
    // y el 0 es el flag para indicar si una zona es de lectura y escritura o solo de lectura
        aux=errno; /*si se ha creado y no se puede mapear*/
        if (tam){ /*se borra */
            shmctl(id,IPC_RMID,NULL);//con IPC_RMID borra la memoria compartida
        }
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);//borra la memoria compartida que es creada, id es el id de la memoria compartida, la segunda constante indica que hace la funcion. en
    //este caso rellenar la estructura shmid_ds
    /* Guardar En Direcciones de Memoria Shared (p, s.shm_segsz, clave.....);*/
    item.dir_malloc=p;
    item.key=clave;
    strcpy(item.nome_ficheiro,"");
    item.tam=s.shm_segsz;
    item.tipo=SHARED;
    insertItemM(item,NULL,M);

    return (p);
}//shmdt decinvula una variable de la zona de memoria

void SharedCreate (char *arg[],tListM *M){ /*arg[0] is the key
        and arg[1] is the size*/
    key_t k;//esta sera la clave del fichero
    size_t tam=0;//inicializamos ficherp
    void *p;//direccion
    if (arg[0]==NULL || arg[1]==NULL){/*Listar Direcciones de Memoria Shared */; //revisamos que no sea NULL ninguno de los parametos
    return;
    }
        k=(key_t) atoi(arg[0]);//hacemos un cast de la clave
        if (arg[1]!=NULL){//comprobamos que el tamaño sea distinto de NULL
            tam=(size_t) atoll(arg[1]);//hacemos un cast de tam
        }
        if ((p=ObtenerMemoriaShmget(k,tam,M))==NULL){//obtenemosmemoria
            perror ("Imposible obtener memoria shmget");
        }else{
            printf ("Memoria de shmget de clave %d asignada en %p\n",k,p);
        }
}
/************************************************************************/
/************************************************************************/ //funciones para mmap y read
void * MmapFichero (char * fichero, int protection, tListM *M){//mandamos el nombre del ficheroy la proteccion
    tItemM item;
    int df, map=MAP_PRIVATE,modo=O_RDONLY;//key fichero, en modo es para como queremos abrir el fichero, al principiso solo en modo lectura, y nuestro MMAP se abre de manera privada
    struct stat s;//struct para obtener longitud y  tal
    void *p;//direccion de memoria donde se guarda el fichero
    if (protection&PROT_WRITE){ modo=O_RDWR;}//si vemos que la proteccion tiene activa la lectura, entonces tambien se abre en modo escritura
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1){//miramos que se pueda abrir el fichero y que podemos obtener su longitud
    //open date a chave para poñela en memoria, e logo mapeamos ca chave
    return NULL;
    }//si existe el fichero hacemos el mmap 
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED){//al indicar NULL en mmap el kernel se encarga de asignar la memoria
        return NULL;
    }//ahora podemos recorrer el fichero como si fuera un array
    obt_hora(item.hora);
    /*Guardar Direccion de Mmap (p, s.st_size,fichero,df......);*/
    item.dir_malloc=p;
    strcpy(item.nome_ficheiro,fichero);
    item.key=df;
    item.tam=s.st_size;
    item.tipo=MMAP;
    insertItemM(item,NULL,M);
    return p;
}
void Mmap (char *arg[], tListM *M){ /*arg[0] is the file name
    and arg[1] is the permissions*/
    //en esta funcion lo que hacemos es pasarle los argumentos(fichero y permisos)  y declaramos
    // char permisos, el p direccion y la protecion que tendrá
    char *perm;
    void *p;
    int protection=0;
    if (arg[0]==NULL){/*Listar Direcciones de Memoria mmap;*/ return;} //revisamos que el fichero no sea un null
    if ((perm=arg[1])!=NULL && strlen(perm)<4) {
    if (strchr(perm,'r')!=NULL) protection|=PROT_READ; //asignamos los permisos haciendo un or bit a bit
    if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
    if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
    }
    if ((p=MmapFichero(arg[0],protection, M))==NULL){ //llamamos a la funcion mmap fichero y permisos a asignar
        perror ("Imposible mapear fichero");
    }else{
        printf ("fichero %s mapeado en %p\n", arg[0], p);
    }
}
ssize_t LeerFichero (char *fich, void *p, ssize_t n){ /* le n bytes del fichero fich en p */
    ssize_t nleidos,tam=n; /*si n==-1 lee el fichero completo*/
    int df, aux;
    struct stat s;
    if (stat (fich,&s)==-1 || (df=open(fich,O_RDONLY))==-1){//miramos que se pueda abrir el fichero perfectamente(abrimos el fichero como solo lectura)
        return ((ssize_t)-1);
    }
    if (n==LEERCOMPLETO){//si el tam es -1, entonces leemos todo el fichero
        tam=(ssize_t) s.st_size;
    }
    if ((nleidos=read(df,p, tam))==-1){//miramos que read devuelva el numero de palabras a nleidos, y en p tendremos los valores leidos para luego mostrar
        aux=errno;//juegan con el errno para que close no lo sobreescria
        close(df);
        errno=aux;
        return ((ssize_t)-1);//en caso de que no se pueda leer devuelve -1
    }
    close (df);
    return (nleidos);//en caso de que se pueda leer devuelve nleidos
}//con nleidos tenemos el numero de bytes leidos y con *p tenemos los caracteres leidos.

/*********************************************************************/
/*********************************************************************/
void SharedDelkey (char *args[], tListM *M){/*arg[0] points to a str containing the key*/ //sirve para eliminar la zona de memoria compartida
    key_t clave;
    int id;
    char *key=args[0];
    tPosM pos;
    if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){//miramos que la clave no sea nula y que sea publica y no privada
        printf (" shared -delkey clave_valida\n");
        return;
    }
    if ((id=shmget(clave,0,0666))==-1){//se obtiene la id de la memoria compartida
        perror ("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id,IPC_RMID,NULL)==-1){  perror ("shmctl: imposible eliminar memoria compartida\n");}else{//se elimina la memoria compartida
        pos=findkeyM(((int) clave),*M);
        if(pos==NULL){
            printf("Se eliminó el bloque de memoria pero no el elemento de la lista\n");
        }else{
            deleteAtPositionM(pos,M);
            printf("Se eliminó correctamente el bloque a eliminar\n");
        }
    }
}

void dopmap (void){ /*no arguments necessary*/
    pid_t pid; /*ejecuta el comando externo pmap para */
    char elpid[32]; /*pasandole el pid del proceso actual */
    char *argv[3]={"pmap",elpid,NULL};
    sprintf (elpid,"%d", (int) getpid());
    if ((pid=fork())==-1){
        perror ("Imposible crear proceso");
        return;
    }
    if (pid==0){
        if (execvp(argv[0],argv)==-1){perror("cannot execute pmap");}
        exit(1);
    }
    waitpid (pid,NULL,0);
}


//FUNCIONES AUXILIARES


void obt_hora(char hora[]){
    time_t now;
    time(&now);
    strcpy(hora,ctime(&now));
}
bool isNumber2(cadena param1) {//funcion para comprobar si una cadena es un numero
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