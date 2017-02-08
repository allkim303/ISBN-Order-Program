/*=========================================================
	MINJI KIM 067742122
===========================================================*/

#include <iostream>
#include "ISBN.h"

/*=============================================================
	Order class manages a single bookstore order, where the order 
	refers to one specific edition of a publication; that is, 
	to one ISBN.
===============================================================*/
class Order{

	ISBN orISBN;
	char* cname;
	int Ordered, Delivered;

public:
	Order();
	Order(const ISBN& isbn);
	Order(const ISBN& isbn, const char* nm);
	Order(const Order& source);
	virtual ~Order();
	bool has(const ISBN& isbn) const;
	void name(char* str) const;
	int outstanding() const;
	bool client(istream& is);
	virtual bool add(istream& is);
	bool add(int n);
	bool receive(istream& is);
	virtual void display(ostream& os) const;	
	Order& operator=(const Order& source);
};

ostream& operator<<(ostream& os, const Order& order);