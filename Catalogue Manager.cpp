#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Base class for all types of library resources
class Resource {
protected:
    string title;
    string author;
    string ISBN;
    string type;

public:
    // Constructor to initialize resource attributes
    Resource(string title, string author, string ISBN, string type) {
        this->title = title;
        this->author = author;
        this->ISBN = ISBN;
        this->type = type;
    }

    // Accessor methods to retrieve resource details
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getISBN() { return ISBN; }
    string getType() { return type; }

    // Method to print the details of a resource
    virtual void printDetails() {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN << ", Type: " << type << endl;
    }

    // Virtual destructor for the base class
    virtual ~Resource() {}
};

// Derived class for book resources
class Books : public Resource {
public:
    Books(string title, string author, string ISBN) : Resource(title, author, ISBN, "Book") {}
};

// Derived class for journal resources
class Journal : public Resource {
public:
    Journal(string title, string author, string ISBN) : Resource(title, author, ISBN, "Journal") {}
};

// Derived class for digital resources
class Digital : public Resource {
public:
    Digital(string title, string author, string ISBN) : Resource(title, author, ISBN, "Digital") {}
};

// Catalog class that manages a collection of resources
class Catalog {
private:
    vector<Resource*> resources; // Stores all resources

public:
    // Add a resource to the catalog
    void addResource(Resource* resource) {
        resources.push_back(resource);
    }

    // Remove a resource by ISBN
    void removeResource(string ISBN) {
        for (auto it = resources.begin(); it != resources.end(); ++it) {
            if ((*it)->getISBN() == ISBN) {
                delete *it;                  // Delete resource from memory
                resources.erase(it);         // Remove resource from vector
                cout << "Resource removed successfully.\n\n";
                return;
            }
        }
        cout << "Resource not found.\n\n";
    }

    // Search for resources by title, author, or ISBN
    void searchResources(string& query, char& criteria) {
        bool found = false;
        for (const auto& resource : resources) {
            // Check based on specified criteria
            if ((criteria == 'T' && resource->getTitle() == query) ||
                (criteria == 'A' && resource->getAuthor() == query) ||
                (criteria == 'I' && resource->getISBN() == query)) {
                cout << "Resource found:\n";
                resource->printDetails();
                cout << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No matching resource found.\n\n";
        }
    }

    // Generate a report grouping resources by type
    void generateReport() {
        map<string, vector<Resource*>> groupedResources;

        // Group resources by type
        for (auto& resource : resources) {
            groupedResources[resource->getType()].push_back(resource);
        }

        // Display each group with details of resources
        for (auto& pair : groupedResources) {
            cout << pair.first << ":\n";
            for (auto& resource : pair.second) {
                resource->printDetails();
            }
            cout << endl;
        }
    }

    // Destructor to clean up dynamically allocated resources
    ~Catalog() {
        for (auto& resource : resources) {
            delete resource;
        }
    }
};

// Main function to interact with the catalog
int main() {
    Catalog catalog;
    int option;
    string title, author, ISBN, query;
    char resource, criteria;
    bool menu = true;
    
    while (menu) {
        cout << "Welcome to the Richfield Library!\n";
        cout << "Choose an option:\n";
        cout << "1. Add a new resource\n";
        cout << "2. Remove a resource\n";
        cout << "3. Search for a resource\n";
        cout << "4. Generate a report of all resources\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore();  // Clear newline character from input buffer

        switch (option) {
            case 1:
                // Adding a new resource
                cout << "Enter the resource title: ";
                getline(cin, title);
                cout << "Enter the author's name: ";
                getline(cin, author);
                cout << "Enter the ISBN: ";
                getline(cin, ISBN);
                cout << "Resource type - Book (B), Journal (J), or Digital (D): ";
                cin >> resource;
                
                // Add based on type input
                if (resource == 'B') {
                    catalog.addResource(new Books(title, author, ISBN));
                    cout << "Book added successfully.\n";
                } else if (resource == 'J') {
                    catalog.addResource(new Journal(title, author, ISBN));
                    cout << "Journal added successfully.\n";
                } else if (resource == 'D') {
                    catalog.addResource(new Digital(title, author, ISBN));
                    cout << "Digital resource added successfully.\n";
                } else {
                    cout << "Invalid resource type selected.\n";
                }
                break;

            case 2:
                // Remove a resource by ISBN
                cout << "Enter ISBN to remove the resource: ";
                cin >> ISBN;
                catalog.removeResource(ISBN);
                break;

            case 3:
                // Search for a resource by title, author, or ISBN
                cout << "Search by Title (T), Author (A), or ISBN (I): ";
                cin >> criteria;
                cin.ignore();  // Clear newline character from input buffer
                cout << "Enter search query: ";
                getline(cin, query);
                catalog.searchResources(query, criteria);
                break;

            case 4:
                // Generate a report of all resources
                cout << "\nCatalog Report:\n";
                catalog.generateReport();
                break;

            case 5:
                // Exit the menu loop
                menu = false;
                break;

            default:
                cout << "Invalid option selected.\n";
                break;
        }
    }
    return 0;
}
