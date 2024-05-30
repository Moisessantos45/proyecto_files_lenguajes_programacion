#ifndef CDICCCIONARIO_H
#define CDICCCIONARIO_H 0

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

using namespace std;

// se declara una cadena de 30 caracteres
typedef char cadena[30];

// se declara un arreglo de tamaños de datos
const int TAMANIOS[] = {sizeof(char), sizeof(int), sizeof(float), sizeof(double), sizeof(long)};

// se declara una estructura de atributos
// se declara el nombre del atributo, el tipo de dato, el tamaño del dato, la cantidad de datos, el siguiente atributo y si es llave primaria
typedef struct atr
{
    cadena nombre;
    int tipo;
    int tam;
    long sig;
    char isKp;
} Atributos;

// se declara una estructura de entidad
// esta funciona para guardar el nombre de la entidad, la dirección de la entidad, la dirección de los atributos, la dirección de los datos y la dirección de la siguiente entidad
typedef struct
{
    cadena nombre;
    long dir;
    long atr;
    long data;
    long sig;
} Entidad;

void def();

// Se declara la clase CDiccionario que se encarga de manejar las entidades y los atributos
// Se declaran las funciones que se encargan de dar de todas las funcionalidades de mi diccionario
class CDiccionario
{
private:
    FILE *f;
    Entidad entactiva;
    long posentactiva;
    void *bloque;
    long tambloque;
    int Natributos;
    Atributos atributos[50];

public:
    CDiccionario();
    int imprimeMenu(cadena *menu, int tam);

    // ENTIDADES
    void escribeCabEntidades();
    long escribeEntidad(Entidad ent);
    void altaEntidad();
    Entidad capturaEntidad();
    Entidad leeEntidad(long dir);
    long getCabEntidades();
    long buscarEntidad(cadena nombre);
    void insertaEntidad(Entidad ent, long dirNuevo);
    void reescribeCabEntidad(long dir);
    void bajaEntidad();
    long eliminaEntidad(cadena nombre);
    void consultaEntidades();
    void pideNombreEntidad(cadena *name);
    void modificaEntidad();

    // MENUS Y OPCIONES
    void menuInicial();
    void menuEntidades();
    void menuAtributos();
    void menuDatos();

    // DICCIONARIO-> ATRIBUTOS
    void reescribeEntidad(Entidad ent, long dir);
    void cierraActualDiccionario();
    int abrirDiccionario();
    int crearDiccionario();

    //  ATRIBUTOS
    long eliminaAtributo(cadena nombre);
    void bajaAtributo();
    Atributos leeAtributo(long dir);
    void insertaAtributo(Atributos newAtributo, long dirNueva);
    Atributos capturaAtributo();
    void reescribeAtributo(Atributos newAtributo, long dir);
    long escribeAtributo(Atributos newAtributo);
    void altaAtributo();
    long buscaAtributo(cadena name);
    void modificaAtributo();
    void pideNombreAtributo(cadena *name);
    void consultaAtributos();
    long getCabAtributos();
    int pedirEntidad();
    long clavePrimaria();
    void cambiaKP();
    int checkData();
    void insertarComoClavePrimaria(Atributos &newAtributo, long dirNueva);
    void insertarEnCabecera(Atributos &newAtributo, long dirNueva);
    void insertarAntesDeActual(Atributos &newAtributo, long dirNueva, Atributos &atrAnt, long cabAnt, Atributos &atrActual, long cab);
    void buscarPosicionInsertar(Atributos &newAtributo, long &cab, Atributos &atrActual, Atributos &atrAnt, long &cabAnt);

    // BLOQUES
    int getAtributos();
    void *capturaBloque();
    long getApuntadorSig(void *bloque);
    void setApuntadorSig(void *bloque, long dir);
    bool existeKP();
    int comparaBloque(void *bloque1, void *bloque2);
    void InsertaBloque(void *nuevoB, long posB);
    void altaBloque();
    void reescribeBloque(long dir, void *bloque);
    long escribeBloque(void *nuevo);
    void *leeBloque(long dir);
    long buscaBloque(void *bloque);
    void bajaSecuencia();
    bool modificaBloque();
    long eliminaBloque(void *claveB);
    void consultaBloques();
    void *capturaKp();
    void insertarEnCabecera(void *nuevoB, long posB);
    void insertarAntesDeActual(void *nuevoB, long posB, void *bAnte, long posAnte, long cabB);
    void buscarPosicionInsertar(void *&bloque, long &cabB, void *&bAnte, long &posAnte, void *nuevoB);

    virtual ~CDiccionario();

protected:
};

// Cierra cualquier archivo abierto, pide el nombre y si no existia uno
// así llamado ya, regresa un 1, si no un 0
int CDiccionario::abrirDiccionario()
{
    cadena namefile;
    cout << "Como se llama el diccionario que quieres abrir" << endl;
    cin >> namefile;
    f = fopen(namefile, "rb+");
    if (f != NULL)
        return 1;
    else
    {
        cout << "El archivo no existe" << endl;
        return 0;
    }
}

// esta funcion se encarga de crear un diccionario
// se pide el nombre del diccionario y si no existe ya un archivo con ese nombre
int CDiccionario::crearDiccionario()
{
    cadena namefile;
    cout << "Como se llama el diccionario que quieres abrir" << endl;
    cin >> namefile;
    if (access(namefile, F_OK) == -1)
    {
        f = fopen(namefile, "wb+");
        return 1;
    }
    else
    {
        cout << "El archivo ya existe" << endl;
        return 0;
    }
}

// si hay un diccionario abierto lo cierra
void CDiccionario::cierraActualDiccionario()
{
    if (f != NULL)
    {
        fclose(f);
    }
}

