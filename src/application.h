/**
 * @file application.h
 * @author Anna Kawasaki, Natasha Naylor, Jonathan Nguyen, Viktoriya Petrova, Kay Randall, Andy Truong
 * @
 * @version 0.4 - kay change login
 * @date 2022-03-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "directory_list.h"
#include "manager.h"
#include "member.h"
#include "member_list.h"
#include "personal_info.h"
#include "procedure.h"
#include "provider.h"
#include "provider_list.h"
#include "service.h"
#include "service_list.h"


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstring>
using namespace std;


/**
 * +---Login
 *     +---Menu
 *         +---Exit
 *         +---Enter After Visit Summary (Only Available to Providers)
 *         +---Add or Remove (Only Available to Managers)
 *         |   +---Back[Up a Menu]
 *         |   +---Add Member
 *         |   +---Remove Member
 *         |   +---Add Provider
 *         |   +---Remove Provider
 *         |
 *         +---Edit Information
 *         |   +---Back[Up a Menu]
 *         |   +---Edit Member
 *         |   +---Edit Provider (Only Available to Managers)
 *         |
 *         +---Generate Weekly Report [export file] (Only Available to Managers)
 *         |
 *         +---Display Directory List
 */

class application{
public:
    //Menu functionality
    void application_cold_start();


    int ask_for_login(bool manager_key);
    bool exit_or_logout(vector<vector<string>> vector_menu);


    static vector<vector<string>> build_menu();
    static void display_menu_choice(vector<vector<string>>vector_list, int menu_option);
    void menu_prompt(const vector<vector<string>>& vector_menu, bool manager_key, int ID);
    int ask_for_input();
    int get_number_input(int user_input); // NOLINT(readability-redundant-declaration)


    bool get_staff_class();
    void generate_after_visit_summary(int prov_id);
    void generate_weekly_report();
    static void error_prompt();
    static void access_denied(bool manager_key);
    int add_remove_hub(int user_input);
    int edit_info_hub(int user_input, bool manager_key);
    int generate_reports_hub(int user_input);
    int main_menu_setup(const vector<vector<string>>& vector_list,int user_input, bool manager_key, int ID);
    void populate_data();

    //procedure directory functionality
    void display_procedure_directory() const;
    bool search_procedure_directory(int pro_code);
    procedure retrieve_procedure(int pro_code);
    int get_procedure_directory_size() const;

    //provider directory functionality
    void display_provider_directory() const;
    bool search_provider_directory(int prov_code);
    provider retrieve_provider(int prov_code);
    int get_provider_directory_size() const;

    //member list functionality
    void display_all_members() const;
    bool search_member(int mem_id);
    member retrieve_member(int mem_id);
    int get_member_list_size() const;
    void save_new_mem();
    void delete_mem();
    void update_mem_all(); //updates the member but keeps ID
    
private:
    directory_list pro_directory;
    member_list membership_list;
    provider_list providers;
};


#endif //APPLICATION_H
//