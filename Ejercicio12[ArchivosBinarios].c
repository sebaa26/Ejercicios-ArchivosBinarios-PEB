/*
12. Se dispone de un archivo con nombre Llamadas.dat que contiene llamadas telefónicas realizadas en una
empresa. Por cada llamada se dispone de la siguiente información:
• Sector (15 caracteres máximo)
• Duración en segundos (entero)
• Tipo de llamada (entero: 1 local, 2 larga distancia, 3 celular)
El archivo se encuentra organizado por Sector. Se solicita:
a. Calcular y mostrar por cada sector, la cantidad de llamadas realizadas de cada tipo.
b. Determinar cuál es el sector que habló la mayor cantidad de tiempo.
c. En un archivo llamado costos.dat hay un único registro que contiene los costos por segundo de los
tres tipos de llamadas (3 float). Se debe generar el archivo gastos.dat que totalice los gastos de
llamadas de cada sector.
d. Realizar una función que muestre los datos almacenados en gastos.dat en forma de listado.
e. Generar un archivo para cada sector con el detalle de llamadas valorizado. El archivo se debe
generar con nombresector.dat y debe contener:
• Duración en segundos (entero)
• Tipo de llamada (entero)
• Costo de la llamada (float)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ESTRUCTURAS
typedef struct{
    char Sector[16];
    int Duracion;
    int Tipo;
}LLAMADAS;

typedef struct{
    float Costo1;
    float Costo2;
    float Costo3;
}COSTOS;

typedef struct{
    char Sector[16];
    float Costo;
}GASTOS;

typedef struct{
    int Duracion;
    int Tipo;
    float Costo;
}DetalleValorizado;

//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
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

void PROCESO(){
    FILE *ArchLlamadas, *ArchCostos, *ArchGastos, *ArchSectores;
    LLAMADAS llamadas;
    COSTOS costos;
    GASTOS gastos;
    DetalleValorizado detalle;
    //Variables auxiliares
    int CantidadLLamadas, MaxSegundos, flag=-1, CantidadSegundos, c1, c2, c3;
    float CostoTotal, costoActual;
    char  AnteriorSector[16], MaxSector[16], ArchNuevoSector[25];
    //Abrimos los archivos
    ArchLlamadas = AbrirArchivo("LLAMADAS.dat", "rb");
    ArchCostos = AbrirArchivo("COSTOS.dat", "rb");
    //Creamos el archivo en modo de escritura
    ArchGastos = AbrirArchivo("GASTOS.dat", "wb");

    rewind(ArchLlamadas);
    fread(&llamadas, sizeof(LLAMADAS), 1, ArchLlamadas);
    fread(&costos, sizeof(COSTOS), 1, ArchCostos);
    while(!feof(ArchLlamadas)){
        CantidadLLamadas = 0;
        CantidadSegundos = 0;
        CostoTotal = 0;
        c1=0;
        c2=0;
        c3=0;
        costoActual=0;
        strcpy(AnteriorSector, llamadas.Sector);
        //Armamos el nombre del nuevo archivo dinamico
        strcpy(ArchNuevoSector, llamadas.Sector);
        strcat(ArchNuevoSector, ".dat");
        while(!feof(ArchLlamadas) && strcmpi(AnteriorSector, llamadas.Sector) == 0){
            CantidadLLamadas++;
            CantidadSegundos+=llamadas.Duracion;
            if(llamadas.Tipo == 1){
                c1++;
                costoActual = llamadas.Duracion * costos.Costo1;
            }
            else if(llamadas.Tipo == 2){
                c2++;
                costoActual = llamadas.Duracion * costos.Costo2;
            }
            else{
                c3++;
                costoActual = llamadas.Duracion * costos.Costo3;
            }
            CostoTotal+=costoActual;
            //PUNTO E
            detalle.Duracion = llamadas.Duracion;
            detalle.Costo = costoActual;
            detalle.Tipo = llamadas.Tipo;
            fwrite(&detalle, sizeof(DetalleValorizado), 1, ArchSectores);
            //Releemos el archivo llamadas
            fread(&llamadas, sizeof(LLAMADAS), 1, ArchLlamadas);
        }
        //Cerramos el archivo ya que cargo todas las llamadas del sector
        fclose(ArchSectores);
        //PUNTO A
        printf("Cantidad de tipos de llamadas del sector %s: \n TIPO 1:%d -- TIPO 2: %d -- TIPO 3: %d\n", AnteriorSector, c1, c2, c3);
        //PUNTO B
        if(flag == -1 || MaxSegundos < CantidadSegundos){
            MaxSegundos = CantidadSegundos;
            strcpy(MaxSector, AnteriorSector);
            flag = 0;
        }
        //CARGAMOS LOS DATOS
        strcpy(gastos.Sector, AnteriorSector);
        gastos.Costo = CostoTotal;
        fwrite(&gastos, sizeof(GASTOS), 1, ArchGastos);
    }
    fclose(ArchLlamadas);
    fclose(ArchGastos);
    fclose(ArchCostos);
    printf("Listado de el costo de las llamadas\n");
    LECTURA(ArchGastos);
}

void LECTURA(FILE *Archivo){
    Archivo = AbrirArchivo("GASTOS.dat", "rb");
    GASTOS gastos;
    rewind(Archivo);
    fread(&gastos, sizeof(GASTOS), 1, Archivo);
    while(!feof(Archivo)){
        printf("SECTOR: %s -- COSTO: %.2f\n", gastos.Sector, gastos.Costo);
        fread(&gastos, sizeof(GASTOS), 1, Archivo);
    }
}
