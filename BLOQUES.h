#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDiccionario.h"

bool existeKP()
{
    for (int i = 0; i < nAtr; i++)
    {
        if (data[i].iskp == 's' || data[i].iskp == 'S')
        {
            return true;
        }
    }
    return false;
}

// esta funcion se encarga de capturar un bloque
// se captura el bloque mediante la clave primaria
long buscaBloque(void *bloque)
{
    long cabData = entActiva.data;
    void *auxB;
    while (cabData != -1)
    {
        auxB = leeBloque(cabData);
        if (comparaBloques(auxB, bloque) == 0)
            return cabData;
        else
        {
            if (comparaBloques(auxB, bloque) > 0)
                return -1;
            else
                cabData = getApuntadorSig(auxB);
        }
    }
    return -1;
}

// esta funcion se encarga de leer un bloque en el archivo
// se lee el bloque en la posicion que le corresponde
void *leeBloque(long dir)
{
    if (dir != -1)
    {
        void *bloque = malloc(tambloque);
        fseek(f, dir, SEEK_SET);
        fread(bloque, tambloque, 1, f);
        return bloque;
    }
    else
        return NULL;
}

// esta funcion se encarga de escribir un bloque en el archivo
// se escribe el bloque se escribe en la ultima posicion del archivo

long escribeBloque(void *nuevo)
{
    fseek(f, 0, SEEK_END);
    pos = ftell(f);
    fwrite(nuevo, tambloque, 1, f);
    return pos;
}

// esta funcion se encarga de reescribir un bloque en el archivo
// se reescribe el bloque en la posicion que le corresponde

void reescribeBloque(long dir, void *bloque)
{
    fseek(f, dir, SEEK_SET);
    fwrite(bloque, tambloque, 1, f);
}

void altaBloque()
{
    bloque = capturaBloque();
    if (buscaBloque(Bloque) == -1)
    {
        long pos = escribeBloque(bloque);
        insertaBloque(bloque, pos);
    }
    freeI(bloque);
}

// esta funcion se encarga de insertar un bloque en la lista de bloques
// se inserta el bloque en la posicion que le corresponde

void InsertaBloque(void *nuevoB, long posB)
{
    void *wbAnte = NULL;
    long cabB = entActiva.data;
    if (cabB == -1)
    {
        entActiva.data = posB;
        reescribeEntidad(entActiva, posEntidad);
    }
    else
    {
        void *bloque = leeBloque(entActiva.data);
        if (comparaBloque(nuevoB, bloque) < 0)
        {
            *((long *)nuevoB + 0) = cabB;
            reescribeBloque(nuevoB, posB);
            entActiva.data = posB;
            reescribeEntidad(entActiva, posEntActiva);
        }
        else
        {
            do
            {
                if (bAnte != NULL)
                    free(bAnte);
                bAnte = bloque;
                long posBAnte = cabB;
                cabB = getApSig(bloque);
                if (cabB != -1)
                    bloque = leeBloque(cabB);
            } while (cabB != -1 && comparaBloque(nuevoB, bloque) > 0);
            if (cabB != -1)
            {
                *((long *)(nuevo + 0)) = cabB;
                reescribeBloque(nuevoB, posB);
            }
            *((long *)(bAnte + 0)) = posB;
            reescribeBloque(bAnte, posBAnte);
            free(bAnte);
        }
    }
}

// esta funcion se encargar de comparar dos bloques y devolver un entero
// se calcular la diferencia entre dos bloques mediante la clave primaria
int comparaBloque(void *bloque1, void *bloque2)
{
    double resul;
    switch (data[0].tipo)
    {
    case 1:
        resul = strcmp(((char *)(bloque1 + sizeof(long))), ((char *)(bloque2 + sizeof(long))));
    case 2:
        resul = *((int *)(bloque1 + sizeof(long))) - *((int *)(bloque2 + sizeof(long)));
    case 3:
        resul = *((float *)(bloque1 + sizeof(long))) - *((float *)(bloque2 + sizeof(long)));
    case 4:
        resul = *((double *)(bloque1 + sizeof(long))) - *((double *)(bloque2 + sizeof(long)));
    case 5:
        resul = *((long *)(bloque1 + sizeof(long))) - *((long *)(bloque2 + sizeof(long)));
    }
    return resul;
}

// esta funcion se encarga de obtener el apuntador siguiente de un bloque
// mediante el tamaño del bloque se obtiene el apuntador siguiente
long *getApuntadorSig(void *bloque)
{
    long apSig = *((long *)((char *)bloque));
    return apSig;
}