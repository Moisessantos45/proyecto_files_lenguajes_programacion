#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char cadena[50];

typedef struct
{
    int entero;
    float flotante;
    double doble;
    char *string;
    long eneteroGrande;
} Tvalor;

typedef struct
{
    int direccion;
    int typeDato;
    Tvalor valor;
} TEstudiante;

#define TCHAR 1
#define TINT 2
#define TFlOAT 3
#define TDOUBLE 4
#define TLONG 5

void opciones();
void abrirFile();
void crearFile();
void leerDatosFile();
void agregarDatosFile();

int main()
{
}

void agregarDatosFile()
{
    TEstudiante datos;
    FILE *archivo = NULL;
    int tipo;
    archivo = fopen("datos.bin", "wb+");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo");
        return;
    }
    printf("Ingrese la direccion: ");
    scanf("%d", &datos.direccion);
    printf("Ingrese el tipo de dato: %d TCHAR, %d TINT, %d TFlOAT, %d TDOUBLE, %d TLONG", TCHAR, TINT, TFlOAT, TDOUBLE, TLONG);
    scanf("%d", &tipo);
    switch (tipo)
    {
    case TINT:
        scanf("%d", &datos.valor.entero);
        datos.typeDato = TINT;
        break;
    case TCHAR:
        scanf("%s", &datos.valor.string);
        datos.typeDato = TCHAR;
        break;
    case TFlOAT:
        scanf("%f", &datos.valor.flotante);
        datos.typeDato = TFlOAT;
        break;
    case TDOUBLE:
        scanf("%lf", &datos.valor.doble);
        datos.typeDato = TDOUBLE;
        break;
    case TLONG:
        scanf("%ld", &datos.valor.eneteroGrande);
        datos.typeDato = TLONG;
        break;
    default:
        printf("Tipo de dato no valido");
        break;
    }
    fseek(archivo, datos.direccion, SEEK_SET);
    fwrite(&datos, sizeof(TEstudiante), 1, archivo);
}

void leerDatosFile()
{
    TEstudiante datos;
    FILE *archivo = NULL;
    int direccion;
    archivo = fopen("datos.bin", "rb+");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo");
        return;
    }
    switch (fseek(archivo, direccion, SEEK_SET))
    {
    case 0:
        fread(&datos, sizeof(TEstudiante), 1, archivo);
        switch (datos.typeDato)
        {
        case TINT:
            printf("%d", datos.valor.entero);
            break;
        case TCHAR:
            printf("%s", datos.valor.string);
            break;
        case TFlOAT:
            printf("%f", datos.valor.flotante);
            break;
        case TDOUBLE:
            printf("%lf", datos.valor.doble);
            break;
        case TLONG:
            printf("%ld", datos.valor.eneteroGrande);
            break;
        default:
            printf("Tipo de dato no valido");
            break;
        }
        break;
    case -1:
        printf("Error al leer el archivo");
        break;
    default:
        printf("Error al leer el archivo");
        break;
    }
}