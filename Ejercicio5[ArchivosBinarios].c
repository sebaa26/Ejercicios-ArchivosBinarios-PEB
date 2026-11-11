/*
5.
Se desea realizar un programa que permita actualizar la lista de precios de una empresa en forma
individual a cada uno de sus productos.
Los productos que están guardados en el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Para modificar un precio se ingresa por teclado el código del producto y el nuevo precio. La modificación
de precios finaliza con un código de producto igual a 0.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ESTRUCTURAS
typedef struct{
    int Codigo;
    float Precio;
    char Descripcion[51];
}PRODUCTOS;
//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
int IngrMayorIgualA(int);
float IngrFloatMayorA(float);
int Busqueda(FILE *, int);

int main(){
    int Codigo, pos;
    float Precio;
    FILE *Arch;
    Arch = AbrirArchivo("productos.dat", "r+b");
    PRODUCTOS prod={{355, 1500.0, "Tanza"}};
    fwrite(&prod, sizeof(PRODUCTOS), 1, Arch);
    printf("Ingrese el codigo de producto para cambiar su precio (ingrese 0 para salir)\n");
    Codigo = IngrMayorIgualA(0);
    while(Codigo != 0){
        pos = Busqueda(Arch, Codigo);
        if(pos == -1){
            printf("El codigo %d no es valido\n", Codigo);
        }
        else{
            printf("Ingrese el precio nuevo\n");
            Precio = IngrFloatMayorA(0.0);
            fseek(Arch, pos*sizeof(PRODUCTOS), SEEK_SET);
            fread(&prod, sizeof(PRODUCTOS), 1, Arch);
            prod.Precio = Precio;
            fseek(Arch, pos*sizeof(PRODUCTOS), SEEK_SET);
            fwrite(&prod, sizeof(PRODUCTOS), 1, Arch);
            printf("Precio actualizado correctamente\n");
            fflush(Arch);
        }
        printf("Ingrese el codigo de producto para cambiar su precio (ingrese 0 para salir)\n");
        Codigo = IngrMayorIgualA(0);
    }
fclose(Arch);
return 0;
}

FILE *AbrirArchivo(char Nombre[], char Modo[]){
    FILE *Archivo;
    Archivo = fopen(Nombre, Modo);
    if(Archivo == NULL){
        printf("No se pudo abrir correctamente el archivo %s\n", Nombre);
        exit(1);
    }
return Archivo;
}

int IngrMayorIgualA(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<lim){
        printf("Dato invalido, ingrese dentro del rango (> %d)\n", lim);
        scanf("%d", &dato);
    }
return dato;
}

float IngrFloatMayorA(float lim){
    float dato;
    scanf("%f", &dato);
    while(dato<lim){
        printf("Dato invalido, ingrese dentro del rango (> %.2f)\n", lim);
        scanf("%f", &dato);
    }
return dato;
}

int Busqueda(FILE *Archivo, int dato){
    PRODUCTOS prod;
    int numRegistro=-1, i=0;
    fseek(Archivo, 0, SEEK_SET);
    fread(&prod, sizeof(PRODUCTOS), 1, Archivo);
    while(!feof(Archivo) && numRegistro==-1){
        if(prod.Codigo == dato){
            numRegistro = i;
        }
        else{
            i++;
            fread(&prod, sizeof(PRODUCTOS), 1, Archivo);
        }
    }
return numRegistro;
}
