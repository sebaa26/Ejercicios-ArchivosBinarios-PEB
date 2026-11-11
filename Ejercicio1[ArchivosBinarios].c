/* 1. Los datos de los alumnos de una comisión de Computación Transversal son:
• Número de DNI (entero)
• Nombre y Apellido (80 caracteres)
• Nota1, Nota2 (entero)
• Nota Promedio (real, calculado según Nota1 y Nota2)
 a. Declarar un tipo de dato que contenga la información del alumno.
 b. Con la información indicada para los alumnos. Grabar los datos en el archivo “ALUMNOS.dat”. Esta
 información de grabación finaliza con DNI cero.
 c. Leer los datos del archivo, mediante la Función LECTURA.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//STRUCTS
typedef struct{
    int DNI;
    char NombreyApellido[82];
    int Nota1;
    int Nota2;
    float NotaProm;
}ALUMNO;
//PROTOTIPOS
FILE *abrir_archivo(char[], char[]);
int EstaDentroDelRangoCF(int, int, int);
void LeerTexto(char[], int);
int LeeryValidar(int, int);
float Promedio(int, int);
void LECTURA();

int main(){
    FILE *pf;
    ALUMNO alumno;
    int DNI, Nota1, Nota2;
    float NotaProm;
    char NombreyApellido[82];
    pf = abrir_archivo("ALUMNOS.dat", "wb");
    printf("Ingrese el DNI del alumno (Ingrese 0 para salir)\n");
    DNI = EstaDentroDelRangoCF(100, 999, 0);
    while(DNI!=0){
        printf("Ingrese el nombre y apellido del alumno\n");
        LeerTexto(NombreyApellido, 82);
        printf("Ingrese la nota N°1 (0-10)\n");
        Nota1 = LeeryValidar(0, 10);
        printf("Ingrese la nota N°2 (0-10)\n");
        Nota2 = LeeryValidar(0, 10);
        NotaProm = Promedio(Nota1, Nota2);
        //Cargamos los datos
        alumno.DNI = DNI;
        strcpy(alumno.NombreyApellido, NombreyApellido);
        alumno.Nota1 = Nota1;
        alumno.Nota2 = Nota2;
        alumno.NotaProm = NotaProm;

        fwrite(&alumno, sizeof(ALUMNO), 1, pf);
        //Reingresamos los datos
        printf("Ingrese el DNI del alumno (Ingrese 0 para salir)\n");
        DNI = EstaDentroDelRangoCF(100, 999, 0);
    }
fclose(pf);
LECTURA();
return 0;
}
//FUNCIONES
FILE *abrir_archivo(char NombreArchivo[], char modo[]){
    FILE *alumnos;
    alumnos = fopen(NombreArchivo, modo);
    if(alumnos == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
return alumnos;
}

int EstaDentroDelRangoCF(int li, int ls, int cf){
    int dato;
    scanf("%d", &dato);
    while((dato<li || dato>ls) && dato != cf){
        printf("Dato invalido, ingrese dentro del rango (%d - %d) (ingrese %d para salir)\n", li, ls, cf);
        scanf("%d", &dato);
    }
return dato;
}

void LeerTexto(char Texto[], int ce){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(Texto, ce, stdin);
    Texto[strcspn(Texto, "\n")]='\0';
}

int LeeryValidar(int li, int ls){
    int dato;
    scanf("%d", &dato);
    while(dato<li || dato>ls){
        printf("Dato invalido, ingrese dentro del rango (%d - %d)", li, ls);
        scanf("%d", &dato);
    }
return dato;
}

float Promedio(int nota1, int nota2){
    float prom;
    prom=(float)(nota1+nota2)/2;
return prom;
}

void LECTURA(){
    FILE *pf;
    ALUMNO alumno;
    pf=abrir_archivo("ALUMNOS.dat", "rb");
    //Guardamos los datos del archivo para mostrarlos.
    fread(&alumno, sizeof(ALUMNO), 1, pf);
    while(!feof(pf)){
        printf("%d -- %s -- %d -- %d -- %.2f", alumno.DNI, alumno.NombreyApellido, alumno.Nota1, alumno.Nota2, alumno.NotaProm);
        fread(&alumno, sizeof(ALUMNO), 1, pf);
    }
fclose(pf);
}
