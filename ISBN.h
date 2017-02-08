/*=========================================================
	MINJI KIM 067742122
===========================================================*/
#include <iostream>
class ISBNPrefix;

/*========================================================
	This class manages a single ISBN.
==========================================================*/
class ISBN{

	char area[6],
		 publisher[8],
		 title[6],
		 Isbn[11];
		
	bool isRegistered(const ISBNPrefix&);

public:
	ISBN();
	ISBN(const char*, const ISBNPrefix&);
	bool empty() const;
	bool isRegistered() const;
	void toStr(char*) const;
	void toStrWithStyle(char*) const;
	void display(ostream& os) const;
	bool read(istream& is, const ISBNPrefix&);

};

int isValid(const char* str);
bool operator==(const ISBN& left, const ISBN& right);
ostream& operator<<(ostream& os, const ISBN& isbn);