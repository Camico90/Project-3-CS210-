#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>

using namespace std;
 // GroceryTracker class definition
class GroceryTracker {
private:
	map<string, int> itemFrequency; // Stores each item and its frequency

public:
	// Loads all grocery data from file into map
	void LoadDataFromFile(const string& CS210_Project_Three_Input_File) {
		ifstream inFile(CS210_Project_Three_Input_File); // Open input file
		// Validate that file is open successfully
		if (!inFile.is_open()) {
			cout << "ERROR: Unable to open file" << CS210_Project_Three_Input_File << endl;// Display Error Message
			return;
		}

		string item;
		// Read each item from the file
			while (inFile >> item) {
				// Assigning first letter as capital and the rest are lower
				if (!item.empty()) {
					item[0] = toupper(item[0]);// Convert first letter to capital
					for (size_t i = 1; i < item.size(); ++i) {
						item[i] = tolower(item[i]); // Convert remaining letters to lowercase
					}
				}
				itemFrequency[item]++; // Frequency count
			}
			inFile.close();// Closing file
			// Write to backup
			WriteBackupFile("frequency.dat");
	}
	// Writes item frequency data to a backup file
	void WriteBackupFile(const string& frequency) {
		ofstream outFile(frequency); // Create/open file
		// Check if file opened successfully
		if (!outFile.is_open()) {
			cout << "ERROR: Unable to open file" << frequency << endl;// Display Error Message
			return;
		}
		// Loop through each item, then Write each item and its frequency
		for (const auto& pair : itemFrequency) {
			outFile << pair.first << " " << pair.second << endl;
		}

		outFile.close();// Closing file
		cout << "*********Backup Successful**********" << frequency << endl;// Display confirmation Message
	}
	// Returns frequency of a specific item
	int GetItemFrequency(const string& itemName) {
		string formattedItem = itemName;
		// Check if string is not empty
		if (!formattedItem.empty()) {
			formattedItem[0] = toupper(formattedItem[0]);// Capitalize first letter of item
			// All other letters of item to lowercase
			for (size_t i = 1; i < formattedItem.size(); ++i) {
				formattedItem[i] = tolower(formattedItem[i]);
			}
		}
		// Return count if found, otherwise 0
		if (itemFrequency.find(formattedItem) != itemFrequency.end()) {
			return itemFrequency[formattedItem];
		}
		return 0; // Item not found
	}

	// Print all items and their frequencies
	void PrintAllItems() {
		// Display Item Frequency List
		cout << "\t\t\t*******************************";
		cout << "\n\t\t\t***** Item Frequency List *****\n";
		cout << "\t\t\t*******************************\n";
		// Loop through map to print item and its frequency
		for (const auto& pair : itemFrequency) {
			cout << left << setw(15) << "\t\t\t" << pair.first << " " << pair.second << endl;
		}
	}

	// Print histogram (item name + asterisks)
	void PrintHistogram() {
		// Display Purchase Frequency Histogram
		cout << "\t\t\t****************************************";
		cout << "\n\t\t\t***** Purchase Frequency Histogram *****\n";
		cout << "\t\t\t****************************************\n";
		// Loop through each item
		for (const auto& pair : itemFrequency) {
			cout << left << setw(15) << "\t\t\t" << pair.first << " ";// Display item name
			// Loop to print astericks "*" equal to frequency
			for (int i = 0; i < pair.second; ++i) {
				cout << "*"; // Display "*" per frequency
			}
			cout << endl;
		}
	}
};