#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include "Header.h"

using namespace std;

// Main function
int main() {
    GroceryTracker tracker;// Creates instance of GroceryTracker class

    // Load data from provided file
    tracker.LoadDataFromFile("CS210_Project_Three_Input_File.txt");

    int choice = 0; // Assign default vraiable for user's menu choice
    string itemName;// Variable stores name of item from user's input

    do {
        // Loop main menu and options
        cout << "\n\t\t\t******************************";
        cout << "\n\t\t\t***** Corner Grocer Menu *****\n";
        cout << "\t\t\t******************************\n";
        cout << "\t\t\t1. Search for an item\n";
        cout << "\t\t\t2. Display all item frequencies\n";
        cout << "\t\t\t3. Display histogram\n";
        cout << "\t\t\t4. Exit\n";
        cout << "\t\t\tChoose an option (1-4): ";
        cin >> choice; // Get user input for menu selection

        // Input validation loop to ensure user's choice is between 1 and 4
        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();// Clear the input error flag
            cin.ignore(1000, '\n');// Ignore up to 1000 characters in input 
            cout << "Invalid input. Please enter a number between 1 and 4: ";// Prompt again if choice is not between 1 and 4
            cin >> choice;// Get user's input (again)
        }
        // Main menu functionality based on user's menu choice
        switch (choice) {
         // Search for an item
        case 1:
            cout << "\nEnter item name to search: ";
            cin >> itemName;
            // Display frequency of the item using the GroceryTracker function
            cout << itemName << " was purchased "
                << tracker.GetItemFrequency(itemName) << " times.\n";
            break;

         // Display all item frequencies
        case 2:
            tracker.PrintAllItems();
            break;

         // Display histogram of items
        case 3:
            tracker.PrintHistogram();
            break;

         // Exit program
        case 4:
            cout << "Goodbye!\n";
            break;
        }
     // Repeat menu loop until user selects option 4 (Exit)
    } while (choice != 4);
    // Exit program with success status (0 errors)
    return 0;
}