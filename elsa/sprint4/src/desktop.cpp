#include "desktop.h"

void Desktop::add_option(Options& option) {options.push_back(&option);}
double Desktop::price() {
    double p = 0.0;
    for(auto o : options) p+= o->cost();
    return p;
}
std::ostream& operator<<(std::ostream& ost, const Desktop& desktop) {
    ost << "Desktop includes";
    for(auto o : desktop.options) ost << "\n  " << *o;
    return ost;
}

void Desktop::save(std::ostream& ost){
    ost << options.size() << '\n';
    for(auto c : options) c->save(ost, *c);

}

Desktop::Desktop(std::istream& ist){
    int vsize;
    ist >> vsize; ist.ignore(32767, '\n');
    while(vsize--) options.push_back(new Options{ist});


}

Desktop::Desktop(){}

