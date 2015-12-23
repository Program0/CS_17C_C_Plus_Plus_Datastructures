/* 
 * File:   map.h
 * Author: super0
 *
 * Created on December 20, 2015, 10:19 AM
 */

#ifndef MAP_H
#define	MAP_H

#include <string>
#include <sstream>
#include <vector> // To hold prime numbers

#include "singlylist.h"
#include "KeyValueList.h"

template<class K, class V>
class Map {
public:

    // Constructors, destructor, and operators

    Map();
    // Default constructor - call main constructor

    Map(unsigned int startSize);
    // Main constructor

    Map(const Map<K, V> & obj);
    // Copy constructor

    ~Map();

    Map<K, V>& operator=(const Map<K, V>& map);
    // Assignment operator    

    // Mutators
    void insert(const K& key, const V& value);
    // Inserts a key value pair into the map

    void remove(const K& key);
    // Removes the key value pair associate by the given entry

    void clear();
    // Removes all entries from the map
    // Accessors
    V& getValue(const K& key) const throw (InvalidArgument);
    // Returns a reference the value associate with the given key   

    bool containsKey(const K& key) const;
    // Returns if a key exists in the map

    bool isEmpty()const;
    // Returns if the map is empty

    unsigned int length()const {
        return keyPairs;
    }
    // Returns the total number key value pairs in the map

    unsigned int capacity() const {
        return tableSize;
    }
    // Returns the current capacity of the hashTable

    std::string toString()const;
    // Returns the contents of the map in a string

    unsigned int totalCollisions() const;
    // Returns the total number of collisions

    /*Hashes to investigate*/
    unsigned int RSHash(const std::string& str);
    unsigned int JSHash(const std::string& str);
    unsigned int PJWHash(const std::string& str);
    unsigned int ELFHash(const std::string& str);
    unsigned int BKDRHash(const std::string& str);
    unsigned int SDBMHash(const std::string& str);
    unsigned int DJBHash(const std::string& str);
    unsigned int DEKHash(const std::string& str);
    unsigned int BPHash(const std::string& str);
    unsigned int FNVHash(const std::string& str);
    unsigned int APHash(const std::string& str);



private:
    float loadFactor;
    unsigned int minimum;
    unsigned int range;
    unsigned int numberPrimes;
    unsigned int *primes;

    unsigned int keyPairs;
    unsigned int tableSize;
    KeyValueList<K, V> *hashTable;

    unsigned int hash(const K& key) const;
    void resize(unsigned int newSize);
    unsigned int hashFunction(const K& key, unsigned int size) const;

};

// Default constructor

template<class K, class V>
Map<K, V>::Map() {

    // Initialize load factor, range, minimum, and numberPrimes
    loadFactor = 1.0;
    minimum = 100;
    range = 31;
    numberPrimes = 29;
    static const int arr[] = {7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381, 32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393, 67108859,
        134217689, 268435399, 536870909, 1073741789, 2147483647};
    primes = new unsigned int [numberPrimes];
    for (int i = 0; i < numberPrimes; i++) {
        primes[i] = arr[i];
    }


    tableSize = minimum;
    hashTable = new KeyValueList<K, V> [tableSize];
    keyPairs = 0;
}

// Main constructor

template<class K, class V>
Map<K, V>::Map(unsigned int startSize) {
    // Initialize constants

    loadFactor = 1.0;
    minimum = 100;
    range = 31;
    numberPrimes = 29;
    static const int arr[] = {7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381, 32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393, 67108859,
        134217689, 268435399, 536870909, 1073741789, 2147483647};
    primes = new unsigned int [numberPrimes];
    for (int i = 0; i < numberPrimes; i++) {
        primes[i] = arr[i];
    }

    if (startSize > minimum) {
        tableSize = startSize;
        hashTable = new KeyValueList<K, V>[tableSize];
    } else {
        tableSize = minimum;
        hashTable = new KeyValueList<K, V>[tableSize];
    }
    keyPairs = 0;
}

// Copy constructor

template<class K, class V>
Map<K, V>::Map(const Map<K, V>& map) {
    // Set the sizes
    loadFactor = 1.0;
    minimum = 100;
    range = 31;
    numberPrimes = 29;
    static const int arr[] = {7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381, 32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393, 67108859,
        134217689, 268435399, 536870909, 1073741789, 2147483647};
    
    primes = new unsigned int [numberPrimes];
      for (int i = 0; i < numberPrimes; i++) {
        primes[i] = arr[i];
    }

    keyPairs = map.keyPairs;
    tableSize = map.tableSize;
    if (map.keyPairs > 0) {
        // Allocate memory
        hashTable = new KeyValueList<K, V>[tableSize];
        // Copy the individual linked lists
        for (int i = 0; i < tableSize; i++) {
            hashTable[i] = map.hashTable[i];

        }
    }
}

//Destructor

