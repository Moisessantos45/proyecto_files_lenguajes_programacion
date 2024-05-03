#include "CDiccionario.h"

// se inicializa el diccionario con un archivo nulo y una dirección activa de -1

CDiccionario::CDiccionario()
{
    f = null;
    dirActiva = -1;
}

// se imprime un menú con las opciones que recibe y se regresa la opción elegida por el usuario

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

// Escribe en el archivo la dirección de la entidad activa

void CDiccionario::escribecabentidades()
{
    fwrite((long)-1, sizeof(long), 1, f);
}

// Se encarga de abrir un diccionario. Se cierra el diccionario actual y se abre el diccionario que se pasa como parámetro.

void CDiccionario::escribeEntidad(Entidad ent)
{
    fseek(f, 0, SEEK_END);
    post = ftell(f);
    fwrite(&ent, sizeof(Entidad), 1, f);
}

// Se encarga de capturar una entidad. Se captura el nombre de la entidad y se regresa una entidad con el nombre capturado y los valores de -1 en los atributos sig, data y atr.

Entidad CDiccionario::capturaEntidad()
{
    printf("Nombre de la entidad: ");
    Entidad nueva;
    scanf("%s", nueva.nombre);
    nueva.sig = nueva.data = nueva.atr = -1;
    return nueva;
}

// Se encarga de leer una entidad en una dirección específica. Usando la direccion de la entidad se lee y se regresa la entidad.

Entidad leeEntidad(long dir)
{
    Entidad ent;
    fseek(f, dir, SEEK_SET);
    fread(&ent, sizeof(Entidad), 1, f);
    return ent;
}

// Se encarga de reescribir una entidad en una dirección específica. Usando la dirección de la entidad y una nueva entidad, se reescribe la entidad en la dirección específica.

void CDiccionario::rescribeEntidad(long dir, Entidad ent)
{
    fseek(f, dir, SEEK_SET);
    fwrite(&ent, sizeof(Entidad), 1, f);
}

// Se encarga de obtener la dirección de la cabecera de las entidades.

long CDiccionario::getCabEntidades()
{
    long cab;
    fseek(f, 0, SEEK_SET);
    fread(&cab, sizeof(long), 1, f);
    return cab;
}

// Se encarga de buscar una entidad en el diccionario. Se recibe el nombre de la entidad y se regresa la dirección de la entidad si se encuentra, de lo contrario se regresa -1.

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

// Se encarga de dar de alta una entidad. Se captura una entidad y se verifica si ya existe en el diccionario. Si no existe se escribe en el archivo y se inserta en la lista de entidades.

void CDiccionario::altaEntidad()
{
    entidad = capEntidad();
    if (buscarEntidad(entidad.nombre) == -1)
    {
        pos = escribeEntidad(entidad);
        insertaEntidad(entidad, pos);
    }
}

// Se encarga de insertar una entidad en el diccionario. Se verifica si la entidad es la primera en la lista de entidades, si es así se escribe en el archivo y se actualiza la cabecera de las entidades. Si no es la primera se recorre la lista de entidades hasta encontrar la posición correcta.

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

// Se encarga de reescribir la cabecera de las entidades. Se recibe la dirección de la nueva cabecera y se reescribe en el archivo.

void CDiccionario::rescribe(cabEntidad, long dir)
{
    fseek(f, 0, SEEK_SET);
    fwrite(&dir, sizeof(long), 1, f);
}

// Se encarga de consultar las entidades en el diccionario. Se recorre la lista de entidades y se imprime el nombre de cada entidad.

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

// Se encarga de dar de baja una entidad. Se pide el nombre de la entidad y se verifica si existe en el diccionario. Si existe se elimina de la lista de entidades.

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

// Se encarga de eliminar una entidad en el diccionario. se recorre la lista de entidades hasta encontrar la entidad. Si la entidad es la primera en la lista se actualiza la cabecera de las entidades. Si no es la primera se recorre la lista de entidades hasta encontrar la entidad y se elimina.

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