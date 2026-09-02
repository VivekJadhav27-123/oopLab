#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

class Medicine {
public:
    int id;
    std::string name;
    std::string company;
    int quantity;
    double price;

    Medicine(int id, std::string name, std::string company, int quantity, double price)
        : id(id), name(name), company(company), quantity(quantity), price(price) {}
};

class PharmacyManager {
private:
    std::vector<Medicine> inventory;
    const std::string filename = "pharmacy_inventory.txt";

    void saveToFile() {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error opening file for saving!\n";
            return;
        }
        for (const auto& med : inventory) {
            outFile << med.id << "," << med.name << "," << med.company << "," 
                    << med.quantity << "," << med.price << "\n";
        }
        outFile.close();
    }

    void loadFromFile() {
        std::ifstream inFile(filename);
        if (!inFile) return;

        inventory.clear();
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            size_t pos = 0;
            std::vector<std::string> tokens;
            while ((pos = line.find(',')) != std::string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() == 5) {
                int id = std::stoi(tokens[0]);
                std::string name = tokens[1];
                std::string company = tokens[2];
                int qty = std::stoi(tokens[3]);
                double price = std::stod(tokens[4]);
                inventory.emplace_back(id, name, company, qty, price);
            }
        }
        inFile.close();
    }

public:
    PharmacyManager() {
        loadFromFile();
    }

    void addMedicine() {
        int id, qty;
        std::string name, company;
        double price;

        std::cout << "\n--- Add New Medicine ---\n";
        std::cout << "Enter Medicine ID: ";
        std::cin >> id;

        for (const auto& med : inventory) {
            if (med.id == id) {
                std::cout << "Error: Medicine with ID " << id << " already exists!\n";
                return;
            }
        }

        std::cin.ignore();
        std::cout << "Enter Medicine Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Manufacturer / Company: ";
        std::getline(std::cin, company);
        std::cout << "Enter Quantity: ";
        std::cin >> qty;
        std::cout << "Enter Unit Price (INR): ";
        std::cin >> price;

        inventory.emplace_back(id, name, company, qty, price);
        saveToFile();
        std::cout << "Medicine added successfully!\n";
    }

    void displayInventory() const {
        std::cout << "\n" << std::string(75, '=') << "\n";
        std::cout << std::left << std::setw(8) << "ID"
                  << std::setw(22) << "Name"
                  << std::setw(20) << "Company"
                  << std::setw(12) << "Quantity"
                  << std::setw(10) << "Price" << "\n";
        std::cout << std::string(75, '=') << "\n";

        if (inventory.empty()) {
            std::cout << "No medicines available in the inventory.\n";
        } else {
            for (const auto& med : inventory) {
                std::cout << std::left << std::setw(8) << med.id
                          << std::setw(22) << med.name
                          << std::setw(20) << med.company
                          << std::setw(12) << med.quantity
                          << std::fixed << std::setprecision(2) << med.price << "\n";
            }
        }
        std::cout << std::string(75, '=') << "\n";
    }

    void searchMedicine() const {
        int choice;
        std::cout << "\nSearch by:\n1. ID\n2. Name\nEnter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int id;
            std::cout << "Enter Medicine ID: ";
            std::cin >> id;
            for (const auto& med : inventory) {
                if (med.id == id) {
                    std::cout << "\nMedicine Found:\n";
                    std::cout << "ID: " << med.id << "\nName: " << med.name
                              << "\nCompany: " << med.company << "\nStock: " << med.quantity
                              << "\nPrice: " << med.price << "\n";
                    return;
                }
            }
            std::cout << "Medicine with ID " << id << " not found.\n";
        } else if (choice == 2) {
            std::string name;
            std::cin.ignore();
            std::cout << "Enter Medicine Name: ";
            std::getline(std::cin, name);
            bool found = false;
            for (const auto& med : inventory) {
                if (med.name.find(name) != std::string::npos) {
                    std::cout << "\nID: " << med.id << " | Name: " << med.name 
                              << " | Stock: " << med.quantity << " | Price: " << med.price << "\n";
                    found = true;
                }
            }
            if (!found) {
                std::cout << "No medicine found matching '" << name << "'.\n";
            }
        } else {
            std::cout << "Invalid search option.\n";
        }
    }

    void updateStock() {
        int id, additionalQty;
        std::cout << "\nEnter Medicine ID to update stock: ";
        std::cin >> id;

        for (auto& med : inventory) {
            if (med.id == id) {
                std::cout << "Current Quantity: " << med.quantity << "\n";
                std::cout << "Enter quantity to add (or negative to reduce): ";
                std::cin >> additionalQty;

                if (med.quantity + additionalQty < 0) {
                    std::cout << "Error: Resulting quantity cannot be negative.\n";
                    return;
                }

                med.quantity += additionalQty;
                saveToFile();
                std::cout << "Stock updated successfully. New Quantity: " << med.quantity << "\n";
                return;
            }
        }
        std::cout << "Medicine not found.\n";
    }

    void generateBill() {
        std::string customerName;
        std::cin.ignore();
        std::cout << "\nEnter Customer Name: ";
        std::getline(std::cin, customerName);

        struct BillItem {
            std::string name;
            int qty;
            double unitPrice;
            double total;
        };

        std::vector<BillItem> billItems;
        char addMore = 'y';

        while (addMore == 'y' || addMore == 'Y') {
            int id, reqQty;
            std::cout << "Enter Medicine ID to purchase: ";
            std::cin >> id;

            bool found = false;
            for (auto& med : inventory) {
                if (med.id == id) {
                    found = true;
                    std::cout << "Medicine: " << med.name << " (Available: " << med.quantity << ")\n";
                    std::cout << "Enter quantity needed: ";
                    std::cin >> reqQty;

                    if (reqQty <= 0) {
                        std::cout << "Invalid quantity.\n";
                    } else if (reqQty > med.quantity) {
                        std::cout << "Insufficient stock available!\n";
                    } else {
                        med.quantity -= reqQty;
                        billItems.push_back({med.name, reqQty, med.price, reqQty * med.price});
                        std::cout << "Item added to bill.\n";
                    }
                    break;
                }
            }

            if (!found) {
                std::cout << "Medicine ID not found.\n";
            }

            std::cout << "Add another item? (y/n): ";
            std::cin >> addMore;
        }

        if (billItems.empty()) {
            std::cout << "No items purchased. Bill cancelled.\n";
            return;
        }

        saveToFile();

        // Print Invoice
        double subtotal = 0.0;
        double gstRate = 0.12; // 12% GST standard on medicines

        std::cout << "\n============================================================\n";
        std::cout << "                    PHARMACY INVOICE                        \n";
        std::cout << "============================================================\n";
        std::cout << "Customer: " << customerName << "\n";
        std::cout << "------------------------------------------------------------\n";
        std::cout << std::left << std::setw(24) << "Item"
                  << std::setw(10) << "Qty"
                  << std::setw(14) << "Unit Price"
                  << std::setw(12) << "Total" << "\n";
        std::cout << "------------------------------------------------------------\n";

        for (const auto& item : billItems) {
            std::cout << std::left << std::setw(24) << item.name
                      << std::setw(10) << item.qty
                      << std::setw(14) << std::fixed << std::setprecision(2) << item.unitPrice
                      << std::setw(12) << item.total << "\n";
            subtotal += item.total;
        }

        double tax = subtotal * gstRate;
        double grandTotal = subtotal + tax;

        std::cout << "------------------------------------------------------------\n";
        std::cout << std::right << std::setw(48) << "Subtotal: " << std::fixed << std::setprecision(2) << subtotal << "\n";
        std::cout << std::right << std::setw(48) << "GST (12%): " << tax << "\n";
        std::cout << std::right << std::setw(48) << "Grand Total: " << grandTotal << "\n";
        std::cout << "============================================================\n";
        std::cout << "Thank you for your purchase!\n\n";
    }
};

int main() {
    PharmacyManager system;
    int choice;

    do {
        std::cout << "\n=========================================\n";
        std::cout << "       PHARMACY MANAGEMENT SYSTEM        \n";
        std::cout << "=========================================\n";
        std::cout << "1. Display All Inventory\n";
        std::cout << "2. Add New Medicine\n";
        std::cout << "3. Search Medicine\n";
        std::cout << "4. Update Stock Quantity\n";
        std::cout << "5. Generate Bill / Point of Sale\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice (1-6): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.displayInventory();
                break;
            case 2:
                system.addMedicine();
                break;
            case 3:
                system.searchMedicine();
                break;
            case 4:
                system.updateStock();
                break;
            case 5:
                system.generateBill();
                break;
            case 6:
                std::cout << "Exiting system. Have a great day!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}