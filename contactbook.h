#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include "contact.h"
#include <vector>
#include <string>

class ContactBook {
private:
    std::vector<Contact> contacts;
    std::string filename = "contacts.txt";

public:
    void addContact(const Contact& contact);
    bool deleteContact(const std::string& lastName);
    bool updateContact(const std::string& lastName, const Contact& updated);

    std::vector<Contact> searchByLastName(const std::string& lastName) const;
    std::vector<Contact> searchByClassification(ContactClassification type) const;
    std::vector<Contact> getFavorites() const;

    bool saveToFile() const;
    bool loadFromFile();
    bool shareContact(const std::string& lastName, const std::string& exportFile) const;

    void printAll() const;
    void printFavorites() const;
    void reverseOrder();
    int count() const { return contacts.size(); }
};

#endif // CONTACTBOOK_H
