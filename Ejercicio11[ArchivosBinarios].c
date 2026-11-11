/* 11. Se dispone de un archivo llamado Rating.dat que guarda la información de los puntos obtenidos de rating
en los distintos programas de canales de cable a lo largo del día. Cada registro contiene:
• Número de canal (entero)
• Programa (texto de 35 caracteres máximo)
• Rating (float)
El archivo se encuentra ordenado por canal.
Se solicita informar:
a. Aquellos canales que obtengan menos de 15 puntos en total.
b. El canal más visto.
c. Generar un archivo con el promedio de rating de cada canal que incluya dos campos:
• Número de canal.
• Promedio.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ESTRUCTURAS
typedef struct{
    int NumeroCanal;
    char Programa[37];
    float Rating;
}CANALES;

typedef struct{
    int NumeroCanal;
    float RatingPromedio;
}PROMEDIO_RATING;

//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
void LECTURA(FILE*);

int main(){
    FILE *ArchRating, *ArchProm;
    ArchRating = AbrirArchivo("RATING.dat", "rb");
    ArchProm = AbrirArchivo("PROMEDIO.dat", "wb");
    CANALES canales;
    PROMEDIO_RATING promedioRating;
    //Variables Auxiliares
    int AnteriorCanal, maxCanal, cantProgramas;
    float SumaRating, RatingTotal=0, maxRating=0, promedio;

    rewind(ArchRating);
    fread(&canales, sizeof(CANALES), 1, ArchRating);
    printf("Listado de canales con rating menor a 15\n");
    while(!feof(ArchRating)){
        AnteriorCanal = canales.NumeroCanal;
        SumaRating = 0;
        cantProgramas=0;
        while(!feof(ArchRating) && AnteriorCanal == canales.NumeroCanal){
            SumaRating+=canales.Rating;
            cantProgramas++;
            fread(&canales, sizeof(CANALES), 1, ArchRating);
        }
        if(SumaRating < 15){
            printf("CANAL: %d -- RATING %.2f\n", AnteriorCanal, SumaRating);
        }
        if(maxRating == 0 || maxRating < SumaRating){
            maxCanal = AnteriorCanal;
            maxRating = SumaRating;
        }
        //Calculamos el promedio
        if(cantProgramas>0){
            promedio = SumaRating/cantProgramas;
            promedioRating.NumeroCanal = AnteriorCanal;
            promedioRating.RatingPromedio = promedio;
            fwrite(&promedioRating, sizeof(PROMEDIO_RATING), 1, ArchProm);
        }
    }
    printf("\n\n El canal con las maximas vistas alcanzadas fue: CANAL: %d -- RATING: %.2f\n\n", maxCanal, maxRating);
    fclose(ArchProm);
    fclose(ArchRating);
    LECTURA(ArchProm);
return 0;
}

FILE *AbrirArchivo(char Nombre[], char Modo[]){
    FILE *Archivo;
    Archivo = fopen(Nombre, Modo);
    if(Archivo == NULL){
        printf("Error al abrir el archivo %s\n", Nombre);
        exit(1);
    }
return Archivo;
}

void LECTURA(FILE *ArchProm){
    PROMEDIO_RATING promedioRating;
    ArchProm = AbrirArchivo("PROMEDIO.dat", "rb");
    rewind(ArchProm);
    fread(&promedioRating, sizeof(PROMEDIO_RATING), 1, ArchProm);
    while(!feof(ArchProm)){
        printf("CANAL: %d -- RATING PROMEDIO: %.2f\n", promedioRating.NumeroCanal, promedioRating.RatingPromedio);
        fread(&promedioRating, sizeof(PROMEDIO_RATING), 1, ArchProm);
    }
}
