/*
6. Dado el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Realizar un programa que permita eliminar productos dado su código
*/
//ESTRUCTURA
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    int Codigo;
    float Precio;
    char Descripcion[51];
}PRODUCTOS;
//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
int IngrMayorIgualA(int);
int Busqueda(FILE*, int);

int main(){
    FILE *Archivo, *BorradosTemp;
    Archivo = AbrirArchivo("productos.dat", "r+b");
    BorradosTemp = AbrirArchivo("Temporal.dat", "wb");
    PRODUCTOS prod;
    int codigo, pos, Borrado=-1;
    printf("Ingrese el codigo de producto a borrar (0 = Salir)\n");
    codigo = IngrMayorIgualA(0);
    while(codigo != 0){
        pos = Busqueda(Archivo, codigo);
        if(pos == -1){
            printf("Codigo no existente\n");
        }
        else{
            fseek(Archivo, pos * sizeof(PRODUCTOS), SEEK_SET);
            fread(&prod, sizeof(PRODUCTOS), 1, Archivo);
            prod.Codigo = -1;
            fseek(Archivo, -(long)sizeof(PRODUCTOS), SEEK_CUR);
            fwrite(&prod, sizeof(PRODUCTOS), 1, Archivo);
        }
        printf("Ingrese el codigo de producto a borrar (0 = Salir)\n");
        codigo = IngrMayorIgualA(0);
    }
    fseek(Archivo, 0, SEEK_SET);
    fread(&prod, sizeof(PRODUCTOS), 1, Archivo);
    while(!feof(Archivo)){
        if(prod.Codigo != Borrado){
            fwrite(&prod, sizeof(PRODUCTOS), 1, BorradosTemp);
        }
        fread(&prod, sizeof(PRODUCTOS), 1, Archivo);
    }
fclose(Archivo);
fclose(BorradosTemp);

remove("productos.dat");
rename("Temporal.dat", "productos.dat");
return 0;
}

FILE *AbrirArchivo(char nombre[], char modo[]){
    FILE *pf;
    pf = fopen(nombre, modo);
    if(pf == NULL){
        printf("No se pudo abrir el archivo %s\n", nombre);
        exit(1);
    }
return pf;
}

int IngrMayorIgualA(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<lim){
        printf("Dato invalido\n");
        scanf("%d", &dato);
    }
return dato;
}

int Busqueda(FILE *Archivo, int Buscado){
    int i=0, posBuscada=-1;
    PRODUCTOS prod;
    fseek(Archivo, 0, SEEK_SET);
    fread(&prod, sizeof(PRODUCTOS), 1, Archivo);
    while(!feof(Archivo) && posBuscada == -1){
        if(prod.Codigo == Buscado){
            posBuscada = i;
        }
        else{
            i++;
            fread(&prod, sizeof(PRODUCTOS), 1, Archivo);
        }
    }
return posBuscada;
}



