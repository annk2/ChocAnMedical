/**
 * @file manager.h
 * @Kay Randall @kalyps0
 * @header file for manager class
 * @version 0.4 - little changes
 * @date 2022-02-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MANAGER_H
#define MANAGER_H
#include "personal_info.h"

class manager: public personal_info {
public:
    manager();
    manager(int manager_id,
            const string& first_name,
            const string& last_name,
            const string& address,
            const string& city,
            const string& state,
            int zip_code,
            const string& email,
            const string& pswd);

    void add_manager();
    bool send_to_acme();
    bool change_password();
    void display(ostream& out) const;
    friend ostream & operator << (ostream &out, const manager &source);

private:
    string password;
    bool change_password(string curr_password);
};

#endif
//