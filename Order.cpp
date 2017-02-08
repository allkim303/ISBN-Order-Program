/*=========================================================
	Allison KIM 
===========================================================*/
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#include "Order.h"

/*========================================================
	a no-argument constructor that creates an Order 
	object in a safe empty state 
==========================================================*/

Order::Order(){
	cname=NULL;
	Ordered=0;
	Delivered=0;
}

/*========================================================
	A one-argument constructor that receives a reference 
	to an ISBN object and initializes an Order object for 
	that ISBN
==========================================================*/
Order::Order(const ISBN& isbn){

	orISBN=isbn;
	cname=NULL;
	Ordered=0;
	Delivered=0;
}

/*========================================================
	A two-argument constructor that receives a reference 
	to an ISBN object and initializes an Order object for 
	that ISBN and the address of a string containing the 
	name of the client.
==========================================================*/
Order::Order(const ISBN& isbn, const char* nm){

	if(nm != NULL){
		cname=new char[strlen(nm)+1];
		strcpy(cname, nm);
		orISBN=isbn;
	}
	else cname=NULL;
	Ordered=0;
	Delivered=0;
}

/*========================================================
	a copy constructor
==========================================================*/
Order::Order(const Order& source){

	orISBN=source.orISBN;
	Ordered=source.Ordered;
	Delivered=source.Delivered;
	if(source.cname!=NULL){
		cname=new char[strlen(source.cname)+1];
		strcpy(cname, source.cname);
	}
	else
		cname=NULL;	
}

/*========================================================
	a destructor that cleans up memory before the current 
	object goes out of scope
==========================================================*/
Order::~Order(){

	if(cname!=NULL)
		delete [] cname;
}

/*========================================================
	A query that receives a reference to an ISBN object 
	and returns true if the Order object is for that ISBN, 
	false otherwise.
==========================================================*/
bool Order::has(const ISBN& isbn) const{
	
	if(orISBN==isbn)
		return true;
	else
		return false;
}

/*========================================================
	A query that returns the name held by the current 
	object
==========================================================*/
void Order::name(char* str) const{
	
	if(cname!=NULL)
		strcpy(str, cname);
	else str=NULL;
}

/*========================================================
	A query that returns the number of copies remaining 
	on order in the current object
==========================================================*/
int Order::outstanding() const{
	return Ordered;
}

/*========================================================
	A modifier that receives a reference to an istream 
	object and updates the name held by the order based 
	upon data recieved from input stream is.
==========================================================*/
bool Order::client(istream& is){

	char nm[101];

	cout<<"Name (0 to quit) : ";
	is.getline(nm,100);
	if(strcmp(nm,"0")==0) return false;
	else if(cname!=NULL) delete [] cname;
		cname=new char[strlen(nm)+1];
		strcpy(cname, nm);	
	return true;
}

/*========================================================
	A modifier that receives a reference to an istream 
	object and increases the number of copies to be ordered 
	based upon data received from input stream is. 	
==========================================================*/
bool Order::add(istream& is){

	int temp;
	do{
		cout<<"Quantity (0 to quit) : ";
		is>>temp;
		is.ignore(100, '\n');
		if(temp<0)
			cout<<"Enter a positive number.  Try again."<<endl;
	}while(temp<0);
	
	if(temp==0)     return false;
	else 
		Ordered=temp;
	return true;
}

/*========================================================
	a modifier that receives the number of copies to be 
	added to the current order 
==========================================================*/
bool Order::add(int n){

	if(n<1 || orISBN.empty()) return false;
	
	Ordered = Ordered + n;
	return true;		
}

/*========================================================
	A modifier that receives a reference to an istream 
	object and records receipt of copies based upon data 
	from the input stream 
==========================================================*/
bool Order::receive(istream& is){

	int temp;
	do{
		cout<<"Quantity (0 to quit) : ";
		is>>temp;
		is.ignore(100, '\n');
		if(temp > Ordered){
			cout<<temp<<" not on order. Only "
				<<Ordered<<" are on order. Try again."<<endl;
		}
		else if(temp<0){
			cout<<"Enter a positive number. Try again."<<endl;
		}			
	}while(temp<0 ||temp>Ordered);

	if(temp==0){ 
		cout<<"**No delivery recorded!"<<endl;
		return false;
	}
	Delivered=temp;
	return true;
}

/*========================================================
	A query that receives a reference to an ostream object 
	and displays the current object on the output stream
==========================================================*/
void Order::display(ostream& os) const{

	orISBN.display(os);
	os.width(9);
	os<<Ordered;
	os.width(11);
	os<<Delivered<<" ";
	if(cname!=NULL){
		os.width(25);
		os<<left<<cname;
	}
}


/*========================================================
	An assignment operator that receives a reference to 
	an unmodifable Order object and copies the information 
	in that referenced object into the current object 
==========================================================*/
Order& Order::operator=(const Order& source){

	if(this != &source){
		Ordered = source.Ordered;
		Delivered = source.Delivered;
		orISBN=source.orISBN;
		if(cname != NULL) delete [] cname;
		if(source.cname!=NULL){
			cname=new char[strlen(source.cname)+1];
			strcpy(cname, source.cname);
		}
		else
			cname=NULL;
	}
	return *this;
}

/*========================================================
	A non friend overloaded operator that receives a 
	reference to an ostream object along with a reference 
	to an unmodifiable Order object and inserts that object's 
	information into the specified output stream  
==========================================================*/
ostream& operator<<(ostream& os, const Order& order){

	order.display(os);
	return os;
}














