/**
 * @file provider.h
 * @Kay Randall @kalyps0
 * @header file for provider class
 * @version 0.8 - add display for save to file
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PROVIDER_H
#define PROVIDER_H
#include "personal_info.h"
#include "service_list.h"

class provider: public personal_info{
public:
    provider();
    provider(int provider_id,
            const string& first_name,
            const string& last_name, 
            const string& address,
            const string& city,
            const string& state,
            int zip_code,
            const string& email,
            float weekly_payout,
            int num_services);
    /*
    provider(const provider &prov_copy);
    ~provider();
*/
    
    void load_from_file(const string& file_name); //loading service list
    void add_provider();
    float add_service(service &new_service);
    int get_num_services() const;
    void display_summary();
    void save_summary();
    void display(ostream& out) const;
    void display_for_save(ostream &out);
    friend ostream & operator << (ostream &out, const provider &prov);
    bool operator == (const provider& to_compare) const;
    bool operator < (const provider& to_compare) const;
    bool operator > (const provider& to_compare) const;

protected:
    int number_of_services;
    float weekly_payout;
    service_list services;
}; 

#endif
//