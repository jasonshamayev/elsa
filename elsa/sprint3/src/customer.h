#ifndef __CUSTOMER_H
#define __CUSTOMER_H

#include <string>
#include <ostream>
#include <iostream>
#include <fstream>

class Customer {
  public:
    void save(std::ostream& ost); //save 
    Customer(std::istream& ist);
    Customer(std::string name, std::string phone, std::string email);
    friend std::ostream& operator<<(std::ostream& ost, const Customer& customer);
  private:
    std::string _name;
    std::string _phone;
    std::string _email;
};

#endif
