/*
    CSC5720 Programming Algorithms
    University of Southern Queensland
    Trimester 1, 2026

    Student: Brett Jenaway
    Student No: W0104215

    Assignment 3 - Report
    UniSQWareHouse Inventory Management System


    TO DO LIST:
      1. Improve/change search algorithm
*/

#include <iostream> // STL library for console output and input
#include <string>   // STL library for strings
#include <sstream>
#include <algorithm> // STL library for sort function and swap function
#include <vector>    // STL library for vector to store the inventory items
#include <iomanip>   // STL library for setw and formatting the output
#include <fstream>   // STL library for reading and writing external database file
using namespace std;

// Class definition
class InventoryItem
{
private:
public:
    string itemName;
    int quantityInStock;
    int storageZone;
    string dateIn;
    string dateOut;
    string itemNotes;

    // Default class input
    InventoryItem()
    {
        itemName = "";
        quantityInStock = 0;
        storageZone = 0;
        dateIn = "";
        dateOut = "";
        itemNotes = "";
    }

    // Class input with all parameters
    InventoryItem(string name, int quantity, int zone, string inDate, string outDate, string notes)
    {
        itemName = name;
        quantityInStock = quantity;
        storageZone = zone;
        dateIn = inDate;
        dateOut = outDate;
        itemNotes = notes;
    }

    // Function to ensure quantity entered is greater than 0
    void setQuantityInStock(int quantity)
    {
        if (quantity >= 0)
        {
            quantityInStock = quantity;
        }
        else
        {
            cout << "Invalid quantity. Quantity set to 1" << endl;
            quantityInStock = 1;
        }
    }

    // Function to ensure zone entered is greater than 0
    void setZone(int zone)
    {
        if (zone > 0)
        {
            storageZone = zone;
        }
        else
        {
            cout << "Invalid quantity. Quantity set to 1" << endl;
            storageZone = 1;
        }
    }
};

// Prototypes
void addInventoryItem();
bool searchInventory();
void displayItem(InventoryItem item);
void displayDatabase();
void deleteItem(vector<InventoryItem> &inventory, int indexNumber);
int itemDeleteIndex = 0;
void openFile(string fileName);
void saveFile(string fileName);

// Define variables
string databaseName = "database.txt";
vector<InventoryItem> database;

// Main function
int main()
{
    // Open database txt file
    openFile(databaseName);

    // Define variables
    int userInput;
    bool flag = false;

    while (!flag)
    {
        // Main function
        cout << "-------------------------------------------" << endl;
        cout << "- UniSQWareHouse Storage Inventory System -" << endl;
        cout << "-------------------------------------------" << endl;
        cout << endl;
        cout << "Welcome to UniSQWareHouse Inventory Management System" << endl;
        cout << endl;
        cout << "Please choose an option from the following selection:" << endl;
        cout << "1. Add item to database" << endl;
        cout << "2. Remove item from database" << endl;
        cout << "3. Search database for item" << endl;
        cout << "4. View database" << endl;
        cout << "5. Exit" << endl
             << endl;
        cout << "Your selection: ";
        cin >> userInput;
        cin.ignore(10000, '\n');

        switch (userInput)
        {
        case 1:
            addInventoryItem();
            break;
        case 2:
            if (searchInventory())
            {
                deleteItem(database, itemDeleteIndex);
            }
            break;
        case 3:
            searchInventory();
            break;
        case 4:
            displayDatabase();
            break;
        case 5:
            cout << "Exiting program" << endl;
            saveFile(databaseName);
            flag = true;
            return 0;
        default:
            cout << "Incorrect selection. Please choose again." << endl;
        }
        cout << endl;
    }
    return 0;
}

// This function to add a new item to the inventory
// Parameters: none
// Returns: none
void addInventoryItem()
{
    string itemInput;
    int quantityInput;
    int zoneInput;
    string inDate;
    string outDate;
    string notesInput;

    cout << "Add a new item to the inventory" << endl;
    cout << "Enter item name: ";
    getline(cin, itemInput); // Use getline instead of cin for instances where multiple words are entered

    cout << "Enter item quantity in stock: ";
    cin >> quantityInput;

    cout << "Enter item storage zone: ";
    cin >> zoneInput;

    cin.ignore(10000, '\n');

    cout << "Enter check-in date: ";
    getline(cin, inDate);

    cout << "Enter check-out date: ";
    getline(cin, outDate);

    cout << "Enter any special notes: ";
    getline(cin, notesInput);

    InventoryItem newItem(itemInput, quantityInput, zoneInput, inDate, outDate, notesInput);
    database.push_back(newItem);

    cout << endl;

    cout << newItem.itemName << " successfully added to inventory" << endl;
}

