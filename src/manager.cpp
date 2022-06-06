/**
 * @file manager.cpp
 * @Kay Randall @kalyps0
 * @implementation file for manager class
 * @version 0.5 - adding output overloading operator
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "manager.h"

manager::manager():password(""){
}

manager::manager(int manager_id, const string& first_name, const string& last_name, const string& address, const string& city,
    const string& state, int zip_code, const string& email, const string& pswd):
    personal_info(manager_id, first_name, last_name, address, city, state, zip_code, email){
    password = pswd;
}


void manager::add_manager(){
    cout << "INFORMATION REQUIRED FOR NEW MANAGER:\n";
    read_personal_info();
    cout << "Please set a password: ";
    getline(cin, password);
    cin.sync();
    cout << "NEW MANAGER ADDED.\n";
}

bool manager::send_to_acme(){
    //TODO:send fees and charges over to acme?
    return true;
}

bool manager::change_password(){
    string curr_password;
    cout << "Please enter current password: ";
    getline(cin, curr_password);
    cin.sync();
    if(curr_password==password){
        return change_password(curr_password);
    }else{
        cout << "Incorrect password.\n";
        return false;
    }
}

bool manager::change_password(string curr_password){
    string new_password;
    cout << "Please enter your new password: ";
    getline(cin, new_password);
    cin.sync();
    if(new_password==curr_password){
        cout << "New password cannot be same as old password.\n";
        return false;
    }else{
        password = new_password;
        cout << "New password is: " << password << endl;
        cout << "Keep it safe in your records.\n";
        return true;
    }
}

void manager::display(ostream& out) const{
    display_personal_info();
    cout << "Your password is: " << password << endl;
}

ostream & operator << (ostream &out, const manager &source){
    source.display(out);
    return out;
}
//