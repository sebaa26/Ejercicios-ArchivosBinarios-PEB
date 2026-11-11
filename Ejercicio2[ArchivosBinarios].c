/* 2. Tomando como base el archivo ALUMNOS.DAT creado en el ejercicio anterior se desea desarrollar un
programa que, basado en la información del archivo, genere 3 archivos:
• Uno con los alumnos PROMOCIONADOS (ambas notas mayores o igual a 7).
• Otro archivo con los alumnos en condición CURSADO (ambas notas mayores o igual a 4 pero no
promocionados).
• Y un tercer archivo con los REPROBADOS (al menos una nota, menor que 4).
Para comprobar los datos guardados realizar una función que reciba por parámetro el nombre del archivo
a mostrar, lo abre y muestre su contenido. Se debe invocar a la función 3 veces para mostrar todos los
archivos generados. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ESTRUCTURAS
typedef struct{
    int DNI;
    char NombreyApellido[82];
    int Nota1;
    int Nota2;
    float NotaProm;
}ALUMNO;
//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
void LECTURA(char[]);

int main(){
    ALUMNO alum;
    FILE *archPROMOCIONADOS, *archCURSADO, *archREPROBADOS, *pf;
    pf = AbrirArchivo("ALUMNOS.dat", "rb");
    archPROMOCIONADOS = AbrirArchivo("PROMOCIONADOS.dat", "wb");
    archCURSADO = AbrirArchivo("CURSADO.dat", "wb");
    archREPROBADOS = AbrirArchivo("REPROBADOS.dat", "wb");

    fread(&alum, sizeof(alum), 1, pf);
    while(!feof(pf)){
        if(alum.Nota1>=7 && alum.Nota2>=7){
            fwrite(&alum, sizeof(ALUMNO), 1, archPROMOCIONADOS);
        }
        else if(alum.Nota1>=4 && alum.Nota2>=4){
            fwrite(&alum, sizeof(ALUMNO), 1, archCURSADO);
        }
        else{
            fwrite(&alum, sizeof(ALUMNO), 1 ,archREPROBADOS);
        }
        fread(&alum, sizeof(alum), 1, pf);
    }
    fclose(pf);
    fclose(archPROMOCIONADOS);
    fclose(archCURSADO);
    fclose(archREPROBADOS);
    //Una vez cerrado, llamamos a la funcion de lectura
    printf("PROMOCIONADOS\n");
    LECTURA("PROMOCIONADOS.dat");
    printf("CURSADAS\n");
    LECTURA("CURSADO.dat");
    printf("REPROBADOS\n");
    LECTURA("REPROBADOS.dat");
return 0;
}

FILE *AbrirArchivo(char NombreArch[], char Modo[]){
    FILE *Archivo;
    Archivo = fopen(NombreArch, Modo);
    if(Archivo == NULL){
        printf("No se pudo abrir el archivo %s, intente mas tarde\n", NombreArch);
        getchar();
        exit(1);
    }
return Archivo;
}

void LECTURA(char Nombre[]){
    ALUMNO alum;
    FILE *Arch;
    Arch = AbrirArchivo(Nombre, "rb");
    fread(&alum, sizeof(ALUMNO), 1, Arch);
    printf("DNI -- Nombre Y Apellido -- Nota 1 -- Nota 2 -- Promedio\n");
    while(!feof(Arch)){
        printf("%d -- %s -- %d -- %d -- %.f\n", alum.DNI, alum.NombreyApellido, alum.Nota1, alum.Nota2, alum.NotaProm);
        fread(&alum, sizeof(ALUMNO), 1, Arch);
    }
    fclose(Arch);
}
