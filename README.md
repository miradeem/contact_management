A simple contact management system implemented in C++. It allows users to add, update, delete, and search for contacts stored in a CSV file. The system is structured around two main classes: `Contact` and `ContactManager`. 

### `Contact` Class

- **Purpose**: Represents a single contact with a name and phone number.
- **Members**:
 - `name`: The contact's name.
 - `phoneNumber`: The contact's phone number.
- **Methods**:
 - `inputContact()`: Allows the user to input a new contact's name and phone number.
 - `displayContact()`: Displays the contact's name and phone number.
 - `updateContact(const string& new_name, const string& new_phone)`: Updates the contact's name and phone number.
 - `getName()`: Returns the contact's name.
 - `getPhoneNumber()`: Returns the contact's phone number.
 - `operator>>`: Overloads the extraction operator to read a contact from a stream.

### `ContactManager` Class

- **Purpose**: Manages a collection of contacts, including adding, updating, deleting, and searching for contacts.
- **Members**:
 - `filename`: The name of the file where contacts are stored.
- **Methods**:
 - `displayMenu()`: Displays a menu of options to the user.
 - `addContact()`: Adds a new contact to the file.
 - `displayAllContacts()`: Displays all contacts in the file.
 - `searchByName()`: Searches for a contact by name.
 - `deleteContact()`: Deletes a contact by name.
 - `updateContactByName()`: Updates a contact's information by name.

### Key Points

- **File Handling**: The system uses file I/O operations to read from and write to a CSV file. This is done using `ifstream` for reading and `ofstream` for writing.
- **Sorting**: When adding a new contact, the system ensures that the contacts are sorted alphabetically by name. This is achieved by using `lower_bound` to find the correct position to insert the new contact.
- **Temporary File**: For operations that modify the contact list (add, delete, update), a temporary file is used. This is a common technique to avoid data loss in case of errors during the operation.
- **User Interaction**: The system provides a simple text-based menu for user interaction.
