#include "Grocer.h" 
#include <iostream>
#include <limits> 

// Using a named enum for menu options 
enum MenuOption {
    SEARCH_ITEM = 1,
    PRINT_LIST = 2,
    PRINT_HISTOGRAM = 3,
    EXIT = 4,
    ADD_ITEM = 5,
    REMOVE_ITEM = 6
};

// Displays the main menu options to the user
void displayMenu() {
    std::cout << "\n************************************" << std::endl;
    std::cout << "1. Search for an item's frequency" << std::endl;
    std::cout << "2. Print frequency of all items" << std::endl;
    std::cout << "3. Print histogram of item frequencies" << std::endl;
    std::cout << "4. Exit Program" << std::endl;
    std::cout << "5. Add Item" << std::endl;
    std::cout << "6. Remove Item" << std::endl;
    std::cout << "************************************" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    // Create an instance of the Grocer class and Its constructor handles loading data
    Grocer storeData;
    int option;

    std::cout << "Welcome to the Corner Grocer Item Tracker!" << std::endl;

    // The main application loop. Runs until the user chooses to exit
    while (true) {
        displayMenu();

        // This loop handles invalid user input (e.x. entering text instead of a number)
        while (!(std::cin >> option)) {
            std::cout << "Invalid input. Please enter a number: ";
            // Clears the error flag on std::cin so future I/O operations will work correctly
            std::cin.clear();
            // Discards the rest of the invalid input line to prevent an infinite loop
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // A switch statement to execute code based on the user's valid integer input
        // Using the enum constants makes the intent of each case clear
        switch (option) {
        case SEARCH_ITEM:
            storeData.printSingleFrequency();
            break;
        case PRINT_LIST:
            storeData.printAllFrequencies();
            break;
        case PRINT_HISTOGRAM:
            storeData.printAllFrequenciesHistogram();
            break;
        case ADD_ITEM:
            storeData.addItem();
            break;
        case REMOVE_ITEM:
            storeData.removeItem();
            break;
        case EXIT:
            std::cout << "Exiting program. Goodbye!" << std::endl;
            return 0; // Terminate the main function and the program
        default:
            // This block runs if the user enters a number that is not a valid menu option
            std::cout << "Invalid option. Please choose a number from 1 to 6." << std::endl;
            break;
        }
    }

    return 0;
}
