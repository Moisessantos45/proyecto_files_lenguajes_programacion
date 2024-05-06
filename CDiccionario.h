// #ifndef CDICCCIONARIO_H
// #define CDICCCIONARIO_H
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

typedef char cadena[30];

typedef struct atr
{
    cadena nombre;
    int tipo;
    long cantidad;
    struct atr *sig;
    cadena isKp;
} Atributos;

typedef struct
{
    cadena nombre;
    long dir;
    long atr;
    long data;
    long sig;
} Entidad;

class CDiccionario
{
private:
    FILE *f;
    Entidad entactiva;
    long posentactiva;
    long dirActiva;

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
    void menuInicial();
    void menuEntidades();
    void menuAtributos();
    void menuDatos();
    void rescribeEntidad(long dir, Entidad ent);
    void cierraActualDiccionario();
    int abrirDiccionario();

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
        f = fopen(namefile, "wb+");
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
            if (abrirDiccionario() == 1)
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
            // Modificar Entidad
            break;
        case 5:
            menuAtributos(); // nombre) &archivo);
            break;
        case 6:
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
            // Nuevo atributo
            break;
        case 2:
            // Consultar atributos
            break;
        case 3:
            // Eliminar atributos
            break;
        case 4:
            // Modificar atributos
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
    }
    else
    {
        entidad = leeEntidad(cab);
        if (strcmp(ent.nombre, entidad.nombre) < 0)
        {
            ent.sig = cab;
            rescribeEntidad(dirNuevo, ent);
            reescribeCabEntidad(dirNuevo);
        }
        else
        {
            entactiva=entidad;
            while (strcmp(ent.nombre, entactiva.nombre) > 0 && cab != -1)
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
                rescribeEntidad(dirNuevo, ent);
            }
            entidadAnt.sig = dirNuevo;
            rescribeEntidad(cabAnte, entidadAnt);
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
        printf("%s\n", ent.nombre);
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
        printf("Entidad no encontrada\n");
    }
}

// Registra el nombre del archivo que nos esten pidiendo
void CDiccionario::pideNombreEntidad(cadena *name)
{
    cout << "\n Dame el nombre de la entidad" << endl;
    cin >> *name;
}

// Se encarga de eliminar una entidad en el diccionario. se recorre la lista de entidades hasta encontrar la entidad. Si la entidad es la primera en la lista se actualiza la cabecera de las entidades. Si no es la primera se recorre la lista de entidades hasta encontrar la entidad y se elimina.

long CDiccionario::eliminaEntidad(cadena nombre)
{
    long cab = getCabEntidades();
    Entidad ent = leeEntidad(cab);
    if (strcmp(ent.nombre, nombre) == 0)
    {
        reescribeCabEntidad(ent.sig);
    }
    else
    {
        long posAnt;
        Entidad entAnt;
        while (cab != -1 && strcmp(ent.nombre, nombre) != 0)
        {
            posAnt = cab;
            entAnt = ent;
            if (cab != -1)
            {
                ent = leeEntidad(cab);
            }
        }
        if (strcmp(ent.nombre, nombre) == 0)
        {
            entAnt.sig = ent.sig;
            rescribeEntidad(posAnt, entAnt);
        }
    }
    return cab;
}

// #endif // CDICCCIONARIO_H