// Declara las opciones del primer menu y dependiendo la elección envía a la función
// respectiva
void CDiccionario::menuInicial()
{
    cadena arr[] = {"\nElige lo que quieres hacer:", "1. Crear diccionario",
                    "2. Abrir diccionario", "3. Salir"};
    // FILE *archivo = NULL;
    int opc;
    do
    {
        cierraActualDiccionario();
        opc = imprimeMenu(arr, 4);
        switch (opc)
        {
        case 1:
            if (crearDiccionario() == 1)
            {
                escribeCabEntidades();
                menuEntidades();
            }
            break;
        case 2:
            if (abrirDiccionario() == 1)
                menuEntidades();
            break;
        case 3:
            cout << "***** Saliendo del programa... *****" << endl;
            cierraActualDiccionario();
            break;
        default:
            def();
            break;
        }
    } while (opc != 3);
}

// Declara las opciones del menu de entidades y dependiendo la elección envía a la función
// respectiva
void CDiccionario::menuEntidades()
{
    cadena arr[8] = {"\nElige lo que quieres hacer:", "1. Crear Entidad",
                     "2. Consultar Entidades", "3. Eliminar Entidad", "4. Modificar Entidad",
                     "5. Menu de atributos", "6. Menu de datos", "7. Regresar al menu principal"};
    int opc;
    do
    {
        opc = imprimeMenu(arr, 8);
        switch (opc)
        {
        case 1:
            altaEntidad();
            break;
        case 2:
            consultaEntidades();
            break;
        case 3:
            bajaEntidad();
            break;
        case 4:
            modificaEntidad();
            break;
        case 5:
            if (pedirEntidad() == 1)
                menuAtributos(); // nombre) &archivo);
            break;
        case 6:
            if (pedirEntidad() == 1)
            {
                if (existeKP() == 1)
                {
                    getAtributos();
                    menuDatos(); // nombre &archivo);
                }
                else
                    cout << "La entidad debe tener una clave que lo diferencíe" << endl;
            }
            break;
        case 7:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            def();
            break;
        }
    } while (opc != 7);
}

// Declara las opciones del menu de atributos y dependiendo la elección envía a la función
// respectiva
void CDiccionario::menuAtributos()
{
    cadena arr[6] = {"\nElige lo que quieres hacer:", "1. Crear atributo",
                     "2. Consultar atributos", "3. Eliminar atributos", "4. Modificar atributos",
                     "5. Regresar al menu Entidades"};
    int opc;
    do
    {
        opc = imprimeMenu(arr, 6);
        switch (opc)
        {
        case 1:
            if (checkData() != 1)
                altaAtributo();
            break;
        case 2:
            consultaAtributos();
            break;
        case 3:
            if (checkData() != 1)
                bajaAtributo();
            break;
        case 4:
            if (checkData() != 1)
                modificaAtributo();
            break;
        case 5:
            cout << "Volviendo al menu de Entidades..." << endl;
            break;
        default:
            def();
            break;
        }
    } while (opc != 5);
}

// Declara las opciones del menu de datos y dependiendo la elección envía a la función
// respectiva
void CDiccionario::menuDatos()
{
    cadena arr[6] = {"\nElige lo que quieres hacer:", "1. Crear registro",
                     "2. Consultar registros", "3. Eliminar registros", "4. Modificar registros",
                     "5. Regresar al menu Entidades"};
    int opc;
    do
    {
        opc = imprimeMenu(arr, 6);
        switch (opc)
        {
        case 1:
            altaBloque();
            break;
        case 2:
            consultaBloques();
            break;
        case 3:
            bajaSecuencia();
            break;
        case 4:
            if (modificaBloque() == 1)
                cout << "Registro modificado con exito" << endl;
            break;
        case 5:
            cout << "Volviendo al menu de Entidades..." << endl;
            break;
        default:
            def();
            break;
        }
    } while (opc != 5);
}

// Destructor del objeto
CDiccionario::~CDiccionario()
{
}

using namespace std;

// se inicializa el diccionario con un archivo nulo y una dirección activa de -1

CDiccionario::CDiccionario()
{
    f = NULL;
    posentactiva = -1;
}

// se imprime un menú con las opciones que recibe y se regresa la opción elegida por el usuario

int CDiccionario::imprimeMenu(cadena *menu, int tam)
{
    int resp;
    for (int i = 0; i < tam; i++)
    {
        cout << menu[i] << endl;
    }
    cin >> resp;
    return resp;
}

// Escribe en el archivo la dirección de la entidad activa

void CDiccionario::escribeCabEntidades()
{
    long valor = -1;
    fseek(f, 0, SEEK_SET);
    fwrite(&valor, sizeof(long), 1, f);
}

// Se encarga de abrir un diccionario. Se cierra el diccionario actual y se abre el diccionario que se pasa como parámetro.

long CDiccionario::escribeEntidad(Entidad ent)
{
    fseek(f, 0, SEEK_END);
    posentactiva = ftell(f);
    fwrite(&ent, sizeof(Entidad), 1, f);
    return posentactiva;
}

// Se encarga de capturar una entidad. Se captura el nombre de la entidad y se regresa una entidad con el nombre capturado y los valores de -1 en los atributos sig, data y atr.

Entidad CDiccionario::capturaEntidad()
{
    Entidad nueva;
    pideNombreEntidad(&nueva.nombre);
    nueva.sig = nueva.data = nueva.atr = -1;
    return nueva;
}

// Se encarga de leer una entidad en una dirección específica. Usando la direccion de la entidad se lee y se regresa la entidad.

Entidad CDiccionario::leeEntidad(long dir)
{
    Entidad ent;
    fseek(f, dir, SEEK_SET);
    fread(&ent, sizeof(Entidad), 1, f);
    return ent;
}

