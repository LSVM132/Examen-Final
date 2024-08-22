#include <iostream>
#include <windows.h>
#include <conio.h>  // Para _getch()
#include <vector>

using namespace std;

// Definición de constantes
const int MAX_VIAJEROS = 100;
const int MAX_REGISTROS = 100;
const int MENU_ANCHO = 40; // Ancho del recuadro del menú
const int MENU_ALTO = 7;   // Número de opciones del menú

// Definición de estructuras
struct Viajero {
    int id;
    string nombre;
    string direccion;
};

struct Ingreso {
    int idViajero;
    string fecha;
    string lugarIngreso;
};

struct Salida {
    int idViajero;
    string fecha;
    string lugarSalida;
};

// Declaración de funciones
void agregarViajero(Viajero viajeros[], int &numViajeros);
void registrarIngreso(Ingreso ingresos[], int &numIngresos);
void registrarSalida(Salida salidas[], int &numSalidas);
void consultarViajero(Viajero viajeros[], int numViajeros);
void borrarRegistros(Viajero viajeros[], int &numViajeros, Ingreso ingresos[], int &numIngresos, Salida salidas[], int &numSalidas, int id);
void generarReporte(Viajero viajeros[], int numViajeros, Ingreso ingresos[], int numIngresos, Salida salidas[], int numSalidas);
void gotoxy(int x, int y);
void cambiarColor(int texto, int fondo);
void limpiarPantalla();
void mostrarMenu();
int obtenerOpcionMenu();

// Definición de colores
const int COLOR_TEXTO_NORMAL = 15;  // Blanco
const int COLOR_FONDO_NORMAL = 0;   // Negro
const int COLOR_TEXTO_ROJO = 12;    // Rojo
const int COLOR_FONDO_ROJO = 0;     // Fondo negro
const int COLOR_TEXTO_AMARILLO = 14; // Amarillo
const int COLOR_FONDO_AMARILLO = 0;  // Fondo negro

// Definición de funciones
void agregarViajero(Viajero viajeros[], int &numViajeros) {
    if (numViajeros >= MAX_VIAJEROS) {
        cambiarColor(COLOR_TEXTO_ROJO, COLOR_FONDO_NORMAL);
        cout << "No se pueden agregar más viajeros." << endl;
        cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
        return;
    }
    Viajero nuevo;
    cout << "Ingrese ID del viajero: ";
    cin >> nuevo.id;
    cin.ignore();
    cout << "Ingrese nombre del viajero: ";
    getline(cin, nuevo.nombre);
    cout << "Ingrese direccion del viajero: ";
    getline(cin, nuevo.direccion);
    viajeros[numViajeros++] = nuevo;
    cambiarColor(COLOR_TEXTO_AMARILLO, COLOR_FONDO_NORMAL);
    cout << "Viajero agregado con éxito." << endl;
    cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
}

void registrarIngreso(Ingreso ingresos[], int &numIngresos) {
    if (numIngresos >= MAX_REGISTROS) {
        cambiarColor(COLOR_TEXTO_ROJO, COLOR_FONDO_NORMAL);
        cout << "No se pueden registrar mas ingresos." << endl;
        cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
        return;
    }
    Ingreso nuevo;
    cout << "Ingrese ID del viajero: ";
    cin >> nuevo.idViajero;
    cin.ignore();
    cout << "Ingrese fecha de ingreso: ";
    getline(cin, nuevo.fecha);
    cout << "Ingrese lugar de ingreso: ";
    getline(cin, nuevo.lugarIngreso);
    ingresos[numIngresos++] = nuevo;
    cambiarColor(COLOR_TEXTO_AMARILLO, COLOR_FONDO_NORMAL);
    cout << "Ingreso registrado con éxito." << endl;
    cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
}

void registrarSalida(Salida salidas[], int &numSalidas) {
    if (numSalidas >= MAX_REGISTROS) {
        cambiarColor(COLOR_TEXTO_ROJO, COLOR_FONDO_NORMAL);
        cout << "No se pueden registrar más salidas." << endl;
        cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
        return;
    }
    Salida nuevo;
    cout << "Ingrese ID del viajero: ";
    cin >> nuevo.idViajero;
    cin.ignore();
    cout << "Ingrese fecha de salida: ";
    getline(cin, nuevo.fecha);
    cout << "Ingrese lugar de salida: ";
    getline(cin, nuevo.lugarSalida);
    salidas[numSalidas++] = nuevo;
    cambiarColor(COLOR_TEXTO_AMARILLO, COLOR_FONDO_NORMAL);
    cout << "Salida registrada con exito." << endl;
    cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
}

void consultarViajero(Viajero viajeros[], int numViajeros) {
    int id;
    cout << "Ingrese ID del viajero a consultar: ";
    cin >> id;
    for (int i = 0; i < numViajeros; ++i) {
        if (viajeros[i].id == id) {
            cambiarColor(COLOR_TEXTO_AMARILLO, COLOR_FONDO_NORMAL);
            cout << "ID: " << viajeros[i].id << endl;
            cout << "Nombre: " << viajeros[i].nombre << endl;
            cout << "Direccion: " << viajeros[i].direccion << endl;
            cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
            return;
        }
    }
    cambiarColor(COLOR_TEXTO_ROJO, COLOR_FONDO_NORMAL);
    cout << "Viajero no encontrado." << endl;
    cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
}

