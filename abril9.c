// Equipo: José Andrés Silva Bravo y Moisés Santos Hernández

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef char cadena[50];

typedef struct
{
    int entero;
    float flotante;
    double doble;
    char string[51];
    long eneteroGrande;
} Tvalor;

typedef struct
{
    int direccion;
    int typeDato;
    Tvalor valor;
} TDatos;

#define TCHAR 1
#define TINT 2
#define TFlOAT 3
#define TDOUBLE 4
#define TLONG 5

int menu1();
int menu2();
int switch1();
int switch2(char nombre[], FILE *archivo);
void abrirFile(char nombre[], FILE *archivo);
void crearFile(char nombre[], FILE *archivo);
void leerDatosFile();
void agregarDatosFile(FILE *archivo);

int main()
{
    switch1();
}

int switch1()
{
    char nombre[50];
    FILE *archivo;
    int opc;
    do
    {
        int opc = menu1();
        switch (opc)
        {
        case 1:
            switch2(nombre, archivo);
            break;
        case 2:
            switch2(nombre, archivo);
            break;
        case 3:
            puts("***** Saliendo del programa... *****");
            fclose(archivo);
            return 0;
            break;
        default:
            puts("Error");
            break;
        }
    } while (opc != 3);
}

int switch2(char nombre[], FILE *archivo)
{
    int opc;
    do
    {
        int opc = menu2();
        switch (opc)
        {
        case 1:
            abrirFile(nombre, archivo);
            agregarDatosFile(archivo);
            break;
        case 2:
            crearFile(nombre, archivo);
            menu2();
            break;
        case 3:
            puts("***** Volviendo al menú... *****");
            return 0;
            break;
        default:
            puts("Error");
            break;
        }
    } while (opc != 3);
}

int menu1()
{
    int opc;
    puts("\nTipo de operacion que deseas realizar:\n");
    printf("************************\n");
    printf("*  1. Abrir un documento ya existente *\n");
    printf("*  2. Crear un nuevo documento *\n");
    printf("*  3. Salir del programa.*\n");
    printf("************************\n");
    printf("Elige una opcion: ");
    scanf("%d", &opc);
    return opc;
}

int menu2()
{
    int opc;
    puts("\nTipo de operacion que deseas realizar:\n");
    printf("************************\n");
    printf("*  1. Leer datos de un documento *\n");
    printf("*  2. Agregar datos a un documento*\n");
    printf("*  3. Volver al menú anterior.*\n");
    printf("************************\n");
    printf("Elige una opcion: ");
    scanf("%d", &opc);
    return opc;
}

void agregarDatosFile(FILE *archivo)
{
    //EDITAR PARA ALUMNOS
    TDatos datos;
    int tipo;
    printf("************************\n");
    printf("Ingrese la direccion: ");
    scanf("%d", &datos.direccion);
    puts("\n");
    printf("************************\n");
    printf("Que tipo de dato es?\n * %d TCHAR *\n * %d TINT *\n * %d TFlOAT *\n * %d TDOUBLE *\n * %d TLONG *\n", TCHAR, TINT, TFlOAT, TDOUBLE, TLONG);
    printf("************************\n");
    printf("ingrese el tipo de dato:");
    scanf("%d", &tipo);
    switch (tipo)
    {
    case TINT:
        printf("************************\n");
        printf("ingrese el dato:");
        scanf("%d", &datos.valor.entero);
        datos.typeDato = TINT;
        break;
    case TCHAR:
        printf("************************\n");
        printf("ingrese el dato:");
        getchar();
        scanf("%[^\n]", datos.valor.string);
        getchar();
        datos.typeDato = TCHAR;
        break;
    case TFlOAT:
        printf("************************\n");
        printf("ingrese el dato:");
        scanf("%f", &datos.valor.flotante);
        datos.typeDato = TFlOAT;
        break;
    case TDOUBLE:
        printf("************************\n");
        printf("ingrese el dato:");
        scanf("%lf", &datos.valor.doble);
        datos.typeDato = TDOUBLE;
        break;
    case TLONG:
        printf("************************\n");
        printf("ingrese el dato:");
        scanf("%ld", &datos.valor.eneteroGrande);
        datos.typeDato = TLONG;
        break;
    default:
        printf("***** Tipo de dato no valido *****\n");
        break;
    }
    fseek(archivo, datos.direccion, SEEK_SET);
    fwrite(&datos, sizeof(TDatos), 1, archivo);
}

void leerDatosFile()
{
    char nombre[50];
    TDatos datos;
    FILE *archivo = NULL;
    int direccion;
    archivo = fopen(nombre, "rb+");
    if (archivo == NULL)
    {
        printf("***** Error al abrir el archivo *****\n");
        return;
    }
    printf("************************\n");
    printf("Ingrese la direccion desde la que desea leer los datos: ");
    scanf("%d", &direccion);
    switch (fseek(archivo, direccion, SEEK_SET))
    {
    case 0:
        fread(&datos, sizeof(TDatos), 1, archivo);
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
            printf("***** Tipo de dato no valido *****\n");
            break;
        }
        break;
    case -1:
        printf(" ***** Error al leer el archivo *****\n");
        break;
    default:
        printf("***** Error al leer el archivo *****\n");
        break;
    }
}

void abrirFile(char nombre[], FILE *archivo)
{
    printf("************************\n");
    puts("Recuerda que el nombre no puede tener mas de 50 caracteres, agrega la terminacion del documento .bin");
    printf("Ingresa el nombre del archivo que quieres abrir: ");
    scanf("%s", nombre);
    //checar existencia del archivo
    archivo = fopen(nombre, "rb+");
    if (archivo == NULL)
    {
        printf("***** Error al abrir el archivo *****\n");
        return;
    }
    else
    {
        printf("***** Archivo correctamente abierto *****\n");
        return;
    }
}

void crearFile(char nombre[], FILE *archivo)
{
    printf("************************\n");
    puts("Recuerda que el nombre no puede tener mas de 50 caracteres, agrega la terminacion del documento .bin");
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombre);
    if (access(nombre, F_OK) != -1)
    {
        printf("****** El archivo ya existe. No se puede crear. *****\n");
    }
    else
    {
        archivo = fopen(nombre, "a");
        if (archivo == NULL)
        {
            fprintf(stderr, "***** Error al crear el archivo. *****\n");
            exit(EXIT_FAILURE);
        }
        printf("***** Archivo creado exitosamente. *****\n");
    }
}