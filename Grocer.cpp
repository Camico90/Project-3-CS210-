#include "Grocer.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip> // For std::setw and std::left

// Using constants for filenames and formatting
const std::string INPUT_FILENAME = "CS210_Project_Three_Input_File.txt";
const std::string BACKUP_FILENAME = "frequency.dat";
const int COLUMN_WIDTH = 20;

// Constructor for the Grocer class. Automatically triggers data loading and backup
Grocer::Grocer() {
    loadDataFromFile();
    backupDataToFile();
}

// Reads the input file and populates the inventory map
void Grocer::loadDataFromFile() {
    // Create a file stream object to read from the input file
    std::ifstream inFS(INPUT_FILENAME);
    std::string itemFromFile;
    frequencyMap.clear(); // Ensure map is empty before loading

    // Always check if the file was opened successfully
    if (!inFS.is_open()) {
        std::cout << "ERROR: Could not open input file: " << INPUT_FILENAME << std::endl;
        return; // Exit the function if the file can't be read
    }

    // Read the file word by word until the end
    while (inFS >> itemFromFile) {
        // Normalize the item name to ensure "apples" and "APPLES" are treated as the same item
        std::string normalizedItem = normalizeItemName(itemFromFile);

        // Use .count() to check if the item already exists in the map
        if (frequencyMap.count(normalizedItem)) {
            // If it exists, get the corresponding GroceryItem object and increment its quantity
            frequencyMap.at(normalizedItem).addQuantity();
        }
        else {
            // If it's a new item, create a new GroceryItem object and insert it into the map
            // .emplace is efficient as it constructs the object in-place
            frequencyMap.emplace(normalizedItem, GroceryItem(normalizedItem));
        }
    }
    // Good practice to always close the file stream when done
    inFS.close();
}

// Saves the current inventory to frequency.dat for backup purposes
void Grocer::backupDataToFile() {
    // Create an output file stream
    std::ofstream outFS(BACKUP_FILENAME);

    // Check for errors opening the file for writing
    if (!outFS.is_open()) {
        std::cout << "ERROR! FILE WRITE FAILED for " << BACKUP_FILENAME << std::endl;
        return;
    }
    std::cout << "\nSystem: Data backup to " << BACKUP_FILENAME << " successful." << std::endl;

    // Iterate through every key and value pair in the map
    for (const std::pair<const std::string, GroceryItem>& pair : frequencyMap) {
        // For each pair, write the item's name and its quantity to a new line in the file
        outFS << pair.second.getName() << " " << pair.second.getQuantity() << std::endl;
    }
    outFS.close(); // Close the stream
}

// Menu Option 1: Search for an item's frequency
void Grocer::printSingleFrequency() {
    std::string userItem;
    std::cout << "\nEnter item name to search for: ";
    std::cin >> userItem;

    // Normalize user input to match the format of the map keys
    std::string normalizedItem = normalizeItemName(userItem);

    // Check if the item exists in the map
    if (frequencyMap.count(normalizedItem)) {
        // If found, print the standardized name and its quantity
        std::cout << "Frequency of " << normalizedItem << ": " << frequencyMap.at(normalizedItem).getQuantity() << std::endl;
    }
    else {
        // If not found, inform the user using the same standardized name for consistency
        std::cout << "Item '" << normalizedItem << "' not found in records." << std::endl;
    }
}

// Menu Option 2: Print a list of all items and their frequencies
void Grocer::printAllFrequencies() {
    std::cout << "\n********** All Item Frequencies **********\n";
    // Iterate through the map and print each item's data
    for (const std::pair<const std::string, GroceryItem>& pair : frequencyMap) {
        // Use std::left and std::setw for clean, aligned columns
        std::cout << std::left << std::setw(COLUMN_WIDTH) << pair.second.getName() << "| " << pair.second.getQuantity() << std::endl;
    }
    std::cout << "**************************************\n";
}

// Menu Option 3: Print a histogram of all frequencies
void Grocer::printAllFrequenciesHistogram() {
    std::cout << "\n********** Item Frequency Histogram **********\n";
    for (const std::pair<const std::string, GroceryItem>& pair : frequencyMap) {
        // Print the item name, aligned to the left
        std::cout << std::left << std::setw(COLUMN_WIDTH) << pair.second.getName() << "| ";

        // Print one asterisk for each unit of quantity
        for (int i = 0; i < pair.second.getQuantity(); ++i) {
            std::cout << "*";
        }
        std::cout << std::endl; // Move to the next line for the next item.
    }
    std::cout << "***********************************************\n";
}

// Adds an item to the inventory
void Grocer::addItem() {
    std::string item;
    std::cout << "Enter an item to add: ";
    std::cin >> item;
    std::string normalizedItem = normalizeItemName(item);

    // Same logic as file loading: increment if exists, create if not
    if (frequencyMap.count(normalizedItem)) {
        frequencyMap.at(normalizedItem).addQuantity();
    }
    else {
        frequencyMap.emplace(normalizedItem, GroceryItem(normalizedItem));
    }
    std::cout << "'" << normalizedItem << "' added. New count: " << frequencyMap.at(normalizedItem).getQuantity() << std::endl;

    // After any modification, back up the data
    backupDataToFile();
}

// Removes an item from the inventory
void Grocer::removeItem() {
    std::string item;
    std::cout << "Enter an item to remove: ";
    std::cin >> item;
    std::string normalizedItem = normalizeItemName(item);

    // First, ensure the item actually exists before trying to remove it
    if (frequencyMap.count(normalizedItem)) {
        // If the quantity is greater than 1, just decrease the count
        if (frequencyMap.at(normalizedItem).getQuantity() > 1) {
            frequencyMap.at(normalizedItem).subtractQuantity();
            std::cout << "'" << normalizedItem << "' count decreased. New count: " << frequencyMap.at(normalizedItem).getQuantity() << std::endl;
        }
        else {
            // If the quantity is 1, remove the item from the map entirely
            frequencyMap.erase(normalizedItem);
            std::cout << "'" << normalizedItem << "' removed from list." << std::endl;
        }
        // Back up the data to reflect the change
        backupDataToFile();
    }
    else {
        // Inform the user if the item wasn't found
        std::cout << "Item '" << item << "' not found." << std::endl;
    }
}

// Normalize strings. Capitalizes the first letter and lowercases the rest
std::string Grocer::normalizeItemName(const std::string& item) const {
    if (item.empty()) return item;

    std::string formatted = item;
    formatted[0] = toupper(formatted[0]);
    for (size_t i = 1; i < formatted.size(); ++i) {
        formatted[i] = tolower(formatted[i]);
    }
    return formatted;
}