// Se encarga de reescribir una entidad en una dirección específica. Usando la dirección de la entidad y una nueva entidad, se reescribe la entidad en la dirección específica.

void CDiccionario::reescribeEntidad(Entidad ent, long dir)
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
    while (cab != -1)
    {
        ent = leeEntidad(cab);
        if (strcmpi(ent.nombre, nombre) == 0)
        {
            posentactiva = cab;
            return cab;
        }
        cab = ent.sig;
    }
    return -1;
}

// Se encarga de dar de alta una entidad. Se captura una entidad y se verifica si ya existe en el diccionario. Si no existe se escribe en el archivo y se inserta en la lista de entidades.

void CDiccionario::altaEntidad()
{
    Entidad entidad = capturaEntidad();
    if (buscarEntidad(entidad.nombre) == -1)
    {
        posentactiva = escribeEntidad(entidad);
        insertaEntidad(entidad, posentactiva);
    }
}

// Se encarga de insertar una entidad en el diccionario. Se verifica si la entidad es la primera en la lista de entidades, si es así se escribe en el archivo y se actualiza la cabecera de las entidades. Si no es la primera se recorre la lista de entidades hasta encontrar la posición correcta.

void CDiccionario::insertaEntidad(Entidad ent, long dirNuevo)
{
    Entidad entidad, entidadAnt;
    long cab = getCabEntidades(), cabAnte;
    if (cab == -1)
    {
        reescribeCabEntidad(dirNuevo);
        entactiva = ent;
    }
    else
    {
        entidad = leeEntidad(cab);
        if (strcmpi(ent.nombre, entidad.nombre) < 0)
        {
            ent.sig = cab;
            reescribeEntidad(ent, dirNuevo);
            reescribeCabEntidad(dirNuevo);
        }
        else
        {
            entactiva = entidad;
            while (cab != -1 && strcmpi(ent.nombre, entactiva.nombre) > 0)
            {
                entidadAnt = entactiva;
                cabAnte = cab;
                cab = entactiva.sig;
                if (cab != -1)
                {
                    entactiva = leeEntidad(cab);
                }
            }

            ent.sig = cab;
            reescribeEntidad(ent, dirNuevo);
            entidadAnt.sig = dirNuevo;
            reescribeEntidad(entidadAnt, cabAnte);
        }
    }
}

// Se encarga de reescribir la cabecera de las entidades. Se recibe la dirección de la nueva cabecera y se reescribe en el archivo.

void CDiccionario::reescribeCabEntidad(long dir)
{
    fseek(f, 0, SEEK_SET);
    fwrite(&dir, sizeof(long), 1, f);
}

// Se encarga de consultar las entidades en el diccionario. Se recorre la lista de entidades y se imprime el nombre de cada entidad.

void CDiccionario::consultaEntidades()
{
    long cab = getCabEntidades();
    Entidad ent;
    if (cab == -1)
        cout << "No hay entidades" << endl;
    while (cab != -1)
    {
        ent = leeEntidad(cab);
        cout << ent.nombre << endl;
        cab = ent.sig;
    }
}

// Se encarga de dar de baja una entidad. Se pide el nombre de la entidad y se verifica si existe en el diccionario. Si existe se elimina de la lista de entidades.

void CDiccionario::bajaEntidad()
{
    cadena nombre;
    long pos;
    pideNombreEntidad(&nombre);
    if (buscarEntidad(nombre) != -1)
    {
        pos = eliminaEntidad(nombre);
        cout << "Entidad eliminada con exito" << endl;
    }
    else
    {
        cout << "Entidad no encontrada" << endl;
    }
}

// Registra el nombre del archivo que nos esten pidiendo
void CDiccionario::pideNombreEntidad(cadena *name)
{
    cout << "\n Dame el nombre de la entidad" << endl;
    cin >> *name;
}

// se encarga de modificar una entidad en el diccionario. Se pide el nombre de la entidad a modificar y se verifica si existe en el diccionario. Si existe se captura una nueva entidad y se verifica si ya existe en el diccionario. Si no existe se elimina la entidad y se inserta la nueva entidad.
void CDiccionario::modificaEntidad()
{
    cadena entName;
    pideNombreEntidad(&entName);
    if (buscarEntidad(entName) != -1)
    {
        Entidad nuevaEnt = capturaEntidad();
        if (buscarEntidad(nuevaEnt.nombre) == -1)
        {
            long pos = eliminaEntidad(entName);
            reescribeEntidad(nuevaEnt, pos);
            insertaEntidad(nuevaEnt, pos);
        } // ERROR
        else
            cout << "Esa entidad ya existe" << endl;
    }
    else
        cout << "La entidad " << entName << " no existe" << endl;
}

// Se encarga de eliminar una entidad en el diccionario. se recorre la lista de entidades hasta encontrar la entidad. Si la entidad es la primera en la lista se actualiza la cabecera de las entidades. Si no es la primera se recorre la lista de entidades hasta encontrar la entidad y se elimina.

long CDiccionario::eliminaEntidad(cadena nombre)
{
    long cab = getCabEntidades();
    if (cab == -1)
        return -1;
    Entidad ent = leeEntidad(cab);
    if (strcmpi(ent.nombre, nombre) == 0)
    {
        reescribeCabEntidad(ent.sig);
        return cab;
    }
    else
    {
        long posAnt = cab;
        Entidad entAnt = ent;
        while (cab != -1 && strcmpi(ent.nombre, nombre) < 0)
        {
            posAnt = cab;
            entAnt = ent;
            cab = ent.sig;
            if (cab != -1)
            {
                ent = leeEntidad(cab);
            }
        }
        if (strcmpi(ent.nombre, nombre) == 0)
        {
            entAnt.sig = ent.sig;
            reescribeEntidad(entAnt, posAnt);
            return cab;
        }
    }
    return -1;
}

