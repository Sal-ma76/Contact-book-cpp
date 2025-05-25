#include <iostream>
#include <limits>
#include <regex>
#include "contactbook.h"

void displayMenu() {
    std::cout << "\n=== Contact Book ===\n"
              << "1. Add Contact\n"
              << "2. Search by Last Name\n"
              << "3. Search by Type\n"
              << "4. Print All\n"
              << "5. Print Favorites\n"
              << "6. Save to File\n"
              << "7. Load from File\n"
              << "8. Delete Contact\n"
              << "9. Update Contact\n"
              << "10. Share Contact\n"
              << "11. Reverse Order\n"
              << "12. Exit\n"
              << "Choose: ";
}

std::string inputLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

// email validation with regex
bool isValidEmail(const std::string& email) {
    const std::regex pattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return std::regex_match(email, pattern);
}

// phone validation: digits, spaces, +, -, parentheses, length 7-15
bool isValidPhoneNumber(const std::string& phone) {
    const std::regex pattern(R"(^[\d\s+\-\(\)]{7,15}$)");
    return std::regex_match(phone, pattern);
}

// Convert string to classification enum
ContactClassification readClassification() {
    std::string input = inputLine("Enter classification (Friend, Family, Work, Other): ");
    return stringToClassification(input);
}

std::string readPhoneNumber() {
    while (true) {
        std::string phone = inputLine("Phone number: ");
        if (isValidPhoneNumber(phone)) {
            return phone;
        }
        std::cout << "Invalid phone number format. Try again.\n";
    }
}

std::string readEmail() {
    while (true) {
        std::string email = inputLine("Email: ");
        if (isValidEmail(email)) {
            return email;
        }
        std::cout << "Invalid email format. Try again.\n";
    }
}

void addContact(ContactBook& book) {
    std::string firstName = inputLine("First name: ");
    std::string lastName = inputLine("Last name: ");
    std::string phone = readPhoneNumber();
    std::string email = readEmail();

    std::string street = inputLine("Street: ");
    std::string city = inputLine("City: ");
    std::string state = inputLine("State: ");
    std::string zip = inputLine("Zip Code: ");
    std::string country = inputLine("Country: ");
    Address address(street, city, state, zip, country);

    ContactClassification classification = readClassification();

    std::string favStr = inputLine("Mark as favorite? (y/n): ");
    bool isFavorite = (favStr == "y" || favStr == "Y");

    Contact contact(firstName, lastName, phone, email, address, classification, isFavorite);
    book.addContact(contact);
    std::cout << "Contact added.\n";
}

void searchByLastName(const ContactBook& book) {
    std::string lastName = inputLine("Enter last name to search: ");
    auto results = book.searchByLastName(lastName);
    if (results.empty()) {
        std::cout << "No contacts found.\n";
    } else {
        for (const auto& c : results) {
            c.printDetailed();
            std::cout << "-----------------\n";
        }
    }
}

// Search by classification
void searchByType(const ContactBook& book) {
    ContactClassification classification = readClassification();
    auto results = book.searchByClassification(classification);
    if (results.empty()) {
        std::cout << "No contacts found.\n";
    } else {
        for (const auto& c : results) {
            c.printDetailed();
            std::cout << "-----------------\n";
        }
    }
}

void deleteContact(ContactBook& book) {
    std::string lastName = inputLine("Enter last name of contact to delete: ");
    if (book.deleteContact(lastName)) {
        std::cout << "Contact(s) deleted.\n";
    } else {
        std::cout << "No matching contact found.\n";
    }
}

void updateContact(ContactBook& book) {
    std::string lastName = inputLine("Enter last name of contact to update: ");
    auto results = book.searchByLastName(lastName);
    if (results.empty()) {
        std::cout << "No matching contact found.\n";
        return;
    }

    std::cout << "Updating first matching contact:\n";
    results[0].printDetailed();

    // Collect new info, keep old = blank
    std::string phone, email;
    while (true) {
        phone = inputLine("New phone number (leave blank to keep current): ");
        if (phone.empty() || isValidPhoneNumber(phone)) break;
        std::cout << "Invalid phone number format. Try again.\n";
    }
    while (true) {
        email = inputLine("New email (leave blank to keep current): ");
        if (email.empty() || isValidEmail(email)) break;
        std::cout << "Invalid email format. Try again.\n";
    }

    std::string street = inputLine("New street (leave blank to keep current): ");
    std::string city = inputLine("New city (leave blank to keep current): ");
    std::string state = inputLine("New state (leave blank to keep current): ");
    std::string zip = inputLine("New zip code (leave blank to keep current): ");
    std::string country = inputLine("New country (leave blank to keep current): ");
    std::string classStr = inputLine("New classification (Friend, Family, Work, Other, leave blank to keep current): ");
    std::string favStr = inputLine("Mark as favorite? (y/n/leave blank to keep current): ");

    Contact updated = results[0];

    if (!phone.empty()) updated.setPhoneNumber(phone);
    if (!email.empty()) updated.setEmail(email);
    if (!street.empty()) updated.address.street = street;
    if (!city.empty()) updated.address.city = city;
    if (!state.empty()) updated.address.state = state;
    if (!zip.empty()) updated.address.zipCode = zip;
    if (!country.empty()) updated.address.country = country;
    if (!classStr.empty()) updated.setClassification(stringToClassification(classStr));
    if (!favStr.empty()) updated.setIsFavorite(favStr == "y" || favStr == "Y");

    if (book.updateContact(lastName, updated)) {
        std::cout << "Contact updated.\n";
    } else {
        std::cout << "Failed to update contact.\n";
    }
}

// Share contact (export to vcf)
void shareContact(const ContactBook& book) {
    std::string lastName = inputLine("Enter last name of contact to share: ");
    std::string exportFile = inputLine("Enter filename to export VCF: ");

    if (book.shareContact(lastName, exportFile)) {
        std::cout << "Contact exported to " << exportFile << "\n";
    } else {
        std::cout << "Failed to export contact.\n";
    }
}

int main() {
    ContactBook book;
    if (!book.loadFromFile()) {
        std::cout << "No existing contacts found, starting fresh.\n";
    }

    while (true) {
        displayMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: addContact(book); break;
            case 2: searchByLastName(book); break;
            case 3: searchByType(book); break;
            case 4: book.printAll(); break;
            case 5: book.printFavorites(); break;
            case 6:
                if (book.saveToFile())
                    std::cout << "Contacts saved successfully.\n";
                else
                    std::cout << "Failed to save contacts.\n";
                break;
            case 7:
                if (book.loadFromFile())
                    std::cout << "Contacts loaded successfully.\n";
                else
                    std::cout << "Failed to load contacts.\n";
                break;
            case 8: deleteContact(book); break;
            case 9: updateContact(book); break;
            case 10: shareContact(book); break;
            case 11:
                book.reverseOrder();
                std::cout << "Contacts order reversed.\n";
                break;
            case 12:
                book.saveToFile();
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice, please try again.\n";
                break;
        }
    }

    return 0;
}
