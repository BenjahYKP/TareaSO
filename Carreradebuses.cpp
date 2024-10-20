#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <chrono>

using namespace std;

// Variables de la carrera
int distancia, cantidadautos, modo_nombres; 
mutex mtx;
vector<string> nombres;

// Función para generar un número aleatorio
int random(int min, int max) {
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

// Función carrera
void correr(Auto &FranchescoVirgolini, int &autosenlameta, int &lugar_actual) {
    while (FranchescoVirgolini.total_avance < distancia) {
        int avance = random(1, 10);
        FranchescoVirgolini.total_avance += avance;
        int tiempo = random(100, 500);
        
        // Necesita bloquear el candado mutex
        {
            lock_guard<mutex> lock(mtx);
            cout << nombres[FranchescoVirgolini.id] << " avanza " << avance 
                << " metros (total: " << FranchescoVirgolini.total_avance << " metros)\n";
        }
        
        this_thread::sleep_for(chrono::milliseconds(tiempo)); // Pausa aleatoria
    }

    // Necesita bloquear el candado mutex
    {
        lock_guard<mutex> lock(mtx);
        lugar_actual++;
        FranchescoVirgolini.lugar = lugar_actual;
        cout << "\033[36m" // Código de escape ANSI para color verde
        << nombres[FranchescoVirgolini.id] 
        << " termina la carrera en el lugar " << FranchescoVirgolini.lugar 
        << "!\033[0m\n"; // Restablecer el color
    }
    
    autosenlameta++;
}

int main(int argc, char *argv[]) {
    // Verificar argumentos ingresados por teclado
    if (argc < 3 || argc > 4) {
        cout << "Uso: " << argv[0] << " <distancia total> <número de autos> [<nombres default= 0 / nombres de autos= 1>]\n";
        return 1;
    }

    // Asocia los argumentos a las variables
    distancia = stoi(argv[1]);
    cantidadautos = stoi(argv[2]);
    modo_nombres = (argc == 4) ? stoi(argv[3]) : 0;

    // Inicializar nombres de autos
    if (modo_nombres == 0) {
        for (int i = 0; i < cantidadautos; i++) {
            nombres.push_back("Auto" + to_string(i));
        }
    } else {
        vector<string> nombres_reales = {
            "Mazda3", "Corsa", "Raptor", "Civic", "Mustang", "Camaro", "Charger", "Beetle", "Golf", "Focus",
            "Accord", "Altima", "Astra", "Aventador", "A4", "A6", "Benz", "Boxster", "Bronco", "Cherokee",
            "Chiron", "Civic", "Corolla", "Cruze", "Durango", "Elantra", "Enclave", "Equinox", "Escalade", "Explorer",
            "Fiesta", "Fusion", "Genesis", "Giulia", "Grand Cherokee", "Impala", "Jetta", "Kona", "Lancer", "Leaf",
            "Malibu", "Maxima", "Model S", "Model X", "Murano", "Optima", "Outback", "Passat", "Pathfinder", "Pilot"
        };
        for (int i = 0; i < cantidadautos; i++) {
            if (i < static_cast<int>(nombres_reales.size())) {
                nombres.push_back(nombres_reales[i]);
            } else {
                nombres.push_back("Auto" + to_string(i - static_cast<int>(nombres_reales.size())));
            }
        }
    }

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
                if (i <= 3) {
                    // Imprimir los tres primeros lugares en verde
                    cout << "\033[32m" << i << "      " << nombres[car.id] << "\033[0m\n";
                } else {
                    cout << i << "      " << nombres[car.id] << "\n";
                }
            }
        }
    }

    return 0;
}