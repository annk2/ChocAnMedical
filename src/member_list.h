/**
 * @file member_list.h
 * @author Andy Truong (truong7@pdx.edu)
 * @brief 
 * @version 0.1
 * @date 2022-02-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MEMBER_LIST_H
#define MEMBER_LIST_H

#include "member.h"
#include <list>
#include <fstream>
#include <sstream>


class member_list: public member
{
    public:
        void add_member(const member & new_member);
        bool remove_member(int mem_number);
        bool remove_all();
        int get_size() const;
        void display_all(ostream & out) const;
        //member retrieve(int mem_number);
        //member * & retrieve(int mem_number);
        member& retrieve(member& find_member,int mem_number);
        bool search(int member_code);
        void load(const string & file_name);

        void save_new_member(const string & file_name) const; //writes to external txt file   
        void update_member_file(string same_id); //updates a members info and keeps ID   
        bool mem_delete_file(string mem_id); //deletes a member from database
        void update_mem_info(string mem_id); //gets rid of prev info and adds updated info
        void load_from_file(const string& file_name);
        void save_to_file(const string & file_name);

        friend ostream & operator << (ostream & out, const member_list & source);
    protected:
        list<member> m_list; 
};

#endif
//