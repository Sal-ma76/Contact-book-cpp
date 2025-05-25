#include "contact.h"

Contact::Contact(const std::string& firstName, const std::string& lastName)
    : firstName(firstName), lastName(lastName), phoneNumber(""), email(""), address(),
      classification(ContactClassification::OTHER), isFavorite(false) {
    if (firstName.empty() || lastName.empty()) {
        std::cerr << "Please provide a valid name.\n";
    }
}

Contact::Contact(const std::string& firstName, const std::string& lastName,
                 const std::string& phoneNumber, const std::string& email,
                 const Address& address, ContactClassification classification,
                 bool isFavorite)
    : firstName(firstName), lastName(lastName), phoneNumber(phoneNumber), email(email),
      address(address), classification(classification), isFavorite(isFavorite) {}

std::string Contact::getClassificationString() const {
    switch (classification) {
        case ContactClassification::FRIEND: return "Friend";
        case ContactClassification::WORK: return "Work";
        case ContactClassification::FAMILY: return "Family";
        default: return "Other";
    }
}

std::string Contact::toString() const {
    return firstName + "|" + lastName + "|" + phoneNumber + "|" + email + "|" + address.toString()
        + "|" + getClassificationString() + "|" + (isFavorite ? "1" : "0");
}

void Contact::printSummary() const {
    std::cout << getFullName();
    if (isFavorite) std::cout << "  [fav]";
    std::cout << "\n";
}

void Contact::printDetailed() const {
    std::cout << "Name: " << getFullName() << "\n"
              << "Phone: " << phoneNumber << "\n"
              << "Email: " << email << "\n"
              << "Address: " << address.toString() << "\n"
              << "Classification: " << getClassificationString() << "\n"
              << "Favorite: " << (isFavorite ? "Yes" : "No") << "\n";
}

bool Contact::operator==(const Contact& other) const {
    return firstName == other.firstName && lastName == other.lastName;
}

bool Contact::operator<(const Contact& other) const {
    if (lastName != other.lastName) return lastName < other.lastName;
    return firstName < other.firstName;
}

ContactClassification stringToClassification(const std::string& str) {
    if (str == "FRIEND" || str == "Friend") return ContactClassification::FRIEND;
    else if (str == "WORK" || str == "Work") return ContactClassification::WORK;
    else if (str == "FAMILY" || str == "Family") return ContactClassification::FAMILY;
    else return ContactClassification::OTHER;
}
