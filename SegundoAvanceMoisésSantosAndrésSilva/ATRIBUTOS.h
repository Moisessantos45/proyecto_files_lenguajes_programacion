#ifndef ATRIBUTOS_H
#define ATRIBUTOS_H
#include <iostream>

#include "CDICCIONARIO.h"

using namespace std;

typedef char cadena[30];

long eliminaAtributo(cadena nombre);
void bajaAtributo();
Atributos leeAtributo(long dir);
void insertaAtributo(Atributos newAtributo, long dirNueva);
Atributos capturaAtributo();
void reescribeAtributo(long dir, Atributos newAtributo);
long escribeAtributo(Atributos newAtributo);
void altaAtributo();

#endif