// Se encarga de pedir una entidad y la guarda en la variable entactiva. Se pide el nombre de la entidad y se busca en el diccionario. Si se encuentra se guarda en la variable entactiva.
int CDiccionario::pedirEntidad()
{
    tambloque = 0;
    cadena name;
    pideNombreEntidad(&name);
    long dir = buscarEntidad(name);
    if (dir != -1)
    {
        entactiva = leeEntidad(dir);
        posentactiva = dir;
        return 1;
    }
    else
    {
        cout << "La entidad no existe" << endl;
        return -1;
    }
}

// ATRIBUTOS

// busca un atributo con un nombre específico en la entidad activa y lo elimina, actualizando los enlaces de los atributos y la entidad misma si es necesario. Devuelve la dirección del atributo que se eliminó.

long CDiccionario::eliminaAtributo(cadena nombre)
{
    long cab = entactiva.atr;
    Atributos atributoAnterior;
    long cabAnterior;
    Atributos atributoActual = leeAtributo(entactiva.atr);
    if (strcmpi(atributoActual.nombre, nombre) == 0)
    {
        entactiva.atr = atributoActual.sig;
        reescribeEntidad(entactiva, posentactiva);
    }
    else
    {
        do
        {
            cabAnterior = cab;
            atributoAnterior = atributoActual;
            cab = atributoActual.sig;
            if (cab != -1)
            {
                atributoActual = leeAtributo(cab);
            }
        } while (cab != -1 && strcmpi(atributoActual.nombre, nombre) < 0);

        atributoAnterior.sig = atributoActual.sig;
        reescribeAtributo(atributoAnterior, cabAnterior);
    }
    return cab;
}

// Se encarga de eliminar un atributo de una entidad. Se pide el nombre del atributo a eliminar y se llama a la función eliminaAtributo() para realizar la eliminación.
void CDiccionario::bajaAtributo()
{
    long pos;
    cadena nombre;
    pideNombreAtributo(&nombre);
    if (buscaAtributo(nombre) != -1)
    {
        pos = eliminaAtributo(nombre);
        cout << "Atributo eliminado con exito" << endl;
    }
    else
    {
        cout << "No se encontro el atributo" << endl;
    }
}

// Lee un atributo en una dirección específica y lo devuelve. Se utiliza para leer un atributo en una dirección específica.
Atributos CDiccionario::leeAtributo(long dir)
{
    Atributos atributo;
    fseek(f, dir, SEEK_SET);
    fread(&atributo, sizeof(Atributos), 1, f);
    return atributo;
}

// Inserta un atributo en la entidad activa.Se inserta el atributo en la entidad activa, actualizando los enlaces de los atributos y la entidad misma.
void CDiccionario::insertaAtributo(Atributos newAtributo, long dirNueva)
{
    if (newAtributo.isKp == 's')
    {
        insertarComoClavePrimaria(newAtributo, dirNueva);
    }
    else if (entactiva.atr == -1)
    { // Lista vacía
        insertarEnCabecera(newAtributo, dirNueva);
    }
    else
    {
        Atributos atrActual = leeAtributo(entactiva.atr);
        if (strcmpi(newAtributo.nombre, atrActual.nombre) < 0)
        {
            if (atrActual.isKp == 's')
            {
                newAtributo.sig = atrActual.sig;
                reescribeAtributo(newAtributo, dirNueva);
                atrActual.sig = dirNueva;
                reescribeAtributo(atrActual, entactiva.atr);
            }
            else
            {
                insertarEnCabecera(newAtributo, dirNueva);
            }
        }
        else
        {
            Atributos atrAnt;
            long cab = entactiva.atr;
            long cabAnt = cab;
            buscarPosicionInsertar(newAtributo, cab, atrActual, atrAnt, cabAnt);
            insertarAntesDeActual(newAtributo, dirNueva, atrAnt, cabAnt, atrActual, cab);
        }
    }
}

// Se encarga de verificar si la entidad activa tiene una clave primaria. Se recorre la lista de atributos y se verifica si hay una clave primaria. Si se encuentra se regresa 1, de lo contrario se regresa -1.
void CDiccionario::insertarComoClavePrimaria(Atributos &newAtributo, long dirNueva)
{
    newAtributo.sig = entactiva.atr;
    reescribeAtributo(newAtributo, dirNueva);
    entactiva.atr = dirNueva;
    reescribeEntidad(entactiva, posentactiva);
}

// Se encarga de verificar si la entidad activa tiene una clave primaria. Se recorre la lista de atributos y se verifica si hay una clave primaria. Si se encuentra se regresa 1, de lo contrario se regresa -1.
void CDiccionario::insertarEnCabecera(Atributos &newAtributo, long dirNueva)
{
    newAtributo.sig = entactiva.atr;
    entactiva.atr = dirNueva;
    reescribeEntidad(entactiva, posentactiva);
    reescribeAtributo(newAtributo, dirNueva);
}

// Se encarga de verificar si la entidad activa tiene una clave primaria. Se recorre la lista de atributos y se verifica si hay una clave primaria. Si se encuentra se regresa 1, de lo contrario se regresa -1.
void CDiccionario::insertarAntesDeActual(Atributos &newAtributo, long dirNueva, Atributos &atrAnt, long cabAnt, Atributos &atrActual, long cab)
{
    newAtributo.sig = cab;
    reescribeAtributo(newAtributo, dirNueva);
    atrAnt.sig = dirNueva;
    reescribeAtributo(atrAnt, cabAnt);
}

