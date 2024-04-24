#include <iostream>
using namespace std;

typedef char cadena[50];

int menuPrincipal();
int menuEntidades();//cadena nombre, FILE **archivo);
int menuAtributos();//cadena nombre, FILE **archivo);
int menuDatos();//cadena nombre, FILE **archivo);
int showmenuPrinc(cadena arr[]);
int showmenuEnt(cadena arr[]);
int showmenuAtrData(cadena arr[]);

int main()
{
    //CDiccionario dic;
    menuPrincipal();
    return 0;
}

int menuPrincipal()
{
    cadena arr[] = {"\nElige lo que quieres hacer:", "1. Crear diccionario",
                     "2. Abrir diccionario", "3. Salir"};
    cadena nombre = "chancho";
    //FILE *archivo = NULL;
    int opc;
    do
    {
        opc = showmenuPrinc(arr);
        switch (opc)
        {
        case 1:
            //crearFile(nombre);// &archivo);
            cout<<"Opcion1"<<endl;
            menuEntidades();//nombre, &archivo);
            break;
        case 2:
            cout<<"Opcion2"<<endl;
            menuEntidades();//nombre, &archivo);
            break;
        case 3:
            cout<<"***** Saliendo del programa... *****"<<endl;
            //fclose(archivo);
            return 0;
            break;
        default:
            cout<<"*****Error, elige una opción valida*****"<<endl;
            break;
        }
    } while (opc != 3);
    return 0;
}

int showmenuPrinc(cadena arr[])
{
    int opc;
    for (int i = 0; i < 4; i++)
        cout<<arr[i]<<endl;
    cin>>opc;
    return opc;
}

int menuEntidades()//(cadena nombre), FILE **archivo);
{
    cadena arr[8] = {"\nElige lo que quieres hacer:", "1. Crear entidad",
                     "2. Consultar entidades", "3. Eliminar entidad", "4. Modificar entidad",
                     "5. Menu de atributos", "6. Menu de datos", "7. Regresar al menu principal"};
    int opc;
    do
    {
        opc = showmenuEnt(arr);
        switch (opc)
        {
        case 1:
            //Nueva entidad
            break;
        case 2:
            //Consultar entidades
            break;
        case 3:
            //Eliminar entidad
            break;
        case 4:
            //Modificar entidad
            break;
        case 5:
            menuAtributos();//nombre) &archivo);
            break;
        case 6:
            menuDatos();//nombre &archivo);
            break;
        case 7:
            cout<<"Volviendo al menu principal..."<<endl;
            break;
        default:
            cout<<"*****Error, elige una opción valida*****"<<endl;
            break;
        }
    } while (opc != 7);
    return 0;
}

int showmenuEnt(cadena arr[])
{
    int opc;
    for (int i = 0; i < 8; i++)
        cout<<arr[i]<<endl;
    cin>>opc;
    return opc;
}

int menuAtributos()//(cadena nombre), FILE **archivo);
{
    cadena arr[6] = {"\nElige lo que quieres hacer:", "1. Crear atributo",
                     "2. Consultar atributos", "3. Eliminar atributos", "4. Modificar atributos",
                     "5. Regresar al menu de entidades"};
    int opc;
    do
    {
        opc = showmenuAtrData(arr);
        switch (opc)
        {
        case 1:
            //Nuevo atributo
            break;
        case 2:
            //Consultar atributos
            break;
        case 3:
            //Eliminar atributos
            break;
        case 4:
            //Modificar atributos
            break;
        case 5:
            cout<<"Volviendo al menu de entidades..."<<endl;
            break;
        default:
            cout<<"*****Error, elige una opción valida*****"<<endl;
            break;
        }
    } while (opc != 5);
    return 0;
}

int showmenuAtrData(cadena arr[])
{
    int opc;
    for (int i = 0; i < 6; i++)
        cout<<arr[i]<<endl;
    cin>>opc;
    return opc;
}

int menuDatos()//(cadena nombre), FILE **archivo);
{
    cadena arr[6] = {"\nElige lo que quieres hacer:", "1. Crear registro",
                     "2. Consultar registros", "3. Eliminar registros", "4. Modificar registros",
                     "5. Regresar al menu de entidades"};
    int opc;
    do
    {
        opc = showmenuAtrData(arr);
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
    return 0;
}