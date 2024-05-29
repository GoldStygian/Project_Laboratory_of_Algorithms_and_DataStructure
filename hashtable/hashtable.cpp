#include "hashtable.hpp"

// #include <cmath> // for pow
#include <string>
#include <cstring>

namespace lasd {

    /* --- Hashable --- */

    /* --- Hashable<int> --- */
    template <>
    class Hashable<int> {
    public:

        ulong operator()(const int& key) noexcept {

            ulong sum = 0;
            int temp = key;

            // Convert integer to a string
            std::string key_str = std::to_string(temp);

            // Divido la stringa in blocchi di 4 caratteri e sommo i loro valori interi
            int intlength = key_str.length() / 4; //4 blocchi da considerare alla volta
            for (int i = 0; i < intlength; i++) {
                ulong val = 0;
                std::memcpy(&val, key_str.substr(i * 4, 4).c_str(), 4);
                //c_str trasforma la sottostringa in un puntatore (richiesto da memcpy)
                //std::memcpy copia tot byte (3 argomento) puntati dal 2 argomento al 1 argomento
                sum += val;
            }

            // caratteri extra da considarare
            int extra = key_str.length() % 4;
            if (extra > 0) {
                ulong val = 0;
                std::memcpy(&val, key_str.substr(intlength * 4).c_str(), extra);
                sum += val;
            }

            return sum;

        }

    };
    
    /* --- Hashable<double> --- */
    template <>
    class Hashable<double> {
    public:

        ulong operator()(const double& key) noexcept {

            ulong sum = 0;

            std::string key_str = std::to_string(key);

            int intlength = key_str.length() / 4;
            for (int i = 0; i < intlength; i++) {
                ulong val = 0;
                std::memcpy(&val, key_str.substr(i * 4, 4).c_str(), 4);
                sum += val;
            }

            int extra = key_str.length() % 4;
            if (extra > 0) {
                ulong val = 0;
                std::memcpy(&val, key_str.substr(intlength * 4).c_str(), extra);
                sum += val;
            }

            return sum;

        }

    };

    /* --- Hashable<string> --- */
    template <>
    class Hashable<std::string> {
    public:

        ulong operator()(const std::string& key) noexcept {

            ulong sum = 0;
            std::string key_str = key;


            int intlength = key_str.length() / 4;
            for (int i = 0; i < intlength; i++) {
                ulong val = 0;
                std::memcpy(&val, key_str.substr(i * 4, 4).c_str(), 4);
                sum += val;
            }

            int extra = key_str.length() % 4;
            if (extra > 0) {
                ulong val = 0;
                std::memcpy(&val, key_str.substr(intlength * 4).c_str(), extra);
                sum += val;
            }

            return sum;

        }

    };

    /* --- HashTable --- */
    template <typename Data>
    ulong HashTable<Data>::HashKey(const Data& key) const{
        Hashable<Data> funHash;
        return (funHash(key) % M);
    }

}
