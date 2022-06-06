/**
 * @file personal_info.h
 * @Viktoriya Petrova @vpetrova971
 * @brief 
 * @version 0.5 - kay edit to add display for file saving
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H
#include <string>
#include <cctype>
#include <regex>
#include <iostream>
#include <limits>
using namespace std;

class personal_info
{
    public:
        personal_info();
        personal_info(int p_id,
                    const string& fname,
                    const string& lname,
                    const string& addrss,
                    const string& cty,
                    const string& st,
                    int zip,
                    const string& eml);

        void display_personal_info() const;
        void read_personal_info();
        void display_name() const;

        bool get_ID();
        bool get_fname();
        bool get_lname();
        bool get_address();
        bool get_city();
        bool get_state();
        bool get_zip();
        bool get_email();

        bool is_unique_ID(int check_ID);
        bool is_valid_name(string &str);
        bool is_valid_email(string &email);
        bool is_valid_city(string &city);
        bool is_valid_state(string &state);

        bool update_name(string &new_fname, string &new_lname);
        bool update_address(string &new_address,
                            string &new_city,
                            string &new_state,
                            int new_zip);
        bool update_email(string &new_email);

        void display_all(ostream & out) const;
        void display_for_file(ostream & out);
        friend ostream & operator << (ostream & out, const personal_info & source);

        //getters for member_list functionality to save to file
        int gets_ID();
        string gets_fname();
        string gets_lname();
        string gets_address();
        string gets_city();
        string gets_state();
        int gets_zip_code();
        string gets_email();
    
        void read_update_pi(string mem_id); //used to read in without generating new id

    protected:
        int ID; 
        string first_name;
        string last_name;
        string address;
        string city;
        string state;
        int zip_code;
        string email;
};
#endif
//