/**
 * @file provider_list.h
 * @Kay Randall @KALYPS0
 * @header file for the provider list
 * @version 0.5- add save to external file
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PROVIDER_LIST_H
#define PROVIDER_LIST_H

#include "provider.h"
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>

class provider_list: public provider{

public:

    //adds provider to the provider_list in increasing order of provider ID
    void add_provider(const provider& new_provider);

    //removes provider from the provider_list based on provider ID
    bool remove_provider(int provider_code);

    //removes all providers from provider_list
    bool remove_all();

    provider& retrieve(provider& find_provider, int provider_code); 

    //searchs for provider based on provider ID
    bool search(int provider_code);

    //returns the number of providers in provider list
    int get_size() const;

    //displays all providers
    void display_all(ostream& out) const;
    //displays only providers who had services that week
    void display_selective() const;

    //loads provider_list from external file
    void load_from_file(const string& file_name);
    void save_to_file(const string & file_name);
    bool prov_delete_file(string prov_id);

    double get_total_payout();
    int get_total_providers();
    int get_total_services();

    friend ostream & operator << (ostream &out, const provider_list &source);

protected:
    list <provider> current_providers;
    double total_payout;
    int total_providers;
    int total_services;
};

#endif
//