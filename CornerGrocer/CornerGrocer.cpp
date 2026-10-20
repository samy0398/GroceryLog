

/*
 * Corner Grocer - Project Three
 * Course: CS-210
 * Description: Tracks grocery item frequencies, displays a histogram,
 * and saves a backup of the frequency data.
 */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>

using namespace std;

class GroceryTracker {
private:
    // Stores each grocery item and its purchase count.
    map<string, int> itemFrequencies;

public:
    // Reads grocery items from the input file and counts them.
    bool LoadItems(const string& filename) {
        ifstream inputFile(filename);
        string item;

        // Check whether the input file opened successfully.
        if (!inputFile.is_open()) {
            cerr << "Error: Could not open " << filename << endl;
            return false;
        }

        // Count each occurrence of a grocery item.
        while (inputFile >> item) {
            itemFrequencies[item]++;
        }

        inputFile.close();
        return true;
    }

    // Searches for an item and displays its frequency.
    void SearchItem(const string& item) const {
        auto found = itemFrequencies.find(item);

        if (found != itemFrequencies.end()) {
            cout << item << " was purchased "
                << found->second << " times." << endl;
        }
        else {
            cout << item << " was not found." << endl;
        }
    }

    // Displays every grocery item and its frequency.
    void PrintFrequencies() const {
        cout << "\nGrocery Item Frequencies" << endl;
        cout << "------------------------" << endl;

        for (const auto& item : itemFrequencies) {
            cout << item.first << " " << item.second << endl;
        }
    }

    // Displays a histogram using asterisks.
    void PrintHistogram() const {
        cout << "\nGrocery Item Histogram" << endl;
        cout << "----------------------" << endl;

        for (const auto& item : itemFrequencies) {
            cout << item.first << " ";

            for (int i = 0; i < item.second; i++) {
                cout << "*";
            }

            cout << endl;
        }
    }

    // Saves all grocery frequencies to a backup file.
    bool SaveFrequencies(const string& filename) const {
        ofstream outputFile(filename);

        // Check whether the backup file opened successfully.
        if (!outputFile.is_open()) {
            cerr << "Error: Could not create "
                << filename << endl;
            return false;
        }

        // Write each item and its frequency to the file.
        for (const auto& item : itemFrequencies) {
            outputFile << item.first << " "
                << item.second << endl;
        }

        outputFile.close();

        if (outputFile.fail()) {
            cerr << "Error: Could not finish writing "
                << filename << endl;
            return false;
        }

        return true;
    }
};

// Displays the main menu.
void DisplayMenu() {
    cout << "\n===== Corner Grocer Menu =====" << endl;
    cout << "1. Search for an item" << endl;
    cout << "2. Display all item frequencies" << endl;
    cout << "3. Display item histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker;

    // Load the grocery data before displaying the menu.
    if (!tracker.LoadItems("CS210_Project_Three_Input_File.txt")) {
        cout << "Please check that the input file is in "
            << "the program's working directory." << endl;
        return 1;
    }

    // Create the backup file automatically at startup.
    tracker.SaveFrequencies("frequency.dat");

    int choice = 0;
    string item;

    // Continue displaying the menu until the user exits.
    while (choice != 4) {
        DisplayMenu();

        // Validate that the menu choice is an integer.
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number "
                << "from 1 to 4." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter a grocery item to search for: ";
            cin >> item;
            tracker.SearchItem(item);
            break;

        case 2:
            tracker.PrintFrequencies();
            break;

        case 3:
            tracker.PrintHistogram();
            break;

        case 4:
            cout << "Thank you for using Corner Grocer!"
                << endl;
            break;

        default:
            cout << "Invalid choice. Please select 1, 2, 3, or 4."
                << endl;
        }
    }

    return 0;
}