template<class K, class V>
Map<K, V>::~Map() {
    for (unsigned int i = 0; i < tableSize; i++) {
        hashTable[i].clear();
    }
    // Clear the hashTable and the primes array
    delete [] primes;
    delete [] hashTable;
}

// Assignment operator

template<class K, class V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& map) {
    // Clear the current map

    // Go through each linked list and clear it
    for (int i = 0; i < tableSize; i++) {
        if (!hashTable[i].isEmpty())
            hashTable[i].clear();
    }

    // Deallocate and reallocate the hashTable
    delete [] hashTable;

    tableSize = map.tableSize;
    // Allocate memory
    hashTable = new KeyValueList<K, V>[tableSize];

    // Copy the linked lists
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = map.hashTable[i];
    }

    // Set the number of key pairs to the map's keyPairs
    keyPairs = map.keyPairs;
    return *this;
}

// Inserts a key value pair into the map. Resizes if necessary depending on 
// the load factor

template<class K, class V>
void Map<K, V>::insert(const K& key, const V& value) {
    // Before adding we need to check if the current load factor is greater
    // than the preset load factor of 1.0
    float currentLoad = ((float) keyPairs / (float) tableSize);

    std::cout << "current load " << currentLoad << " current table size:"
            << tableSize << " current keyPairs " << keyPairs << "\n";
    if (loadFactor < currentLoad) {

        unsigned int newSize = primes[0];
        int index = 1;
        float newLoadFactor = keyPairs / (float) newSize;

        // Find the next biggest prime that will restore the
        // load factor back to less than 1.0
        while (newLoadFactor > loadFactor && index < numberPrimes) {
            // the next size up (size being a prime number)
            if (newLoadFactor > loadFactor) {
                newSize = primes[index++];
            }
            // Update the load factor
            newLoadFactor = (float) keyPairs / newSize;
        }

        std::cout << "We resized \n";
        // Resize the hash table with the new size
        resize(newSize);
    }


    // Find the index of the new entry
    int index = hash(key);
    std::cout << "The index is " << index << " and current tableSize is " << tableSize << "\n";
    // Insert the key at the specified bucket - list

    hashTable[index].insert(key, value);
    keyPairs++;
}

// Returns if the current map is empty

template<class K, class V>
bool Map<K, V>::isEmpty() const {
    return keyPairs == 0;
}

// Returns a value associate with the given key

template<class K, class V>
V& Map<K, V>::getValue(const K& key) const throw (InvalidArgument) {
    try {
        unsigned int index = hash(key);
        hashTable[index].at(key);
    } catch (InvalidArgument) {
        std::cout << "No such element\n";
        exit(EXIT_FAILURE);
    }
}

// Returns whether the given key is in the map

template<class K, class V>
bool Map<K, V>::containsKey(const K& key) const {
    int index = hash(key);
    return hashTable[index].containsKey(key);
}

// Removes a key and its value from the map. Resizes the hash table if the 
// load factor is less than .25.

template<class K, class V>
void Map<K, V>::remove(const K& key) {
    // Get the index for the key
    unsigned int index = hash(key);
    if (hashTable[index].remove(key))
        --keyPairs;

    // Test if we need to resize.
    // Only resize if the load factor is less than 0.25
    float currentLoad = ((float) keyPairs / (float) tableSize);
    if (tableSize > minimum && currentLoad < 0.25) {
        int newSize = primes[numberPrimes - 1];
        int i = numberPrimes - 1;
        double newLoadFactor = keyPairs / (float) newSize;

        // Find the next biggest prime that will restore the
        // load factor back to less than 1.0 and greater than 0.75
        while (newLoadFactor < 0.75 && i > 0) {
            // the next size up (size being a prime number)
            if (newLoadFactor < loadFactor) {
                newSize = primes[i--];
            }
            // Update the load factor
            newLoadFactor = (float) keyPairs / newSize;
        }
        // Resize the hash table with the new size
        resize(newSize);
    }
}

// Clears the map

template<class K, class V>
void Map<K, V>::clear() {
    // Go through each linked list and clear it
    for (int i = 0; i < tableSize; i++) {
        if (!hashTable[i].isEmpty())
            hashTable[i].clear();
    }

    // Deallocate and reallocate the hashTable
    delete [] hashTable;

    tableSize = minimum;
    // Allocate memory
    hashTable = new KeyValueList<K, V>[tableSize];

    // Set the number of key pairs to zero
    keyPairs = 0;
}

template<class K, class V>
unsigned int Map<K,V>::totalCollisions() const{
    // Iterate through the hashTable. Any link with size > 1 has a collision.
    unsigned int collisions = 0;
    for(int i =0; i<tableSize;i++){
        if(hashTable[i].length()>1){
            collisions += (hashTable[i].length()-1);
        }
    }
    return collisions;
}

