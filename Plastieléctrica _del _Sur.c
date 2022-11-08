//?No debe de tener ni una interaccion con la base de datos
// gcc -o Pla Plastieléctrica _del _Sur.c -I /usr/include/postgresql/ -lpq
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
//*inicializacion de lasa funciones
int menuCliente();
int menuArticulos();
int menuVentas();
int showClientes();
int showOneCliente();
int addCliente();
int updateCliente();
int deleteCliente();

//*inicializacion de variables
int fd1,fd2,fde=0,i,x;
double tiempo=0.0;
char txt[2];
//!Funcion principal
int main(){
    int menu;
    while(1){
        //remove("/home/dano/Documentos/7mo/SO/ProyectoFinal/listaclientes2");
        //*menu a presentar al cliente
        printf("\n      Plastieléctrica del Sur       \n");
        printf("------------------------------------\n");
        printf("                MENU                \n");
        printf("------------------------------------\n");
        printf("|1-Clientes                        |\n");
        printf("|2-Articulos                       |\n");
        printf("|3-Ventas                          |\n");
        printf("|4-Salir                           |\n");
        printf("------------------------------------\n");
        scanf("%i",&menu);
        //? El switch nos lleva al segundo menu
        switch(menu){
            //*clientes
            case 1:
                //printf("Entrando a la seccion de clientes\n");
                menuCliente();               
            break;
            //*Articulos
            case 2:
                //menuArticulos();
            break;
            //*Ventas
            case 3:
                //menuVentas();
            break;
            //*Salir
            case 4:
                printf("Saliendo...\n");
                exit(EXIT_SUCCESS);
            break;
            default:
                printf("No tenemos esa opcion, vuelva a intentarlo\n");
            break;
        }
    }
    return 0;
}

menuCliente(){
    int menu;
    char txt[5];
    clock_t begin;
    clock_t end;
    fd2=open("menu1",O_WRONLY);
    printf("------------------------------------\n");
    printf("                CLIENTE             \n");
    printf("------------------------------------\n");
    printf("|1-Lista de clientes               |\n");
    printf("|2-Lista de clientes con credito   |\n");
    printf("|3-Datos de un cliente             |\n");
    printf("|4-Añadir                          |\n");
    printf("|5-Actualizar                      |\n");
    printf("|6-Borrar                          |\n");
    printf("|7-Salir                           |\n");
    printf("------------------------------------\n");
    scanf("%i",&menu);
    fd2=open("menu1",O_WRONLY);
    switch(menu){
        
        //*Lista de clientes 
        case 1:
            begin=clock();
            sprintf(txt,"1");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showClientes();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        case 2:
            begin=clock();
            sprintf(txt,"2");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showClientes();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*Datos de un cliente
        case 3:
            begin=clock();
            sprintf(txt,"3");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showOneCliente();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*añadir
        case 4:
            begin=clock();
            sprintf(txt,"4");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            addCliente();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*Actualizar
        case 5:
            
        break;
        //*borrar
        case 6:

        break;
    }
    
        printf("\n-----------------------\nTiempo de ejecucion:%f\n", tiempo);

}

//?Mostrar clientes
showClientes(){
    char cad[2024];
    fd2=open("lista1",O_RDONLY);
    read(fd2,cad,2024);
    close(fd2);
    printf("--------------------CLIENTES--------------------------\n");
    printf("%s\n",cad);
    
}
//?Se muestra datos de un solo cliente
showOneCliente(){
    char idcad[10],cad[2024];
    int idcli;
    sprintf(idcad,"");
    
    printf("Inserte el id del cliente:");
    scanf("%i",&idcli);
    sprintf(idcad,"%i",idcli);

    fd2=open("IdCliente",O_WRONLY);
    write(fd2,idcad,sizeof(idcad));
    close(fd2);

    fd1=open("lista2",O_RDONLY);
    read(fd1,cad,sizeof(cad));
    close(fd1);
    printf("--------------------DATOS DEL CLIENTE %i--------------------------\n",idcli);
    printf("%s\n",cad);

}

addCliente(){
    char name[100];
    char sql[1024];
    int typecli;
    printf("*******Agregar Cliente********* \n");
    printf("-------------------------------\n");
    printf("Nombre\n");
    scanf("%s",&name);
    //*>Hacemos mayusculas
    for (int indice = 0; name[indice] != '\0'; ++indice){
		name[indice] = toupper(name[indice]);
	}
    printf("---->Solicitud de credito?\n");
    printf("-1:No\n");
    printf("-2:Si\n");
    scanf("%i",&typecli);
    //INSERT INTO CLIENTES (nombre, id_typecli) values (s,i)
    sprintf(sql,"%i,'%s'",typecli,name);
    fd2=open("sqldata",O_WRONLY);
    write(fd2,sql,sizeof(sql));
    close(fd2);
}


