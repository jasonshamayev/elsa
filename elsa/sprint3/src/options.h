#ifndef __OPTIONS_H
#define __OPTIONS_H

#include <string>
#include <ostream>
#include <iostream>
#include <fstream>

class Options {
  public:
    void save(std::ostream& ost); //save 
    Options(std::istream& ist);
    Options(std::string name, double cost);
    virtual ~Options();
    double cost();
    virtual std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& ost, const Options& options);
  protected:
    std::string _name;
    double _cost;
};

#endif
