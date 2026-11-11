/*
8. Se dispone de un archivo que contiene información de los vuelos realizados por las distintas aerolíneas a
lo largo del mes. El archivo se denomina Vuelos.dat y guarda los registros con la siguiente estructura:
• Código Aerolínea (alfanumérico de 10 caracteres máximo)
• Día (entero)
• Número de Vuelo (entero)
• Costo del pasaje (real)
• Pasajeros (inicialmente en el archivo viene en 0)
Luego se dispone de un segundo archivo llamado Pasajeros.dat que incluye la información de los viajeros
del mes para la aerolínea con código “Aero1”, el archivo contiene los siguientes campos:
• DNI (entero)
• Número de Vuelo (entero)
Se desea realizar un programa que actualice la cantidad de pasajeros de la aerolínea con código “Aero1”
con la información de los pasajeros que realizaron los viajes. Tenga en cuenta que los números de vuelo se
repiten entre las distintas aerolíneas. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ESTRUCTURAS
typedef struct{
    char Codigo[11];
    int Dia;
    int NumeroVuelo;
    float CostoPasaje;
    int Pasajeros;
}AEROLINEAS;

typedef struct{
    int DNI;
    int NumeroVuelo;
}PASAJERO;

//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
void LecturaAerolinea(char[]);
void LecturaPasajeros(char[]);

int main(){
    FILE *ArchAero, *ArchPasajero;
    AEROLINEAS aerolineas;
    PASAJERO pasajero;
    ArchAero = AbrirArchivo("VUELOS.dat", "r+b");
    ArchPasajero = AbrirArchivo("PASAJEROS.dat", "rb");

    rewind(ArchPasajero);
    fread(&pasajero, sizeof(PASAJERO), 1, ArchPasajero);
    while(!feof(ArchPasajero)){
        rewind(ArchAero);
        fread(&aerolineas, sizeof(AEROLINEAS), 1, ArchAero);
        while(!feof(ArchAero)){
            if((strcmpi("Aero1", aerolineas.Codigo)==0) && (aerolineas.NumeroVuelo == pasajero.NumeroVuelo)){
                aerolineas.Pasajeros++;
                fseek(ArchAero, sizeof(AEROLINEAS)*-1, SEEK_CUR);
                fwrite(&aerolineas, sizeof(AEROLINEAS), 1, ArchAero);
                fflush(ArchAero);
            }
            fread(&aerolineas, sizeof(AEROLINEAS), 1, ArchAero);
        }
        fread(&pasajero, sizeof(PASAJERO), 1, ArchPasajero);
    }
    fclose(ArchAero);
    fclose(ArchPasajero);
    LecturaAerolinea("VUELOS.dat");
    LecturaPasajeros("PASAJEROS.dat");
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

void LecturaAerolinea(char Nombre[]){
    FILE *Archivo;
    AEROLINEAS aerolinea;
    Archivo = AbrirArchivo(Nombre, "rb");
    rewind(Archivo);
    fread(&aerolinea, sizeof(AEROLINEAS), 1, Archivo);
    printf("Codigo aerolinea: \tDia\tNumero Vuelo: \tPrecio\tPasajeros\n");
    while(!feof(Archivo)){
        printf("%s\t\t\t%d\t\t%d\t%.2f\t%d\n", aerolinea.Codigo, aerolinea.Dia, aerolinea.NumeroVuelo, aerolinea.CostoPasaje, aerolinea.Pasajeros);
        fread(&aerolinea, sizeof(AEROLINEAS), 1, Archivo);
    }
    fclose(Archivo);
}

void LecturaPasajeros(char Nombre[]){
    FILE *Archivo;
    PASAJERO pasajeros;
    Archivo = AbrirArchivo(Nombre, "rb");
    rewind(Archivo);
    fread(&pasajeros, sizeof(PASAJERO), 1, Archivo);
    printf("Dni\t\tNum vuelo:\n");
    while(!feof(Archivo)){
        printf("\n%d\t%d\n", pasajeros.DNI, pasajeros.NumeroVuelo);
        fread(&pasajeros, sizeof(PASAJERO), 1, Archivo);
    }
fclose(Archivo);
}
