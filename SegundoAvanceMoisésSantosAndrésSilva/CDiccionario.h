#ifndef CDICCCIONARIO_H
#define CDICCCIONARIO_H
#include <iostream>
#include <string>
typedef char cadena[30];

typedef struct
{

} ENTIDAD;

class CDicccionario
{
private:
    FILE *f;
    ENTIDAD entactiva;
    long posentactiva;

public:
    CDicccionario();
    int imprimeMenu(cadena *menu, int tam);
    virtual ~CDicccionario();
};

#endif // CDICCCIONARIO_H