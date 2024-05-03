#include "ATRIBUTOS.h"
#include "CDICCIONARIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// busca un atributo con un nombre específico en la entidad activa y lo elimina, actualizando los enlaces de los atributos y la entidad misma si es necesario. Devuelve la dirección del atributo que se eliminó.

long eliminaAtributo(cadena nombre)
{
    long cab = entidadActiva.atr;
    long atributoAnterior;
    long cabAnterior;
    Atributos atributoAtual = leeAtributo(entidadActiva.atr);
    if (strcmp(atributoAtual.nombre, nombre) == 0)
    {
        entidadActiva.atr = atributoAtual.sig;
        reescribeEntidad(entidadActiva, posEntidadActiva);
    }
    else
    {
        while (cab != -1 && strcmp(atributoAtual.nombre, nombre) < 0)
        {
            cabAnterior = cab;
            atributoAnterior = atributoAtual;
            cab = atributoAtual.sig;
            if (cab != -1)
            {
                atributoAtual = leeAtributo(cab);
            }
        }
        atributoAtual.sig = atributoAtual.sig;
        reescribeAtributo(atributoAnterior, cabAnterior);
    }
    return cab;
}

// Se encarga de eliminar un atributo de una entidad. Se pide el nombre del atributo a eliminar y se llama a la función eliminaAtributo() para realizar la eliminación.

void bajaAtributo()
{
    cadena nombre = pideNombreAtributo();
    if (buscarAtributo(nombre) != -1)
    {
        post = eliminaAtributo(nombre);
    }
    else
    {
        printf("No se encontro el atributo\n");
    }
}

// Lee un atributo en una dirección específica y lo devuelve. Se utiliza para leer un atributo en una dirección específica.

Atributos leeAtributo(long dir)
{
    Atributos atributo;
    fseek(f, dir, SEEK_SET);
    fread(&atributo, sizeof(Atributos), 1, f);
    return atributo;
}

// Inserta un atributo en la entidad activa.Se inserta el atributo en la entidad activa, actualizando los enlaces de los atributos y la entidad misma.

void insertaAtributo(Atributos newAtributo, long dirNueva)
{
    long cab;
    if (entidadActiva.atr == -1)
    {
        entidadActiva.atr = pos.atrNueva;
        reescribeAtributo(entidadActiva, posEntidadActiva);
    }
    else
    {
        cab = entidadActual = leeAtributo(entidadActiva.atr);
        if (strcmp(newAtributo.nombre, atrActual.nombre) < 0)
        {
            newAtributo.sig = entidadActiva.atr;
            entidadActiva.atr = pos.atrNueva;
            rescribeEntidad(entidadActiva, posEntidadActiva);
            reescribeAtributo(newAtributo, posAtrNuevo);
        }
        else
        {
            cab = entidadActiva.atr;
            while (cab != -1 && strcmp(newAtributo.nombre, atrActual.nombre) > 0)
            {
                atrAnterior = atrActual;
                cabAnterior = cab;
                cab = atrActual.sig;
                if (cab != -1)
                {
                    atrActual = leeAtributo(cab);
                }
            }
            if (cab != -1)
            {
                newAtributo.sig = cab;
                reescribeAtributo(newAtributo, dirNueva);
            }
            else
            {
                atrAnterior.sig = dirNueva;
                reescribeAtributo(atrAnterior, cabAnterior);
            }
        }
    }
}

// Se captura un atributo y se devuelve. Se pide al usuario que ingrese los datos del atributo y se devuelve el atributo capturado.

Atributos capturaAtributo()
{
    Atributos nuevoAtributo;
    printf("Nombre del atributo: ");
    scanf("%s", nuevoAtributo.nombre);
    printf("Tipo de dato: \n");
    printf("1. Char \n 2. Int \n 3. Float \n 4. Double \n 5. Long \n");
    scanf("%d", &nuevoAtributo.tipo);
    switch (nuevoAtributo.tipo)
    {
    case 1:
        printf("Ingrese la cantidad de caracteres: ");
        scanf("%d", &nuevoAtributo.tam);
        nuevoAtributo.tam = nuevoAtributo.tam * sizeof(char);
        break;
    case 2:
        nuevoAtributo.tam = sizeof(int);
        break;
    case 3:
        nuevoAtributo.tam = sizeof(float);
        break;
    case 4:
        nuevoAtributo.tam = sizeof(double);
        break;
    case 5:
        newAtributo.tam = sizeof(long);
    default:
        break;
    }
    printf("Es llave primaria ??: \n");
    printf("1. Si \n 2. No \n");
    scanf("%d", &nuevoAtributo.llave);
    newAtributo.sig = -1;
    return nuevoAtributo;
}

// Reescribe un atributo en una dirección específica. Usando la dirección de un atributo y un nuevo atributo, se reescribe el atributo en la dirección específica.

void reescribeAtributo(long dir, Atributos newAtributo)
{
    fseek(f, dir, SEEK_SET);
    fwrite(&newAtributo, sizeof(Atributos), 1, f);
}

// Escribe un atributo en el archivo y devuelve la dirección. Usando un nuevo atributo, se escribe en el archivo y se devuelve la dirección.

long escribeAtributo(Atributos newAtributo)
{
    long dir;
    fseek(f, 0, SEEK_END);
    dir = ftell(f);
    fwrite(&newAtributo, sizeof(Atributos), 1, f);
    return dir;
}

// Se encarga de dar de alta un atributo en una entidad. Se captura un atributo y se verifica si ya existe en la entidad activa. Si no existe, se escribe en el archivo y se inserta en la entidad activa.

void altaAtributo()
{
    Atributos nuevoAtributo;
    nuevoAtributo = capturaAtributo();

    if (buscarAtributo(nuevoAtributo.nombre) == -1)
    {
        pos = escribeAtributo(nuevoAtributo);
        insertaAtributo(nuevoAtributo, pos);
    }
    else
    {
        printf("El atributo ya existe\n");
    }
}
