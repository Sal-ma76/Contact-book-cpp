#include "contactbook.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>

//for case-insensitive comparison
bool iequals(const std::string& a, const std::string& b) {
    return std::equal(a.begin(), a.end(), b.begin(),
        [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}

// Add a new contact (avoid duplicates)
void ContactBook::addContact(const Contact& contact) {
    if (std::find(contacts.begin(), contacts.end(), contact) == contacts.end()) {
        contacts.push_back(contact);
    } else {
        std::cout << "Contact already exists.\n";
    }
}

// Delete contact by last name (case-insensitive)
bool ContactBook::deleteContact(const std::string& lastName) {
    auto it = std::remove_if(contacts.begin(), contacts.end(),
        [&](const Contact& c) { return iequals(c.getLastName(), lastName); });

    bool deleted = (it != contacts.end());
    contacts.erase(it, contacts.end());
    return deleted;
}

// Update contact information
bool ContactBook::updateContact(const std::string& lastName, const Contact& updated) {
    for (auto& c : contacts) {
        if (iequals(c.getLastName(), lastName)) {
            c = updated;
            return true;
        }
    }
    return false;
}

// Search by last name (case-insensitive)
std::vector<Contact> ContactBook::searchByLastName(const std::string& lastName) const {
    std::vector<Contact> results;
    for (const auto& c : contacts) {
        if (iequals(c.getLastName(), lastName)) {
            results.push_back(c);
        }
    }
    return results;
}

std::vector<Contact> ContactBook::searchByClassification(ContactClassification type) const {
    std::vector<Contact> results;
    for (const auto& c : contacts) {
        if (c.getClassification() == type) {
            results.push_back(c);
        }
    }
    return results;
}

std::vector<Contact> ContactBook::getFavorites() const {
    std::vector<Contact> results;
    for (const auto& c : contacts) {
        if (c.getIsFavorite()) {
            results.push_back(c);
        }
    }
    return results;
}

// Save to text file (not binary)
bool ContactBook::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& c : contacts) {
        file << c.toString() << "\n";
    }
    return true;
}

// Load from text file (with parsing)
bool ContactBook::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    contacts.clear();
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string firstName, lastName, phone, email, addrStr, classificationStr, favStr;

        std::getline(iss, firstName, '|');
        std::getline(iss, lastName, '|');
        std::getline(iss, phone, '|');
        std::getline(iss, email, '|');
        std::getline(iss, addrStr, '|');
        std::getline(iss, classificationStr, '|');
        std::getline(iss, favStr);

        std::istringstream addrStream(addrStr);
        std::string street, city, state, zip, country;
        std::getline(addrStream, street, ',');
        std::getline(addrStream, city, ',');
        std::getline(addrStream, state, ',');
        std::getline(addrStream, zip, ',');
        std::getline(addrStream, country);

        // Trim
        auto trim = [](std::string& s) {
            s.erase(0, s.find_first_not_of(" \t\r\n"));
            s.erase(s.find_last_not_of(" \t\r\n") + 1);
        };

        trim(street); trim(city); trim(state); trim(zip); trim(country);

        Address addr(street, city, state, zip, country);
        ContactClassification cc = stringToClassification(classificationStr);
        bool fav = (favStr == "1");

        Contact c(firstName, lastName, phone, email, addr, cc, fav);
        contacts.push_back(c);
    }

    return true;
}

// Export contact as .vcf (vCard format)
bool ContactBook::shareContact(const std::string& lastName, const std::string& exportFile) const {
    auto results = searchByLastName(lastName);
    if (results.empty()) return false;

    std::ofstream vcf(exportFile);
    if (!vcf) return false;

    const auto& c = results[0];  // Only exports the first match
    vcf << "BEGIN:VCARD\n"
        << "VERSION:3.0\n"
        << "FN:" << c.getFullName() << "\n"
        << "TEL:" << c.getPhoneNumber() << "\n"
        << "EMAIL:" << c.getEmail() << "\n"
        << "END:VCARD\n";

    return true;
}

void ContactBook::reverseOrder() {
    std::reverse(contacts.begin(), contacts.end());
}

void ContactBook::printAll() const {
    for (const auto& c : contacts) {
        c.printDetailed();
        std::cout << "-----------------\n";
    }
}

void ContactBook::printFavorites() const {
    auto favs = getFavorites();
    for (const auto& c : favs) {
        c.printSummary();
    }
}
