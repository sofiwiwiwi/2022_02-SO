#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){

    DIR *dir;
    DIR *dir2;
    struct dirent *dp;

    const char *path="./archivos"; //ubicacion inicial de los archivos
    char path1[300]="";
    char direc[300]; //string para el path completo final del archivo a mover
    char ano[300]; //strings para nombres de las carpetas
    char prioridad[100];

    char *aux;
    char aux2[300];

    int int_ano, int_prioridad;
    FILE *fp;

    if(opendir("./CWD") == NULL){ //verifica si existe la carpeta CWD, si no la crea
        mkdir("./CWD",0700);
    }
    
    dir = opendir(path); //Abre el directorio donde se encuentran los archivos .txt
    if(dir==NULL){
        printf("No se abrio el directorio");//si no retornara un error
        exit(2);
    }
    while( (dp=readdir(dir)) ){
        if ((strcmp(dp->d_name,".") == 0) || (strcmp(dp->d_name,"..") == 0)){    //salta las carpetas . y ..    
        }
        else{

            strcpy(direc, "./archivos/");
            strcat(direc, dp->d_name);

            fp = fopen(direc, "r"); //Abre el archivo .txt

            fscanf(fp, "%d", &int_ano); //lectura de datos
            fscanf(fp, "%d", &int_prioridad);

            sprintf(ano, "%d", int_ano); //conversion de int a string para los nombres de las carpetas
            sprintf(prioridad, "%d", int_prioridad);

            strcpy(aux2, "./CWD/");
            strcat(aux2, ano);

            dir2 = opendir(aux2);
            if(dir2==NULL){  //Verifica que no exista la carpeta, si existe sigue o si no la crea
                mkdir(aux2,0700);
            }

            strcpy(aux2, "./CWD/");
            strcat(aux2, ano);
            strcat(aux2, "/");  
            if(int_prioridad < 6000){
                strcat(aux2, "3000+");
                aux = "3000+";
            }
            else if(6000 <= int_prioridad && int_prioridad < 9000){  
                strcat(aux2, "6000+");
                aux = "6000+";
            }
            else{  
                strcat(aux2, "9000+");
                aux = "9000+";                
            }
            dir2 = opendir(aux2);

            if(dir2==NULL){  //Verifica que no exista la carpeta, si existe sigue o si no la crea
                mkdir(aux2,0700);
            }

            strcat(path1,"./CWD/"); //comienza a crear el path final del archivo
            strcat(path1, ano);
            strcat(path1, "/");
            strcat(path1,aux);
            strcat(path1,"/");
            strcat(path1,dp->d_name);
            rename(direc,path1); //Mueve el archivo a la carpeta
            strcpy(path1,"");
            fclose(fp);
            closedir(dir2);
        }
    }   
    closedir(dir);

    return 0;
}