void borrarRegistros(Viajero viajeros[], int &numViajeros, Ingreso ingresos[], int &numIngresos, Salida salidas[], int &numSalidas, int id) {
    // Borrar viajero
    for (int i = 0; i < numViajeros; ++i) {
        if (viajeros[i].id == id) {
            for (int j = i; j < numViajeros - 1; ++j) {
                viajeros[j] = viajeros[j + 1];
            }
            --numViajeros;
            break;
        }
    }

    // Borrar registros de ingreso
    for (int i = 0; i < numIngresos; ++i) {
        if (ingresos[i].idViajero == id) {
            for (int j = i; j < numIngresos - 1; ++j) {
                ingresos[j] = ingresos[j + 1];
            }
            --numIngresos;
            break;
        }
    }

    // Borrar registros de salida
    for (int i = 0; i < numSalidas; ++i) {
        if (salidas[i].idViajero == id) {
            for (int j = i; j < numSalidas - 1; ++j) {
                salidas[j] = salidas[j + 1];
            }
            --numSalidas;
            break;
        }
    }
    cambiarColor(COLOR_TEXTO_AMARILLO, COLOR_FONDO_NORMAL);
    cout << "Registros eliminados con Exito." << endl;
    cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
}

void generarReporte(Viajero viajeros[], int numViajeros, Ingreso ingresos[], int numIngresos, Salida salidas[], int numSalidas) {
    cambiarColor(COLOR_TEXTO_AMARILLO, COLOR_FONDO_NORMAL);
    cout << "Lista de Viajeros:" << endl;
    for (int i = 0; i < numViajeros; ++i) {
        cout << "ID: " << viajeros[i].id << " Nombre: " << viajeros[i].nombre << " Dirección: " << viajeros[i].direccion << endl;
    }

    cout << "\nRegistros de Ingreso:" << endl;
    for (int i = 0; i < numIngresos; ++i) {
        cout << "ID Viajero: " << ingresos[i].idViajero << " Fecha: " << ingresos[i].fecha << " Lugar: " << ingresos[i].lugarIngreso << endl;
    }

    cout << "\nRegistros de Salida:" << endl;
    for (int i = 0; i < numSalidas; ++i) {
        cout << "ID Viajero: " << salidas[i].idViajero << " Fecha: " << salidas[i].fecha << " Lugar: " << salidas[i].lugarSalida << endl;
    }
    cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void cambiarColor(int texto, int fondo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, texto | (fondo << 4));
}

void limpiarPantalla() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD dwWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Obtiene el tamaño del búfer de la pantalla
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Llena la pantalla con espacios en blanco
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coord, &dwWritten);

    // Restaura el color y la posición del cursor
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coord, &dwWritten);
    SetConsoleCursorPosition(hConsole, coord);
}

void mostrarMenu() {
    limpiarPantalla();  // Limpia la pantalla usando la nueva función

    const string menu[] = {
        "1. Agregar Viajero",
        "2. Registrar Ingreso",
        "3. Registrar Salida",
        "4. Consultar Informacion",
        "5. Borrar Registros",
        "6. Generar Reporte",
        "7. Salir"
    };

    // Obtiene las dimensiones de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consolaAncho = csbi.dwSize.X;
    int consolaAlto = csbi.dwSize.Y;

    // Calcula la posición del menú para centrarlo
    int menuX = (consolaAncho - MENU_ANCHO) / 2;
    int menuY = (consolaAlto - MENU_ALTO) / 2;

    cambiarColor(COLOR_TEXTO_AMARILLO, COLOR_FONDO_ROJO);
    
    // Dibujar el marco superior
    gotoxy(menuX, menuY);
    cout << '+' << string(MENU_ANCHO - 2, '-') << '+' << endl;

    // Dibujar el contenido del menú
    for (int i = 0; i < MENU_ALTO; ++i) {
        gotoxy(menuX, menuY + i + 1);
        cout << '|' << " " << menu[i] << string(MENU_ANCHO - menu[i].length() - 3, ' ') << '|' << endl;
    }

    // Dibujar el marco inferior
    gotoxy(menuX, menuY + MENU_ALTO + 1);
    cout << '+' << string(MENU_ANCHO - 2, '-') << '+' << endl;

    cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
}

int obtenerOpcionMenu() {
    int opcion;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore();  // Para limpiar el buffer de entrada
    return opcion - 1;  // Ajusta el índice de 0 a 6
}

// Función principal
int main() {
    Viajero viajeros[MAX_VIAJEROS];
    Ingreso ingresos[MAX_REGISTROS];
    Salida salidas[MAX_REGISTROS];
    int numViajeros = 0, numIngresos = 0, numSalidas = 0;

    int opcionSeleccionada = -1;

    while (opcionSeleccionada != 6) {
        mostrarMenu();
        opcionSeleccionada = obtenerOpcionMenu();

        switch (opcionSeleccionada) {
            case 0:
                agregarViajero(viajeros, numViajeros);
                break;
            case 1:
                registrarIngreso(ingresos, numIngresos);
                break;
            case 2:
                registrarSalida(salidas, numSalidas);
                break;
            case 3:
                consultarViajero(viajeros, numViajeros);
                break;
            case 4:
                {
                    int id;
                    cout << "Ingrese ID del viajero a eliminar: ";
                    cin >> id;
                    cin.ignore();  // Para limpiar el buffer de entrada
                    borrarRegistros(viajeros, numViajeros, ingresos, numIngresos, salidas, numSalidas, id);
                }
                break;
            case 5:
                generarReporte(viajeros, numViajeros, ingresos, numIngresos, salidas, numSalidas);
                break;
            case 6:
                cambiarColor(COLOR_TEXTO_AMARILLO, COLOR_FONDO_NORMAL);
                cout << "Saliendo del programa." << endl;
                cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
                break;
            default:
                cambiarColor(COLOR_TEXTO_ROJO, COLOR_FONDO_NORMAL);
                cout << "Opcion invalida." << endl;
                cambiarColor(COLOR_TEXTO_NORMAL, COLOR_FONDO_NORMAL);
                break;
        }
    }

    return 0;
}

