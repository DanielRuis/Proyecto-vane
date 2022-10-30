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
char *dataBase = "ferreteria";
char *user = "postgres";
char *passwd = "31342522";
//?variables globales
int i,j,fd1,fd2,sqldata;
char txt[5],sql[1234];
// gcc -o Server Server.c -I /usr/include/postgresql/ -lpq
//!Funcion principal
int main(){
    con = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);//*abro conexion   
    if(PQstatus(con) != CONNECTION_BAD){
        printf("Iniciando...\n");
    }else{
        printf("Fallo en la conexion\n");
    }
}
