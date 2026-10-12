#include <iostream>
#include <string>

using namespace std;

// --- ESTRUCTURAS ---
struct Multas {
    string placa;
    int codigo_multa;
    string fecha_multa;
    Multas* sig;
};

struct Vehiculos {
    string placa;
    string marca;
    int modelo;
    string cedula_prop;
    Vehiculos* sig;
};



// Insertar un vehículo al final de la lista
void insertarVehiculo(Vehiculos* &cab, string placa, string marca, int modelo, string cedula) {
    Vehiculos* nuevo = new Vehiculos();
    nuevo->placa = placa;
    nuevo->marca = marca;
    nuevo->modelo = modelo;
    nuevo->cedula_prop = cedula;
    nuevo->sig = nullptr;

    if (cab == nullptr) {
        cab = nuevo;
    } else {
        Vehiculos* aux = cab;
        while (aux->sig != nullptr) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

// Insertar una multa al final de la lista
void insertarMulta(Multas* &cab, string placa, int codigo, string fecha) {
    Multas* nuevo = new Multas();
    nuevo->placa = placa;
    nuevo->codigo_multa = codigo;
    nuevo->fecha_multa = fecha;
    nuevo->sig = nullptr;

    if (cab == nullptr) {
        cab = nuevo;
    } else {
        Multas* aux = cab;
        while (aux->sig != nullptr) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

// Imprimir la lista de vehículos 
void imprimirVehiculos(Vehiculos* cab) {
    Vehiculos* aux = cab;
    cout << "--- LISTA DE VEHICULOS ACTUAL ---" << endl;
    if (aux == nullptr) {
        cout << "La lista esta vacia." << endl;
    }
    while (aux != nullptr) {
        cout << "Placa: " << aux->placa 
             << " | Marca: " << aux->marca 
             << " | Modelo: " << aux->modelo << endl;
        aux = aux->sig;
    }
    cout << "---------------------------------" << endl;
}

// --- SI-NO ---
void eliminarVehiculosSinMultas(Vehiculos* &cab1, Multas* cab2) {
    Vehiculos* actual = cab1;
    Vehiculos* anterior = nullptr;
    int eliminados = 0;

    while (actual != nullptr) {
        bool tieneMulta = false;
        Multas* auxMulta = cab2;
        
        while (auxMulta != nullptr) {
            if (auxMulta->placa == actual->placa) {
                tieneMulta = true;
                break; 
            }
            auxMulta = auxMulta->sig;
        }

        if (!tieneMulta) {
            Vehiculos* temp = actual;
            
            if (anterior == nullptr) {
                cab1 = actual->sig;
                actual = cab1;
            } else {
                anterior->sig = actual->sig;
                actual = actual->sig;
            }
            delete temp;
            eliminados++;
        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }
    
    cout << ">>> Se eliminaron " << eliminados << " vehiculos sin multas." << endl;
}
int main() {
    // 1. Declarar las cabezas de las listas
    Vehiculos* cab1 = nullptr;
    Multas* cab2 = nullptr;

    // 2. Llenar la lista de Vehiculos (cab1) - Simulando datos de Barranquilla
    insertarVehiculo(cab1, "ABC123", "Mazda", 2020, "123456");
    insertarVehiculo(cab1, "DEF456", "Chevrolet", 2018, "789012");
    insertarVehiculo(cab1, "GHI789", "Renault", 2022, "345678");
    insertarVehiculo(cab1, "JKL012", "Kia", 2019, "901234");
    insertarVehiculo(cab1, "MNO345", "Toyota", 2021, "567890");

    // 3. Llenar la lista de Multas (cab2) - Solo algunos vehículos tienen multas
    insertarMulta(cab2, "ABC123", 101, "2023-01-15"); // Tiene multa
    insertarMulta(cab2, "GHI789", 102, "2023-02-20"); // Tiene multa
    insertarMulta(cab2, "MNO345", 103, "2023-03-10"); // Tiene multa

    // Mostrar listas antes de la eliminación
    cout << "=== ANTES DE LA ELIMINACION ===" << endl;
    imprimirVehiculos(cab1);

    // 4. Llamar al procedimiento SI-NO
    cout << "=== EJECUTANDO PROCEDIMIENTO ===" << endl;
    eliminarVehiculosSinMultas(cab1, cab2);

    // 5. Mostrar resultado después de la eliminación
    cout << "=== DESPUES DE LA ELIMINACION ===" << endl;
    imprimirVehiculos(cab1);

    // 6. Liberar memoria restante (buena práctica)
    // Liberar lista de vehículos restantes
    while (cab1 != nullptr) {
        Vehiculos* temp = cab1;
        cab1 = cab1->sig;
        delete temp;
    }
    // Liberar lista de multas
    while (cab2 != nullptr) {
        Multas* temp = cab2;
        cab2 = cab2->sig;
        delete temp;
    }

    return 0;
}