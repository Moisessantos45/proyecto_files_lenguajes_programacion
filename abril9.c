// Equipo: José Andrés Silva Bravo y Moisés Santos Hernández

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef char cadena[50];
typedef struct
{
    cadena nombre;
    float edad;
    float promedio;
    cadena carrera;
} TEstudiante;

#define TCHAR 1
#define TINT 2
#define TFlOAT 3
#define TDOUBLE 4
#define TLONG 5

int menu1();
int menu2();
int switch1();
int switch2(cadena nombre, FILE *archivo);
int abrirFile(cadena nombre, FILE *archivo);
void crearFile(cadena nombre, FILE *archivo);
void leerDatosFile(FILE *archivo);
void agregarDatosFile(FILE *archivo);
bool verifyNumber(void *number, int type);
int lengthFile(FILE *archivo);

int main()
{
    switch1();
}

int switch1()
{
    cadena nombre;
    FILE *archivo;
    int opc;
    do
    {
        int opc = menu1();
        switch (opc)
        {
        case 1:
            printf("************************\n");
            puts("Recuerda que el nombre no puede tener mas de 50 caracteres, agrega la terminacion del documento .bin");
            printf("Ingresa el nombre del archivo que quieres abrir: ");
            scanf("%s", nombre);
            if(abrirFile(nombre, archivo))
                switch2(nombre, archivo);
            break;
        case 2:
            crearFile(nombre, archivo);
            break;
        case 3:
            puts("***** Saliendo del programa... *****");
            fclose(archivo);
            return 0;
            break;
        default:
            puts("*****Error, elige una opción valida*****");
            break;
        }
    } while (opc != 3);
}

int switch2(cadena nombre, FILE *archivo)
{
    int opc;
    do
    {
        int opc = menu2();
        switch (opc)
        {
        case 1:
            leerDatosFile(archivo);
            break;
        case 2:
            agregarDatosFile(archivo);
            menu2();
            break;
        case 3:
            puts("***** Volviendo al menú... *****");
            fclose(archivo);
            return 0;
            break;
        default:
            puts("*****Error, elige una opción valida*****");
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
    printf("*  3. Volver al menu anterior.*\n");
    printf("************************\n");
    printf("Elige una opcion: ");
    scanf("%d", &opc);
    return opc;
}

void agregarDatosFile(FILE *archivo)
{
    int cantidad;
    printf("ingresa la cantidad de alumnos que deseas agregar: ");
    scanf("%d", &cantidad);
    TEstudiante *datos[cantidad];
    int direccion;
    printf("************************\n");
    printf("Ingrese la direccion: ");
    scanf("%d", &direccion);
    while (!verifyNumber(&direccion, 1))
    {
        printf("***** Ingresa una direccion positiva *****\n");
        scanf("%d", &direccion);
    }
    for (int i = 0; i < cantidad; i++)
    {
        datos[i] = (TEstudiante *)malloc(sizeof(TEstudiante));
        printf("************************\n");
        printf("Ingresa el nombre del alumno: ");
        getchar();
        scanf("%[^\n]", datos[i]->nombre);

        printf("Ingresa la edad del alumno: ");
        scanf("%f", &datos[i]->edad);

        printf("Ingresa el promedio del alumno: ");
        scanf("%f", &datos[i]->promedio);

        printf("Ingresa la carrera del alumno: ");
        getchar();
        scanf("%[^\n]", datos[i]->carrera);
    }
    puts("\n");
    printf("************************\n");
    puts("****Agregado correctamente****");
    printf("************************\n");
    for (int i = 0; i < cantidad; i++)
    {
        fseek(archivo, direccion, SEEK_SET);
        fwrite(datos[i], sizeof(TEstudiante), 1, archivo);
    }
    // libera memoria
    for (int i = 0; i < cantidad; i++)
    {
        free(datos[i]);
    }
}

int lengthFile(FILE *archivo)
{
    int length;
    fseek(archivo, 0, SEEK_END);
    length = ftell(archivo);
    int size = length / sizeof(TEstudiante);
    return size;
}

void leerDatosFile(FILE *archivo)
{

    TEstudiante *datos[1];
    int direccion;
    printf("************************\n");
    printf("Ingrese la direccion desde la que desea leer los datos: ");
    scanf("%d", &direccion);
    int dir = fseek(archivo, direccion, SEEK_SET);
    int size = lengthFile(archivo);
    switch (dir)
    {
    case 0:
        fread(datos[0], sizeof(TEstudiante), 1, archivo);
        printf("************************\n");
        for (int i = 0; i < size; i++)
        {
            datos[i] = (TEstudiante *)malloc(sizeof(TEstudiante));
            fread(datos[i], sizeof(TEstudiante), 1, archivo);
        }
        for (int i = 0; i < size; i++)
        {
            printf("Nombre: %s\n", datos[i]->nombre);
            printf("Edad: %f\n", datos[i]->edad);
            printf("Promedio: %f\n", datos[i]->promedio);
            printf("Carrera: %s\n", datos[i]->carrera);
        }
        // libera memoria
        for (int i = 0; i < size; i++)
        {
            free(datos[i]);
        }
        break;
    default:
        printf("***** Error al leer el archivo *****\n");
        break;
    }
}

bool verifyNumber(void *number, int type)
{
    bool isNegative = true;
    switch (type)
    {
    case 1:
        if (*((int *)number) < 0)
        {
            printf("***** Error, el dato no puede ser negativo *****\n");
            isNegative = false;
        }
        break;
    case 3:
        if (*((float *)number) < 0)
        {
            printf("***** Error, el dato no puede ser negativo *****\n");
            isNegative = false;
        }
        break;
    case 4:
        if (*((double *)number) < 0)
        {
            printf("***** Error, el dato no puede ser negativo *****\n");
            isNegative = false;
        }
        break;
    case 5:
        if (*((long *)number) < 0)
        {
            printf("***** Error, el dato no puede ser negativo *****\n");
            isNegative = false;
        }
        break;
    default:
        printf("Tipo de dato no válido\n");
        isNegative = false;
    }
    return isNegative;
}

int abrirFile(cadena nombre, FILE *archivo)
{
    // checar existencia del archivo
    archivo = fopen(nombre, "rb+");
    if (archivo == NULL)
    {
        printf("***** Error al abrir el archivo *****\n");
        return 0;
    }
    else
    {
        printf("***** Archivo correctamente abierto *****\n");
        return 1;
    }
}

void crearFile(cadena nombre, FILE *archivo)
{
    printf("************************\n");
    puts("Recuerda que el nombre no puede tener mas de 50 caracteres, agrega la terminacion del documento .bin");
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombre);

    archivo = fopen(nombre, "a");
    if (archivo == NULL)
    {
        fprintf(stderr, "***** Error al crear el archivo. *****\n");
        exit(EXIT_FAILURE);
    }
    printf("***** Archivo creado exitosamente. *****\n");
    fclose(archivo);
}