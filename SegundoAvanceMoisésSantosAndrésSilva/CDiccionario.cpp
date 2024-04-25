#include "CDiccionario.h"

CDiccionario::CDiccionario()
{
    f = null;
    dirActiva = -1;
}

int CDiccionario::imprimeMenu(cadena *menu, int tam)
{
    int resp;
    for (int i = 0; i < tam; i++)
    {
        cout << i + 1 << ".- " << menu[i] << endl;
    }
    cin >> resp;
    return resp;
}

void CDiccionario::escribecabentidades()
{
    fwrite((long)-1, sizeof(long), 1, f);
}

void CDiccionario::escribeEntidad(Entidad ent)
{
    fseek(f, 0, SEEK_END);
    post = ftell(f);
    fwrite(&ent, sizeof(Entidad), 1, f);
}

Entidad CDiccionario::capturaEntidad()
{
    printf("Nombre de la entidad: ");
    Entidad nueva;
    scanf("%s", nueva.nombre);
    nueva.sig = nueva.data = nueva.atr = -1;
    return nueva;
}

Entidad leeEntidad(long dir)
{
    Entidad ent;
    fseek(f, dir, SEEK_SET);
    fread(&ent, sizeof(Entidad), 1, f);
    return ent;
}

void CDiccionario::rescribeEntidad(long dir, Entidad ent)
{
    fseek(f, dir, SEEK_SET);
    fwrite(&ent, sizeof(Entidad), 1, f);
}

long CDiccionario::getCabEntidades()
{
    long cab;
    fseek(f, 0, SEEK_SET);
    fread(&cab, sizeof(long), 1, f);
    return cab;
}

long CDiccionario::buscarEntidad(cadena nombre)
{
    long cab = getCabEntidades();
    Entidad ent;
    while (cab != -1 && ent == leeEntidad(dir))
    {
        if (strcmp(ent.nombre, nombre) == 0)
        {
            return dir;
        }
        cab = ent.sig;
    }

    return -1;
}

void CDiccionario::altaEntidad()
{
    entidad = capEntidad();
    if (buscarEntidad(entidad.nombre) == -1)
    {
        pos = escribeEntidad(entidad);
        insertaEntidad(entidad, pos);
    }
}

void CDiccionario::insertaEntidad(Entidad ent, long dirNuevo)
{
    Entidad entidad, cabAnte, entidadAct;
    long cab = getCabEntidades();
    if (cab == -1)
    {
        rescribeCabEntidad(dirNuevo);
    }
    else
    {
        entidad = leeEntidad(cab);
    }
    if (strcmp(ent.nombre, entidad.nombre) > 0)
    {
        ent.sig = cab;
        rescribeEntidad(dirNuevo, ent);
        rescribeCabEntidad(dirNuevo);
    }
    else
    {
        while (strcmp(ent.nombre, entidad.nombre) > 0)
        {
            entidadAnte = entidadAct;
            cabAnte = cab;
            cab = entidadAct.sig;
            if (cab != -1)
            {
                entidadAct = leeEntidad(cab);
            }
        }
        if (cab != -1)
        {
            ent.sig = cab;
            rescribeEntidad(dirNuevo, ent);
        }
        entidadAnte.sig = dirNuevo;
        rescribe(entidadAnte, cabAnte);
    }
}

void CDiccionario::rescribe(cabEntidad, long dir)
{
    fseek(f, 0, SEEK_SET);
    fwrite(&dir, sizeof(long), 1, f);
}

void CDiccionario::consultaEntidades()
{
    cab = getCabEntidades();
    while (cab != -1)
    {
        ent = leeEntidad(cab);
        printf("%s\n", ent.nombre);
        cab = ent.sig;
    }
}

void CDiccionario::bajaEntidad()
{
    nombre = pideNombreEntidad();
    if (buscarEntidad(nombre) != -1)
    {
        pos = eliminaEntidad(nombre);
    }
    else
    {
        printf("Entidad no encontrada\n");
    }
}

long CDiccionario::eliminaEntidad(cadena nombre)
{
    cab = getCabEntidades();
    ent = leeEntidad(cab);
    if (strcmp(ent.nombre, nombre) == 0)
    {
        rescribeCabEntidad(ent.sig);
        return cab;
    }
    else
    {
        while (cab != -1 && strcmp(ent.nombre, nombre) == 0)
        {
            postAnt = cab;
            entAnt = ent;
            if (cab != -1)
            {
                ent = leeEntidad(cab);
            }
        }
        if (strcmp(ent.nombre, nombre) == 0)
        {
            entAnt.sig = ent.sig;
            rescribeEntidad(postAnt, entAnt);
        }
    }
    return cab;
}