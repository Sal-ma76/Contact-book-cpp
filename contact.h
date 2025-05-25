#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <iostream>

enum class ContactClassification {
    FRIEND,
    FAMILY,
    WORK,
    OTHER
};

class Address {
public:
    std::string street;
    std::string city;
    std::string state;
    std::string zipCode;
    std::string country;

    Address() : street(""), city(""), state(""), zipCode(""), country("") {}

    Address(const std::string& street, const std::string& city, const std::string& state,
            const std::string& zipCode, const std::string& country)
        : street(street), city(city), state(state), zipCode(zipCode), country(country) {}

    std::string toString() const {
        return street + ", " + city + ", " + state + ", " + zipCode + ", " + country;
    }
};

class Contact {
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string email;
    ContactClassification classification;
    bool isFavorite;

public:
    Address address;

    Contact(const std::string& firstName, const std::string& lastName);
    Contact(const std::string& firstName, const std::string& lastName,
            const std::string& phoneNumber, const std::string& email,
            const Address& address, ContactClassification classification,
            bool isFavorite = false);

    const std::string& getFirstName() const { return firstName; }
    const std::string& getLastName() const { return lastName; }
    const std::string& getPhoneNumber() const { return phoneNumber; }
    const std::string& getEmail() const { return email; }
    ContactClassification getClassification() const { return classification; }
    bool getIsFavorite() const { return isFavorite; }

    void setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
    void setEmail(const std::string& email) { this->email = email; }
    void setClassification(ContactClassification cclass) { classification = cclass; }
    void setIsFavorite(bool favorite) { isFavorite = favorite; }

    std::string getFullName() const { return firstName + " " + lastName; }
    std::string getClassificationString() const;

    std::string toString() const;

    void printSummary() const;
    void printDetailed() const;

    bool operator==(const Contact& other) const;
    bool operator<(const Contact& other) const;
};

//string to ContactClassification enum convertion
ContactClassification stringToClassification(const std::string& str);

#endif // CONTACT_H
