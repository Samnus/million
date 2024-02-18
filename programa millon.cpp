#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iterator>

const int NUM_NUMBERS = 1000000;
const int MIN_RANGE = -10000000;
const int MAX_RANGE = 10000000;

int generateRandomNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(MIN_RANGE, MAX_RANGE);
    return dis(gen);
}

void generateAndSaveRandomNumbers(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    for (int i = 0; i < NUM_NUMBERS; ++i)
        file << generateRandomNumber() << '\n';

    std::cout << "Números aleatorios generados y guardados en '" << filename << "'." << std::endl;
}

std::vector<int> readNumbersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo " << filename << std::endl;
        return {};
    }

    std::vector<int> numbers;
    int number;
    while (file >> number)
        numbers.push_back(number);

    file.close();
    return numbers;
}

void shuffleNumbers(std::vector<int>& numbers) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(numbers.begin(), numbers.end(), rng);
}

void sortNumbers(std::vector<int>& numbers) {
    std::sort(numbers.begin(), numbers.end());
}

void saveNumbersToFile(const std::string& filename, const std::vector<int>& numbers) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    for (const int& num : numbers)
        file << num << '\n';

    std::cout << "Números guardados en '" << filename << "'." << std::endl;
    file.close();
}

int main() {
    std::cout << "Bienvenido al Generador de Números Aleatorios UMG" << std::endl;
    std::cout << "Seleccione una opción:" << std::endl;
    std::cout << "1. Generar y guardar números aleatorios" << std::endl;
    std::cout << "2. Desordenar números" << std::endl;
    std::cout << "3. Ordenar números" << std::endl;
    std::cout << "4. Salir" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: {
            const std::string randomNumbersFile = "random_numbers.txt";
            generateAndSaveRandomNumbers(randomNumbersFile);
            break;
        }
        case 2: {
            const std::string randomNumbersFile = "random_numbers.txt";
            std::vector<int> numbers = readNumbersFromFile(randomNumbersFile);
            shuffleNumbers(numbers);
            saveNumbersToFile("shuffled_numbers.txt", numbers);
            break;
        }
        case 3: {
            const std::string randomNumbersFile = "random_numbers.txt";
            std::vector<int> numbers = readNumbersFromFile(randomNumbersFile);
            sortNumbers(numbers);
            saveNumbersToFile("sorted_numbers.txt", numbers);
            break;
        }
        case 4:
            std::cout << "Saliendo del programa..." << std::endl;
            return 0;
        default:
            std::cerr << "Opción no válida. Saliendo del programa." << std::endl;
            return 1;
    }

    return 0;
}

