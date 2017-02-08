// Bookstore Order Processor
// OOP244.132 - Assignment 4
// a4main.cpp
// Version 1.1
// Chris Szalwinski
// Jan 15 2011

#include <cstdio>
#include <iostream>
using namespace std;
#include "ISBNPrefix.h"
#include "SpecialOrder.h"

#define MAXORDERS 100
char menu(istream& is);
char style(istream& is);

int main() {
    char c, choice;
    int noOrders = 0;
    Order* order[MAXORDERS];
    ISBNPrefix prefixList("prefixRanges.txt");

    cout << "Bookstore Order Processor\n"
         << "=========================\n";

    // process user input
    do {
        choice = menu(cin);
        cout << endl;
        switch(choice) {
            case 'P':
                {
                    ISBN isbn;
                    if (isbn.read(cin, prefixList)) {
                        int index = -1, created = false;
                        for (int i = 0; i < noOrders && index == -1; i++)
                            if (order[i]->has(isbn))
                                index = i;
                        if (index == -1)
                            if (noOrders < MAXORDERS) {
                                index = noOrders;
                                order[noOrders++] = new Order(isbn);
                                created = true;
                            }
                            else
                                cerr << "No space for more orders!" << endl;
                        if(!order[index]->add(cin) && created)
                            delete order[--noOrders];
                    }
                }
                break;
            case 'S':
                {
                    ISBN isbn;
                    if (isbn.read(cin, prefixList)) {
                        int index = -1, created = false;
                        for (int i = 0; i < noOrders && index == -1; i++)
                            if (order[i]->has(isbn))
                                index = i;
                        if (index == -1)
                            if (noOrders < MAXORDERS) {
                                index = noOrders;
                                order[noOrders++] = new SpecialOrder(isbn, "");
                                created = true;
                            }
                            else
                                cerr << "No space for more orders!" << endl;
                        if(!order[index]->add(cin) && created)
                            delete order[--noOrders];
                    }
                }
                break;
            case 'A':
                {
                    ISBN isbn;
                    if (isbn.read(cin, prefixList)) {
                        int index = -1;
                        for (int i = 0; i < noOrders && index == -1; i++)
                            if (order[i]->has(isbn))
                                index = i;
                        if (index != -1)
                            order[index]->add(1);
                        else
                            cerr << "No order for " << isbn << " found!" << endl;
                    }
                }
                break;
            case 'D':
                {
                    ISBN isbn;
                    if (isbn.read(cin, prefixList)) {
                        int index = -1;
                        for (int i = 0; i < noOrders && index == -1; i++)
                            if (order[i]->has(isbn))
                                index = i;
                        if (index != -1)
                            order[index]->receive(cin);
                        else
                            cerr << "No order for " << isbn << " found!" << endl;
                    }
                }
                break;
            case 'V':
                cout << "         ISBN  Ordered  Delivered Instructions\n";
                cout << "----------------------------------------------\n";
                for (int i = 0; i < noOrders; i++) {
                    cout << *order[i] << endl;
                }
                break;
        }
    } while (choice != 'Q');

    cout << "\nSigning off ... " << endl;
    // deallocate order memory
    for (int i = 0; i < noOrders; i++)
        delete order[i];
    return 0;
}

// menu prompts for and accepts an option selection from standard input and
// returns the character identifying the selected option
//
char menu(istream& is) {
    char c;
    int  ok = false;

    cout << '\n';
    cout << "Please select from the following options :\n";
    cout << " P - Place an order with a publisher\n";
    cout << " S - Place a special order with a publisher\n";
    cout << " A - Add one copy to an existing order\n";
    cout << " D - Record a delivery from a publisher\n";
    cout << " V - View status of books on order\n";
    cout << " Q - Quit\n";
    do {
        cout << " Your selection : ";
        c = ' ';
        is.get(c);
        if (c >= 'a' && c <= 'z')
            c -= 'a' - 'A';
        if (is.fail()) {
            is.clear();
            is.ignore(2000, '\n');
            cerr << " Invalid input.  Try again." << endl;
        } else if (c == '\n') {
            ; // no input - try again
        } else if (c != 'P' && c != 'S' && c != 'A' && c != 'D' && c != 'V'
         && c != 'Q') {
            is.ignore(2000, '\n');
            cerr << " Invalid Character.  Try again." << endl;
        } else if (is.get() != '\n') {
            is.ignore(2000, '\n');
            cerr << " Trailing Characters.  Try Again. " << endl;
        } else if (c == 'P' || c == 'S' || c == 'A' || c == 'D' || c == 'V'
         || c == 'Q')
            ok = true;
    } while (ok == 0);

    return c;
}

