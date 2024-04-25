#ifndef CDICCCIONARIO_H
#define CDICCCIONARIO_H
#include <iostream>
#include <string>

using namespace std;

typedef char cadena[30];

typedef struct
{

} ENTIDAD;

class CDiccionario
{
private:
    FILE *f;
    ENTIDAD entactiva;
    long posentactiva;
    long dirActiva;

public:
    CDiccionario();
    int imprimeMenu(cadena *menu, int tam);
    //void reescribeCabEntidades(long dir);
    void menuInicial();
    void menuEntidades();
    void menuAtributos();
    void menuDatos();
    //void cierraActualDiccionario();
    //void abrirDiccionario();

    virtual ~CDiccionario();

protected:
};

CDiccionario::CDiccionario()
{
    f = NULL;
    dirActiva = -1;
}

/*CDiccionario::abrirDiccionario()
{
    cadena namefile;
    cierraActualDiccioario();
    cout<<"Como se llama el diccionario que quieres abrir"<<endl;
    cin>>namefile;
}*/

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

void CDiccionario::menuInicial()
{
    cadena arr[] = {"\nElige lo que quieres hacer:", "1. Crear diccionario",
                    "2. Abrir diccionario", "3. Salir"};
    cadena nombre = "chancho";
    // FILE *archivo = NULL;
    int opc;
    do
    {
        opc = imprimeMenu(arr, 4);
        switch (opc)
        {
        case 1:
            //  crearFile(nombre &archivo);
            menuEntidades();
            break;
        case 2:
            // abrirFIle(nombre &archivo);
            menuEntidades();
            break;
        case 3:
            cout << "***** Saliendo del programa... *****" << endl;
            // fclose(archivo);
            break;
        default:
            cout << "*****Error, elige una opción valida*****" << endl;
            break;
        }
    } while (opc != 3);
}

void CDiccionario::menuEntidades()
{
    cadena arr[8] = {"\nElige lo que quieres hacer:", "1. Crear entidad",
                     "2. Consultar entidades", "3. Eliminar entidad", "4. Modificar entidad",
                     "5. Menu de atributos", "6. Menu de datos", "7. Regresar al menu principal"};
    int opc;
    do
    {
        opc = imprimeMenu(arr, 8);
        switch (opc)
        {
        case 1:
            // Nueva entidad
            break;
        case 2:
            // Consultar entidades
            break;
        case 3:
            // Eliminar entidad
            break;
        case 4:
            // Modificar entidad
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

void CDiccionario::menuAtributos()
{
    cadena arr[6] = {"\nElige lo que quieres hacer:", "1. Crear atributo",
                     "2. Consultar atributos", "3. Eliminar atributos", "4. Modificar atributos",
                     "5. Regresar al menu entidades"};
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
            cout << "Volviendo al menu de entidades..." << endl;
            break;
        default:
            cout << "*****Error, elige una opción valida*****" << endl;
            break;
        }
    } while (opc != 5);
}

void CDiccionario::menuDatos()
{
        cadena arr[6] = {"\nElige lo que quieres hacer:", "1. Crear registro",
                     "2. Consultar registros", "3. Eliminar registros", "4. Modificar registros",
                     "5. Regresar al menu entidades"};
    int opc;
    do
    {
        opc = imprimeMenu(arr, 6);
        switch (opc)
        {
        case 1:
            //Nuevo registro
            break;
        case 2:
            //Consultar registros
            break;
        case 3:
            //Eliminar registros
            break;
        case 4:
            //Modificar registros
            break;
        case 5:
            cout<<"Volviendo al menu de entidades..."<<endl;
            break;
        default:
            cout<<"*****Error, elige una opción valida*****"<<endl;
            break;
        }
    } while (opc != 5);
}

CDiccionario::~CDiccionario()
{ 
}

#endif // CDICCCIONARIO_H