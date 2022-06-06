/**
 * @file personal_info.cpp
 * @Viktoriya Petrova @vpetrova971
 * @implementation file for the personal_info class
 * @version 0.5  - kay edit to add display for saving to file
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "personal_info.h"
using namespace std;

//Default constructor
personal_info::personal_info(){
    ID = 0;
    first_name = "";
    last_name = ""; 
    address = "";
    city = "";
    state = "";
    zip_code = 0;
    email = "";
}

//Constructor.
personal_info::personal_info(int p_id, const string& fname, const string& lname, const string& addrss,
    const string& cty, const string& st, int zip, const string& eml){
    ID = p_id;
    first_name = fname;
    last_name = lname;
    address = addrss;
    city = cty;
    state = st;
    zip_code = zip;
    email = eml;
}

//Display all personal info
void personal_info::display_personal_info() const{
    if(!ID){
        cout << "ERROR: No information on record." <<endl;
    }
    else{
        cout <<"ID: " <<ID
             << "\nName: " <<first_name <<" " <<last_name
             << "\nAddress: " <<address <<" " <<city <<" " <<state <<" " <<zip_code
             << "\nEmail: " <<email
             <<endl;
    }
}

//Take in user input.
void personal_info::read_personal_info(){
    bool flag;
    
    while(!get_ID()){}
    do{
        if(!(flag = get_fname())){
            cout <<"ERROR: Invalid name." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_lname())){
            cout <<"ERROR: Invalid name." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_address())){
            cout <<"ERROR: Invalid adress." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_city())){
            cout <<"ERROR: Invalid city." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_state())){
            cout <<"ERROR: Invalid state (Example 'OR' for 'Oregon')." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_zip())){
            cout <<"ERROR: Invalid zip code (5 digits)." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_email())){
            cout <<"ERROR: Invalid email (you@domain.com)." <<endl;
        }
    }while(!flag);
}

//Display first and last name only.
void personal_info::display_name() const{
    cout << first_name << " " << last_name;
}

//Generate ID of 9 random numbers.
bool personal_info::get_ID(){
    srand(time(NULL));
    ID = rand() % 990000000 + 100000000;
    if(!ID){
        return false;
    }
    return true;
}

//Prompt for first name and call on is_valid_name to check validity.
bool personal_info::get_fname(){
        cout <<"Enter first name: ";
        getline(cin, first_name); cin.sync();
        if(!is_valid_name(first_name)){
            return false;
        }
        return true;
}
 
//Prompt for last name and call on is_valid_name to check validity.   
bool personal_info::get_lname(){
    cout <<"Enter last name: ";
    getline(cin, last_name); cin.sync();
    if(!is_valid_name(last_name)){
        return false;
    }
    return true;
}

//Prompt for street address and check for length validity.
bool personal_info::get_address(){
    cout <<"Enter street address: ";
    getline(cin, address); cin.sync();
    if(address.length() > 25){
        return false;
    }
    return true;
}

//Prompt for city and call on is_valid_city to check validity.
bool personal_info::get_city(){
    cout <<"Enter city: ";
    getline(cin, city); cin.sync();
    if(!is_valid_city(city)){
        return false;
    }
    return true;
}

//Prompt for state and call on is_valid_state to check validity.
bool personal_info::get_state(){
    cout <<"Enter state: ";
    getline(cin, state); cin.sync();
    if(!is_valid_state(state)){
        return false;
    }
    return true;
}

//Prompt for zip code and verify length.
bool personal_info::get_zip(){
    int input = 0;
    cout <<"Enter zip code: ";
    cin >> zip_code;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }   
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(zip_code <10000 || zip_code > 99999){
        return false;
    }
    return true;
}
 
//Prompt for email and call on is_valid_email to check for validity.
bool personal_info::get_email(){
    cout <<"Enter email: ";
    getline(cin, email); cin.sync();
    if(!is_valid_email(email)){
        return false;
    }
    return true;
}

//Updates the first and last name with the passed in strings.
bool personal_info::update_name(string &new_fname, string &new_lname){
    if(new_fname.empty() || new_lname.empty()){
        return false;
    }
    if(!is_valid_name(new_fname) || !is_valid_name(new_lname)){
        return false;
    }

    first_name = new_fname;
    last_name = new_lname;
    return true;
}

//Updates the address (steer, city, state, zip) with the passed in strings. All passed in strings have to be 
//valid information or the function will terminate and return false.
bool personal_info::update_address(string &new_address, string &new_city, string &new_state, int new_zip){
    if(new_address.empty() || new_city.empty() || new_state.empty() || !new_zip){
        return false;
    }
    if(new_address.length() > 25 || !is_valid_city(new_city) || !is_valid_state(new_state) || new_zip < 10000 || new_zip > 99999){
        return false;
    }

    address = new_address;
    city = new_city;
    state = new_state;
    zip_code = new_zip;
    return true;
}

//Updates the email address with the passed in string. Calls on is_valid_email to verify that
//the passed in string has the correct format.
bool personal_info::update_email(string &new_email){
    if(new_email.empty()){
        return false;
    }
    if(!is_valid_email(new_email)){
        return false;
    }

    email = new_email;
    return true;
}

//Updates the ID number with the passed in int.
bool personal_info::is_unique_ID(int new_ID){
    return ID != new_ID;
}

//Checks that the email string has a valid (you@domain.com) format. It will return false
//if there is no character before the "@", no character before the ".", and no character after
//the ".".
bool personal_info::is_valid_email(string &email){
    regex pattern ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    if(!regex_match(email, pattern)){
        return false;
    }
    return true;
}

//Check that the name string contains only valid characters. If the name contains anything other
//than "A-Z", "a-z", apostrophe, or a dash it will return false. If the name exceeds the length it 
//will return false. 
bool personal_info::is_valid_name(string &str){
    regex pattern ("^[A-Za-z]+(((\\'|\\-|\\.)?([A-Za-z])+))?$");
    if(!regex_match(str, pattern)){
        return false;
    }
    if(str.length() > 25){
        return false;
    }   
    return true;
}

//Check that the city string contains only valid characters. It follows the same format as the is_valid_name
//function. If the string contains anything other than "A-Z", "a-z", apostrophe, or a dash it will return false. 
//If the city exceeds the length it will return false. 
bool personal_info::is_valid_city(string &city){
    regex pattern ("^[A-Za-z]+(((\\'|\\-|\\.)?([A-Za-z])+))?$");
    if(!regex_match(city, pattern)){
        return false;
    }
    if(city.length() > 14){
        return false;
    }
    return true;
}

//Check that the state contains only valid charactes. If the string contains anything other than 
//"A-Z" or "a-z" it will return false. If the string is not exaclty 2 characters it will return false. 
bool personal_info::is_valid_state(string &state){
    regex pattern ("^[A-Za-z]+$");
    if(!regex_match(state, pattern)){
        return false;
    }
    if(state.length() != 2){
        return false;
    }
    state[0] = toupper(state[0]); state[1] = toupper(state[1]);
    return true;
}

//MEMBER LIST FUNCTION OVERLOAD.
void personal_info::display_all(ostream & out) const
{
    out << "ID: " << ID << endl
        << "Name: " << first_name << " " << last_name << endl  
        << "Address: " << address << " " << city << ", " << zip_code << endl    
        << "Email: " << email << endl;
}

void personal_info::display_for_file(ostream & out){
    out << ID << ";" << first_name << ";" << last_name << ";" << address << ";" << city << ";"
    << state << ";" << zip_code << ";" << email << ";";
}

//Overloaded << operator.
ostream & operator << (ostream & out, const personal_info & source)
{
    source.display_all(out);
    return out;
}

//getters for member list save to file
int personal_info::gets_ID()
{
    return ID;
}
string personal_info::gets_fname()
{
    return first_name;
}
string personal_info::gets_lname()
{
    return last_name;
}
string personal_info::gets_address()
{
    return address;
}
string personal_info::gets_city()
{
    return city;
}
string personal_info::gets_state()
{
    return state;
}
int personal_info::gets_zip_code()
{
    return zip_code;
}
string personal_info::gets_email()
{
    return email;
}

//used to update the member and keep the mem id 
void personal_info::read_update_pi(string mem_id){
        bool flag;
    
	//use the same ID
	ID = stoi(mem_id);
    do{
        if(!(flag = get_fname())){
            cout <<"ERROR: Invalid name." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_lname())){
            cout <<"ERROR: Invalid name." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_address())){
            cout <<"ERROR: Invalid adress." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_city())){
            cout <<"ERROR: Invalid city." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_state())){
            cout <<"ERROR: Invalid state (Example 'OR' for 'Oregon')." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_zip())){
            cout <<"ERROR: Invalid zip code (5 digits)." <<endl;
        }
    }while(!flag);
    do{
        if(!(flag = get_email())){
            cout <<"ERROR: Invalid email (you@domain.com)." <<endl;
        }
    }while(!flag);
}
//
//