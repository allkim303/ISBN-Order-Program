/*=========================================================
	MINJI KIM 067742122
===========================================================*/

/*========================================================
	This class manages access to the prefix table.
==========================================================*/
class ISBNPrefix{

	FILE* fp;
	ISBNPrefix(const ISBNPrefix& source);
	ISBNPrefix& operator=(const ISBNPrefix& source);

public:
	ISBNPrefix(const char*);
	~ISBNPrefix();
	bool isRegistered(int) const;
	int minNoDigits(int) const;
	bool isRegistered(int, const char*) const;
};