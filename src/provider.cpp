/**
 * @file provider.cpp
 * @Kay Randall @kalyps0
 * @implementation file for provider class
 * @version 0.12 - add display for save to file
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "provider.h"

provider::provider():number_of_services(0),weekly_payout(0.00),services(){
}

provider::provider(int provider_id, const string& first_name, const string& last_name, const string& address, const string& city,
    const string& state, int zip_code, const string& email, float payout, int num_services):
    personal_info(provider_id, first_name, last_name, address, city, state, zip_code, email){
    weekly_payout = payout;
    number_of_services = num_services;
    //TODO: fix or consider removing from constructor. need to overload = operator -nnaylor
    //services = NULL;
}

/*
provider::provider(const provider &prov_copy): personal_info(prov_copy){
    if(prov_copy.number_of_services != 0){
        number_of_services = prov_copy.number_of_services;
    }
    if(prov_copy.weekly_payout != 0.00){
        weekly_payout = prov_copy.weekly_payout;
    }
    //TODO - need to be able to copy service_list over: need to overload == in 
    //service_list class ?
}

provider::~provider(){
    if(number_of_services != 0){
        number_of_services = 0;
    }
    if(weekly_payout != 0.00){
        weekly_payout = 0.00;
    }
     TODO: fix or consider deleting destructor? Since = operator isn't overloaded
             the following code won't compile -nnaylor
    if(services!=NULL){
        //TODO: call the desctructor for all services first
        services = NULL;
    }
    
}
*/

void provider::add_provider(){
    cout << "INFORMATION REQUIRED FOR NEW PROVIDER:\n";
    read_personal_info();
    number_of_services = 0;
    weekly_payout = 0.00;
    cout << "NEW PROVIDER ADDED.\n";
}

float provider::add_service(service & to_add){ 
    services.add_service(to_add);
    float new_service = to_add.get_fee();
    weekly_payout += new_service;
    ++number_of_services;
    cout << "One new service added. Weekly payout has been updated.\n";
    return weekly_payout;
}

int provider::get_num_services() const {
    return number_of_services;
}

void provider::display_summary(){
    //display services from service_list
    //TODO - does this need other stuff or should it call display or ?
    services.display_all_prov(cout);
}

void provider::load_from_file(const string& file_name) {
    int added = services.load_from_file(file_name);
    number_of_services += added;
}


void provider::save_summary(){
    string file_name;
    string date;
    cout << "Please enter today's date in the format as follows using only numbers 'MM_DD_YYYY_'.\n";
    cout << "Example: 03_11_2022\n";
    cout << "Please enter today's date in the specified format: ";
    getline(cin, date, '\n');
    file_name= first_name+"_"+last_name+"_"+date+".txt";
    cout << "Weekly summary report's file name is " << file_name << endl;
    ofstream report;
    report.open (file_name);
    display_all(report);
    services.save_to_file_prov(report);
    report << "Total Consultations: " << number_of_services << endl;
    report << "Total Weekly Fees: " << weekly_payout << endl;
    report.close();
}

void provider::display(ostream& out) const{
    display_personal_info();
    cout << "Number of services provided this week: " << number_of_services << endl;
    cout << "Payout for this week: " << weekly_payout << endl;
    //TODO display all services? display_summary?
}

void provider::display_for_save(ostream &out){
    display_for_file(out);
    out << weekly_payout << ";" << number_of_services << endl;
}


ostream & operator << (ostream &out, const provider &source){
    source.display(out);
    return out;
}

//not sure if this is going to work
bool provider::operator== (const provider& to_compare) const{
    return (last_name == to_compare.last_name) && (ID == to_compare.ID)
        && (number_of_services == to_compare.number_of_services);
}

//checks if provider id name comes numerically after another
bool provider::operator > (const provider& to_compare) const{
    if(ID > to_compare.ID){
        return true;
    }
    return false;
}

//checks if provider id name comes numerically before another
bool provider::operator < (const provider& to_compare) const{
    if(ID < to_compare.ID){
        return true;
    }
    return false;
}  
//