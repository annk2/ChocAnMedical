/**
 * @file service_list.h
 * @Anna Kawasaki @annk2
 * @header file for service_list class
 * @version 0.1
 * @date 2022-02-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SERVICE_LIST_H
#define SERVICE_LIST_H
#include "service.h"
#include <list>

class service_list: public service{
public:

    void add_service(const service& new_service);
    bool remove_service(const service& to_remove);
    bool search_service(const service& to_search);
    void remove_all();
    int get_size() const;
    void save_to_file_mem(ostream &out); 
    void save_to_file_prov(ostream &out); 

    int load_from_file(const string& file_name);

    void display_all(ostream &out);
    void display_all_mem(ostream &out);
    void display_all_prov(ostream &out);

    friend ostream& operator << (ostream& out, service_list& source);
private:
    list <service> s_list;
};

#endif
//