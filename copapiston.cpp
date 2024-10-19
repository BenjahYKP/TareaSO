#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <chrono>
#include <string>

using namespace std;

// Variables de la carrera
int distancia, cantidadautos; 
mutex mtx; // Sincronizar los recursos compartidos

// Datos del auto
struct Auto {
    string nombre; // Cambiado de id a nombre
    int total_avance = 0;
    int lugar = 0;
};

// Función para generar un número aleatorio
int random_int(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// Función de carrera
void correr(Auto &car, int &autosenlameta, int &lugar_actual) {
    
    while (car.total_avance < distancia) {
        int avance = random_int(1, 10);
        car.total_avance += avance;
        int tiempo = random_int(100, 500);
        
        // Necesita bloquear el candado mutex
        {
            lock_guard<mutex> lock(mtx);
            cout << car.nombre << " avanza " << avance 
                 << " metros (total: " << car.total_avance << " metros)\n";
        }
        
        this_thread::sleep_for(chrono::milliseconds(tiempo)); // Pausa aleatoria
    }

    // Necesita bloquear el candado mutex
    {
        lock_guard<mutex> lock(mtx);
        lugar_actual++;
        car.lugar = lugar_actual;
        cout << car.nombre << " termina la carrera en el lugar " << car.lugar << "!\n";
    }
    
    autosenlameta++;
}

int main(int argc, char *argv[]) {

    // Verificar argumentos ingresados por teclado
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <distancia total distancia> <número de autos cantidadautos>\n";
        return 1;
    }

    distancia = stoi(argv[1]);
    cantidadautos = stoi(argv[2]);

    // Nombres posibles para los autos
    vector<string> nombres_posibles = {"Rayo McQueen", "Francesco Virgolini", "Mate", "Sally", "Doc Hudson", "Luigi", "Jackson Storm", "Chick Hicks", "Cruz Ramirez", "Guido"};
    
    // Vector de autos
    vector<Auto> autos(cantidadautos);
    for (int i = 0; i < cantidadautos; i++) {
        if (i < nombres_posibles.size()) {
            autos[i].nombre = nombres_posibles[i]; // Asigna un nombre de la lista
        } else {
            autos[i].nombre = "Auto" + to_string(i + 1); // Nombre genérico si no hay más nombres
        }
    }

    vector<thread> hilos;
    int autosenlameta = 0; // Contador de autos que han llegado
    int lugar_actual = 0; // Lugar actual en la carrera

    // Crear hilos
    for (int i = 0; i < cantidadautos; i++) {
        hilos.emplace_back(correr, ref(autos[i]), ref(autosenlameta), ref(lugar_actual));
    }

    // Esperar a que todos los autos terminen
    for (auto &hilo : hilos) {
        hilo.join();
    }

    // Imprimir resultados de la carrera
    cout << "\nResultados de la Copa Piston:\n";
    cout << "Lugar  Auto\n";
    for (int i = 1; i <= cantidadautos; i++) {
        for (const auto &car : autos) {
            if (car.lugar == i) {
                cout << i << "      " << car.nombre << "\n";
            }
        }
    }

    return 0;
}
