#ifndef __DESKTOP_H
#define __DESKTOP_H

#include "options.h"
#include <vector>
#include <iostream>
#include <fstream>

class Desktop {
  public: 
    Desktop();
    void save(std::ostream& ost); //save
    Desktop(std::istream& ist);   
    void add_option(Options& option);
    double price();
    friend std::ostream& operator<<(std::ostream& ost, const Desktop& desktop);
  private:
    std::vector<Options*> options;
};

#endif
