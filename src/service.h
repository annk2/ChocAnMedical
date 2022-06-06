/**
 * @file service.h
 * @Anna Kawasaki @annk2
 * @header file for service class
 * @version 0.2
 * @date 2022-02-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef SERVICE_H
#define SERVICE_H

#include "procedure.h"

class member;
class provider;

class service: public procedure{

public:
    service();

    service(procedure &proc, int m_id, string &m_name, int p_id, string &p_name);
    service(procedure &new_proc, string cur_date, string dos, int m_id, string m_name, int p_id, string p_name, string com);

    //overloaded comparison operator
    bool operator == (const service& to_compare) const;

    //checks if service DOS is before another
    bool operator < (const service& to_compare) const;

    //checks if service DOS is after another
    bool operator > (const service& to_compare) const;

    void read_date();
    void read_comment();

    void display(ostream &out) const;
    void display_prov(ostream &out) const;
    void display_mem(ostream &out) const;

    friend ostream& operator << (ostream& out, const service& source);

protected:
    string reformat_date(const string &date) const;
    bool is_valid_date(string &date);
    int compare_DOS(const service & to_compare) const;

    string current_date;
    string DOS;
    int member_id;
    int provider_id;
    string provider_name;
    string member_name;
    string comments;
}; 

#endif
//