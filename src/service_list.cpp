/**
 * @file service_list.cpp
 * @
 * @implementation of service_list 
 * @version 0.2
 * @date 2022-03-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "service_list.h"


void service_list::add_service(const service &new_service)
{
    s_list.push_back(new_service);
}

//removes service from service list
bool service_list::remove_service(const service &to_remove){
     if(!s_list.empty()){
        if(search_service(to_remove) == true){
            s_list.remove(to_remove);
            return true;
        }else{
            return false;
        }
    }else{
        cout << "The Service List is empty." << endl;
        return false;
    }
}

//checks if service is in service list
bool service_list::search_service(const service &to_find){
    if(!s_list.empty()){
        for(auto it = s_list.begin(); it != s_list.end(); ++it){
            if(*it == to_find)
                return true;
            }
        return false;
        }
    else{
        cout << "The Service List is empty." << endl;
        return false;
    }     
}


//removes all services from service list
void service_list::remove_all(){
    if(!s_list.empty()){
        s_list.clear();
    }
    else{
        cout << "The Service List is empty." << endl;
    }
}

int service_list::get_size() const
{
    return s_list.size();
}

//display all services (manager format so all information is visible)
void service_list::display_all(ostream &out) 
{
    s_list.sort();
    out << "List of services: " << endl << endl;
    if(!s_list.empty())
    {
        for(auto it = s_list.begin(); it != s_list.end(); ++it)
        {
            out << *it << endl;
        }
    }
    else
    {
        cout << "The Service List is empty." << endl;
    }
}

//display all services (member format)
void service_list::display_all_mem(ostream &out) 
{
    s_list.sort();
    out << "List of services: " << endl << endl;
    if(!s_list.empty())
    {
        for(auto it = s_list.begin(); it != s_list.end(); ++it)
        {
            it->display_mem(out);
        }
    }
    else
    {
        cout << "The Service List is empty." << endl;
    }
}

//display all services (provider format)
void service_list::display_all_prov(ostream &out) 
{
    s_list.sort();
    out << "List of services: " << endl << endl;
    if(!s_list.empty())
    {
        for(auto it = s_list.begin(); it != s_list.end(); ++it)
        {
            it->display_prov(out);
        }
    }
    else
    {
        cout << "The Service List is empty." << endl;
    }
}

int service_list::load_from_file(const string& file_name){
    int count = 0;
    ifstream in(file_name);

    string pro_name;
    int pro_code;
    float fee;

    string cur_date;
    string dos;
    int m_id;
    int p_id;
    string p_name;
    string m_name;
    string com;

    string line;

    //if there is no data in the external file, exit system
    if(!in){
        cerr << "Failed to open file " << file_name << " for reading." << endl;
        exit(1);
    }

    while(getline(in, line)){
        stringstream linestream(line);
        getline(linestream, pro_name, ';');
        linestream >> pro_code;
        linestream.ignore(1, ';');
        linestream >> fee;
        linestream.ignore(1, ';');
        getline(linestream, cur_date, ';');
        getline(linestream, dos, ';');
        linestream >> m_id;
        linestream.ignore(1, ';');
        linestream >> p_id;
        linestream.ignore(1, ';');
        getline(linestream, p_name, ';');
        getline(linestream, m_name, ';');
        getline(linestream, com, ';');
        procedure new_proc(pro_name, pro_code, fee); //constructor
        service new_service (new_proc, cur_date, dos, m_id, m_name, p_id, p_name, com);
        add_service(new_service);
        ++count;
    }

    return count;
}


//generates report for member
void service_list::save_to_file_mem(ostream &out) {
    s_list.sort();
    display_all_mem(out);
}

//generates report for provider
void service_list::save_to_file_prov(ostream &out) {
    s_list.sort();
    display_all_prov(out);
}

ostream &operator<<(ostream &out, service_list &source) {
    source.display_all(out);
    return out;
}
//