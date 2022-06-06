/**
 * @file member.cpp
 * @Kay Randall @kalyps0
 * @implementation file for member class
 * @version 0.11 - add display for save to file
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "member.h"

member::member():validity(false),membership_fee(0.00),status(""),overdue(false), member_summary(){
}

member::member(int member_id, const string& first_name, const string& last_name, const string& address,
    const string& city, const string& state, int zip_code, const string& email, const string& member_status, int valid, float fee):
    personal_info(member_id, first_name, last_name, address, city, state, zip_code, email){
    status = member_status;
    membership_fee = fee;
    if(valid==1){
        validity = true;
        overdue = false;
    } else if(valid == 0){
        validity = false;
        overdue = true;
    }
}

bool member::add_member(){
    cout << "INFORMATION REQUIRED FOR NEW MEMBER:\n";
    read_personal_info();
    validity = true;
    cout << "Please enter the monthly membership fee: $";
    cin >> membership_fee;
    cin.ignore(7, '\n');
    status = "VALID";
    overdue = false;
    return validity;
}

void member::add_service(service &new_service)
{
    member_summary.add_service(new_service);
}

void member::display_summary(){
    member_summary.display_all_mem(cout);
}

void member::display_status() const{
    cout << status;
}


void member::save_summary(){
    string file_name;
    string date;
    cout << "Please enter today's date in the format as follows using only numbers 'MM_DD_YYYY_'.\n";
    cout << "Example: 03_11_2022\n";
    cout << "Please enter today's date in the specified format: ";
    getline(cin, date, '\n');
    file_name= first_name+"_"+ last_name+"_"+date+".txt";
    cout << "Weekly summary report's file name is " << file_name << endl;
    ofstream report;
    report.open (file_name);
    display_all(report);
    member_summary.save_to_file_mem(report);
    report.close();
}

bool member::check_validity(){
    return validity;
}

bool member::check_overdue(){
    return overdue;
}

void member::display(ostream& out) const{
    //display_personal_info();
    //replaced using Operator Overloaded << display, - Andy
    display_all(out);

    cout << "Membership fee: $" << membership_fee << endl;
    cout << "Member status: " << status << endl;
    if(overdue){
        cout << "MEMBER HAS OVERDUE FEES.\n";
    }
    if(validity){
        cout << "VALID membership.\n";
    }else if(!validity){
        cout << "INVALID membership.\n";
    }
    //if(member_summary !=NULL){
        //display_summary(); //not implemented yet
    //}
}

void member::display_for_save(ostream &out){
    display_for_file(out);
    out << status << ";";
    if(validity){
        out << "1;";
    } else if(!validity){
        out << "0;";
    }
    out << membership_fee << endl;
}

void member::load_from_file(const string& file_name) {
    member_summary.load_from_file(file_name);
}

bool member::operator == (const member& to_compare) const{
    return (last_name == to_compare.last_name) && (first_name == to_compare.first_name)
        && (ID == to_compare.ID);
}

bool member::operator < (const member& to_compare) const{
    if(ID < to_compare.ID){
        return true;
    }
    return false;
}

bool member::operator > (const member& to_compare) const{
    if(ID > to_compare.ID){
        return true;
    }
    return false;
}

ostream & operator << (ostream &out, const member &source){
    source.display(out);
    return out;
}



//getters for member list to save to file
bool member::gets_validity()
{
    return validity;
}
float member::gets_membership_fee()
{
    return membership_fee;
}
string member::gets_status()
{
    return status;
}
bool member::gets_overdue()
{
    return overdue;
}

//used for updating the information of an existing member (keep their ID)
void member::update_info(string mem_id)
{
    read_update_pi(mem_id);
    validity = true;
    cout << "Please enter the monthly membership fee: $";
    cin >> membership_fee;
    cin.ignore(7, '\n');
    status = "VALID";
    overdue = false;

}
//