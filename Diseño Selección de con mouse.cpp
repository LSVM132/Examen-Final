#include <iostream>
#include <windows.h>
#include <conio.h>  // Para _getch()
#include <vector>

using namespace std;

// Definición de constantes
const int MAX_VIAJEROS = 100;
const int MAX_REGISTROS = 100;

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
void mostrarMenu(int &opcionSeleccionada);
void detectarClick(int &x, int &y);

// Definición de funciones
void agregarViajero(Viajero viajeros[], int &numViajeros) {
    if (numViajeros >= MAX_VIAJEROS) {
        cout << "No se pueden agregar más viajeros." << endl;
        return;
    }
    Viajero nuevo;
    cout << "Ingrese ID del viajero: ";
    cin >> nuevo.id;
    cin.ignore();
    cout << "Ingrese nombre del viajero: ";
    getline(cin, nuevo.nombre);
    cout << "Ingrese dirección del viajero: ";
    getline(cin, nuevo.direccion);
    viajeros[numViajeros++] = nuevo;
    cout << "Viajero agregado con éxito." << endl;
}

void registrarIngreso(Ingreso ingresos[], int &numIngresos) {
    if (numIngresos >= MAX_REGISTROS) {
        cout << "No se pueden registrar más ingresos." << endl;
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
    cout << "Ingreso registrado con éxito." << endl;
}

void registrarSalida(Salida salidas[], int &numSalidas) {
    if (numSalidas >= MAX_REGISTROS) {
        cout << "No se pueden registrar más salidas." << endl;
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
    cout << "Salida registrada con éxito." << endl;
}

void consultarViajero(Viajero viajeros[], int numViajeros) {
    int id;
    cout << "Ingrese ID del viajero a consultar: ";
    cin >> id;
    for (int i = 0; i < numViajeros; ++i) {
        if (viajeros[i].id == id) {
            cout << "ID: " << viajeros[i].id << endl;
            cout << "Nombre: " << viajeros[i].nombre << endl;
            cout << "Dirección: " << viajeros[i].direccion << endl;
            return;
        }
    }
    cout << "Viajero no encontrado." << endl;
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
    cout << "Registros eliminados con Exito." << endl;
}

void generarReporte(Viajero viajeros[], int numViajeros, Ingreso ingresos[], int numIngresos, Salida salidas[], int numSalidas) {
    cout << "Lista de Viajeros:" << endl;
    for (int i = 0; i < numViajeros; ++i) {
        cout << "ID: " << viajeros[i].id << " Nombre: " << viajeros[i].nombre << " Direccion: " << viajeros[i].direccion << endl;
    }

    cout << "\nRegistros de Ingreso:" << endl;
    for (int i = 0; i < numIngresos; ++i) {
        cout << "ID Viajero: " << ingresos[i].idViajero << " Fecha: " << ingresos[i].fecha << " Lugar: " << ingresos[i].lugarIngreso << endl;
    }

    cout << "\nRegistros de Salida:" << endl;
    for (int i = 0; i < numSalidas; ++i) {
        cout << "ID Viajero: " << salidas[i].idViajero << " Fecha: " << salidas[i].fecha << " Lugar: " << salidas[i].lugarSalida << endl;
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void detectarClick(int &x, int &y) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD events;
    INPUT_RECORD inputRecord;
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    while (true) {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);
        if (inputRecord.EventType == MOUSE_EVENT) {
            if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                x = inputRecord.Event.MouseEvent.dwMousePosition.X;
                y = inputRecord.Event.MouseEvent.dwMousePosition.Y;
                break;
            }
        }
    }
}

void mostrarMenu(int &opcionSeleccionada) {
    system("cls");  // Limpia la pantalla

    const string menu[] = {
        "1. Agregar Viajero",
        "2. Registrar Ingreso",
        "3. Registrar Salida",
        "4. Consultar InformaciOn",
        "5. Borrar Registros",
        "6. Generar Reporte",
        "7. Salir"
    };

    for (int i = 0; i < 7; ++i) {
        gotoxy(0, i);  // Mueve el cursor a la posición de la opción
        cout << menu[i] << endl;  // Muestra el menú
    }

    int x, y;
    detectarClick(x, y);

    // Mapear las coordenadas del clic a una opción del menú
    if (y >= 0 && y < 7) {
        opcionSeleccionada = y;
    } else {
        opcionSeleccionada = -1;  // Si el clic está fuera del menú, se establece una opción inválida
    }
}

// Función principal
int main() {
    Viajero viajeros[MAX_VIAJEROS];
    Ingreso ingresos[MAX_REGISTROS];
    Salida salidas[MAX_REGISTROS];
    int numViajeros = 0, numIngresos = 0, numSalidas = 0;

    int opcionSeleccionada = -1;

    while (opcionSeleccionada != 6) {
        mostrarMenu(opcionSeleccionada);

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
                    borrarRegistros(viajeros, numViajeros, ingresos, numIngresos, salidas, numSalidas, id);
                }
                break;
            case 5:
                generarReporte(viajeros, numViajeros, ingresos, numIngresos, salidas, numSalidas);
                break;
            case 6:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
                break;
        }
    }

    return 0;
}


























