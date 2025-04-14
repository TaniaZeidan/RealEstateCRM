#include <iostream>
#include <string>
#include <functional>
#include <cctype>  // for isdigit()
#include "CRMSystem.h"
#include "Agent.h"
#include "Client.h"
#include "Property.h"
#include "Contract.h"

using namespace std;

//------------------------------
// Validation Helper Functions
//------------------------------

// Ensure phone is exactly 8 digits
bool validPhone8(const string &phone) {
    if (phone.size() != 8) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Basic email check: must contain '@'
bool validEmail(const string &email) {
    return email.find('@') != string::npos;
}

// Basic date check: expecting exactly "YYYY-MM-DD" (10 characters, '-' at positions 4 and 7)
bool validDate(const string &date) {
    if (date.size() != 10) return false;
    return (date[4] == '-' && date[7] == '-');
}

// Validates a date or the special keyword "empty"
// If "empty" is entered, it will later be converted to an empty string.
bool validDateOrEmptyKeyword(const string &s) {
    if (s == "empty") return true;
    return validDate(s);
}

//------------------------------
// Interactive Input Helpers
//------------------------------

// Prompt the user and validate string input using a validator function.
string getValidInputString(const string &prompt, function<bool(const string&)> validator, const string &errorMessage) {
    string input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (validator(input))
            break;
        cout << errorMessage << endl;
    }
    return input;
}

// Template helper for numeric input.
template<typename T>
T getValidInputNumber(const string &prompt) {
    T num;
    while (true) {
        cout << prompt;
        cin >> num;
        if (!cin.fail())
            break;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid numeric input. Please enter a valid number." << endl;
    }
    return num;
}

// Helper to get boolean input (only 0 or 1 allowed).
bool getValidInputBool(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && (value == 0 || value == 1))
            return (value == 1);
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter 1 for yes or 0 for no." << endl;
    }
}

