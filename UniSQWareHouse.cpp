/*
    CSC5720 Programming Algorithms
    University of Southern Queensland
    Trimester 1, 2026

    Student: Brett Jenaway
    Student No: W0104215

    Assignment 3 - Report
    UniSQWareHouse Inventory Management System
*/

#include <iostream>  // STL library for console output and input
#include <string>    // STL library for strings
#include <algorithm> // STL library for sort function and swap function
#include <list>      // STL library for list to store items
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

    void setQuantityInStock(int quantity)
    {
        if (quantity >= 0)
        {
            quantityInStock = quantity;
        }
        else
        {
            cout << "Invalid quantity" << endl;
        }
    }
};

// Prototypes
InventoryItem addInventoryItem();

// Main function
int main()
{
    InventoryItem newItem = addInventoryItem();
    cout << endl;
    cout << "Item added to inventory:" << endl;
    cout << "Item name: " << newItem.itemName << endl;
    cout << "Quantity in stock: " << newItem.quantityInStock << endl;
    cout << "Storage zone: " << newItem.storageZone << endl;
    cout << "Date in: " << newItem.dateIn << endl;
    cout << "Date out: " << newItem.dateOut << endl;
    cout << "Notes: " << newItem.itemNotes << endl;
}

InventoryItem addInventoryItem()
{
    string itemInput;
    int quantityInput;
    int zoneInput;
    string inDate;
    string outDate;
    string notesInput;

    cout << "Add new item to inventory" << endl;
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

    return newItem;
}