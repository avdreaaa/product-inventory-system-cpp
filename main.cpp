#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <limits>
#include <stdexcept>
using namespace std;

class Product {
public:
    int id;
    string name;
    string category;
    double price;
    int quantity;

    Product(int id, string name, const string& category, double price, int quantity)
        : id(id), name(name), category(category), price(price), quantity(quantity) {}
};

class Inventory {
private:
    vector<Product> products;
    vector<string> validCategories = {"Electronics", "Fashion", "Home & Kitchen", "Health & Beauty", "Automotive", "Sports and Outdoors", "Toys & Games", "Books & Stationary", "Pet Supplies", "Groceries & Food"};

public:
void loadProductsFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int id;
        string name;
        string category;
        double price;
        int quantity;
        while (file >> id >> name >> category >> price >> quantity) {
            products.push_back(Product(id, name, category, price, quantity));
        }
        file.close();
    }
}

void saveProductsToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& product : products) {
            file << product.id << " " << product.name << " " << product.category << " " << product.price << " " << product.quantity << endl;
        }
        file.close();
    }
}
    void createProduct(int id, string name, double price, int quantity) {
        for (const auto& product : products) {
            if (product.id == id) {
                cout << "Product with ID " << id << " already exists. Please enter a different ID." << endl;
                return;
            }
        }

        string categoryInput;

        cout << "----------------------------------------" << endl;
        cout << "   Available Categories for Products    " << endl;
        cout << "----------------------------------------" << endl;
        cout << setw(3) << "No." << setw(30) << "Category" << endl;
        cout << "----------------------------------------" << endl;
        for (size_t i = 0; i < validCategories.size(); ++i) {
            cout << setw(3) << i + 1 << setw(30) << validCategories[i] << endl;
        }
        cout << "----------------------------------------" << endl;

        cout << "Enter Product Category (choose one): ";
        cin.ignore();
        getline(cin, categoryInput);

        int index;
        try {
            index = stoi(categoryInput);
        } catch (const std::invalid_argument& e) {
            cout << "Invalid input. Please enter a valid integer." << endl;
            return;
        }

        if (index > 0 && index <= validCategories.size()) {
            products.push_back(Product(id, name, validCategories[index - 1], price, quantity));
        } else {
            cout << "Invalid category index: " << index << ". Please choose from the available categories." << endl;
            return;
        }
    }

    void updateProduct(int id, string name, double price, int quantity) {
        for (auto& product : products) {
            if (product.id == id) {
                product.name = name;
                product.price = price;
                product.quantity = quantity;
                break;
            }
        }
    }

    void viewProducts() {
        cout << left << setw(5) << "ID" << "      " << setw(20) << "Name" << setw(30) << "Category" << setw(15) << "Price" << setw(10) << "Quantity" << endl << endl;
        cout << "---------------------------------------------------------------------------------------" << endl;
        for (const auto& product : products) {
            cout << setw(5) << product.id  << "      " << setw(20) << product.name << setw(30) << product.category << setw(15) << fixed << setprecision(2) << product.price << setw(10) << product.quantity << endl;
        }
    }

    void deleteProduct(int id) {
        auto it = remove_if(products.begin(), products.end(), [id](const Product& product) { return product.id == id; });
        if (it != products.end()) {
            products.erase(it, products.end());
        } else {
            cout << "Product with ID " << id << " does not exist." << endl;
        }
    }


void searchAndFilter() {
    string searchCriteria;

    cout << "Enter Keywords to Search: ";
    cin.ignore();
    getline(cin, searchCriteria);

    transform(searchCriteria.begin(), searchCriteria.end(), searchCriteria.begin(), ::tolower);

    bool found = false;
    for (const auto& product : products) {
        string productNameLower = product.name;
        transform(productNameLower.begin(), productNameLower.end(), productNameLower.begin(), ::tolower);
        if (productNameLower.find(searchCriteria) != string::npos) {
            cout << endl;
            cout << "ID: " << product.id << " Name: " << product.name << " Category: " << product.category << " Price: " << product.price << " Quantity: " << product.quantity << endl;
            found = true;
        }
    }

        if (!found) {
            cout << "No products found matching the search criteria." << endl;
        }
    }
};

int main() {
    Inventory inventory;
    inventory.loadProductsFromFile("products.txt");

    int choice;

    while (true) {
        cout << "---------------------------------------" << endl << endl;
        cout << "  Grocery Inventory Management System" << endl << endl;
        cout << "  *********** Main Menu *************" << endl << endl;
        cout << "---------------------------------------" << endl << endl;
        cout << "1. Create Product" << endl;
        cout << "2. Update Product" << endl;
        cout << "3. View Products" << endl;
        cout << "4. Delete Product" << endl;
        cout << "5. Search and Filter" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                string name;
                double price;
                int quantity;

                cout << endl;
                cout << "Enter Product ID: ";
                cin >> id;

                cout << "Enter Product Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter Product Price: ";
                cin >> price;

                cout << "Enter Product Quantity: ";
                cin >> quantity;

                inventory.createProduct(id, name, price, quantity);
                break;
            }
            case 2: {
                int id;
                string name;
                double price;
                int quantity;

                cout << endl;
                cout << "Enter Product ID: ";
                cin >> id;

                cout << "Enter Updated Product Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter Updated Product Price: ";
                cin >> price;

                cout << "Enter Updated Product Quantity: ";
                cin >> quantity;

                inventory.updateProduct(id, name, price, quantity);
                break;
            }
            case 3: {
                inventory.viewProducts();
                cout << endl;
                break;
            }
            case 4: {
                int id;

                cout << endl;
                cout << "Enter Product ID: ";
                cin >> id;
                inventory.deleteProduct(id);
                cout << endl;
                break;
            }
            case 5: {
                inventory.searchAndFilter();
                break;
            }
            case 6: {
                inventory.saveProductsToFile("products.txt");
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}
