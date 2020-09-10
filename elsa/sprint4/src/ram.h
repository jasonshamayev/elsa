#ifndef __RAM_H
#define __RAM_H

#include "options.h"
#include <iostream> 

class Ram : public Options {
	public:
		Ram(std::string name, double cost, int gb);
		virtual ~Ram();
		Ram(std::istream& ist);
		void save(std::ostream& ost, const Options& options) override;
		std::string to_string() const override;
	protected:
		int _gb;
		





};
#endif
