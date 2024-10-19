#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <chrono>

using namespace std;

// Variables de la carrera
int distancia, cantidadautos; 
mutex mtx;

// Función para generar un número aleatorio
int random_int(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// Datos del auto
struct Auto {
    int id;
    int total_avance = 0;
    int lugar = 0;
};


// Función  carrera
void correr(Auto &FranchescoVirgolini, int &autosenlameta, int &lugar_actual) {
    
    while (FranchescoVirgolini.total_avance < distancia) {
        int avance = random_int(1, 10);
        FranchescoVirgolini.total_avance += avance;
        int tiempo = random_int(100, 500);
        
        // Necesita bloquear el candado mutex
        {
            lock_guard<mutex> lock(mtx);
            cout << "Auto" << FranchescoVirgolini.id << " avanza " << avance 
                 << " metros (total: " << FranchescoVirgolini.total_avance << " metros)\n";
        }
        
        this_thread::sleep_for(chrono::milliseconds(tiempo)); // Pausa aleatoria
    }

    // Necesita bloquear el candado mutex
    {
        lock_guard<mutex> lock(mtx);
        lugar_actual++;
        FranchescoVirgolini.lugar = lugar_actual;
        cout << "Auto" << FranchescoVirgolini.id << " termina la carrera en el lugar " << FranchescoVirgolini.lugar << "!\n";
    }
    
    autosenlameta++;
}



int main(int argc, char *argv[]) {

    // Verificar argumentos ingresados por teclado
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <distancia total distancia> <número de autos cantidadautos>\n";
        return 1;
    }

    //Asocia los argumentos a las variables
    distancia = stoi(argv[1]);
    cantidadautos = stoi(argv[2]);

    // Vector de autos
    vector<Auto> autos(cantidadautos);
    for (int i = 0; i < cantidadautos; i++) {
        autos[i].id = i;
    }

    vector<thread> hilos;
    int autosenlameta = 0, lugar_actual = 0; // Variables compartidas

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
                cout << i << "      Auto" << car.id << "\n";
            }
        }
    }

    return 0;
}