// Se encarga de verificar si la entidad activa tiene una clave primaria. Se recorre la lista de atributos y se verifica si hay una clave primaria. Si se encuentra se regresa 1, de lo contrario se regresa -1.
void CDiccionario::buscarPosicionInsertar(Atributos &newAtributo, long &cab, Atributos &atrActual, Atributos &atrAnt, long &cabAnt)
{
    while (cab != -1 && strcmpi(newAtributo.nombre, atrActual.nombre) > 0)
    {
        atrAnt = atrActual;
        cabAnt = cab;
        cab = atrActual.sig;
        if (cab != -1)
        {
            atrActual = leeAtributo(cab);
        }
    }
}

// Se captura un atributo y se devuelve. Se pide al usuario que ingrese los datos del atributo y se devuelve el atributo capturado.
Atributos CDiccionario::capturaAtributo()
{
    Atributos nuevoAtributo;
    cout << "Nombre del nuevo atributo: ";
    cin >> nuevoAtributo.nombre;
    cout << "Tipo de dato: \n";
    cout << "1. Cadena \n 2. Entero \n 3. Numero con decimal \n 4. Doble \n 5. Numero grande \n";
    cin >> nuevoAtributo.tipo;

    if (nuevoAtributo.tipo >= 1 && nuevoAtributo.tipo <= 5)
    {
        if (nuevoAtributo.tipo == 1)
        {
            cout << "Tamanio de la cadena: ";
            cin >> nuevoAtributo.tam;
            nuevoAtributo.tam *= TAMANIOS[0];
        }
        else
        {
            nuevoAtributo.tam = TAMANIOS[nuevoAtributo.tipo - 1];
        }
    }
    else
    {
        def();
    }

    if (clavePrimaria() == -1)
    {
        cout << "Es llave primaria? \n";
        do
        {
            cout << "s-Si \n n-No \n";
            cin >> nuevoAtributo.isKp;
            if (nuevoAtributo.isKp != 's' && nuevoAtributo.isKp != 'n')
                def();
        } while (nuevoAtributo.isKp != 's' && nuevoAtributo.isKp != 'n');
    }
    else
    {
        nuevoAtributo.isKp = 'n';
    }
    nuevoAtributo.sig = -1;
    return nuevoAtributo;
}

// Reescribe un atributo en una dirección específica. Usando la dirección de un atributo y un nuevo atributo, se reescribe el atributo en la dirección específica.

void CDiccionario::reescribeAtributo(Atributos newAtributo, long dir)
{
    fseek(f, dir, SEEK_SET);
    fwrite(&newAtributo, sizeof(Atributos), 1, f);
}

// Escribe un atributo en el archivo y devuelve la dirección. Usando un nuevo atributo, se escribe en el archivo y se devuelve la dirección.

long CDiccionario::escribeAtributo(Atributos newAtributo)
{
    long dir;
    fseek(f, 0, SEEK_END);
    dir = ftell(f);
    fwrite(&newAtributo, sizeof(Atributos), 1, f);
    return dir;
}

// Se encarga de dar de alta un atributo en una entidad. Se captura un atributo y se verifica si ya existe en la entidad activa. Si no existe, se escribe en el archivo y se inserta en la entidad activa.

void CDiccionario::altaAtributo()
{
    long pos;
    Atributos nuevoAtributo;
    nuevoAtributo = capturaAtributo();

    if (buscaAtributo(nuevoAtributo.nombre) == -1)
    {
        pos = escribeAtributo(nuevoAtributo);
        insertaAtributo(nuevoAtributo, pos);
    }
    else
    {
        cout << "El atributo ya existe" << endl;
    }
}

// Se encarga de buscar un atributo en una entidad. Se recorre la lista de atributos y se compara el nombre del atributo con el nombre que se recibe como parámetro. Si se encuentra el atributo se regresa la dirección del atributo, de lo contrario se regresa -1.
long CDiccionario::buscaAtributo(cadena name)
{
    Atributos atr;
    long cab = entactiva.atr;
    if (cab != -1)
        do
        {
            atr = leeAtributo(cab);
            if (strcmpi(atr.nombre, name) == 0)
                return cab;
            else if (strcmpi(atr.nombre, name) > 0)
                break;
            cab = atr.sig;
        } while (cab != -1 && strcmpi(atr.nombre, name) != 0);
    return -1;
}

// se encarga de modificar un atributo en una entidad. Se pide el nombre del atributo a modificar y se verifica si existe en la entidad activa. Si existe se captura un nuevo atributo y se verifica si ya existe en la entidad activa. Si no existe se elimina el atributo y se inserta el nuevo atributo.
void CDiccionario::modificaAtributo()
{
    cadena atrName;
    pideNombreAtributo(&atrName);
    long posAtributo = buscaAtributo(atrName);

    if (posAtributo != -1)
    {
        Atributos atrActual = leeAtributo(posAtributo);

        // Captura del nuevo atributo
        Atributos nuevoAtr = capturaAtributo();
        nuevoAtr.sig = atrActual.sig; // Mantener el enlace de lista

        if (strcmpi(atrActual.nombre, nuevoAtr.nombre) != 0 && buscaAtributo(nuevoAtr.nombre) != -1)
        {
            cout << "Ese atributo ya existe" << endl;
        }
        else
        {
            reescribeAtributo(nuevoAtr, posAtributo);
            cout << "Atributo modificado exitosamente." << endl;
        }
    }
    else
    {
        cout << "El atributo " << atrName << " no existe" << endl;
    }
}

// Pide el nombre de un atributo y lo guarda en la variable name
void CDiccionario::pideNombreAtributo(cadena *name)
{
    cout << "\n Dame el nombre del atributo" << endl;
    cin >> *name;
}

