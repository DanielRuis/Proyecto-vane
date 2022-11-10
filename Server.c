#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libpq-fe.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
PGconn *con = NULL;
PGresult *result = NULL;
//?Variables para la conexion a la bd
char *host = "localhost";
char *port = "5432";
char *dataBase = "electronica";
char *user = "postgres";
char *passwd = "31342522";
//*variables globales
int i,j,fd1,fd2,sqldata,menu;
char txt[5],sql[1234],idcli[10],deuda[100];
//*funciones:Cliente
void deleteop();
void updateop();
int addCliente();
int updateCliente();
int showCliente();
int deleteCliente();
int showAllCliente();
int showOneCliente();
// gcc -o Server Server.c -I /usr/include/postgresql/ -lpq
//!Funcion principal
int main(){
    while(1){
        //*borramos los archivos
        sprintf(deuda,"0"); 
        remove("/home/dano/Documentos/7mo/SO/ProyectoFinal/lista1");
        remove("/home/dano/Documentos/7mo/SO/ProyectoFinal/menu");
        mkfifo("lista1",0666);
        mkfifo("menu1",0666);//*->Abrimos el fifo para el menu de acciones
        fd1=open("menu1",O_RDONLY);
        read(fd1,txt,5);//*->Leemos y se guarda en la variable txt
        close(fd1);
        menu=atoi(txt);
        //? Switch de acciones
        switch(menu){
            //!Seccion de clientes del 1-5
            case 1:
                printf("Entra a mostrar clientes\n");
                showAllCliente(menu);//*->Mostrar lista de clientes detallado
            break;
            case 2:
                printf("Entrando a mostar clientes con credito\n");
                showAllCliente(menu);
            break;
            case 3:
                showOneCliente();//*->Mostrar a un solo cliente
            break;
            case 4:
                addCliente();//*->Añadir Cliente
            break;
            case 5:
                showOneCliente();
                updateop(1);//*->Actualizar cliente
            break;
            case 6:
                showOneCliente();
                deleteop(1);//*->Borrar cliente
            break;
            //!------Seccion de articulos

            case 7:

            break;
        }


    }
}

//! ------------------CLIENTES--------------------------------------------------------
//? Muestra todos los clientes
int showAllCliente(int m){
    char bf[900],cad[2024];
    int ls;
    sprintf(cad,"");
    printf("Servicio de mostrar a todos los clientes\n");
    //*Se inicia conexion
    con = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);//*abro conexion   
    //?Decide que consulta hacer
    switch(m){
        case 1:
            result=PQexec(con, "select * from clientes");
            strcat(cad,"ID\t\tTIPO\t\tNOMBRE\t\tFECHAINI\t\tDEUDA($)\tCRED($)\t\tFECHDES(M)\n");
        break;
        case 2:
            result=PQexec(con, "select id_cliente, nombre, credito, deuda from clientes where id_typecli=2");
            strcat(cad,"ID\t\tNOMBRE\t\tCRED($)\t\tDEUDA($)\n\n");
        break;
    }
    printf("Filas:%d, Columnas:%d \n",PQntuples(result),PQnfields(result));
    mkfifo("lista1",0666);//*Creamos el FIFO
    fd2=open("lista1",O_WRONLY);//*Abrimos para escritura
    //?Entramos a la lista de datos a mostrar
    if(PQntuples(result)!=0){
        i=0;
        for (i = 0; i < PQntuples(result); i++){ 
            for (j = 0; j < PQnfields(result); j++){
                sprintf(bf,"%s\t\t",PQgetvalue(result,i,j));
                
                strcat(cad,bf);   
            } 
            strcat(cad,"\n");
        }
        //printf("%s\n",cad);
        write(fd2,cad,sizeof(cad));//!Se escribe y se manda al cliente
    }else{
        //?Entra si no hay clientes en la base de datos
        sprintf(cad,"No hay clientes\n");
        printf("%s",cad);
        write(fd2,cad,sizeof(cad));//!Escribe que no hay clientes
    }
    close(ls);//*Cerramos
    PQfinish(con);
}

