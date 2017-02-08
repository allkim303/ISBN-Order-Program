/*=========================================================
	Allison KIM
===========================================================*/

#include <iostream>
#include "Order.h"

#define MAXCHAR 100

/*===========================================================
	This Derived class named SpecialOrder from your Order 
	class holds and displays special instructions.
=============================================================*/
class SpecialOrder : public Order{

	char* instruction;

public:
	SpecialOrder();	
	SpecialOrder(const ISBN& isbn, const char* instr);
	SpecialOrder(const SpecialOrder& source);
	~SpecialOrder();
	bool add(istream& is);
	void display(ostream& os) const;
	SpecialOrder& operator=(const SpecialOrder& source);
};
