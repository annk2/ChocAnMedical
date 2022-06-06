/**
 * @file member.h
 * @Kay Randall @kalyps0
 * @header file for member class
 * @version 0.10 - add display for save to file
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MEMBER_H
#define MEMBER_H
#include "personal_info.h"
#include "service_list.h"


class member: public personal_info {
public:
    member(); //default constructor

    //constructor 
    member(int member_id,
            const string& first_name,
            const string& last_name,
            const string& address,
            const string& city,
            const string& state,
            int zip_code,
            const string& email,
            const string& member_status,
            int valid,
            float fee);     

    bool add_member();
    void add_service(service &new_service);
    void display_summary();
    void display_status() const;
    void save_summary();
    bool check_validity();
    bool check_overdue();
    void display(ostream& out) const;
    void display_for_save(ostream &out);

    void load_from_file(const string& file_name); //loading service list

    //overloaded operators
    bool operator == (const member& to_compare) const;
    bool operator < (const member& to_compare) const;
    bool operator > (const member& to_compare) const;
    friend ostream & operator << (ostream &out, const member &source);

    //adding getters for member_list save to file
    bool gets_validity();
    float gets_membership_fee();
    string gets_status();
    bool gets_overdue();

    //for member_list update func
    void update_info(string mem_id); //used to update members_list.txt

protected:
    bool validity;
    float membership_fee;
    string status;
    bool overdue;
    
    service_list member_summary;
};

#endif
//