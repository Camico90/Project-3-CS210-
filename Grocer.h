#ifndef GROCER_H
#define GROCER_H

#include "GroceryItem.h" 
#include <map>           
#include <string>        

// Grocer class is responsible for loading data from a file and tracking item frequencies
class Grocer {
public:
    //  Constructs the Grocer object and loads initial data
    Grocer();

    // Finds and prints the frequency of a single user-specified item
    void printSingleFrequency();

    // Prints a formatted list of all items and their frequencies
    void printAllFrequencies();

    // Prints a histogram representation of all item frequencies
    void printAllFrequenciesHistogram();

    // Adds a new item or increments an existing one
    void addItem();

    // Decrements an item's count or removes it if the count is one
    void removeItem();

private:
    // A map where the key is the normalized item name for fast lookups,
    // and the value is the complete GroceryItem object, which holds all item data
    std::map<std::string, GroceryItem> frequencyMap;

    // Loads item data from the source file into the frequencyMap
    void loadDataFromFile();

    // Saves the current inventory data from frequencyMap to the backup file
    void backupDataToFile();

    // Normalize a string to a consistent format (e.x. "Apples")
    std::string normalizeItemName(const std::string& item) const;
};

#endif // GROCER_H
