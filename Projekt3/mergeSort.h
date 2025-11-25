
#pragma once
#include <vector>
#include <iterator>
#include <algorithm>
#include <type_traits> // Dla std::decay_t

// Definiowanie typu wartoœci na podstawie iteratora
template <typename Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;


namespace custom_sort {

    /**
     * @brief Funkcja scalaj¹ca dwa posortowane podci¹gi.
     * U¿ywa bufora tymczasowego do wykonania scalania.
     */
    template <typename Iterator>
    void merge(Iterator first, Iterator middle, Iterator last, std::vector<ValueType<Iterator>>& buffer) {
        // Aliasy dla czytelnoœci
        using T = ValueType<Iterator>;

        Iterator i = first;
        Iterator j = middle;

        // Zapewnienie, ¿e bufor jest pusty i wystarczaj¹co du¿y (choæ w tym przypadku bufor jest
        // alokowany raz na pocz¹tku, ale ta implementacja jest bardziej ogólna)
        // W kontekœcie globalnej funkcji sortuj¹cej, bufor jest zarz¹dzany przez wywo³uj¹cego.

        // Bufor musi byæ wystarczaj¹co du¿y dla sekcji [first, last)
        size_t section_size = std::distance(first, last);
        buffer.clear();
        buffer.reserve(section_size);

        // 1. Scalanie do bufora tymczasowego
        while (i != middle && j != last) {
            if (*i <= *j) {
                buffer.push_back(std::move(*i++));
            }
            else {
                buffer.push_back(std::move(*j++));
            }
        }

        // 2. Kopiowanie pozosta³ych elementów
        std::move(i, middle, std::back_inserter(buffer));
        std::move(j, last, std::back_inserter(buffer));

        // 3. Kopiowanie posortowanych elementów z bufora z powrotem do oryginalnej sekcji
        // U¿ywamy std::move, aby unikn¹æ zbêdnego kopiowania, jeœli to mo¿liwe
        std::move(buffer.begin(), buffer.end(), first);
    }


    /**
     * @brief Pomocnicza funkcja rekurencyjna.
     */
    template <typename Iterator>
    void merge_sort_helper(Iterator first, Iterator last, std::vector<ValueType<Iterator>>& buffer) {
        // Warunek bazowy: sekcja jest pusta lub zawiera jeden element
        if (std::distance(first, last) <= 1) {
            return;
        }

        // Znajdowanie œrodkowego iteratora
        Iterator middle = first;
        std::advance(middle, std::distance(first, last) / 2);

        // Dzielenie
        merge_sort_helper(first, middle, buffer);
        merge_sort_helper(middle, last, buffer);

        // Scalanie
        merge(first, middle, last, buffer);
    }

    /**
     * @brief G³ówna funkcja Merge Sort.
     * Sortuje sekwencjê w zakresie [first, last).
     * @param first Iterator do pierwszego elementu.
     * @param last Iterator za ostatnim elementem.
     */
    template <typename Iterator>
    void merge_sort(Iterator first, Iterator last) {
        if (first == last) {
            return;
        }

        // Alokacja bufora tymczasowego tylko raz (o maksymalnym potrzebnym rozmiarze)
        std::vector<ValueType<Iterator>> buffer;
        buffer.reserve(std::distance(first, last));

        merge_sort_helper(first, last, buffer);
    }

} // namespace custom_sort