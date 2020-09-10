#ifndef __ORDER_H
#define __ORDER_H

#include "customer.h"
#include "desktop.h"
#include <iostream>
#include <fstream>

class Order {
  public:
    void save(std::ostream& ost); //save 
    Order(Customer& customer);
    Order(std::istream& ist);
    virtual ~Order();
    int add_product(Desktop& desktop);
    double price() const;
    friend std::ostream& operator<<(std::ostream& ost, const Order& order);
  private:
    Customer* _customer; // may need to change to *
    std::vector<Desktop*> _products;
};

#endif
