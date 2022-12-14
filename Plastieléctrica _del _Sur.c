//?No debe de tener ni una interaccion con la base de datos
// gcc -o Pla Plastieléctrica -I /usr/include/postgresql/ -lpq
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
int showdata();
int showOneCliente();
int addCliente();
int updateCliente();
int deleteCliente();
int addarti();
int updateArticulo();
int deleteArticulo();
int updateInventario();
int menuVentas();
int venta();
int showOneVenta();
int showODV();
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
                menuArticulos();
            break;
            //*Ventas
            case 3:
                menuVentas();
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
            showdata(1);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        case 2:
            begin=clock();
            sprintf(txt,"2");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(1);
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
            begin=clock();
            sprintf(txt,"5");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            updateCliente();
            printf("Cierra update\n");
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*borrar
        case 6:
            begin=clock();
            sprintf(txt,"6");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            deleteCliente();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*regresar al menu principal
        case 7:
            printf("||||||....Regresando al menu principal.....|||||\n");
        break;
    }
    
        printf("\n-----------------------\nTiempo de ejecucion:%f\n", tiempo);

}

//?Mostrar clientes
showdata(int i){
    char cad[2024];
    fd2=open("lista1",O_RDONLY);
    read(fd2,cad,2024);
    close(fd2);
    if(i==1){
        printf("--------------------CLIENTES--------------------------\n");
    }else if(i==2){
        printf("--------------------ARTICULOS--------------------------\n");
    }else if(i==3){
        printf("--------------------INVENTARIO--------------------------\n");
    }else if(i==4){
        printf("--------------------VENTAS--------------------------\n");
    }else if(i==5){
        printf("--------------------FACTURAS--------------------------\n");
    } 
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

updateCliente(){
    char data[50],sql[1024],idcad[10],menu[5],cad[1024],cad2[1024],deuda[100];
    int c1, c2,c3,m;
    float de,abo,res;
    sprintf(idcad,"");//*LImpiamos cadena
    sprintf(menu,"");//*LImpiamos cadena
    sprintf(cad2,"No se encuentra el cliente en la lista\n");

    printf("*******Actualizar Cliente********* \n");
    printf("-----------------------------------\n");
    printf("Inserte el id del cliente:");
    scanf("%s",&idcad);

    fd2=open("IdCliente",O_WRONLY);
    write(fd2,idcad,sizeof(idcad));
    close(fd2);

    fd1=open("lista2",O_RDONLY);
    read(fd1,cad,sizeof(cad));
    close(fd1);
    printf("--------------------DATOS DEL CLIENTE %s--------------------------\n",idcad);
    printf("%s\n",cad);
    //sprintf(cad2,"%s",cad);
    for (int indice = 0; cad[indice] != '\0'; ++indice){
		c1=indice;
	}
    for (int indice = 0; cad2[indice] != '\0'; ++indice){
		c2=indice;
	}
    printf("C1:%i-----C2:%i\n",c1,c2);


    //*Si hay un cliente manda al servidor la indicacion del menu
    fd2=open("menuupdate",O_WRONLY);
    if(c1!=c2){
        printf("*******Actualizar Cliente********* \n");
        printf("-----------------------------------\n");
        printf("|1-Solicitar credito               \n");
        printf("|2-Nombre                          \n");
        printf("|3-Abonar a deuda                  \n");
        printf("-----------------------------------\n");
        scanf("%i",&m);
        sprintf(menu,"%i",m);
        write(fd2,menu,sizeof(menu));
        close(fd2);
        
        //*Switch para el menu de la actualizacion
        switch(m){
            //*Solicitar credito
            case 1:
                printf("Solicitud de credito hecha\n");                
            break;
            //*Cambiar nombre
            case 2:
                printf("Coloque el nuevo dato\n");
                scanf("%s",&data);
                for (int indice = 0; data[indice] != '\0'; ++indice){
		            data[indice] = toupper(data[indice]);
	            }
                fd1=open("data",O_WRONLY);
                write(fd1,data,sizeof(data));
                close(fd1);
            break;
            //*Abonar a deuda
            case 3:
                fd1=open("data",O_RDONLY);
                read(fd1,deuda,sizeof(deuda));
                close(fd1);
                de=atof(deuda);
                if(de>0){
                    c3=0;
                    printf("Tiene deudas de: $%0.2f\n",de);
                    while(c3==0){
                        printf("\n---------------------------\n");
                        printf("Coloca el monto a abonar\n$");
                        scanf("%f",&abo);
                        if(abo>de){
                            printf(">Abono mayor que la deuda,vuelba a colocar el monto\n");

                        }else if( abo==de){
                            printf(">Deuda saldada de forma completa\n");
                            res=0.0;
                            c3=1;
                        }else if(abo<de){
                            res=de-abo;
                            
                            printf(">Deuda faltante: $%0.2f\n",res);
                            c3=1;
                        }
                        printf("---------------------------\n");
                        if(c3==1){
                            sprintf(data,"%0.2f",res);
                            fd2=open("newdata",O_WRONLY);
                            write(fd2,data,sizeof(data));
                            close(fd2);
                        }
                    }
                    
                    

                }else{
                    printf("No tiene deuda este usuario\n");
                    sprintf(data,"%0.2f",res);
                    fd2=open("newdata",O_WRONLY);
                    write(fd2,data,sizeof(data));
                    close(fd2);
                }
                
            break;

            default:
                printf("Funcion erronea\n");
                sprintf(menu,"10");
                write(fd2,menu,sizeof(menu));
                close(fd2);

            break;
        }


        
    }else if(strcmp(cad,cad2)==0){
        sprintf(menu,"10");
        write(fd2,menu,sizeof(menu));
        close(fd2);
    }
    
    
    
}

deleteCliente(){
    char data[50],sql[1024],idcad[10],menu[5],cad[1024],cad2[1024],deuda[100];
    int c1, c2,c3,m;
    printf("*******Borrar Cliente********* \n");
    printf("-----------------------------------\n");
    printf("Inserte el id del cliente:");
    scanf("%s",&idcad);

    fd2=open("IdCliente",O_WRONLY);
    write(fd2,idcad,sizeof(idcad));
    close(fd2);

    fd1=open("lista2",O_RDONLY);
    read(fd1,cad,sizeof(cad));
    close(fd1);
    printf("--------------------DATOS DEL CLIENTE %s--------------------------\n",idcad);
    printf("%s\n",cad);
    //sprintf(cad2,"%s",cad);
    //*Verificamos que exista el cliente
    for (int indice = 0; cad[indice] != '\0'; ++indice){
		c1=indice;
	}
    for (int indice = 0; cad2[indice] != '\0'; ++indice){
		c2=indice;
	}
    //*SI encuentra al cliente
    if(c1!=c2){
        printf("Cliente eliminado\n");

    }else if(strcmp(cad,cad2)==0){
        printf("No está el cliente en la lista\n");
    }

    
}

//?-----Seccion de articulos------------
menuArticulos(){
    int menu;
    char txt[5];
    clock_t begin;
    clock_t end;
    fd2=open("menu1",O_WRONLY);
    printf("------------------------------------\n");
    printf("              ARTICULOS             \n");
    printf("------------------------------------\n");
    printf("|1-Lista de articulos              |\n");
    printf("|2-Lista de inventario             |\n");
    printf("|3-Datos de un articulo            |\n");
    printf("|4-Añadir                          |\n");
    printf("|5-Actualizar Articulos            |\n");
    printf("|6-Actualizar Inventario           |\n");
    printf("|7-Borrar                          |\n");
    printf("|8-Salir                           |\n");
    printf("------------------------------------\n");
    scanf("%i",&menu);
    fd2=open("menu1",O_WRONLY);
    switch(menu){
        
        //*Lista de articulos 
        case 1:
            begin=clock();
            sprintf(txt,"7");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(2);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*lista de inventario
        case 2:
            begin=clock();
            sprintf(txt,"8");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(3);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*Datos de un articulo
        case 3:
            begin=clock();
            sprintf(txt,"9");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showOneArticulo();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*añadir
        case 4:
            begin=clock();
            sprintf(txt,"10");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            addarti();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*Actualizar
        case 5:
            begin=clock();
            sprintf(txt,"11");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            updateArticulo();
            printf("Cierra update\n");
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        case 6:
            begin=clock();
            sprintf(txt,"12");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            updateInventario();
            printf("Cierra update\n");
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;

        break;
        //*borrar
        case 7:
            begin=clock();
            sprintf(txt,"13");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            deleteArticulo();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*regresar al menu principal
        case 8:
            printf("||||||....Regresando al menu principal.....|||||\n");
        break;
    }
    
        printf("\n-----------------------\nTiempo de ejecucion:%f\n", tiempo);

}
//*Muestra un solo articulo
void showOneArticulo(){
    char idcad[10],cad[2024];
    int idcli;
    sprintf(idcad,"");
    
    printf("Inserte el id del articulo:");
    scanf("%i",&idcli);
    sprintf(idcad,"%i",idcli);

    fd2=open("IdArticulo",O_WRONLY);
    write(fd2,idcad,sizeof(idcad));
    close(fd2);

    fd1=open("lista2",O_RDONLY);
    read(fd1,cad,sizeof(cad));
    close(fd1);
    printf("--------------------DATOS DEL ARTICULO %i--------------------------\n",idcli);
    printf("%s\n",cad);
    return 0;
}
addarti(){
    char cad[2024],name[50],marca[50],descri[50],precio[10],cad2[2];
    int op;
    sprintf(cad,"");
    sprintf(name,"");
    printf("Coloque el nombre del articulo\n");
    scanf("%s",&name);
    printf("Coloque la marca del articulo\n");
    scanf("%s",&marca);
    printf("Coloque el tipo de articulo\n");
    scanf("%s",&descri);
    printf("Coloque el precio del articulo\n$");
    scanf("%s",&precio);

    fd2=open("sqldata",O_WRONLY);
    write(fd2,name,sizeof(name));
    close(fd2);

    fd1=open("mensaje",O_RDONLY);
    read(fd1,cad2,sizeof(cad2));
    close(fd1);

    if((op=atoi(cad2))==1){
        printf("Articulo agregado\n");
        sprintf(cad,"'%s','%s','%s',%s",name,marca,descri,precio);
        fd2=open("sqldata",O_WRONLY);
        write(fd2,cad,sizeof(cad));
        close(fd2);
    }else if((op=atoi(cad2))==2){
        printf("Articulo ya existente\n");
    }
}
//*Actualizar articulo
updateArticulo(){
    char data[50],sql[1024],idcad[10],menu[5],cad[1024],cad2[1024],deuda[100];
    int c1, c2,c3,m;
    float de,abo,res;
    sprintf(idcad,"");//*LImpiamos cadena
    sprintf(menu,"");//*LImpiamos cadena
    sprintf(cad2,"No vendemos el articulo que busca\n");

    printf("*******Actualizar Articulo*********\n");
    printf("-----------------------------------\n");
    printf("Inserte el id del articulo:");
    scanf("%s",&idcad);

    fd2=open("IdArticulo",O_WRONLY);
    write(fd2,idcad,sizeof(idcad));
    close(fd2);

    fd1=open("lista2",O_RDONLY);
    read(fd1,cad,sizeof(cad));
    close(fd1);
    printf("--------------------DATOS DEL ARTICULO %s--------------------------\n",idcad);
    printf("%s\n",cad);
    //sprintf(cad2,"%s",cad);
    for (int indice = 0; cad[indice] != '\0'; ++indice){
		c1=indice;
	}
    for (int indice = 0; cad2[indice] != '\0'; ++indice){
		c2=indice;
	}

    printf("C1:%i-----C2:%i\n",c1,c2);


    //*Si hay un cliente manda al servidor la indicacion del menu
    fd2=open("menuupdate",O_WRONLY);
    if(c1!=c2){
        printf("****Actualizar Articulo***** \n");
        printf("-------------------------\n");
        printf("|1-Nombre                |\n");
        printf("|2-Marca                 |\n");
        printf("|3-Descripcion           |\n");
        printf("|4-Precio                |\n");
        printf("--------------------------\n");
        scanf("%i",&m);
        sprintf(menu,"%i",m);
        write(fd2,menu,sizeof(menu));
        close(fd2);
        
        //*Switch para el menu de la actualizacion
        if(m>=1 && m<5){
            printf("Coloque el nuevo dato\n");
            scanf("%s",&data);
            for (int indice = 0; data[indice] != '\0'; ++indice){
		        data[indice] = toupper(data[indice]);
	        }
            fd1=open("data",O_WRONLY);
            write(fd1,data,sizeof(data));
            close(fd1);
        }else{
            printf("Funcion erronea\n");
            sprintf(menu,"10");
            write(fd2,menu,sizeof(menu));
            close(fd2);
        }


        
    }else if(strcmp(cad,cad2)==0){
        sprintf(menu,"10");
        write(fd2,menu,sizeof(menu));
        close(fd2);
    }
    
    
    
}
//*Actualizar inventario
updateInventario(){
    char data[50],sql[1024],idcad[10],menu[5],cad[1024],cad2[1024],inv[100];
    int c1, c2,c3,m,actual,new,res;
    
    sprintf(idcad,"");//*LImpiamos cadena
    sprintf(menu,"");//*LImpiamos cadena
    sprintf(cad2,"No vendemos el articulo que busca\n");

    printf("*******Actualizar INVENTARIO*********\n");
    printf("-----------------------------------\n");
    printf("Inserte el id del INVENTARIO:");
    scanf("%s",&idcad);

    fd2=open("IdArticulo",O_WRONLY);
    write(fd2,idcad,sizeof(idcad));
    close(fd2);

    fd1=open("lista2",O_RDONLY);
    read(fd1,cad,sizeof(cad));
    close(fd1);
    printf("--------------------DATOS DEL INVENTARIO %s--------------------------\n",idcad);
    printf("%s\n",cad);
    //sprintf(cad2,"%s",cad);
    for (int indice = 0; cad[indice] != '\0'; ++indice){
		c1=indice;
	}
    for (int indice = 0; cad2[indice] != '\0'; ++indice){
		c2=indice;
	}

    //*Si hay un cliente manda al servidor la indicacion del menu
    fd2=open("menuupdate",O_WRONLY);
    if(c1!=c2){
        printf("****Actualizar INVENTARIO***** \n");
        printf("-------------------------\n");
        printf("|1-Dar de alta           |\n");
        printf("|2-Dar de baja           |\n");
        printf("--------------------------\n");
        scanf("%i",&m);
        sprintf(menu,"1",1);
        write(fd2,menu,sizeof(menu));
        close(fd2);
        //leemos la cantidad de inventario
        fd1=open("data",O_RDWR);
        read(fd1,inv,sizeof(inv));
        close(fd1);
        actual=atoi(inv);
        switch(m){
            case 1:
                printf("Coloque el inventario a agregar\n");
                scanf("%i",&new);
                res=actual+new;
            break;
            
            case 2:
                printf("Coloque el inventario a dar de baja\n");
                scanf("%i",&new);
                if(new>actual){
                    printf("No se puede eliminar más de lo que hay\n");
                    m=10;
                }else{
                    res=actual-new;
                }
            break;

            default:
                printf("No contamos con esa opcion\n");
                m=10;
            break;
        }
        fd2=open("newdata",O_WRONLY);
        if(m==1||m==2){
            sprintf(data,"%i",res);
            write(fd2,data,sizeof(data));
            close(fd2);
        }else{
            write(fd2,inv,sizeof(inv));
            close(fd2);
        }
    }else if(strcmp(cad,cad2)==0){
        sprintf(menu,"10");
        write(fd2,menu,sizeof(menu));
        close(fd2);
    }
    
    
}


//borrar articulo
deleteArticulo(){
    char data[50],sql[1024],idcad[10],menu[5],cad[1024],cad2[1024],deuda[100];
    int c1, c2,c3,m;
    printf("*******Borrar Articulo********* \n");
    printf("-----------------------------------\n");
    printf("Inserte el id del articulo:");
    scanf("%s",&idcad);

    fd2=open("IdArticulo",O_WRONLY);
    write(fd2,idcad,sizeof(idcad));
    close(fd2);

    fd1=open("lista2",O_RDONLY);
    read(fd1,cad,sizeof(cad));
    close(fd1);
    printf("--------------------DATOS DEL Articulo %s--------------------------\n",idcad);
    printf("%s\n",cad);
    //sprintf(cad2,"%s",cad);
    //*Verificamos que exista el articulo
    for (int indice = 0; cad[indice] != '\0'; ++indice){
		c1=indice;
	}
    for (int indice = 0; cad2[indice] != '\0'; ++indice){
		c2=indice;
	}
    //*SI encuentra al cliente
    if(c1!=c2){
        printf("Articulo eliminado\n");

    }else if(strcmp(cad,cad2)==0){
        printf("No está el Articulo en la lista\n");
    }

    
}

//!Seccion de ventaas
menuVentas(){
    int menu;
    char txt[5];
    clock_t begin;
    clock_t end;
    fd2=open("menu1",O_WRONLY);
    printf("------------------------------------\n");
    printf("                VENTAS              \n");
    printf("------------------------------------\n");
    printf("|1-Lista de ventas hechas          |\n");
    printf("|2-Datos de una venta              |\n");
    printf("|3-Mostrar facturas                |\n");
    printf("|4-Mostrar Facturas con credito    |\n");
    printf("|5-Mostrar Facturas con descuento  |\n");
    printf("|6-Mostrar articulo más vendido    |\n");
    printf("|7-Mostrar articulo menos vendido  |\n");
    printf("|8-Realizar una venta              |\n");
    printf("|9-Salir                           |\n");
    printf("------------------------------------\n");
    scanf("%i",&menu);
    fd2=open("menu1",O_WRONLY);
    switch(menu){
        
        //*Lista de ventas hechas 
        case 1:
            begin=clock();
            sprintf(txt,"14");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(4);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*lista de unq venta
        case 2:
            begin=clock();
            sprintf(txt,"15");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(4);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*Mostrar facutras
        case 3:
            begin=clock();
            sprintf(txt,"16");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(5);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*mostrar facturas con credito
        case 4:
            begin=clock();
            sprintf(txt,"17");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(5);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*mostrar facturas con descuento
        case 5:
            begin=clock();
            sprintf(txt,"18");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(5);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*mostrar articulo más vendido
        case 6:
            begin=clock();
            sprintf(txt,"19");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(3);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*mostrar  articulos menos vendidos
        case 7:
            begin=clock();
            sprintf(txt,"20");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            showdata(3);
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*Venta de un articulo
        case 8:
            begin=clock();
            sprintf(txt,"21");
            write(fd2,txt,sizeof(txt));
            close(fd2);
            addarti();
            end=clock();
            tiempo+=(double)(end-begin)/CLOCKS_PER_SEC;
        break;
        //*regresar al menu principal
        case 9:
            printf("||||||....Regresando al menu principal.....|||||\n");
        break;
    }
    
        printf("\n-----------------------\nTiempo de ejecucion:%f\n", tiempo);

}