// Se encarga de consultar los atributos en la entidad activa. Se recorre la lista de atributos y se imprime el nombre de cada atributo.
void CDiccionario::consultaAtributos()
{
    long cab = getCabAtributos();
    Atributos atr;
    if (-1 != cab)
    {
        cout << "Nombre \t" << "Tipo \t" << "Tamanio \t" << "Is KP \t" << endl;
        while (cab != -1)
        {
            atr = leeAtributo(cab);
            cout << atr.nombre << "\t" << atr.tipo << "\t" << atr.tam << "\t" << "\t" << atr.isKp << endl;
            cab = atr.sig;
        }
    }
    else
        cout << "Aun no hay atributos" << endl;
}

// Se encarga de obtener la dirección de cabecera de la entidad.
long CDiccionario::getCabAtributos()
{
    long cab = entactiva.atr;
    return cab;
}

// Se encarga de obtener la dirección de la clave primaria de la entidad activa.
// Si no hay clave primaria regresa -1
long CDiccionario::clavePrimaria()
{
    long cab = entactiva.atr;
    Atributos atr;
    while (cab != -1)
    {
        atr = leeAtributo(cab);
        if (atr.isKp == 's' || atr.isKp == 'S')
        {
            return cab;
        }
        cab = atr.sig;
    }
    return -1;
}

// Se encarga de cambiar la clave primaria de la entidad activa.
// Se busca la clave primaria y se cambia el valor de isKp a 'n'.
void CDiccionario::cambiaKP()
{
    long diraux = clavePrimaria();
    Atributos aux = leeAtributo(diraux);
    aux.isKp = 'n';
    reescribeAtributo(aux, diraux);
}

int CDiccionario::checkData()
{
    if (entactiva.data != -1)
    {
        cout << "Esta entidad ya tiene registros, no se permite modificar los atributos" << endl;
        return 1;
    }
    else
        return -1;
}

// BLOQUES

// Se encarga de dar de alta un bloque en una entidad. Se captura un bloque y se verifica si ya existe en la entidad activa. Si no existe, se escribe en el archivo y se inserta en la entidad activa.
int CDiccionario::getAtributos()
{
    long pos, cab = entactiva.atr;
    Natributos = tambloque = 0;
    if (cab != -1)
    {
        do
        {
            atributos[Natributos] = leeAtributo(cab);
            tambloque += atributos[Natributos].tam;
            cab = atributos[Natributos].sig;
            Natributos++;
        } while (cab != -1);
        return 1;
    }
    else
    {
        cout << "Esta entidad no tiene atributos" << endl;
        return -1;
    }
}

// Se encarga de dar de alta un bloque en una entidad. Se captura un bloque y se verifica si ya existe en la entidad activa. Si no existe, se escribe en el archivo y se inserta en la entidad activa.

void *CDiccionario::capturaBloque()
{
    long desp = sizeof(long);
    void *newBloque = malloc(tambloque);
    if (newBloque == NULL)
    {
        cout << "No hay memoria" << endl;
        return 0;
    }
    *((long *)((char *)newBloque + 0)) = (long)-1;
    for (int i = 0; i < Natributos; i++)
    {
        switch (atributos[i].tipo)
        {
        case 1:
            cout << "Ingresa el " << atributos[i].nombre << endl;
            char cadena[500];
            cin >> cadena;
            cadena[strlen(cadena)] = '\0';
            if (strlen(cadena) >= atributos[i].tam)
                cadena[atributos[i].tam - 1] = '\0';
            strcpy((char *)((char *)newBloque + desp), cadena);
            break;
        case 2:
            int datoI;
            cout << "Dame el " << atributos[i].nombre << endl;
            cin >> datoI;
            *((int *)((char *)newBloque + desp)) = datoI;
            break;
        case 3:
            float datoF;
            cout << "Dame el " << atributos[i].nombre << endl;
            cin >> datoF;
            *((float *)((char *)newBloque + desp)) = datoF;
            break;
        case 4:
            double datoD;
            cout << "Dame el " << atributos[i].nombre << endl;
            cin >> datoD;
            *((double *)((char *)newBloque + desp)) = datoD;
            break;
        case 5:
            long datoL;
            cout << "Dame el " << atributos[i].nombre << endl;
            cin >> datoL;
            *((long *)((char *)newBloque + desp)) = datoL;
            break;
        default:
            break;
        }
        desp += atributos[i].tam;
    }
    return newBloque;
}

// Se encarga de buscar un bloque en la entidad activa. Se recorre la lista de bloques hasta encontrar el bloque. Si se encuentra se regresa la dirección del bloque, si no se regresa -1.
long CDiccionario::getApuntadorSig(void *bloque)
{
    long apSig = *((long *)((char *)bloque));
    return apSig;
}

// Se encarga de buscar un bloque en la entidad activa. Se recorre la lista de bloques hasta encontrar el bloque. Si se encuentra se regresa la dirección del bloque, si no se regresa -1.
void CDiccionario::setApuntadorSig(void *bloque, long dir)
{
    *((long *)((char *)bloque)) = dir;
}

// Se encarga de buscar un bloque en la entidad activa. Se recorre la lista de bloques hasta encontrar el bloque. Si se encuentra se regresa la dirección del bloque, si no se regresa -1.
bool CDiccionario::existeKP()
{
    for (int i = 0; i < Natributos; i++)
    {
        if (atributos[i].isKp == 's' || atributos[i].isKp == 'S')
        {
            return true;
        }
    }
    return false;
};

