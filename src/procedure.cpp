/**
 * @file procedure.cpp
 * @Natasha Naylor @nnaylor
 * @implementation file for procedure class
 * @version 0.3
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "procedure.h"
#include <iomanip>


//procedure default constructor
procedure::procedure(): procedure_name(), procedure_code(000000), service_fee(0.00) { }


//initializes procedure object
procedure::procedure(const string& new_procedure_name, int new_procedure_code, float new_service_fee):
    procedure_name(new_procedure_name), procedure_code(new_procedure_code), service_fee(new_service_fee) { }


//displays procedure information
void procedure::display(ostream& out) const{
    out << setw(40) << left <<  procedure_name
        << setw(25) << procedure_code
        << setw(35) << fixed << setprecision(2) << service_fee << setw(20) << endl;
}

void procedure::display_normal(ostream& out) const{
    out << "Service Name: " << procedure_name << endl;
    out << "Service Code: " << procedure_code << endl;
    out << "Service Fee: " << service_fee << endl;
}


//displays only procedure name
void procedure::display_name() const{
    cout << procedure_name;
}

//displays only procedure name
void procedure::display_name(ostream &out) const{
    out << procedure_name;
}


//checks if procedure code entered is unique
bool procedure::is_unique_code(int new_procedure_code){
    return new_procedure_code != procedure_code;
}


//overloaded comparison operator
bool procedure::operator== (const procedure& to_compare) const{
    return (procedure_name == to_compare.procedure_name) && (procedure_code == to_compare.procedure_code)
        && (service_fee == to_compare.service_fee);
}


//checks if procedure name comes alphabetically before another
bool procedure::operator < (const procedure& to_compare) const{
    if(procedure_name < to_compare.procedure_name){
        return true;
    }
    return false;
}

//checks if procedure name comes alphabetically after another
bool procedure::operator > (const procedure& to_compare) const{
    if(procedure_name > to_compare.procedure_name){
        return true;
    }
    return false;
}

float procedure::get_fee(){
    return service_fee;
}


//overloaded insertion operator 
ostream& operator << (ostream& out, const procedure& source){
    source.display(out);
    return out;
}
//