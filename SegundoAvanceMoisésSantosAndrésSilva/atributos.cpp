#include "ATRIBUTOS.h"
#include "CDICCIONARIO.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

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
    cout << "Nombre del atributo: ";
    getline(cin, nuevoAtributo.nombre);
    cout << "Tipo de dato: \n";
    cout << "1. Cadena \n 2. Entero \n 3. Numero con decimal \n 4. Doble \n 5. Numero grande \n";

    switch (nuevoAtributo.tipo)
    {
    case 1:
        cout << "Tamaño de la cadena: ";
        cin >> nuevoAtributo.tam;
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
    cout << "¿Es llave primaria? \n";
    cout << "1. Si \n 2. No \n";
    getline(cin, nuevoAtributo.llave);
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
