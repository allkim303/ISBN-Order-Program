/*=========================================================
	Allison Kim
===========================================================*/
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
#include "ISBNPrefix.h"
#include "ISBN.h"

/*===========================================================
	This constructor creates an ISBN object
	in a safe empty state.
=============================================================*/
ISBN::ISBN(){
	area[0]='\0';
	publisher[0]='\0';
	title[0]='\0';
	Isbn[0]='\0';
}

/*===========================================================
	This constructor with two arguments creates an ISBN object 
	and checks if the ISBN code is valid and registered.
	If the code is not valid, it makes the object an empty state.
=============================================================*/
ISBN::ISBN(const char* str, const ISBNPrefix& list){

	if(isValid(str)){
		strcpy(Isbn, str);
		if(!isRegistered(list)){
			area[0]='\0';
			publisher[0]='\0';
			title[0]='\0';
		}
	}
	else{
		area[0]='\0';
		publisher[0]='\0';
		title[0]='\0';
		Isbn[0]='\0';
	}
}

/*============================================================
	This is a private modifier that receives a reference to an 
	ISBNPrefix object. It checks if the ISBN string is registered.
	If the string is registered, this function extracts the area,
	publisher, and title components and returns true.
==============================================================*/
bool ISBN::isRegistered(const ISBNPrefix& list){

	int area_int=0,
		flag=0,
		area_len=0,
		pub_len=0,
		title_len=0,
		area_pub_len=0,
		i=0;

	while(flag==0 && area_len<5){
		area_len++;
		for(i=0; i<area_len; i++){
			area[i]=Isbn[i];
		}
		area[area_len]='\0';		
		area_int = atoi(area);			
		if(list.isRegistered(area_int))		flag=1;
	}

	if(flag){
		pub_len = list.minNoDigits(area_int);		
		if(pub_len<=0 || pub_len>=8)	return false;
	}

	if(flag){
		area_pub_len = area_len;
		for(i=0; i<pub_len ; i++){
			publisher[i]= Isbn[area_pub_len];
			area_pub_len++;
		}
		publisher[pub_len]='\0';
		flag=0;
		while(area_pub_len<9 && pub_len<8 && flag==0){
			if(list.isRegistered(area_int, publisher))	flag=1;
			else{
				publisher[pub_len]=Isbn[area_pub_len];
				pub_len++;
				area_pub_len++;
				publisher[pub_len]='\0';
			}
		}
	}
	if(flag){

		title_len = 9-area_pub_len;
		for (i=0; i<title_len && area_pub_len<10; i++){
			title[i]=Isbn[area_pub_len];
			area_pub_len++;
		}
		title[title_len]='\0';
	}

	if(flag)		return true;
	else			return false;
}

/*===========================================================
	This function returns true if the object is in a safe
	empty state.
=============================================================*/
bool ISBN::empty() const{

	if(Isbn[0]=='\0' && area[0]=='\0')
		return true;
	else 
		return false;
}

/*===========================================================
	This function returns true if the object is registered.
=============================================================*/
bool ISBN::isRegistered() const{
	if(area[0] != '\0')
		return true;
	else
		return false;
}

/*============================================================
	This function passes the ISBN string in an unformatted form
	through the function's parameter.
==============================================================*/
void ISBN::toStr(char* str) const{
	strcpy(str, Isbn);
}

/*=============================================================
	This function passes the ISBN string in a formatted form if
	the object is registered. If the object is unregistered, the
	string is in an unformatted form.
===============================================================*/
void ISBN::toStrWithStyle(char* str) const{

	if(area[0]!='\0'){
		strcpy(str, area);
		strcat(str,"-");
		strcat(str, publisher);
		strcat(str,"-");
		strcat(str, title);
		strcat(str,"-");
		str[12]=Isbn[9];
		str[13]='\0';
	}
	else
		strcpy(str, Isbn);
}

/*============================================================
	This function receives a reference to an ostream object.
	It displays the ISBN in dash style if it is registered.
	If the ISBN is not registered, the function displays the 
	ISBN in the concatenated style.
==============================================================*/
void ISBN::display(ostream& os) const{
	
	char Isbn_display[14];
	if(area[0] != '\0')
		toStrWithStyle(Isbn_display);
	else
		toStr(Isbn_display);
	os.width(13);
	os<<Isbn_display;		
}

/*=============================================================
	This function accepts a string. If the string is a valid ISBN,
	it stores the ISBN string in the current object.
	If the input is unacceptable, this function requests another 
	string or "0" to quit.
===============================================================*/
bool ISBN::read(istream& is, const ISBNPrefix& list){

	char _isbn[11];

	do{
		cout<<"ISBN (0 to quit) : ";
		is>>_isbn;
		is.ignore(2000, '\n');
		if(strlen(_isbn)<10 && strcmp(_isbn, "0")!=0 )
			cout<<"Too few characters. Try again."<<endl;
		else if(isValid(_isbn)){			
			strcpy(Isbn, _isbn);
			if(!isRegistered(list)){
				area[0]='\0';
				publisher[0]='\0';
				title[0]='\0';
			}		
			return true;
		}
		else if(!(isValid(_isbn)) && strcmp(_isbn, "0")!=0 )
			cout<<"Invalid check digit. Try again."<<endl;
	}while(strcmp(_isbn, "0")!=0);

	return false;			
}


/*===============================================================
	This function receives a string and checks if the string is
	a valid ISBN.
=================================================================*/
int isValid(const char* str){

	int i=0,
		weight=10, 
		num, sum, 
		flag = 0, 
		Total= 0;
	char digit[2];

	if(str==NULL || strlen(str)!=10)
		return flag;

	for(i=0; i<10; i++, weight--){
		if(i<9 && (str[i]<'0' || str[i]>'9')){
			i=11;
		}
		else if(i<10 && (str[i]>='0' && str[i]<='9')){
			digit[0]=str[i];
			digit[1]='\0';
			num = atoi(digit);
			sum= num * weight;
			Total +=sum;
		}
		else if(i==9 && (str[9]=='x' || str[9]=='X'))
			Total += 10;
	}
	if(i==10 && Total%11==0)
		flag=1;	

	return flag;		
}

/*================================================================
	an overloaded operator that receives references to two 
	unmodifiable ISBN objects and compares the objects for 
	equality. It returns true if both objects hold the same 
	ISBN; false otherwise.
==================================================================*/
bool operator==(const ISBN& left, const ISBN& right){

	char Lisbn[11],
		 Risbn[11];

	left.toStr(Lisbn);
	right.toStr(Risbn);

	if(strcmp(Lisbn, Risbn))
		return false;
	else
		return true;
}
/*=====================================================================
	a non friend overloaded operator that receives a reference to 
	an ostream object along with a reference to an unmodifiable 
	ISBN object and display the object on the specified output stream
=======================================================================*/
ostream& operator<<(ostream& os, const ISBN& isbn){

	isbn.display(os);
	return os;
}


	




