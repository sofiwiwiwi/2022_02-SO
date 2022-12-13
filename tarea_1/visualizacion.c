#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){

    int ano_count, k3count, k6count, k9count; //contadores
    int k3globalcount, k6globalcount, k9globalcount;
    char aux[300] = "";
    char ch_ano[300]; 
    char ch_prioridad[100];
    DIR * dirp;
    struct dirent * entry;
    k3globalcount= k6globalcount= k9globalcount=0;
    
    for(int ano = 2019; ano <= 2021; ano++){
        ano_count=0;
        for(int prioridad = 3000; prioridad <= 9000; prioridad = prioridad + 3000){
            strcpy(aux,"");
            sprintf(ch_ano, "%d", ano); //conversion de int a string para luego poder concatenar
            sprintf(ch_prioridad, "%d", prioridad);

            if(prioridad < 6000){
                k3count=0;           
            }
            else if(6000 <= prioridad && prioridad < 9000){
                k6count=0;            
            }
            else{
                k9count=0;
            }

            strcat(aux, "./CWD/"); //comienza a crear el path para que se abra el archivo
            strcat(aux, ch_ano);
            strcat(aux, "/");
            strcat(aux, ch_prioridad);
            strcat(aux, "+");
            dirp = opendir(aux); 
            
            if(dirp==NULL){  //Verifica que no exista la carpeta, si no existe se asume que no hay ningún estudiante.
                if(prioridad < 6000){
                    k3count=0;           
                }
                else if(6000 <= prioridad && prioridad < 9000){
                    k6count=0;            
                }
                else{
                    k9count=0;
                }
            }
            else{
                while ((entry = readdir(dirp)) != NULL) {
                    if (entry->d_type == DT_REG) {// chequea si la entrada es una carpeta valida, si es que si la cuenta
                        ano_count++;
                        if(prioridad < 6000){
                            k3count++;
                            k3globalcount++;
                        }
                        else if(6000 <= prioridad && prioridad < 9000){
                            k6count++;
                            k6globalcount++;
                        }
                        else{
                            k9count++;
                            k9globalcount++;
                        }
                    }
                }
            }
            closedir(dirp);    
        }
        printf("La cantidad de estudiantes para el año %d es %d\n", ano, ano_count);
        printf("\tLa cantidad de estudiantes de año %d con prioridad 3000-5999 son: %d\n",ano,k3count);
        printf("\tLa cantidad de estudiantes de año %d con prioridad 6000-8999 son: %d\n",ano,k6count);
        printf("\tLa cantidad de estudiantes de año %d con prioridad 9000+ son: %d\n",ano,k9count);
    }
    printf("Del total de estudiantes:\n");
    printf("\tExisten %d con prioridad 3000-5999.\n",k3globalcount);
    printf("\tExisten %d con prioridad 6000-8999.\n",k6globalcount);
    printf("\tExisten %d con prioridad 9000+.\n",k9globalcount);
    return 0;
}