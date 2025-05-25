# Contact Book Application

A simple command-line Contact Book implemented in C++ using dynamic arrays (`std::vector`).  
Manage your contacts with features like adding, deleting, updating, searching, sorting, sharing, and saving/loading contacts.

---

## Features

- Add new contacts with details including name, phone, email, address, classification, and favorite status  
- Delete and update existing contacts by last name (case-insensitive)  
- Search contacts by last name or classification type  
- Mark contacts as favorites and list them  
- Save contacts to a text file and load from it  
- Export individual contacts as vCard (.vcf) files for sharing  
- Reverse contact order and print detailed or summary views  
- Basic validation of phone numbers and emails

---

## Data Structure

Uses a dynamic array (`std::vector`) to store contacts, ensuring efficient and scalable management.

---

## Requirements

- C++11 or newer compiler  
- Standard C++ libraries
  
---

## How to Use

1. Clone the repository  
2. Build the project using your preferred C++ compiler or IDE  
3. Run the executable  
4. Use the interactive menu to manage contacts

---

## File Structure

- `contact.h` / `contact.cpp` — Defines the `Contact` class and related methods  
- `contactbook.h` / `contactbook.cpp` — Defines the `ContactBook` class managing a collection of contacts  
- `main.cpp` — Contains the interactive menu and program entry point  

---
## License

This project is open source and available under the MIT License.

---

## Contact

Created by Salma Sherif. Feel free to contribute or report issues.
