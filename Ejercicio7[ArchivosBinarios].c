/* 7. Se dispone de un archivo llamado Stock.dat que contiene la información de los productos que vende una
fábrica. En el archivo se guarda:
• Código de artículo (entero)
• Descripción (50 caracteres máximo)
• Stock (entero)
Luego se ingresan por teclado las ventas a realizar indicando:
• Código de artículo
• Cantidad
La carga por teclado de las ventas finaliza con un código de artículo igual a 0.
Por cada venta se debe controlar si hay stock suficiente y si lo hay, restar el stock de dicho producto, sino
hay stock se debe vender lo que quede disponible y grabar un registro en un archivo Faltantes.dat con la
cantidad que no pudo venderse, dicho registro debe contener:
• Código de artículo
• Cantidad faltante
Si ya hay un registro previo en dicho archivo de faltantes con el mismo producto debe incrementarse la
cantidad. */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ESTRUCTURA
typedef struct{
    int Codigo;
    char Descripcion[51];
    int Stock;
}PRODUCTOS;

typedef struct{
    int Codigo;
    int Stock;
}FALTANTE;
//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
int IngrMayorIgualA(int);
int IngrMayorA(int);
int BusquedaCodigo(FILE *, int);
int BusquedaFaltante(FILE *, int);

int main(){
    PRODUCTOS productos;
    FALTANTE faltante;
    FILE *ArchOrig, *ArchFalt;
    ArchOrig = AbrirArchivo("Stock.dat", "r+b");
    ArchFalt = AbrirArchivo("Faltantes.dat", "w+b");
    int Codigo, Cantidad, pos, cantidadFaltante;

    printf("Ingrese el codigo de articulo\n");
    Codigo = IngrMayorIgualA(0);
    while(Codigo != 0){
        pos = BusquedaCodigo(ArchOrig, Codigo);
        if(pos == -1){
            printf("Codigo Inexistente\n");
        }
        else{
            printf("Ingrese la cantidad a comprar\n");
            Cantidad = IngrMayorA(0);
            rewind(ArchOrig);
            fseek(ArchOrig, pos*sizeof(PRODUCTOS), SEEK_SET);
            fread(&productos, sizeof(PRODUCTOS), 1, ArchOrig);
            if(productos.Stock < Cantidad){
                pos = BusquedaFaltante(ArchFalt, Codigo);
                if(pos == -1){
                    cantidadFaltante = Cantidad - productos.Stock;
                    productos.Stock = 0;
                    faltante.Codigo = Codigo;
                    faltante.Stock = cantidadFaltante;
                    fseek(ArchOrig, sizeof(PRODUCTOS)*-1, SEEK_CUR);
                    fwrite(&productos, sizeof(PRODUCTOS), 1, ArchOrig);
                    fseek(ArchFalt, 0, SEEK_END);
                    fwrite(&faltante, sizeof(FALTANTE), 1, ArchFalt);
                }
                else{
                    fseek(ArchFalt, pos * sizeof(FALTANTE), SEEK_SET);
                    fread(&faltante, sizeof(FALTANTE), 1, ArchFalt);
                    cantidadFaltante = productos.Stock + Cantidad;
                    faltante.Stock += cantidadFaltante;
                    fseek(ArchFalt, sizeof(FALTANTE)*-1, SEEK_CUR);
                    fwrite(&faltante, sizeof(FALTANTE), 1, ArchFalt);
                }
            }
            else{
                productos.Stock -= Cantidad;
                fseek(ArchOrig, sizeof(PRODUCTOS)*-1, SEEK_CUR);
                fwrite(&productos, sizeof(PRODUCTOS), 1, ArchOrig);
            }
        }
        printf("Ingrese el codigo de articulo\n");
        Codigo = IngrMayorIgualA(0);
    }
fclose(ArchOrig);
fclose(ArchFalt);
return 0;
}
//FUNCIONES

FILE *AbrirArchivo(char Nombre[], char Modo[]){
    FILE *Archivo;
    Archivo = fopen(Nombre, Modo);
    if(Archivo == NULL){
        printf("No se pudo abrir el archivo %s\n", Nombre);
        exit(1);
    }
return Archivo;
}

int IngrMayorIgualA(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato< lim){
        printf("Dato invalido, ingrese dentro del rango (>=%d)\n", lim);
        scanf("%d", &dato);
    }
return dato;
}

int IngrMayorA(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato <= lim){
        printf("Dato invalido, ingrese dentro del rango (>%d)\n", lim);
        scanf("%d", &dato);
    }
return dato;
}

int BusquedaCodigo(FILE *Archivo, int Buscado){
    int posBuscada=-1, i=0;
    PRODUCTOS prod;
    fseek(Archivo, 0, SEEK_SET);
    fread(&prod, sizeof(PRODUCTOS), 1, Archivo);
    while(!feof(Archivo) && posBuscada==-1){
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

int BusquedaFaltante(FILE *Archivo, int Buscado){
    int posBuscada=-1, i=0;
    FALTANTE falt;
    fseek(Archivo, 0, SEEK_SET);
    fread(&falt, sizeof(FALTANTE), 1, Archivo);
    while(!feof(Archivo) && posBuscada==-1){
        if(falt.Codigo == Buscado){
            posBuscada = i;
        }
        else{
            i++;
            fread(&falt, sizeof(FALTANTE), 1, Archivo);
        }
    }
return posBuscada;
}
