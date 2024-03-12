#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// class and member functions declaration
class Contact {
private:
    string name;
    string phoneNumber;

public:
    void inputContact();
    void displayContact() const;
    const string& getName() const { return name; }
    void updateContact(const string& new_name, const string& new_phone);
    
    friend istream& operator>>(istream& in, Contact& contact) {
        getline(in, contact.name, ',');
        getline(in, contact.phoneNumber);
        return in;
    }

    const string& getPhoneNumber() const { return phoneNumber; }
};

class ContactManager {
private:
    string filename;

public:
    ContactManager(const string& file) : filename(file) {}
    void displayMenu();
    void addContact();
    void displayAllContacts();
    void searchByName();
    void deleteContact();
    void updateContactByName();
};

/* Contact member functions */

void Contact::inputContact() {
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Phone Number: ";
    getline(cin, phoneNumber);
}

void Contact::displayContact() const {
    cout << "Name: " << name << endl;
    cout << "Phone Number: " << phoneNumber << endl;
}

/* void Contact::updateContact(const string& newName,const string& new_phone) {
    if (name == newName) {
        cout << "Enter New Phone Number: ";
        cin.ignore(); // Clear buffer
        getline(cin, phoneNumber);
    }else{
        cout<<"Enter the name: ";
        cin.ignore();
        getline(cin,name);

        cout << "Enter New Phone Number: ";
        cin.ignore(); // Clear buffer
        getline(cin, phoneNumber);
    }
} */

void Contact::updateContact(const string& new_name, const string& new_phone) {
    name = new_name;
    phoneNumber = new_phone;
}

/* Contact Manager member functions */

void ContactManager::displayMenu() {
    int choice;

    do {
        system("cls"); // Clear screen
        cout << "\n\t\tContact Management System\n";
        cout << "\t\t------------------------\n";
        cout << "\t\t1. Add Contact\n";
        cout << "\t\t2. Update Contact\n";
        cout << "\t\t3. Delete Contact\n";
        cout << "\t\t4. Search\n";
        cout << "\t\t5. Display All Contacts\n";
        cout << "\t\t6. Exit\n";
        cout << "\t\t------------------------\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                updateContactByName();
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                searchByName();
                break;
            case 5:
                displayAllContacts();
                break;
            case 6:
                cout << "\t\tExiting program.\n";
                break;
            default:
                cout << "\t\tInvalid choice. Please try again.\n";
        }

        cout << "\t\tPress Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 5);
}

void ContactManager::addContact() {
    vector<Contact> contacts;
    Contact newContact;

    // Read existing contacts into the vector
    ifstream fileIn(filename);
    while (fileIn >> newContact) {
        contacts.push_back(newContact);
    }
    fileIn.close();

    // Input the new contact
    newContact.inputContact();

    // Add the new contact to the vector in the right sorted place
    auto it = lower_bound(contacts.begin(), contacts.end(), newContact, [](const Contact& a, const Contact& b) {
        return a.getName() < b.getName();
    });
    contacts.insert(it, newContact);

    // Write the sorted contacts back to the CSV file
    ofstream fileOut(filename);
    for (const auto& contact : contacts) {
        fileOut << contact.getName() << "," << contact.getPhoneNumber() << "\n";
    }
    fileOut.close();
}

void ContactManager::displayAllContacts() {
    ifstream file(filename);
    Contact contact;

    while (file >> contact) {
        contact.displayContact();
        cout << "---------------------\n";
    }

    file.close();

    // Pause to allow user to see the displayed contacts
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void ContactManager::searchByName() {
    ifstream file(filename);
    Contact contact;
    string searchName;
    bool found = false;

    cout << "Enter the name to search: ";
    cin.ignore(); // Clear buffer
    getline(cin, searchName);

    while (file >> contact) {
        if (contact.getName() == searchName) {
            contact.displayContact();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Contact not found.\n";
    }

    file.close();
}

void ContactManager::deleteContact() {
    ifstream fileIn(filename);
    ofstream fileOut("temp.csv"); // Temporary file to store non-deleted contacts
    Contact contact;
    string deleteName;
    char choice;

    cout << "Enter the name to delete: ";
    cin.ignore(); // Clear buffer
    getline(cin, deleteName);

    bool found = false;

    while (fileIn >> contact) {
        if (contact.getName() == deleteName) {
            contact.displayContact();
            found = true;
            cout << "Do you want to delete this contact? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << "Contact deleted successfully.\n";
            } else {
                fileOut << contact.getName() << "," << contact.getPhoneNumber() << "\n";
            }
        } else {
            fileOut << contact.getName() << "," << contact.getPhoneNumber() << "\n";
        }
    }

    fileIn.close();
    fileOut.close();

    if (!found) {
        cout << "Contact not found.\n";
    } else {
        remove(filename.c_str());          // Remove the original file
        rename("temp.csv", filename.c_str()); // Rename the temporary file
    }
}

void ContactManager::updateContactByName() {
    ifstream fileIn(filename);
    ofstream fileOut("temp.csv"); // Temporary file to store updated contacts
    Contact contact;
    string updateName;

    cout << "Enter the name to update: ";
    cin.ignore(); // Clear buffer
    getline(cin, updateName);

    bool found = false;

    while (fileIn >> contact) {
        if (contact.getName() == updateName) {
            string new_name, new_phone;

            cout << "Enter new name: ";
            cin >> new_name; // Update the name

            cout << "Enter new phone number: ";
            cin >> new_phone; // Update the phone number

            contact.updateContact(new_name, new_phone);
            found = true;
        }

        fileOut << contact.getName() << "," << contact.getPhoneNumber() << "\n";
    }


    fileIn.close();
    fileOut.close();

    if (!found) {
        cout << "Contact not found.\n";
    } else {
        remove(filename.c_str());          // Remove the original file
        rename("temp.csv", filename.c_str()); // Rename the temporary file
        cout << "Contact updated successfully.\n";
    }
}

int main() {
    ContactManager contactManager("contacts.csv");
    contactManager.displayMenu();

    return 0;
}