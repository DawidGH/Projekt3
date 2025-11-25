#include <iostream>
#include <vector>
#include <sstream>
#include <iterator> // Dodane dla std::back_inserter i std::distance
#include <type_traits> // Dodane dla std::is_same_v
#include "mergeSort.h" // Zawiera teraz funkcjê custom_sort::merge_sort

// Funkcja pomocnicza do wczytywania wektora od u¿ytkownika
template <typename T>
std::vector<T> readVector(const std::string& typeName) {
    // ... (Logika wczytywania pozostaje bez zmian, jak w poprzedniej odpowiedzi) ...
    // Uwaga: Dla uproszczenia, w pe³ni zaimplementowana wersja jest poni¿ej

    std::vector<T> vec;
    std::string line;
    T value;

    std::cout << "Wprowadz elementy typu " << typeName << ", oddzielone spacjami (): \n> ";
    std::getline(std::cin, line);
    std::stringstream ss(line);

    while (ss >> value) {
        vec.push_back(value);
    }

    if (ss.fail() && !ss.eof()) {
        std::cerr << "Ostrzezenie: Wprowadzono niepoprawne dane dla typu " << typeName << ". Wczytano tylko czesc elementow.\n";
    }

    if (vec.empty()) {
        std::cout << "Brak elementow do sortowania. Uzywam domyslnych.\n";
        if constexpr (std::is_same_v<T, int>) return { 5, 2, 8, 1 };
        if constexpr (std::is_same_v<T, long>) return { 100L, 20L, 5L, 40L };
        //  if constexpr (std::is_same_v<T, float>) return { 3.14f, 1.1f, -2.5f, 0.0f };
         // if constexpr (std::is_same_v<T, double>) return { 9.99, 3.3, 7.7, 2.2 };
        return {};
    }

    return vec;
}

// Funkcja pomocnicza do wyœwietlania wektora
template <typename T>
void printVector(const std::string& typeName, const std::vector<T>& vec) {
    std::cout << "Posortowany " << typeName << ": ";
    for (const auto& x : vec) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    // 1. Wczytywanie wektorów od u¿ytkownika
    std::vector<int>    v1 = readVector<int>("int");
    std::vector<long>   v2 = readVector<long>("long");
    //std::vector<float>  v3 = readVector<float>("float");
    //std::vector<double> v4 = readVector<double>("double");

    // 2. Sortowanie przy u¿yciu nowej globalnej funkcji
    std::cout << "\nRozpoczynanie sortowania...\n";

    // U¿ywamy funkcji na zakresie [begin, end)
    custom_sort::merge_sort(v1.begin(), v1.end());
    custom_sort::merge_sort(v2.begin(), v2.end());
    //custom_sort::merge_sort(v3.begin(), v3.end());
    //custom_sort::merge_sort(v4.begin(), v4.end());

    // 3. Wyœwietlanie wyników
    std::cout << "\n--- Wyniki sortowania ---\n";
    printVector("int", v1);
    printVector("long", v2);
    //printVector("float", v3);
   // printVector("double", v4);

    return 0;
}