//------------------------------
// Main Application
//------------------------------
int main() {
    CRMSystem system;
    int mainChoice = 0;

    while (true) {
        cout << "\n=== Real Estate CRM System ===\n"
             << "1. Manage Agents\n"
             << "2. Manage Clients\n"
             << "3. Manage Properties\n"
             << "4. Manage Contracts\n"
             << "5. Create New Contract\n"
             << "6. Exit\n"
             << "Enter choice: ";
        cin >> mainChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cerr << "Invalid input, try again.\n";
            continue;
        }

        //--------------- Manage Agents ---------------
        if (mainChoice == 1) {
            while (true) {
                cout << "\n=== Agent Menu ===\n"
                     << "1. Add Agent\n"
                     << "2. Remove Agent\n"
                     << "3. Search Agent by ID\n"
                     << "4. Modify Agent\n"
                     << "5. Display All Agents\n"
                     << "6. Return to Main Menu\n"
                     << "Enter choice: ";
                int choice;
                cin >> choice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cerr << "Invalid input, try again.\n";
                    continue;
                }
                if (choice == 1) {
                    Agent a;
                    string firstName = getValidInputString(
                        "Enter first name: ",
                        [](const string &s) { return !s.empty(); },
                        "First name cannot be empty."
                    );
                    a.setFirstName(firstName);

                    string lastName = getValidInputString(
                        "Enter last name: ",
                        [](const string &s) { return !s.empty(); },
                        "Last name cannot be empty."
                    );
                    a.setLastName(lastName);

                    string phone = getValidInputString(
                        "Enter phone (8 digits): ",
                        validPhone8,
                        "Phone must be exactly 8 numeric digits."
                    );
                    a.setPhone(phone);

                    string email = getValidInputString(
                        "Enter email: ",
                        validEmail,
                        "Invalid email format, must contain '@'."
                    );
                    a.setEmail(email);

                    string startDate = getValidInputString(
                        "Enter start date (YYYY-MM-DD): ",
                        validDate,
                        "Invalid date format, should be YYYY-MM-DD."
                    );
                    a.setStartDate(startDate);

                    // For end date, allow "empty" to clear the field.
                    string endDate = getValidInputString(
                        "Enter end date (YYYY-MM-DD or 'empty'): ",
                        validDateOrEmptyKeyword,
                        "Invalid date format, should be YYYY-MM-DD or 'empty'."
                    );
                    if (endDate == "empty")
                        endDate.clear();
                    a.setEndDate(endDate);

                    try {
                        system.addAgent(a);
                        cout << "Agent added successfully.\n";
                    }
                    catch (const exception &e) {
                        cerr << "Error: " << e.what() << "\n";
                    }
                }
                else if (choice == 2) {
                    int id = getValidInputNumber<int>("Enter agent ID to remove: ");
                    if (system.removeAgent(id))
                        cout << "Agent removed successfully.\n";
                    else
                        cout << "Agent not found.\n";
                }
                else if (choice == 3) {
                    int id = getValidInputNumber<int>("Enter agent ID to search: ");
                    try {
                        Agent a = system.searchAgentById(id);
                        cout << "Found: " << a << "\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 4) {
                    int id = getValidInputNumber<int>("Enter agent ID to modify: ");
                    try {
                        Agent existing = system.searchAgentById(id);
                        cout << "Current: " << existing << "\n";
                        string firstName = getValidInputString("New first name: ",
                            [](const string &s) { return !s.empty(); },
                            "First name cannot be empty.");
                        existing.setFirstName(firstName);
                        string lastName = getValidInputString("New last name: ",
                            [](const string &s) { return !s.empty(); },
                            "Last name cannot be empty.");
                        existing.setLastName(lastName);
                        string phone = getValidInputString("New phone (8 digits): ",
                            validPhone8,
                            "Phone must be exactly 8 numeric digits.");
                        existing.setPhone(phone);
                        string email = getValidInputString("New email: ",
                            validEmail,
                            "Invalid email format, must contain '@'.");
                        existing.setEmail(email);
                        string startDate = getValidInputString("New start date (YYYY-MM-DD): ",
                            validDate,
                            "Invalid date format, should be YYYY-MM-DD.");
                        existing.setStartDate(startDate);
                        string endDate = getValidInputString("New end date (YYYY-MM-DD or 'empty'): ",
                            validDateOrEmptyKeyword,
                            "Invalid date format, should be YYYY-MM-DD or 'empty'.");
                        if (endDate == "empty")
                            endDate.clear();
                        existing.setEndDate(endDate);
                        if (system.modifyAgent(existing))
                            cout << "Agent modified successfully.\n";
                        else
                            cout << "Modification failed.\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 5) {
                    system.displayAgents();
                }
                else if (choice == 6) {
                    break;
                }
                else {
                    cout << "Invalid choice.\n";
                }
            }
        }
        //--------------- Manage Clients ---------------
        else if (mainChoice == 2) {
            while (true) {
                cout << "\n=== Client Menu ===\n"
                     << "1. Add Client\n"
                     << "2. Remove Client\n"
                     << "3. Search Client by ID\n"
                     << "4. Modify Client\n"
                     << "5. Display All Clients\n"
                     << "6. Return to Main Menu\n"
                     << "Enter choice: ";
                int choice;
                cin >> choice;
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cerr << "Invalid input, try again.\n";
                    continue;
                }
                if (choice == 1) {
                    Client c;
                    string firstName = getValidInputString("Enter first name: ",
                        [](const string &s){ return !s.empty(); },
                        "First name cannot be empty.");
                    c.setFirstName(firstName);
                    string lastName = getValidInputString("Enter last name: ",
                        [](const string &s){ return !s.empty(); },
                        "Last name cannot be empty.");
                    c.setLastName(lastName);
                    string phone = getValidInputString("Enter phone (8 digits): ",
                        validPhone8,
                        "Phone must be exactly 8 numeric digits.");
                    c.setPhone(phone);
                    string email = getValidInputString("Enter email: ",
                        validEmail,
                        "Invalid email format, must contain '@'.");
                    c.setEmail(email);
                    bool married = getValidInputBool("Is married? (1 for yes, 0 for no): ");
                    c.setIsMarried(married);
                    double budget = getValidInputNumber<double>("Enter budget: ");
                    c.setBudget(budget);
                    string budgetType = getValidInputString("Enter budget type ('rent' or 'buy'): ",
                        [](const string &s){ return s=="rent" || s=="buy"; },
                        "Budget type must be 'rent' or 'buy'.");
                    c.setBudgetType(budgetType);
                    try {
                        system.addClient(c);
                        cout << "Client added successfully.\n";
                    }
                    catch (const exception &e) {
                        cerr << "Error: " << e.what() << "\n";
                    }
                }
                else if (choice == 2) {
                    int id = getValidInputNumber<int>("Enter client ID to remove: ");
                    if (system.removeClient(id))
                        cout << "Client removed successfully.\n";
                    else
                        cout << "Client not found.\n";
                }
                else if (choice == 3) {
                    int id = getValidInputNumber<int>("Enter client ID to search: ");
                    try {
                        Client c = system.searchClientById(id);
                        cout << "Found: " << c << "\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 4) {
                    int id = getValidInputNumber<int>("Enter client ID to modify: ");
                    try {
                        Client existing = system.searchClientById(id);
                        cout << "Current: " << existing << "\n";
                        string firstName = getValidInputString("New first name: ",
                            [](const string &s){ return !s.empty(); },
                            "First name cannot be empty.");
                        existing.setFirstName(firstName);
                        string lastName = getValidInputString("New last name: ",
                            [](const string &s){ return !s.empty(); },
                            "Last name cannot be empty.");
                        existing.setLastName(lastName);
                        string phone = getValidInputString("New phone (8 digits): ",
                            validPhone8,
                            "Phone must be exactly 8 numeric digits.");
                        existing.setPhone(phone);
                        string email = getValidInputString("New email: ",
                            validEmail,
                            "Invalid email format, must contain '@'.");
                        existing.setEmail(email);
                        bool married = getValidInputBool("Is married? (1 for yes, 0 for no): ");
                        existing.setIsMarried(married);
                        double budget = getValidInputNumber<double>("New budget: ");
                        existing.setBudget(budget);
                        string budgetType = getValidInputString("New budget type ('rent' or 'buy'): ",
                            [](const string &s){ return s=="rent" || s=="buy"; },
                            "Budget type must be 'rent' or 'buy'.");
                        existing.setBudgetType(budgetType);
                        if (system.modifyClient(existing))
                            cout << "Client modified successfully.\n";
                        else
                            cout << "Modification failed.\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 5) {
                    system.displayClients();
                }
                else if (choice == 6) {
                    break;
                }
                else {
                    cout << "Invalid choice.\n";
                }
            }
        }
        //--------------- Manage Properties ---------------
        else if (mainChoice == 3) {
            while (true) {
                cout << "\n=== Property Menu ===\n"
                     << "1. Add Property\n"
                     << "2. Remove Property\n"
                     << "3. Search Property by ID\n"
                     << "4. Modify Property\n"
                     << "5. Display All Properties\n"
                     << "6. Return to Main Menu\n"
                     << "Enter choice: ";
                int choice;
                cin >> choice;
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cerr << "Enter a number.\n";
                    continue;
                }
                if (choice == 1) {

                    //They chose to add a property
                    Property p;
                    double size = getValidInputNumber<double>("Enter size (sqm): ");
                    while(size<=0) {
                        cout << "Size must be greater than 0.\n";
                        size = getValidInputNumber<double>("Enter size (sqm): ");
                    }
                    p.setSizeSqm(size);

                    double price = getValidInputNumber<double>("Enter price: ");
                    while (price <= 0) {
                        cout << "Price must be greater than 0.\n";
                        price = getValidInputNumber<double>("Enter price: ");
                    }
                    p.setPrice(price);

                    //Did not touch it is correct. ~Jad
                    string type = getValidInputString("Enter property type ('land', 'house', or 'apartment'): ",
                                           [](const string &s){ return s=="land" || s=="house" || s=="apartment"; },
                                           "Property type must be 'land', 'house', or 'apartment'.");
                    p.setPropertyType(type);

                    //We will not allow the user to input bedrooms and bathrooms if the property is land. ~Jad
                    if (p.getPropertyType() != "land") {
                        int bedrooms = getValidInputNumber<int>("Enter number of bedrooms: ");
                        p.setBedrooms(bedrooms);
                    }else{
                        p.setBedrooms(0);
                    }

                    //We will not allow the user to input bedrooms and bathrooms if the property is land. ~Jad
                    if (p.getPropertyType() != "land") {
                        int bathrooms = getValidInputNumber<int>("Enter number of bathrooms: ");
                        p.setBathrooms(bathrooms);
                    }else{
                        p.setBathrooms(0);
                    }

                    //Did not touch it is correct ~Jad
                    string place = getValidInputString("Enter place: ",
                                           [](const string &s){ return !s.empty(); },
                                           "Place cannot be empty.");
                    p.setPlace(place);

                    //Did not touch it is correct ~Jad
                    int availInt = getValidInputNumber<int>("Is the property available? (1 for yes, 0 for no): ");
                    p.setAvailability(availInt != 0);

                    //Did not touch it is correct ~Jad
                    string listing = getValidInputString("Enter listing type ('sale' or 'rent'): ",
                                           [](const string &s){ return s=="sale" || s=="rent"; },
                                           "Listing type must be 'sale' or 'rent'.");

                    p.setListingType(listing);
                    
                    try {
                        system.addProperty(p);
                        cout << "Property added successfully.\n";
                    }
                    catch (const exception &e) {
                        cerr << "Error: " << e.what() << "\n";
                    }
                }
                else if (choice == 2) {
                    int id = getValidInputNumber<int>("Enter property ID to remove: ");
                    if (system.removeProperty(id))
                        cout << "Property removed successfully.\n";
                    else
                        cout << "Property not found.\n";
                }
                else if (choice == 3) {
                    int id = getValidInputNumber<int>("Enter property ID to search: ");
                    try {
                        Property p = system.searchPropertyById(id);
                        cout << "Found: " << p << "\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 4) {
                    int id = getValidInputNumber<int>("Enter property ID to modify: ");
                    try {
                        Property existing = system.searchPropertyById(id);
                        cout << "Current: " << existing << "\n";
                        double size = getValidInputNumber<double>("New size (sqm): ");
                        existing.setSizeSqm(size);
                        double price = getValidInputNumber<double>("New price: ");
                        existing.setPrice(price);
                        string type = getValidInputString("New property type ('land', 'house', or 'apartment'): ",
                                           [](const string &s){ return s=="land" || s=="house" || s=="apartment"; },
                                           "Property type must be 'land', 'house', or 'apartment'.");
                        existing.setPropertyType(type);
                        int bedrooms = getValidInputNumber<int>("New number of bedrooms: ");
                        existing.setBedrooms(bedrooms);
                        int bathrooms = getValidInputNumber<int>("New number of bathrooms: ");
                        existing.setBathrooms(bathrooms);
                        string place = getValidInputString("New place: ",
                                           [](const string &s){ return !s.empty(); },
                                           "Place cannot be empty.");
                        existing.setPlace(place);
                        int availInt = getValidInputNumber<int>("Is the property available? (1 for yes, 0 for no): ");
                        existing.setAvailability(availInt != 0);
                        string listing = getValidInputString("New listing type ('sale' or 'rent'): ",
                                           [](const string &s){ return s=="sale" || s=="rent"; },
                                           "Listing type must be 'sale' or 'rent'.");
                        existing.setListingType(listing);
                        if (system.modifyProperty(existing))
                            cout << "Property modified successfully.\n";
                        else
                            cout << "Modification failed.\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 5) {
                    system.displayProperties();
                }
                else if (choice == 6) {
                    break;
                }
                else {
                    cout << "Invalid choice.\n";
                }
            }
        }
        //--------------- Manage Contracts ---------------
        else if (mainChoice == 4) {
            while (true) {
                cout << "\n=== Contract Menu ===\n"
                     << "1. Add Contract\n"
                     << "2. Remove Contract\n"
                     << "3. Search Contract by ID\n"
                     << "4. Modify Contract\n"
                     << "5. Display All Contracts\n"
                     << "6. Return to Main Menu\n"
                     << "Enter choice: ";
                int choice;
                cin >> choice;
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cerr << "Invalid input, try again.\n";
                    continue;
                }
                if (choice == 1) {
                    Contract ct;
                    int propId = getValidInputNumber<int>("Enter property ID: ");
                    ct.setPropertyId(propId);
                    int clientId = getValidInputNumber<int>("Enter client ID: ");
                    ct.setClientId(clientId);
                    int agentId = getValidInputNumber<int>("Enter agent ID: ");
                    ct.setAgentId(agentId);
                    double price = getValidInputNumber<double>("Enter price: ");
                    ct.setPrice(price);
                    string sd = getValidInputString("Enter start date (YYYY-MM-DD): ",
                                                    validDate, "Invalid date format, should be YYYY-MM-DD.");
                    ct.setStartDate(sd);
                    string ed = getValidInputString("Enter end date (YYYY-MM-DD or 'empty'): ",
                                                    validDateOrEmptyKeyword, "Invalid date format, should be YYYY-MM-DD or 'empty'.");
                    if (ed == "empty")
                        ed.clear();
                    ct.setEndDate(ed);
                    string cType = getValidInputString("Enter contract type ('sale' or 'rent'): ",
                                                       [](const string &s){ return s=="sale" || s=="rent"; },
                                                       "Contract type must be 'sale' or 'rent'.");
                    ct.setContractType(cType);
                    int activeInt = getValidInputNumber<int>("Is the contract active? (1 for yes, 0 for no): ");
                    ct.setIsActive(activeInt != 0);
                    try {
                        system.addContract(ct);
                        cout << "Contract added successfully.\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 2) {
                    int id = getValidInputNumber<int>("Enter contract ID to remove: ");
                    if (system.removeContract(id))
                        cout << "Contract removed successfully.\n";
                    else
                        cout << "Contract not found.\n";
                }
                else if (choice == 3) {
                    int id = getValidInputNumber<int>("Enter contract ID to search: ");
                    try {
                        Contract c = system.searchContractById(id);
                        cout << "Found: " << c << "\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 4) {
                    int id = getValidInputNumber<int>("Enter contract ID to modify: ");
                    try {
                        Contract existing = system.searchContractById(id);
                        cout << "Current: " << existing << "\n";
                        int propId = getValidInputNumber<int>("New property ID: ");
                        existing.setPropertyId(propId);
                        int clientId = getValidInputNumber<int>("New client ID: ");
                        existing.setClientId(clientId);
                        int agentId = getValidInputNumber<int>("New agent ID: ");
                        existing.setAgentId(agentId);
                        double price = getValidInputNumber<double>("New price: ");
                        existing.setPrice(price);
                        string sd = getValidInputString("New start date (YYYY-MM-DD): ",
                                                       validDate, "Invalid date format, should be YYYY-MM-DD.");
                        existing.setStartDate(sd);
                        string ed = getValidInputString("New end date (YYYY-MM-DD or 'empty'): ",
                                                       validDateOrEmptyKeyword, "Invalid date format, should be YYYY-MM-DD or 'empty'.");
                        if (ed == "empty")
                            ed.clear();
                        existing.setEndDate(ed);
                        string cType = getValidInputString("New contract type ('sale' or 'rent'): ",
                                                           [](const string &s){ return s=="sale" || s=="rent"; },
                                                           "Contract type must be 'sale' or 'rent'.");
                        existing.setContractType(cType);
                        int activeInt = getValidInputNumber<int>("Is the contract active? (1 for yes, 0 for no): ");
                        existing.setIsActive(activeInt != 0);
                        if (system.modifyContract(existing))
                            cout << "Contract modified successfully.\n";
                        else
                            cout << "Modification failed.\n";
                    }
                    catch (const exception &e) {
                        cerr << e.what() << "\n";
                    }
                }
                else if (choice == 5) {
                    system.displayContracts();
                }
                else if (choice == 6) {
                    break;
                }
                else {
                    cout << "Invalid choice.\n";
                }
            }
        }
        //--------------- Create Contract from Existing Records ---------------
        else if (mainChoice == 5) {
            int propId = getValidInputNumber<int>("Enter property ID: ");
            int clientId = getValidInputNumber<int>("Enter client ID: ");
            int agentId = getValidInputNumber<int>("Enter agent ID: ");
            double price = getValidInputNumber<double>("Enter price: ");
            string sd = getValidInputString("Enter start date (YYYY-MM-DD): ",
                                            validDate, "Invalid date format, should be YYYY-MM-DD.");
            string ed = getValidInputString("Enter end date (YYYY-MM-DD or 'empty'): ",
                                            validDateOrEmptyKeyword, "Invalid date format, should be YYYY-MM-DD or 'empty'.");
            if (ed == "empty")
                ed.clear();
            string cType = getValidInputString("Enter contract type ('sale' or 'rent'): ",
                                               [](const string &s){ return s=="sale" || s=="rent"; },
                                               "Contract type must be 'sale' or 'rent'.");
            int activeInt = getValidInputNumber<int>("Is the contract active? (1 for yes, 0 for no): ");
            try {
                system.createContract(-1, propId, clientId, agentId, price, sd, ed, cType, activeInt != 0);
                cout << "Contract created successfully.\n";
            }
            catch (const exception &e) {
                cerr << "Error: " << e.what() << "\n";
            }
        }
        else if (mainChoice == 6) {
            cout << "Exiting. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}
