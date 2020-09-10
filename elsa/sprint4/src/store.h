#ifndef __STORE_H
#define __STORE_H

#include "customer.h"
#include "options.h"
#include "desktop.h"
#include "order.h"
#include "ram.h"
#include <iostream>
#include <fstream>

const std::string ELSA_COOKIE = "ℰ𐑃𐊖ᴀ";
const std::string ELSA_VERSION = "1.1.0";
const std::string ELSA_FILE_VERSION = "1.0-simple";

class Store {
  public:
	Store(); // start a new blank file
	Store(std::istream& ist); // open previously saved
	void save(std::ostream& ost); //save 

    void add_customer(Customer& customer);
    int num_customers();
    Customer& customer(int index);

    void add_option(Options& option);
    int num_options();
    Options& option(int index);

    int new_desktop(); // returns index
    void add_option(int option, int desktop); // to desktop
    int num_desktops();
    Desktop& desktop(int index);

    int new_order(int customer); // returns order number
    void add_desktop(int desktop, int order); // to order
    int num_orders();
    Order& order(int index);
  private:
    std::vector<Customer> customers;
    std::vector<Options*>  options;
    std::vector<Desktop>  desktops;
    std::vector<Order>    orders;
};

#endif
