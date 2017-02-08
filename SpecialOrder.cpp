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

#include "SpecialOrder.h"

/*===========================================================
	a no-argument constructor that creates a SpecialOrder 
	object in a safe empty state
=============================================================*/
SpecialOrder::SpecialOrder():Order(){
	instruction=NULL;
}

/*===========================================================
	a two-argument constructor that creates a SpecialOrder 
	object from a reference to an ISBN object and the address 
	of a string containing the special instructions 
=============================================================*/
SpecialOrder::SpecialOrder(const ISBN& isbn, const char* instr):Order(isbn){
	if(instr!=NULL){
		instruction=new char[strlen(instr)+1];
		strcpy(instruction, instr);
	}
	else     add(cin);

}

SpecialOrder:: SpecialOrder(const SpecialOrder& source): Order(source){
	 if(source.instruction!=NULL){
		 instruction=new char[strlen(source.instruction)+1];
		 strcpy(instruction, source.instruction);
	 }
	 else     instruction=NULL;
}

/*===========================================================
	a destructor that cleans up memory before the current 
	object goes out of scope 
=============================================================*/
SpecialOrder::~SpecialOrder(){
	if(instruction!=NULL)
		delete [] instruction;
}

/*===========================================================

=============================================================*/
bool SpecialOrder::add(istream& is){

	char inst[MAXCHAR+1];
	inst[0]='\0';
	if(Order::add(is)){
		cout<<"Instruction : ";
		is.getline(inst, MAXCHAR);		
		if(inst[0]!='\0'){
			if(instruction!=NULL)	delete [] instruction;	
			instruction=new char[strlen(inst)+1];
			strcpy(instruction, inst);
			return true;
		}
	}

	return false;
}

/*===========================================================

=============================================================*/
void SpecialOrder::display(ostream& os) const{

	Order::display(os);
	os<<instruction;
}

/*===========================================================

=============================================================*/
SpecialOrder& SpecialOrder::operator=(const SpecialOrder& source){
	if(this != &source){
		(Order&) *this = (Order&) source;
		if(instruction != NULL) delete [] instruction;
		if(source.instruction !=NULL){
			instruction=new char[strlen(source.instruction)+1];
			strcpy(instruction, source.instruction);
		}
		else     instruction=NULL;
	}
	return *this;
}