// Se encarga de buscar un bloque en la entidad activa. Se recorre la lista de bloques hasta encontrar el bloque. Si se encuentra se regresa la dirección del bloque, si no se regresa -1.
int CDiccionario::comparaBloque(void *bloque1, void *bloque2)
{
    double valor;
    switch (atributos[0].tipo)
    {
    case 1:
        valor = strcmp(((char *)((char *)bloque1 + sizeof(long))), ((char *)((char *)bloque2 + sizeof(long))));
    case 2:
        valor = *((int *)((char *)bloque1 + sizeof(long))) - *((int *)((char *)bloque2 + sizeof(long)));
    case 3:
        valor = *((float *)((char *)bloque1 + sizeof(long))) - *((float *)((char *)bloque2 + sizeof(long)));
    case 4:
        valor = *((double *)((char *)bloque1 + sizeof(long))) - *((double *)((char *)bloque2 + sizeof(long)));
    case 5:
        valor = *((long *)((char *)bloque1 + sizeof(long))) - *((long *)((char *)bloque2 + sizeof(long)));
    }
    return valor;
};

// Se encarga de buscar un bloque en la entidad activa. Se recorre la lista de bloques hasta encontrar el bloque. Si se encuentra se regresa la dirección del bloque, si no se regresa -1.
void CDiccionario::InsertaBloque(void *nuevoB, long posB)
{
    long cabB = entactiva.data;
    if (cabB == -1)
    {
        insertarEnCabecera(nuevoB, posB);
    }
    else
    {
        void *bloque = leeBloque(cabB);
        if (comparaBloque(nuevoB, bloque) < 0)
        {
            insertarEnCabecera(nuevoB, posB);
        }
        else
        {
            void *bAnte = nullptr;
            long posAnte = cabB;
            buscarPosicionInsertar(bloque, cabB, bAnte, posAnte, nuevoB);
            insertarAntesDeActual(nuevoB, posB, bAnte, posAnte, cabB);
            free(bloque);
            free(bAnte);
        }
    }
}

// Se encarga de buscar la posición en la que se debe insertar un bloque en una entidad. Se recorre la lista de bloques hasta encontrar la posición correcta.
void CDiccionario::insertarEnCabecera(void *nuevoB, long posB)
{
    *((long *)((char *)nuevoB)) = entactiva.data;
    reescribeBloque(posB, nuevoB);
    entactiva.data = posB;
    reescribeEntidad(entactiva, posentactiva);
}

// Se encarga de buscar la posición en la que se debe insertar un bloque en una entidad. Se recorre la lista de bloques hasta encontrar la posición correcta.
void CDiccionario::insertarAntesDeActual(void *nuevoB, long posB, void *bAnte, long posAnte, long cabB)
{
    if (cabB == -1)
    {
        setApuntadorSig(bAnte, posB);
        reescribeBloque(posAnte, bAnte);
        reescribeBloque(posB, nuevoB);
    }
    else
    {
        setApuntadorSig(nuevoB, cabB);
        reescribeBloque(posB, nuevoB);
        setApuntadorSig(bAnte, posB);
        reescribeBloque(posAnte, bAnte);
    }
}

// Se encarga de buscar la posición en la que se debe insertar un bloque en una entidad. Se recorre la lista de bloques hasta encontrar la posición correcta.
void CDiccionario::buscarPosicionInsertar(void *&bloque, long &cabB, void *&bAnte, long &posAnte, void *nuevoB)
{
    while (cabB != -1 && comparaBloque(nuevoB, bloque) > 0)
    {
        if (bAnte != nullptr)
        {
            free(bAnte);
        }
        bAnte = bloque;
        posAnte = cabB;
        cabB = getApuntadorSig(bloque);
        if (cabB != -1)
        {
            bloque = leeBloque(cabB);
        }
    }
}

// Se encarga de dar de alta un bloque en una entidad. Se captura un bloque y se verifica si ya existe en la entidad activa. Si no existe, se escribe en el archivo y se inserta en la entidad activa.
void CDiccionario::altaBloque()
{
    void *bloque = capturaBloque();
    long pos = buscaBloque(bloque);
    if (pos == -1)
    {
        pos = escribeBloque(bloque);
        InsertaBloque(bloque, pos);
    }
    else
    {
        cout << "El bloque ya existe" << endl;
        free(bloque);
    }
}

// Se encarga de reescribir un bloque en una dirección específica. Usando la dirección de un bloque y un nuevo bloque, se reescribe el bloque en la dirección específica.
void CDiccionario::reescribeBloque(long dir, void *bloque)
{
    fseek(f, dir, SEEK_SET);
    fwrite(bloque, tambloque, 1, f);
}

// Se encarga de escribir un bloque en el archivo y devuelve la dirección. Usando un nuevo bloque, se escribe en el archivo y se devuelve la dirección.
long CDiccionario::escribeBloque(void *nuevo)
{
    fseek(f, 0, SEEK_END);
    long dir = ftell(f);
    fwrite(nuevo, tambloque, 1, f);
    return dir;
}

// Se encarga de leer un bloque en una dirección específica. Usando la dirección del bloque se lee y se regresa el bloque.
void *CDiccionario::leeBloque(long dir)
{
    if (dir == -1)
        return NULL;
    void *bloque = malloc(tambloque);
    if (bloque == NULL)
    {
        cout << "No hay memoria" << endl;
    }
    fseek(f, dir, SEEK_SET);
    fread(bloque, tambloque, 1, f);
    return bloque;
}

// Se encarga de buscar un bloque en la entidad activa. Se recorre la lista de bloques hasta encontrar el bloque. Si se encuentra se regresa la dirección del bloque, si no se regresa -1.
long CDiccionario::buscaBloque(void *bloque)
{
    long cabData = entactiva.data;
    void *auxB;
    while (cabData != -1)
    {
        auxB = leeBloque(cabData);
        if (comparaBloque(auxB, bloque) == 0)
        {
            return cabData;
        }
        else
        {
            if (comparaBloque(auxB, bloque) > 0)
            {
                return -1;
            }
            else
            {
                cabData = getApuntadorSig(auxB);
            }
        }
    }
    return -1;
}