bool searchInventory()
{
    bool searching = true;
    bool match = false;
    while (searching)
    {
        // Define variable
        string searchTerm;
        bool found = false;

        // Get search term from user input
        cout << "Search inventory" << endl;
        cout << "Enter item name to search for (case-sensitive): ";
        getline(cin, searchTerm);
        cout << endl;

        // Loop through vector elements
        for (auto iterator = database.begin(); iterator != database.end(); ++iterator)
        {
            if (iterator->itemName == searchTerm)
            {
                displayItem(*iterator);
                found = true;
                match = true;
                itemDeleteIndex = std::distance(database.begin(), iterator);
                return match;
            }
        }

        if (!found)
        {
            cout << "Item not found in inventory" << endl;
            cout << "Search Again? (Y/N): " << endl;
            char answer;
            cin >> answer;
            cin.ignore(1000, '\n');
            if (answer != 'Y' && answer != 'y')
            {
                searching = false;
                match = false;
                return match;
            }
        }
    }
    return match;
}

// This function displays in inventory item in terminal
// Parameters: InventoryItem item - the inventory item to display
// Returns: none (prints inventory item to console)
void displayItem(InventoryItem item)
{
    cout << setw(20) << left << "Item Name:" << item.itemName << endl;
    cout << setw(20) << left << "Quantity in Stock:" << item.quantityInStock << endl;
    cout << setw(20) << left << "Storage zone: " << item.storageZone << endl;
    cout << setw(20) << left << "Date in: " << item.dateIn << endl;
    cout << setw(20) << left << "Date out: " << item.dateOut << endl;
    cout << setw(20) << left << "Notes: " << item.itemNotes << endl
         << endl;
}

// This function displays in inventory item in terminal
// Parameters: InventoryItem item - the inventory item to display
// Returns: none (prints database to console)
void displayDatabase()
{
    cout << "Displaying inventory database" << endl;
    cout << "Total items in inventory: " << database.size() << endl
         << endl;
    for (auto iterator = database.begin(); iterator != database.end(); ++iterator)
    {
        displayItem(*iterator);
    }
    cout << "Enter any character to return to the main menu";
    char ch;
    cin >> ch;
    cin.ignore(10000, '\n');
}

void deleteItem(vector<InventoryItem> &inventory, int indexNumber)
{

    inventory.erase(inventory.begin() + indexNumber);
    cout << "Item successfully deleted from inventory." << endl;
}

void openFile(string fileName)
{
    // fstream dataFile(fileName, ios::out);
    fstream dataFile;
    string line;
    dataFile.open(fileName);

    if (!dataFile.is_open())
    {
        cout << "Error: could not open " << fileName << endl;
        return;
    }
    while (getline(dataFile, line))
    {
        string name, dateIn, dateOut, notes;
        int quantity, zone;

        stringstream ss(line);

        getline(ss, name, ',');
        ss >> quantity;
        ss.ignore();
        ss >> zone;
        ss.ignore();
        getline(ss, dateIn, ',');
        getline(ss, dateOut, ',');
        getline(ss, notes);

        InventoryItem newItem(name, quantity, zone, dateIn, dateOut, notes);
        database.push_back(newItem);
    }
    dataFile.close();
}

void saveFile(string fileName)
{
    // Open file
    ofstream dataFile(fileName);
    // Loop through vector elements and add each item attribute to the database
    for (auto iterator = database.begin(); iterator != database.end(); ++iterator)
    {
        dataFile << iterator->itemName << ",";
        dataFile << iterator->quantityInStock << ",";
        dataFile << iterator->storageZone << ",";
        dataFile << iterator->dateIn << ",";
        dataFile << iterator->dateOut << ",";
        dataFile << iterator->itemNotes << endl;
    }
}