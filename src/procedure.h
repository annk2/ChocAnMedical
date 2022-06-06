/**
 * @file provider.h
 * @Natasha Naylor @nnaylor
 * @header file for procedure class
 * @version 0.3
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class procedure{

public:
    procedure(); //default constructor
    procedure(const string& procedure_name, int procedure_code, float service_fee); //constructor

    //displays procedure information
    void display(ostream& out) const;

    void display_normal(ostream& out) const;

    //displays only procedure name
    void display_name() const;

    void display_name(ostream &out) const;

    //checks if new procedure code entered is unique
    bool is_unique_code(int new_procedure_code);

    //overloaded comparison operator
    bool operator == (const procedure& to_compare) const;

    //checks if procedure name comes alphabetically before another
    bool operator < (const procedure& to_compare) const;

    //checks if procedure name comes alphabetically after another
    bool operator > (const procedure& to_compare) const;

    float get_fee();

    //overloaded insertion operator
    friend ostream& operator << (ostream& out, const procedure& source);

protected:
    string procedure_name;
    int procedure_code;
    float service_fee;

};



#endif
//