//?Servicio de mostrar un solo cliente
//*Se recibe el id del cliente
//*Solo aqui se mostrara la lista de clientes pero cliente no lo va a ver
int showOneCliente(){
    mkfifo("IdCliente",0666);//*Creamos el fifo
    mkfifo("lista2",0666);//*Creamos el FIFO
    char sqlcad[1100],cad[2024],idcad[10],bf[900];
    sprintf(cad,"");
    sprintf(idcad,"");
    sprintf(sqlcad,"");
    sprintf(bf,"");
    printf("Servicio de mostrar a un cliente\n");

    //*Se inicia conexion
    con = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);//*abro conexion   

    //*abrimos canal de comunicacion de lectura
    fd2=open("IdCliente",O_RDONLY);
    read(fd2,idcad,sizeof(idcad));//*->Hacemos lectura dek id
    close(fd2);//*Cerramos el canal fd2
    sprintf(idcli,"%s",idcad);
    //printf("%s\n",idcad);

    //*Se realiza la instruccion sql
    sprintf(sqlcad,"Select * from clientes where id_cliente='%s'",idcad);
    printf("%s\n",sqlcad);
    result=PQexec(con,sqlcad);
    fd1=open("lista2",O_WRONLY);//*Abrimos como escritura con fd1
    //*Se junta los datos
    if(PQntuples(result)!=0){
        strcat(cad,"ID\t\tTIPO\t\tNOMBRE\t\tFECHAINI\t\tDEUDA($)\tCRED($)\t\tFECHDES(M)\n");
        //?Si encuentra al cliente entra
        
        for (j = 0; j < PQnfields(result); j++){
            sprintf(bf,"%s\t\t",PQgetvalue(result,0,j));
            printf("->%i--%s\n",j,PQgetvalue(result,0,j));
            if(j==4){
                sprintf(deuda,"%s",PQgetvalue(result,0,j));
                printf("Deuda:%s\n",deuda);
            }
            strcat(cad,bf);   
        } 
        strcat(cad,"\n");
        //printf("%s\n",cad);
        write(fd1,cad,sizeof(cad));//!Se escribe y se manda al cliente
    }else{
        //?Entra si no está el cliente buscado
        sprintf(cad,"No se encuentra el cliente en la lista\n");
        printf("%s",cad);
        write(fd1,cad,sizeof(cad));//!Escribe que no hay clientes
    }
    close(fd1);//*Cerramos a fd1
    PQfinish(con);//*Cerramos conexion
    return 0;
}
//?Añadir cliente
addCliente(){
    //*Se inicia conexion
    con = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);//*abro conexion 
    char sql[1024], cad[1024];
    //*Limpiamos cadenas
    sprintf(cad,"");
    sprintf(sql,"");

    mkfifo("sqldata",0666);//*->Recreamos el sqldata
    fd2=open("sqldata",O_RDONLY);//*->Abrimos para lectura
    read(fd2,cad,sizeof(cad));
    close(fd2);//*->Cerramos

    sprintf(sql,"insert into clientes (id_typecli,nombre) values(%s)",cad);
    PQexec(con,sql);//!Se ejecunta sql INSERT
    sprintf(sql,"select credito((select max(id_cliente) from clientes))");
    PQexec(con,sql);
    sprintf(sql,"select f_descuento((select max(id_cliente) from clientes))");
    PQexec(con,sql);
    PQfinish(con);//*Cerramos con
}

//?Actualizar
updateop(int op){
    //*Se inicia conexion
    con = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);//*abro conexion 
    char sql[1024], cad[1024],menu[10];
    int menup;
    //*Limpiamos cadenas
    sprintf(cad,"");
    sprintf(sql,"");
    mkfifo("menuupdate",0666);
    mkfifo("mensaje",0666);
    mkfifo("sqldata",0666);//*->Recreamos el sqldata
    //*Seleccion de actualizacion
    switch(op){
        //todo:Actualiza clientes-------------------------------------
        case 1:
            //*Switch para el menu de actualizar clientes
            fd2=open("menuupdate",O_RDONLY);//*->Abrimos para lectura
            read(fd2,menu,sizeof(menu));
            close(fd2);
            menup=atoi(menu);
            printf("%i\n",menup);
            switch(menup){
                //*Actualizar la solicitud de credito
                case 1:
                    sprintf(sql,"update clientes set id_typecli=2 where id_cliente=%s",idcli);
                    printf("%s\n",sql);
                    PQexec(con,sql);
                    sprintf(sql,"select credito(%s)",idcli);
                    PQexec(con,sql);
                    
                break;
                //*Actualizar el nombre
                case 2:
                   mkfifo("data",0666);
                   fd1=open("data",O_RDONLY);
                   read(fd1,cad,sizeof(cad));
                   close(fd1);
                   sprintf(sql,"update clientes set nombre='%s' where id_cliente=%s",cad,idcli);
                   PQexec(con,sql);
                   
                break;
                //*Actualizar la deuda(solver o reducir)
                case 3:
                    mkfifo("data",0666);
                    fd1=open("data",O_WRONLY);
                    write(fd1,deuda,sizeof(deuda));
                    close(fd1);
                    mkfifo("newdata",0666);
                    fd2=open("newdata",O_RDONLY);
                    read(fd2,cad,sizeof(cad));
                    close(fd2);
                    sprintf(sql,"update clientes set deuda=%s where id_cliente=%s",cad, idcli);
                    printf("%s\n",sql);
                    PQexec(con,sql);
                    
                break;
                case 10:
                    printf("-->No ingreso cliente correcto\n");
                break;
            }
            sprintf(idcli,"");


        break;
    }
}

//?Borrar
deleteop(int op){
    //*Se inicia conexion
    con = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);//*abro conexion 
    char sql[1024], cad[1024],menu[10];
    int menup;
    //*Limpiamos cadenas
    sprintf(cad,"");
    sprintf(sql,"");
    mkfifo("menuupdate",0666);
    mkfifo("mensaje",0666);
    mkfifo("sqldata",0666);//*->Recreamos el sqldata
    //*Seleccion de borrado
    switch(op){
        //*borrar cliente
        case 1:
            sprintf(sql,"delete from clientes where id_cliente=%s",idcli);
            printf("%s\n",sql);
            PQexec(con,sql);
        break;
    }
}