template<class K, class V>
std::string Map<K,V>::toString() const{
    std::string s;
    for(int i =0; i<tableSize;i++){
        s += hashTable[i].keyValueToString();    
    }
    return s;    
}

/*Utility Functions*/

// Spans the size of the hashTable based on the hashFunction

template<class K, class V>
unsigned int Map<K, V>::hash(const K& key) const {
    int hash = hashFunction(key, tableSize);
    hash = hash % tableSize;
    if (hash < 0)
        hash = hash + tableSize;
    return hash;
}

// Hash function to map a key to an index in the hashTable

template<class K, class V>
unsigned int Map<K, V>::hashFunction(const K& key, unsigned int size) const {
    double temp = 0.0;
    std::stringstream s;
    s << key;
    std::string output = s.str();
    for (int i = 0; i < output.length(); i++) {
        temp = range * temp + static_cast<double> (output[i]);
    }
    // Code from textbook. We assign the bits from temp to
    // bits then shift the bits 32 bits to the right and cast to an int
    long bits = static_cast<double> (temp);
    int hash = (int) (bits ^ (bits >> 32));
    return hash;
}

// Resizes the hashTabe

template<class K, class V>
void Map<K, V>::resize(unsigned int newSize) {
    unsigned int newHash = 0;
    // Resize only if the new size is greater than the required minimum
    if (newSize > minimum) {
        KeyValueList<K, V> *tempTable = new KeyValueList<K, V>[newSize];

        // Store the current size of the hashTable

        unsigned int temp = tableSize;
        // Update the size of the current object table size
        // and number of key pairs. Affects the result of hash(key))
        tableSize = newSize;
        for (unsigned int i = 0; i < temp; i++) {
            {
                // Only add those keys where the chains are not empty
                if (!hashTable[i].isEmpty()) {
                    typename KeyValueList<K, V>::iterator it;
                    typename KeyValueList<K, V>::iterator finish = hashTable[i].end();
                    for (it = hashTable[i].begin(); it != finish; it++) {
                        // Put the key in the existing objects hash table
                        // in the new hash table                        
                        newHash = hash((*it).first);
                        tempTable[newHash].insert((*it).first, (*it).second);
                    }
                }
            }
        }
        // Change the reference to point to the new hash table
        delete [] hashTable;
        hashTable = tempTable;
    }
}

// Hash to test

template<class K, class V>
unsigned int Map<K, V>::RSHash(const std::string& str) {
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash = hash * a + str[i];
        a = a * b;
    }

    return hash;
}
/* End Of RS Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::JSHash(const std::string& str) {
    unsigned int hash = 1315423911;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash ^= ((hash << 5) + str[i] + (hash >> 2));
    }

    return hash;
}
/* End Of JS Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::PJWHash(const std::string& str) {
    unsigned int BitsInUnsignedInt = (unsigned int) (sizeof (unsigned int) * 8);
    unsigned int ThreeQuarters = (unsigned int) ((BitsInUnsignedInt * 3) / 4);
    unsigned int OneEighth = (unsigned int) (BitsInUnsignedInt / 8);
    unsigned int HighBits = (unsigned int) (0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash = (hash << OneEighth) + str[i];

        if ((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}
/* End Of  P. J. Weinberger Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::ELFHash(const std::string& str) {
    unsigned int hash = 0;
    unsigned int x = 0;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash = (hash << 4) + str[i];
        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }

    return hash;
}
/* End Of ELF Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::BKDRHash(const std::string& str) {
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash = (hash * seed) + str[i];
    }

    return hash;
}
/* End Of BKDR Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::SDBMHash(const std::string& str) {
    unsigned int hash = 0;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash = str[i] + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}
/* End Of SDBM Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::DJBHash(const std::string& str) {
    unsigned int hash = 5381;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash = ((hash << 5) + hash) + str[i];
    }

    return hash;
}
/* End Of DJB Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::DEKHash(const std::string& str) {
    unsigned int hash = static_cast<unsigned int> (str.length());

    for (std::size_t i = 0; i < str.length(); i++) {
        hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
    }

    return hash;
}
/* End Of DEK Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::BPHash(const std::string& str) {
    unsigned int hash = 0;
    for (std::size_t i = 0; i < str.length(); i++) {
        hash = hash << 7 ^ str[i];
    }

    return hash;
}
/* End Of BP Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::FNVHash(const std::string& str) {
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hash = 0;
    for (std::size_t i = 0; i < str.length(); i++) {
        hash *= fnv_prime;
        hash ^= str[i];
    }

    return hash;
}
/* End Of FNV Hash Function */


// Hash to test

template<class K, class V>
unsigned int Map<K, V>::APHash(const std::string& str) {
    unsigned int hash = 0xAAAAAAAA;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ str[i] * (hash >> 3)) :
                (~((hash << 11) + (str[i] ^ (hash >> 5))));
    }

    return hash;
}

#endif	/* MAP_H */