// Se encarga de dar de baja un bloque en una entidad. Se pide el bloque a eliminar y se verifica si existe en la entidad activa. Si existe se elimina de la lista de bloques.
void CDiccionario::bajaSecuencia()
{
    void *claveB = capturaKp();
    long bloque = eliminaBloque(claveB);
}

// Se encarga de modificar un bloque en una entidad. Se pide el bloque a modificar y se verifica si existe en la entidad activa. Si existe se captura un nuevo bloque y se verifica si ya existe en la entidad activa. Si no existe se elimina el bloque y se inserta el nuevo bloque.
bool CDiccionario::modificaBloque()
{
    void *claveB = capturaKp();
    long search = buscaBloque(claveB);
    if (search != -1)
    {
        void *newBloque = capturaBloque();
        long deleteBloque = eliminaBloque(claveB);
        reescribeBloque(deleteBloque, newBloque);
        InsertaBloque(newBloque, deleteBloque);
        return true;
    }
    else
    {
        cout << "No se encontro el bloque" << endl;
        return false;
    }
}

// Se encarga de eliminar un bloque en una entidad. Se recorre la lista de bloques hasta encontrar el bloque. Si se encuentra se elimina de la lista de bloques.
long CDiccionario::eliminaBloque(void *claveB)
{
    long cab = entactiva.data;
    void *bloqueAnterior = NULL;
    void *bloqueActual = NULL;
    long cabAnterior;
    if (cab == -1)
        return -1;
    bloqueActual = leeBloque(cab);
    if (comparaBloque(claveB, bloqueActual) == 0)
    {
        entactiva.data = getApuntadorSig(bloqueActual);
        reescribeEntidad(entactiva, posentactiva);
        free(bloqueActual);
        return cab;
    }
    else
    {
        do
        {
            cabAnterior = cab;
            bloqueAnterior = bloqueActual;
            cab = getApuntadorSig(bloqueActual);
            if (cab != -1)
            {
                bloqueActual = leeBloque(cab);
            }
        } while (cab != -1 && comparaBloque(claveB, bloqueActual) > 0);
        if (comparaBloque(claveB, bloqueActual) == 0)
        {
            setApuntadorSig(bloqueAnterior, getApuntadorSig(bloqueActual));
            reescribeBloque(cabAnterior, bloqueAnterior);
            free(bloqueActual);
            free(bloqueAnterior);
            return cab;
        }
    }
    free(bloqueActual);
    free(bloqueAnterior);
    return -1;
};

// Se encarga de consultar los bloques en la entidad activa. Se recorre la lista de bloques y se imprime el contenido de cada bloque.
void CDiccionario::consultaBloques()
{
    void *bloque;
    long avance, cab = entactiva.data;
    if (cab == -1)
        return;
    while (cab != -1)
    {
        bloque = leeBloque(cab);
        avance = sizeof(long);
        for (int i = 0; i < Natributos; i++)
        {
            switch (atributos[i].tipo)
            {
            case 1:
                cout << atributos[i].nombre << ": " << (char *)((char *)bloque + avance) << endl;
                break;
            case 2:
                cout << atributos[i].nombre << ": " << *((int *)((char *)bloque + avance)) << endl;
                break;
            case 3:
                cout << atributos[i].nombre << ": " << *((float *)((char *)bloque + avance)) << endl;
                break;
            case 4:
                cout << atributos[i].nombre << ": " << *((double *)((char *)bloque + avance)) << endl;
                break;
            case 5:
                cout << atributos[i].nombre << ": " << *((long *)((char *)bloque + avance)) << endl;
                break;
            default:
                break;
            }
            avance += atributos[i].tam;
        }
        cab = getApuntadorSig(bloque);
        free(bloque);
    }
}

// Se encarga de capturar un bloque y devolverlo. Se pide al usuario que ingrese los datos del bloque y se devuelve el bloque capturado.
void *CDiccionario::capturaKp()
{
    long apunt = sizeof(long);
    void *newBloque = malloc(tambloque);
    *((long *)((char *)newBloque + 0)) = (long)-1;
    if (newBloque == NULL)
    {
        cout << "No hay memoria" << endl;
        return 0;
    }
    switch (atributos[0].tipo)
    {
    case 1:
        cout << "Ingresa el " << atributos[0].nombre << endl;
        char cadena[500];
        cin >> cadena;
        cadena[strlen(cadena)] = '\0';
        if (strlen(cadena) >= atributos[0].tam)
            cadena[atributos[0].tam - 1] = '\0';
        strcpy((char *)((char *)newBloque + apunt), cadena);
        break;
    case 2:
        int datoI;
        cout << "Dame el " << atributos[0].nombre << endl;
        cin >> datoI;
        *((int *)((char *)newBloque + apunt)) = datoI;
        break;
    case 3:
        float datoF;
        cout << "Dame el " << atributos[0].nombre << endl;
        cin >> datoF;
        *((float *)((char *)newBloque + apunt)) = datoF;
        break;
    case 4:
        double datoD;
        cout << "Dame el " << atributos[0].nombre << endl;
        cin >> datoD;
        *((double *)((char *)newBloque + apunt)) = datoD;
        break;
    case 5:
        long datoL;
        cout << "Dame el " << atributos[0].nombre << endl;
        cin >> datoL;
        *((long *)((char *)newBloque + apunt)) = datoL;
        break;
    default:
        break;
    }
    return newBloque;
}

// EXTRAS
void def()
{
    cin.clear();
    cin.ignore(500, '\n');
    cout << "*****Error, elige una opcion valida*****" << endl;
}

#endif // CDICCCIONARIO_H