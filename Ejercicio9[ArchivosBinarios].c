/* 9. Se dispone de un archivo denominado INSCRIPTOS.dat que contiene la información de los inscriptos a un
curso de programación. El archivo aún no está completo ya que la inscripción se realiza por partes. Por
cada inscripto se tiene la siguiente información:
• DNI (entero)
• Apellido y Nombres (texto de 20 caracteres máximo)
• Pagado (campo entero donde 1 indica que pagó y 0 que aún adeuda la matrícula)
Se desea realizar un programa que cumpla con dos funciones:
a. Registrar los pagos de los alumnos ya inscriptos.
b. SI hay cupo, agregar nuevos inscriptos (el cupo máximo es de 60 alumno).
El programa solicitará el ingreso del DNI y lo buscará entre los inscriptos, en caso de que lo encuentre
dará la opción para registrar el pago (si es que no está pago ya). En caso de que no lo encuentre dará la
opción para inscribirlo al curso (el pago se realiza luego). En el momento que ya no quede cupo en el curso
si llega un nuevo inscripto se le preguntará si desea quedar registrado para un curso futuro, y en caso
afirmativo se le solicitará el teléfono y se guardará el nombre, DNI y teléfono en un archivo
Interesados.dat. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//ESTRUCTURAS
typedef struct{
    int DNI;
    char NombreyApellido[21];
    int Estado;
}INSCRIPTOS;

typedef struct{
    int DNI;
    char NombreYApellido[21];
    char Telefono[21];
}INTERESADOS;
//PROTOTIPOS
FILE *AbrirArchivo(char[], char[]);
int IngrMayorIgualA(int);
void LeerTexto(char[], int);
char ValidarLetra(char, char);
int Busqueda(FILE*, int);
int Cantidad(FILE*);

int main(){
    FILE *ArchInscriptos, *ArchInteresados;
    ArchInscriptos = AbrirArchivo("INSCRIPTOS.dat", "r+b");
    ArchInteresados = AbrirArchivo("Interesados.dat", "ab");
    INSCRIPTOS inscriptos;
    INTERESADOS interesados;
    int DNI, cant, pos;
    char Opcion, NyA[22], numTelefonico[22];

    cant = Cantidad(ArchInscriptos);
    rewind(ArchInscriptos);
    fread(&inscriptos, sizeof(INSCRIPTOS), 1, ArchInscriptos);
    printf("Ingrese el DNI (0 - salir)\n");
    DNI = IngrMayorIgualA(0);
    while(DNI != 0){
        pos = Busqueda(ArchInscriptos, DNI);
        if(pos != -1){
            fseek(ArchInscriptos, pos*sizeof(INSCRIPTOS), SEEK_SET);
            fread(&inscriptos, sizeof(INSCRIPTOS), 1, ArchInscriptos);
            if(inscriptos.Estado == 0){
                printf("Desea pagar la mensualidad? (Si-s  No-n)\n");
                Opcion = ValidarLetra('s', 'n');
                Opcion = tolower(Opcion);
                if(Opcion == 's'){
                    inscriptos.Estado = 1;
                    fseek(ArchInscriptos, sizeof(INSCRIPTOS)*-1, SEEK_CUR);
                    fwrite(&inscriptos, sizeof(INSCRIPTOS), 1, ArchInscriptos);
                    printf("Pago recibido\n");
                }
                else{
                    printf("El pago queda pendiente\n");
                }
            }
            else{
                printf("La mensualidad ya esta pagada\n");
            }
        }
        //Si no lo encontro
        else{
            if(cant < 60){
                printf("No se encontro el alumno, Desea inscribirlo?\n");
                Opcion = ValidarLetra('s', 'n');
                if(Opcion == 's'){
                    printf("Ingrese el nombre y apellido del alumno\n");
                    LeerTexto(NyA, 22);
                    fseek(ArchInscriptos, 0, SEEK_END);
                    inscriptos.DNI = DNI;
                    strcpy(inscriptos.NombreyApellido, NyA);
                    inscriptos.Estado = 0;
                    fwrite(&inscriptos, sizeof(INSCRIPTOS), 1, ArchInscriptos);
                    printf("Inscripto correctamente\n");
                    cant++;
                }
            }
            else{
                printf("No hay mas cupos disponibles, desea estar en la lista de interesados?\n");
                Opcion = ValidarLetra('s', 'n');
                if(Opcion == 's'){
                    printf("Ingrese el Nombre y Apellido\n");
                    LeerTexto(NyA, 22);
                    printf("Ingrese un numero de telefono\n");
                    LeerTexto(numTelefonico, 22);
                    interesados.DNI = DNI;
                    strcpy(interesados.NombreYApellido, NyA);
                    strcpy(interesados.Telefono, numTelefonico);
                    fwrite(&interesados, sizeof(INTERESADOS), 1, ArchInteresados);
                }
            }
        }
        //Reingresamos los datos
        printf("Ingrese el DNI (0 - salir)\n");
        DNI = IngrMayorIgualA(0);
    }
    fclose(ArchInscriptos);
    fclose(ArchInteresados);
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

int IngrMayorIgualA(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<lim){
        printf("Dato invalido (>=%d)\n", lim);
        scanf("%d", &dato);
    }
return dato;
}

void LeerTexto(char Texto[], int ce){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(Texto, ce, stdin);
    Texto[strcspn(Texto, "\n")] = '\0';
}

char ValidarLetra(char SI, char NO){
    char letra;
    scanf(" %c", &letra);
    letra = tolower(letra);
    while(letra != SI && letra != NO){
        printf("Letra invalida, solamente se permite (%c - %c)\n", SI, NO);
        scanf(" %c", &letra);
    }
return letra;
}

int Busqueda(FILE *Archivo, int Buscado){
    INSCRIPTOS inscriptos;
    int i=0, posBuscada=-1;
    rewind(Archivo);
    fread(&inscriptos, sizeof(INSCRIPTOS), 1, Archivo);
    while(!feof(Archivo) && posBuscada == -1){
        if(inscriptos.DNI == Buscado){
            posBuscada = i;
        }
        else{
            i++;
            fread(&inscriptos, sizeof(INSCRIPTOS), 1, Archivo);
        }
    }
return posBuscada;
}

int Cantidad(FILE *Archivo){
    int cantidad;
    INSCRIPTOS inscriptos;
    //Mandamos el cursor al final para que tome la cantidad total de bytes
    fseek(Archivo, 0, SEEK_END);
    cantidad = ftell(Archivo)/sizeof(INSCRIPTOS);
    return cantidad;
}
