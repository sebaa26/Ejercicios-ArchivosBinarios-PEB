/* 13. La empresa RED VIAL S.A. desea controlar el flujo vehicular en sus cabinas de peaje a lo largo del mes.
Para ello se debe procesar la información provista por las barreras que se encuentra almacenada en el
archivo barreras.dat que contiene la siguiente información:
• Día (entero)
• Hora (0 a 24)
• Número de barrera (entero)
Dentro del archivo la información se encuentra ordenada por día y hora. Determinar:
a. La cantidad de vehículos por cada hora.
b. La cantidad de vehículos de cada día.
c. Ingresar por teclado los precios del peaje para horario normal y horario pico (de 7 a 11 y de 17 a
19). Con esos valores guardar un archivo con la recaudación de cada día. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ESTRUCTURAS
typedef struct{
    int Dia;
    int Hora;
    int NumeroBarrera;
}BARRERA;

typedef struct{
    int Dia;
    float Recaudacion;
}RECAUDACION;

//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
float IngrMayorA(float);
void PROCESO();
void LECTURA();

int main(){
    PROCESO();
    return 0;
}

FILE *AbrirArchivo(char Nombre[], char Modo[]){
    FILE *Archivo;
    Archivo = fopen(Nombre, Modo);
    if(Archivo == NULL){
        printf("No se pudo abrir el archivo %s\n", Nombre);
        exit(1);
    }
return Archivo;
}

float IngrMayorA(float lim){
    float dato;
    scanf("%f", &dato);
    if(dato<lim){
        printf("Dato invalido, ingrese un numero mayor a %.2f\n", lim);
        scanf("%f", &dato);
    }
return dato;
}

void PROCESO(){
    FILE *ArchBarreras, *ArchRecaudacion;
    ArchBarreras = AbrirArchivo("barreras.dat", "rb");
    ArchRecaudacion = AbrirArchivo("Recaudacion.dat", "wb");
    BARRERA barreras;
    RECAUDACION recaudacion;
    //Variables Auxiliares
    int CantHora, CantDia, AnteriorDia, AnteriorHora;
    float PrecioNormal, PrecioPico, RecaudacionDia;
    printf("Ingrese el precio Normal\n");
    PrecioNormal = IngrMayorA(0);
    printf("Ingrese el precio en hora pico\n");
    PrecioPico = IngrMayorA(0);
    fread(&barreras, sizeof(BARRERA), 1, ArchBarreras);
    while(!feof(ArchBarreras)){
        //Inicializamos las variables
        AnteriorDia = barreras.Dia;
        RecaudacionDia = 0;
        CantDia = 0;
        while(!feof(ArchBarreras) && barreras.Dia == AnteriorDia){
            AnteriorHora = barreras.Hora;
            CantHora = 0;
            while(!feof(ArchBarreras) && barreras.Hora == AnteriorHora && barreras.Dia == AnteriorDia){
                CantHora++;
                CantDia++;
                //Conseguimos lo Recaudado
                if(barreras.Hora>=7 && barreras.Hora<=11 || barreras.Hora>=17 && barreras.Hora<=19){
                    RecaudacionDia += PrecioPico;
                }
                else{
                    RecaudacionDia += PrecioNormal;
                }
                fread(&barreras, sizeof(BARRERA), 1, ArchBarreras);
            }
            printf("Dia %d -- Hora %d -- Vehiculos: %d\n", AnteriorDia, AnteriorHora, CantHora);
        }
        //Escribimos los datos de lo recaudado
        recaudacion.Dia = AnteriorDia;
        recaudacion.Recaudacion = RecaudacionDia;
        fwrite(&recaudacion, sizeof(RECAUDACION), 1, ArchRecaudacion);
        printf("Cantidad de vehiculos del dia %d: %d\n", AnteriorDia, CantDia);
    }
fclose(ArchBarreras);
fclose(ArchRecaudacion);
LECTURA();
}

void LECTURA(){
    FILE *Archivo;
    Archivo = AbrirArchivo("Recaudacion.dat", "rb");
    RECAUDACION recaudacion;
    printf("Total Recaudado en el dia\n");
    fread(&recaudacion, sizeof(RECAUDACION), 1, Archivo);
    while(!feof(Archivo)){
        printf("DIA: %d -- TOTAL RECAUDADO: %.2f\n", recaudacion.Dia, recaudacion.Recaudacion);
        fread(&recaudacion, sizeof(RECAUDACION), 1, Archivo);
    }
}
