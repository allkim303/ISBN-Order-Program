/*=========================================================
	MINJI KIM 067742122
===========================================================*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#include "ISBNPrefix.h"

/*===========================================================
	This constructure receives a string containing the name
	of a file and open the file. If it fails to open the file,
	it returns NULL.
=============================================================*/
ISBNPrefix::ISBNPrefix(const char* filename){
	
	if(filename == NULL)
		fp = NULL;
	else
		fp = fopen(filename, "r");
}

/*============================================================
	This query receives an area identifier and check if the area
	is listed. If the area is listed, it returns true. 
==============================================================*/
bool ISBNPrefix::isRegistered(int area) const{
	int area_table, temp1, temp2;
	rewind(fp);
	while(fscanf( fp, "%d %d %d\n" , &area_table, &temp1, &temp2)!=EOF){				
		if( area == area_table)
			return true;				
	}	
	return false;
}

/*=============================================================
	This query recieves an area identifier and determines the
	minimum number of digits of publisher identifier.
===============================================================*/
int ISBNPrefix::minNoDigits(int area) const{

	char publisher_table[8];
	int area_table,temp,
		flag=0;
	
	rewind(fp);
	while(fscanf( fp, "%d %s %d\n" , &area_table, publisher_table, &temp)!=EOF && flag==0){
		if(area_table == area){   	
			flag = strlen(publisher_table);
		}		
	}	
	return flag;
}

/*================================================================
	This query receives an area identifier and publisher identifier.
	It checks if the publisher identifier is within a puvlisher 
	range listed under that area.
==================================================================*/
bool ISBNPrefix::isRegistered(int area, const char* publisher) const{

	int publisher_int, area_table, max;
	char min[8];

	publisher_int = atoi(publisher);
	rewind(fp);
	while(fscanf( fp, "%d %s %d\n" , &area_table, min, &max)!=EOF){

		if(area==area_table && (strlen(publisher)==strlen(min))){
			if(publisher_int>=(atoi(min)) && publisher_int<=max)
				return true;		
		}
	}	
	return false;
}

/*===============================================================
	This destructor closes the file before the current object
	goes out of scope.
=================================================================*/
ISBNPrefix::~ISBNPrefix(){

	fclose(fp);

}

	