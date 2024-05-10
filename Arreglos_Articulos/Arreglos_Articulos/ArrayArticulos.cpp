#ifdef _unix_         
#elif defined(_WIN32) || defined(WIN32) 
#define OS_Windows
#endif

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

void limpiarPantalla() {
#ifdef OS_Windows 
    
    system("cls");
#else
    
    system("clear"); 
#endif  
}

typedef struct Reporte { 
    string codigoDeBarras = ""; 
    string nombreDeArticulo = ""; 
}Reporte;

string getUserString(string nombrePropiedad, int longitudMaxima) {
    string userString;
    int n;
    do {
        cout << "Ingresa el " << nombrePropiedad << " (" << longitudMaxima << " caracteres maximo): ";
        getline(cin >> ws, userString);

        n = userString.size();
        if (n > longitudMaxima)
            cout << "Error. El " << nombrePropiedad << " no debe exceder " << longitudMaxima << " caracteres." << endl;
    } while (n > longitudMaxima);
    return userString;
}

void pausa() {
    cout << "Presionar enter para continuar (a veces tienes que dar doble enter por motivos de administracion): ";
    cin.ignore();
    cin.get();
    
}

bool compararString(Reporte r1, Reporte r2) {
    return r1.nombreDeArticulo < r2.nombreDeArticulo;
}

void imprimirReporte(Reporte r) {
    cout << "Articulo:" << endl;
    cout << "  Codigo de barras: " << r.codigoDeBarras << endl;
    cout << "  Nombre de articulo: " << r.nombreDeArticulo << endl;
}


bool isCodigoDeBarrasInReportes(Reporte* reportes, int iReportes, string codigoDeBarras) {
    bool codigoDeBarrasInReportes = false;
    for (int i = 0; i < iReportes; i++) {
        if (reportes[i].codigoDeBarras == codigoDeBarras) {
            codigoDeBarrasInReportes = true;
            break;
        }
    }
    return codigoDeBarrasInReportes;
}

Reporte obtenerNuevoReporteUnico(Reporte* reportes, int iReportes) {
    string codigoDeBarras;
    bool codigoDeBarrasInReportes;
    do {
        codigoDeBarras = getUserString("codigo de barras", 15);
        cout << "EL CODIGO DE BARRAS INGRESADO: " << codigoDeBarras << endl;
        codigoDeBarrasInReportes = isCodigoDeBarrasInReportes(reportes, iReportes, codigoDeBarras);

        if (codigoDeBarrasInReportes)
            cout << "Lo sentimos. El codigo de barras ya se encuentra registrado en el sistema. Intente otro. " << endl;
    } while (codigoDeBarrasInReportes);

    string nombreDeArticulo = getUserString("nombre de articulo", 80);
    Reporte nuevoReporte;
    nuevoReporte.nombreDeArticulo = nombreDeArticulo;
    nuevoReporte.codigoDeBarras = codigoDeBarras;
    return nuevoReporte;
}


int buscarCodigoDeBarrasInReportes(Reporte* reportes, int iReportes, string codigoDeBarras) {


    bool codigoDeBarrasInReportes = false;
    int j = -1;
    for (int i = 0; i < iReportes; i++) {
        if (reportes[i].codigoDeBarras == codigoDeBarras) {
            j = i;
            codigoDeBarrasInReportes = true;
            break;
        }
    }
    return j;
}

int main() {

    bool seguir = true;
    bool errorOpcionIngresada=0;
    int opcionIngresada;
    Reporte reportes[1000];
    int iReportes = 0;
    string codigoDeBarras;
    string nombreDeArticulo;
    int n;
    bool codigoDeBarrasInReportes = false;
    do {
        limpiarPantalla();
        if (errorOpcionIngresada) {
            cout << "==> Error. Opción inválida, ingrese una opción del menú" << endl << endl;

        }
        cout << "============" << endl;
        cout << "| REPORTES |" << endl;
        cout << "============" << endl;
        cout << "1) Altas" << endl;
        cout << "2) Consultas" << endl;
        cout << "3) Cambios" << endl;
        cout << "4) Bajas" << endl;
        cout << "5) Reportes" << endl;
        cout << "6) Salir del programa" << endl;
        cout << "Ingrese opcion deseada: ";
        cin >> opcionIngresada;
        errorOpcionIngresada = false;
        if (opcionIngresada == 1) {
            
            limpiarPantalla();
            cout << "ALTAS" << endl << endl;

            Reporte nuevoReporte = obtenerNuevoReporteUnico(reportes, iReportes);
            reportes[iReportes] = nuevoReporte;
            iReportes++;

        }
        else if (opcionIngresada == 2) {
            
            limpiarPantalla();
            cout << "CONSULTAS" << endl;
            cout << "Se buscara en reportes el codigo de barras ingresado: " << endl;
            codigoDeBarras = getUserString("codigo de barras", 15);
            int jCodigoBarras = buscarCodigoDeBarrasInReportes(reportes, iReportes, codigoDeBarras);
            if (jCodigoBarras == -1)
                cout << "Articulo no encontrado " << endl;
            else
                imprimirReporte(reportes[jCodigoBarras]);
            pausa();

        }
        else if (opcionIngresada == 3) {
           
            limpiarPantalla();
            cout << "CAMBIOS" << endl;
            cout << "Ingresa el codigo de barras a cambiar: " << endl;
            codigoDeBarras = getUserString("codigo de barras", 15);
            int jCodigoBarras = buscarCodigoDeBarrasInReportes(reportes, iReportes, codigoDeBarras);
            if (jCodigoBarras == -1)
                cout << "Articulo no encontrado " << endl;
            else {
                
                cout << "Tu articulo fue encontrado, ahora ingresa la nueva informacion:" << endl << endl;
                Reporte nuevoReporte = obtenerNuevoReporteUnico(reportes, iReportes);
                reportes[jCodigoBarras] = nuevoReporte;
            }
            pausa();

        }
        else if (opcionIngresada == 4) {
           
            limpiarPantalla();
            cout << "BAJAS" << endl;
            cout << "Ingresa el codigo de barras a dar de baja: " << endl;
            codigoDeBarras = getUserString("codigo de barras", 15);
            int jCodigoBarras = buscarCodigoDeBarrasInReportes(reportes, iReportes, codigoDeBarras);
            if (jCodigoBarras == -1)
                cout << "Articulo no encontrado " << endl;
            else {
            
                for (int i = jCodigoBarras + 1; i < iReportes; i++) {
                    reportes[i - 1] = reportes[i];
                }
                iReportes--;
                cout << "Articulo borrado" << endl;
            }
            pausa();


        }
        else if (opcionIngresada == 5) {
       
            limpiarPantalla();
            cout << "REPORTES" << endl;
            vector<Reporte> x;
            for (int i = 0; i < iReportes; i++) {
                x.push_back(reportes[i]);
            }
            sort(x.begin(), x.end(), compararString);
            for (int i = 0; i < iReportes; i++) {
                imprimirReporte(x[i]);
            }
            pausa();

        }
        else if (opcionIngresada == 6) {
           
            seguir = false;
        }
        else {

            errorOpcionIngresada = true;
        }


    } while (seguir);

    return 0;
}