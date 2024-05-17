// #ifndef CDICCCIONARIO_H
// #define CDICCCIONARIO_H
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

// se declara una cadena de 30 caracteres
typedef char cadena[30];

// se declara una estructura de atributos
// se declara el nombre del atributo, el tipo de dato, el tamaño del dato, la cantidad de datos, el siguiente atributo y si es llave primaria
typedef struct atr
{
    cadena nombre;
    int tipo;
    int tam;
    long cantidad;
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

// Se declara la clase CDiccionario que se encarga de manejar las entidades y los atributos
// Se declaran las funciones que se encargan de dar de todas las funcionalidades de mi diccionario
class CDiccionario
{
private:
    FILE *f;
    Entidad entactiva;
    long posentactiva;
    long dirActiva;
    long tambloque;

public:
    CDiccionario();
    int imprimeMenu(cadena *menu, int tam);
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
    void menuInicial();
    void menuEntidades();
    void menuAtributos();
    void menuDatos();
    void reescribeEntidad(Entidad ent, long dir);
    void cierraActualDiccionario();
    int abrirDiccionario();
    int crearDiccionario();
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

    virtual ~CDiccionario();

protected:
};

// Cierra cualquier archivo abierto, pide el nombre y si no existia uno
// así llamado ya, regresa un 1, si no un 0
int CDiccionario::abrirDiccionario()
{
    cadena namefile;
    cierraActualDiccionario();
    cout << "Como se llama el diccionario que quieres abrir" << endl;
    cin >> namefile;
    if (access(namefile, F_OK) == -1)
    {
        f = fopen(namefile, "r+b");
        return 1;
    }
    else
    {
        return 0;
    }
}

int CDiccionario::crearDiccionario()
{
    cadena namefile;
    cierraActualDiccionario();
    cout << "Como se llama el diccionario que quieres abrir" << endl;
    cin >> namefile;
    if (access(namefile, F_OK) == -1)
    {
        f = fopen(namefile, "w+b");
        return 1;
    }
    else
    {
        return 0;
    }
}

// si hay un diccionario abierto lo cierra
void CDiccionario::cierraActualDiccionario()
{
    if (f != NULL)
        fclose(f);
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
        opc = imprimeMenu(arr, 4);
        switch (opc)
        {
        case 1:
            if (crearDiccionario() == 1)
            {
                escribeCabEntidades();
                menuEntidades();
            }
            else
                cout << "El archivo ya existe" << endl;
            break;
        case 2:
            if (abrirDiccionario() == 0)
                menuEntidades();
            else
                cout << "El archivo no existe" << endl;
            break;
        case 3:
            cierraActualDiccionario();
            cout << "***** Saliendo del programa... *****" << endl;
            break;
        default:
            cout << "*****Error, elige una opción valida*****" << endl;
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
            if(pedirEntidad()==1)
                menuAtributos(); // nombre) &archivo);
            break;
        case 6:
            if(pedirEntidad()==1)
                menuDatos(); // nombre &archivo);
            break;
        case 7:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "*****Error, elige una opción valida*****" << endl;
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
            altaAtributo();
            break;
        case 2:
            consultaAtributos();
            break;
        case 3:
            bajaAtributo();
            break;
        case 4:
            modificaAtributo();
            break;
        case 5:
            cout << "Volviendo al menu de Entidades..." << endl;
            break;
        default:
            cout << "*****Error, elige una opción valida*****" << endl;
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
            // Nuevo registro
            break;
        case 2:
            // Consultar registros
            break;
        case 3:
            // Eliminar registros
            break;
        case 4:
            // Modificar registros
            break;
        case 5:
            cout << "Volviendo al menu de Entidades..." << endl;
            break;
        default:
            cout << "*****Error, elige una opción valida*****" << endl;
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
    dirActiva = -1;
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
            return ent.dir;
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
            while (strcmpi(ent.nombre, entactiva.nombre) > 0 && cab != -1)
            {
                entidadAnt = entactiva;
                cabAnte = cab;
                cab = entactiva.sig;
                if (cab != -1)
                {
                    entactiva = leeEntidad(cab);
                }
            }
            if (cab != -1)
            {
                ent.sig = cab;
                reescribeEntidad(ent, dirNuevo);
            }
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
        cout << "La entidad " << entName << "no existe" << endl;
}

// Se encarga de eliminar una entidad en el diccionario. se recorre la lista de entidades hasta encontrar la entidad. Si la entidad es la primera en la lista se actualiza la cabecera de las entidades. Si no es la primera se recorre la lista de entidades hasta encontrar la entidad y se elimina.

long CDiccionario::eliminaEntidad(cadena nombre)
{
    long cab = getCabEntidades();
    Entidad ent = leeEntidad(cab);
    if (strcmpi(ent.nombre, nombre) == 0)
    {
        reescribeCabEntidad(ent.sig);
        return cab;
    }
    else
    {
        long posAnt;
        Entidad entAnt;
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
        }
    }
    return cab;
}

// busca un atributo con un nombre específico en la entidad activa y lo elimina, actualizando los enlaces de los atributos y la entidad misma si es necesario. Devuelve la dirección del atributo que se eliminó.

long CDiccionario::eliminaAtributo(cadena nombre)
{
    long cab = entactiva.atr;
    Atributos atributoAnterior;
    long cabAnterior;
    Atributos atributoAtual = leeAtributo(entactiva.atr);
    if (strcmpi(atributoAtual.nombre, nombre) == 0)
    {
        entactiva.atr = atributoAtual.sig;
        reescribeEntidad(entactiva, posentactiva);
    }
    else
    {
        while (cab != -1 && strcmpi(atributoAtual.nombre, nombre) < 0)
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
void CDiccionario::bajaAtributo()
{
    long pos;
    cadena nombre;
    pideNombreAtributo(&nombre);
    if (buscaAtributo(nombre) != -1)
    {
        pos = eliminaAtributo(nombre);
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
    long cab;
    Atributos atrActual;
    Atributos atrAnt;
    long cabAnt;
    if (newAtributo.isKp == 'S')
    {
        newAtributo.sig = entactiva.atr;
        entactiva.atr = dirNueva;
        reescribeEntidad(entactiva, posentactiva);
        reescribeAtributo(newAtributo, dirNueva);
    }
    else
    {
        if (entactiva.atr == -1)
        {
            entactiva.atr = dirNueva;
            reescribeEntidad(entactiva, posentactiva);
        }
        else
        {
            atrActual = leeAtributo(entactiva.atr);
            if (strcmpi(newAtributo.nombre, atrActual.nombre) < 0)
            {
                newAtributo.sig = entactiva.atr;
                entactiva.atr = dirNueva;
                reescribeEntidad(entactiva, posentactiva);
                reescribeAtributo(newAtributo, dirNueva);
            }
            else
            {
                cab = entactiva.atr;
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
                if (cab != -1)
                {
                    newAtributo.sig = cab;
                    reescribeAtributo(newAtributo, dirNueva);
                    atrAnt.sig = dirNueva;
                    reescribeAtributo(atrAnt, cabAnt);
                }
                else
                {
                    atrAnt.sig = dirNueva;
                    reescribeAtributo(atrAnt, cabAnt);
                }
            }
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

    switch (nuevoAtributo.tipo)
    {
    case 1:
        cout << "Tamanio de la cadena: ";
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
        nuevoAtributo.tam = sizeof(long);
    default:
        break;
    }
    cout << "Es llave primaria? \n";
    do
    {
        cout << "s-Si \n n-No \n";
        cin >> nuevoAtributo.isKp;
        if (nuevoAtributo.isKp != 's' && nuevoAtributo.isKp != 'n')
            cout << "Elige una opcion valida" << endl;
    } while (nuevoAtributo.isKp != 's' && nuevoAtributo.isKp != 'n');
    nuevoAtributo.sig = -1;
    nuevoAtributo.cantidad = 0;
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
    if (buscaAtributo(atrName) != -1)
    {
        Atributos nuevoAtr = capturaAtributo();
        if (buscaAtributo(nuevoAtr.nombre) == -1)
        {
            long pos = eliminaAtributo(atrName);
            reescribeAtributo(nuevoAtr, pos);
            insertaAtributo(nuevoAtr, pos);
        } // ERROR
        else
            cout << "Ese atributo ya existe" << endl;
    }
    else
        cout << "El atributo " << atrName << "no existe" << endl;
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
        cout << "Nombre \t" << "Tipo \t" << "Tamanio \t" << "Cantidad \t" << "Is KP \t" << endl;
        while (cab != -1)
        {
            atr = leeAtributo(cab);
            cout << atr.nombre << "\t" << atr.tipo << "\t" << atr.tam << "\t" << atr.cantidad << "\t" << atr.isKp << endl;
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

int CDiccionario::pedirEntidad()
{
    cadena name;
    long dir;
    pideNombreEntidad(&name);
    if (buscarEntidad(name) != -1)
    {
        dir = getCabEntidades();
        entactiva = leeEntidad(dir);
        while (strcmpi(name, entactiva.nombre) != 0)
        {
            dir = entactiva.sig;
            entactiva = leeEntidad(dir);
        }
        return 1;
    }
    else
    {
        cout << "La entidad no existe" << endl;
        return -1;
    }
}
// #endif // CDICCCIONARIO_H