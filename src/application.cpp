/**
 * @file application.cpp
 * @author Anna Kawasaki, Natasha Naylor, Jonathan Nguyen, Viktoriya Petrova, Kay Randall, Andy Truong
 * @brief
 * @version 0.5 -kay fix edit_info_hub function
 * @date 2022-03-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "application.h"

#include <utility>


void application::application_cold_start() {
    vector<vector<string>> vector_menu = build_menu();
    bool manager_key;
    bool stay_connected = true;
    while (stay_connected) {
        display_menu_choice(vector_menu, 9);
        manager_key = get_staff_class();
        display_menu_choice(vector_menu, 9);
        int ID = ask_for_login(manager_key);
        display_menu_choice(vector_menu, 9);
        menu_prompt(vector_menu,manager_key, ID);
        display_menu_choice(vector_menu, 9);
        stay_connected = exit_or_logout(vector_menu);
    }
    /*
    providers.save_to_file("current_providers.txt");
    membership_list.save_to_file("member_list.txt");
    */
}

int application::ask_for_login(bool manager_key){
    int staff_id = 0;
    string password;
    cout << "\n===== Login =====" << std::endl;
    if(!manager_key){
        cout << "Provider ID: ";
        cin >> staff_id;
        cin.ignore();
        if(providers.search(staff_id)){
            provider logged_in = providers.retrieve(logged_in, staff_id);
            cout << "Login successful. Logged in as ";
            logged_in.display_name();
            cout << endl;
            return staff_id;
        }
    } else if (manager_key){
        cout << "Manager ID: ";
        cin >> staff_id;
        cin.ignore();
        cout << "Password: ";
        getline(cin, password);
    }
    cout << "\n";
    return staff_id;
}


bool application::exit_or_logout(vector<vector<string>> vector_menu) {
    display_menu_choice(std::move(vector_menu), 8); //exit confirmation text
    if(ask_for_input() == 0) {
        return false;
    } else {
        return true;
    }

}

vector<vector<string>> application::build_menu() {

    vector <string> logout_text {
        "===== Logging Out System ====="
    };

    vector <string> after_summary_text{
        "===== After Visit Summary ====="
    };

    vector <string> weekly_report_text{
        "======= Generate Report =======",
        "Back [To Main Menu]",
        "Generate Week Report",
        "Generate Provider Report",
        "Generate Member Report"
    };
    //MAIN MENU
    vector <string> menu_main_list{
        "========== Menu ===========",
        "Exit",
        "Enter After Visit Summary",
        "Add or Remove",
        "Edit Information",
        "Generate Weekly Report",
        "Display Directory List"
    };
    // ADD REMOVE
    vector <string> menu_add_remove_list{
        "======== Add/Remove ========",
        "Back [To Main Menu]",
        "Add Member",
        "Remove Member",
        "Add Provider",
        "Remove Provider"
    };
    vector <string> menu_information_list{
        "===== Edit Information =====",
        "Back [To Main Menu]",
        "Edit Member",
        "Edit Provider",
    };

    //EDIT INFO
    vector <string> menu_edit_option_list{
        "===== Edit Information =====",
        "Back [To Main Menu]",
        "Edit Name",
        "Edit Address",
        "Edit Email"
    };
    vector <string> directory_list_display{
        "====== Directory List ======",
    };

    vector <string> billing_display{
        "====== Billing Invoice ======",
    };

    vector <string> exit_display{
        "======= Confirmation =======",
        "Exit",
        "Logout"
    };
    vector <string> decorative_divider {
        "============================================================"
    };


    vector <vector<string>> vector_list;

    vector_list.push_back(logout_text);           //0
    vector_list.push_back(after_summary_text);    //1
    vector_list.push_back(menu_add_remove_list);  //2
    vector_list.push_back(menu_information_list); //3
    vector_list.push_back(weekly_report_text);    //4
    vector_list.push_back(directory_list_display);//5
    vector_list.push_back(menu_main_list);        //6
    vector_list.push_back(menu_edit_option_list); //7
    vector_list.push_back(exit_display);          //8
    vector_list.push_back(decorative_divider);    //9

    return vector_list;
}


void application::display_menu_choice(vector<vector<string>> vector_list,int menu_option) {
    int j = -1;

    cout << "\n";
    for(vector<string>::iterator i = vector_list[menu_option].begin(); i != vector_list[menu_option].end(); ++i) {
        if(j != -1) {
            cout <<"    "<< j << ". " << *i << endl;
        } else {
            cout << *i << endl;
        }
        ++j;
    }
    cout << "\n";

}


void application::menu_prompt(const vector<vector<string>>& vector_menu, bool manager_key, int ID) {
    int main_menu_input = 6;
    display_menu_choice(vector_menu, main_menu_input);
    while(main_menu_input != 0) {
        main_menu_input = main_menu_setup(vector_menu,ask_for_input(),manager_key, ID);
    }
}


int application::ask_for_input() {
    int userInput = 0;
    cout << "Enter Option: ";
    return get_number_input(userInput);
}


int application::get_number_input(int user_input) { // NOLINT(misc-no-recursion)
    cin >> user_input;
    cin.ignore(100,'\n'); 

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Input: \n \n Enter option: ";
        return get_number_input(user_input);
    }

    return user_input;
}


bool application::get_staff_class() {
   //TODO
   //WORKAROUND FOR TESTING
    int input = 0;
    cout << "\n";
    cout << "Please choose how you are logging in (enter 1 or 2).\n";
    cout << "1. Manager\n";
    cout << "2. Provider\n\n";
    cout << "Enter Option: ";
    cin >> input;
    if(input == 1) {
        return true;
    } else if (input == 2) {
        return false;
    } else {
        error_prompt();
        return get_staff_class();
    }
}


//functionality for providers to bill for a service on the provider's terminal
void application::generate_after_visit_summary(int prov_id) {
    //TODO: Add the necessary function calls and code for Steps 2, 3, 6, 7

    /*Step 1: Provider enters in Member ID
                -Case 1: if Member ID is valid and membership is active, display "Validated"
                         result: continue to Step 2
                -Case 2: if Member ID is invalid, display "Invalid number"
                         result: prompt provider to enter ID again
                -Case 3: if Member ID is found but membership is suspended, display "suspended"
                         result: exit function, unable to continue
    */

    provider curr_provider = providers.retrieve(curr_provider, prov_id);

    int member_id;
    cout << "Enter member ID: ";
    cin >> member_id;
    cin.ignore();
    while(!membership_list.search(member_id)){
        cout << "Invalid member ID. Enter valid member ID: ";
        cin >> member_id;
    }

    member curr_member;
    curr_member = membership_list.retrieve(curr_member, member_id);
    if(curr_member.check_validity()){
        cout << "Validated.\n";
    } else {
        cout << "Member exists, but membership is not valid. Membership status: ";
        curr_member.display_status();
        cout << endl;
        return;
    }

    /*
      Step 2: Provider enters DOS (MM-DD-YYYY)
    */

    //Step 3: Provider views the Provider Directory to locate appropriate procedure code
    display_provider_directory();
    
    //Step 4: Provider enters procedure code
    int pro_code = 0;
    procedure find_pro;
    while(pro_code == 0){
        cout << "Enter the procedure code corresponding to the service provided: ";
        cin >> pro_code;
        cin.ignore(100, '\n');

        //Step 5: If procedure code is in the provider directory, display for verification
        if(search_procedure_directory(pro_code) == true){ //made it so it's "search_PROCEDURE_directory"
                                                          //it was named "search_directory" - Andy
            find_pro = retrieve_procedure(pro_code);
            find_pro.display_name();
            cout << "\nIs this service correct? Enter Y for yes or N for no: ";
            char pro_response;
            cin >> pro_response;
            cin.ignore(100, '\n');
            if(pro_response == 'Y' || pro_response == 'y'){
                //Do nothing, continue to Step 6
            }
            else if(pro_response == 'N' || pro_response == 'n'){
                //restart loop
                cout << endl;
                pro_code = 0;
            }
            else{
                //restart loop
                error_prompt();
                pro_code = 0;
            }
        }
        else{
            //restart loop
            error_prompt();
            pro_code = 0;
        }
    }

    string member_name = curr_member.gets_fname() + " " + curr_member.gets_lname();
    string provider_name = curr_provider.gets_fname() + " " + curr_provider.gets_lname();

    //Step 6: Prompt provider to enter optional comments
    //TODO: Make sure service is recorded in provider's service_list and member's service_list
    service to_add(find_pro, member_id, member_name, prov_id, provider_name);
    to_add.read_date();
    bool exit = false;
    while(!exit) {
        cout << "\nWould you like to add a comment for this service? Enter Y for yes or N for no: ";
        char com;
        cin >> com;
        cin.ignore(100, '\n');
        if(com == 'Y' || com == 'y'){
            to_add.read_comment();
            exit = true;
        }
        else if(com == 'N' || com == 'n'){
            exit = true;
        }
        else{
            //restart loop
            error_prompt();
        }
    }

    curr_provider.add_service(to_add);
    curr_member.add_service(to_add);

    cout << "Generating After Visit Summary \n";
    //Step 7: Display after visit summary after it has been entered in by provider
    to_add.display_prov(cout);
}

int application::generate_reports_hub(int user_input) {
    int ID;
    if(user_input == 1) {
       generate_weekly_report();
    } else if (user_input == 2) {
       //TODO: Provider Report
                cout << "Please Enter the provider ID: ";
                cin >> ID;
                cin.ignore(100, '\n');
                while(!providers.search(ID)){
                    cout << "Invalid provider ID. Enter valid provider ID: ";
                    cin >> ID;
                    cin.ignore(100, '\n');
                }
                provider curr_provider;
                curr_provider = providers.retrieve(curr_provider, ID);
                curr_provider.save_summary();
    } else if ( user_input == 3){
       //TODO: Member Report
                cout << "Please Enter the member ID: ";
                cin >> ID;
                cin.ignore(100, '\n');
                while(!membership_list.search(ID)){
                    cout << "Invalid member ID. Enter valid member ID: ";
                    cin >> ID;
                    cin.ignore(100, '\n');
                }
                member curr_member;
                curr_member = membership_list.retrieve(curr_member, ID);
                curr_member.save_summary();
    } else {
        error_prompt();
    }
    return 0;
}

void application::generate_weekly_report() {
    //TODO: FUNCTION GOES HERE
    //display current provider's list of services 
    providers.save_to_file("EFT.txt");

   cout << "Generating Weekly Report...\n";
}


void application::error_prompt() {
    cout << "Invalid Input\n";
}


void application::access_denied(bool manager_key) {
    if(manager_key) {
        cout << "Access Denied: Must be Provider to access this option.\n";
    } else {
        cout << "Access Denied: Must be Manager to access this option.\n";
    }
}


int application::add_remove_hub(int user_input) { 
    if(user_input == 1) {       //testing member_list functions from 1 and 2
        cout << "Add Member\n";
    
        save_new_mem(); //saves a new member into the member_list.txt
        cout << "New member added successfully\n";
    } else if(user_input == 2) {

        delete_mem(); //deletes a curr member by member id
        cout << "Member deleted successfully\n";
    } else if(user_input == 3) {
        cout << "Add Provider\n";
        provider new_provider;
        new_provider.add_provider();
        providers.add_provider(new_provider);
    } else if(user_input == 4) {
        string remove;
        cout << "Remove Provider\n";
        cout << "Please enter ID of provider to be removed: ";
        cin >> remove;
        cin.ignore(100, '\n');
        if(providers.prov_delete_file(remove)){
            cout << "Provider removed.\n";
        }else{
            cout << "Error while trying to remove provider.\n";
        }
    } else {
        error_prompt();
    }
    return 0;
}

int application::edit_info_hub(int user_input, bool manager_key) {
    int to_edit = 0;
    int id_to_edit = 0;
    int menu_choice = 0;

    while(user_input!=1 && user_input!=2){
        cout << "Invalid input. Are you needing to edit a member's (1) or a provider's (2) information? Enter 1 or 2: ";
        cin >> to_edit;
    }
    //Editing member info
    if(user_input==1){
       update_mem_all(); //updates a member (keeps there id and allowed to edit other variables)
    } 
    else if (user_input==2){ //Editing provider info
        cout << "Enter the providers's ID: ";
        cin >> id_to_edit;
        cin.ignore();
        while(!providers.search(id_to_edit)){
            cout << "Provider ID not in list of providers. Please enter ID of current provider: ";
            cin >> id_to_edit;
            cin.ignore();
        }
        provider editing = providers.retrieve(editing, id_to_edit);
        cout << "Are you editing the providers's name (1), address (2), or email (3)?\n";
        cout << "Please enter 1, 2, or 3: ";
        cin >> menu_choice;
        cin.ignore();
        while(menu_choice!=1 && menu_choice!=2 && menu_choice!=3){
            cout << "Please enter a valid option.\n";
            cout << "Are you editing the provider's name (1), address (2), or email (3)?\n";
            cout << "Please enter 1, 2, or 3: ";
            cin >> menu_choice;
            cin.ignore();
        }
        if(menu_choice==1){
            editing.get_fname();
            editing.get_lname();
        } else if(menu_choice==2){
            editing.get_address();
            editing.get_city();
            editing.get_state();
            editing.get_zip();
        } else if(menu_choice==3){
            editing.get_email();
        }
    }
    cout << "Exiting edit hub...\n";
    return 0;
}

int application::main_menu_setup(const vector<vector<string>>&vector_list, int user_input, bool manager_key, int ID) {
    int user_input_add_remove;
    int user_input_edit_info;
    int user_input_reports;
        if (user_input == 0) {
            display_menu_choice(vector_list, 9);
            display_menu_choice(vector_list, user_input);
            return user_input;
        } else if(user_input == 1){ //AFTER VISIT SUMMARY
            display_menu_choice(vector_list, 9);
            if(!manager_key) {
                generate_after_visit_summary(ID);
            } else {
                access_denied(manager_key);
            }
        }
        else if(user_input == 2) { //ADD / REMOVE PROVIDER OR  MANAGER
            display_menu_choice(vector_list, 9);
            if(manager_key) {
                display_menu_choice(vector_list, user_input);
                user_input_add_remove = ask_for_input();
                while (user_input_add_remove != 0) {
                    user_input_add_remove =  add_remove_hub(user_input_add_remove);
                }
            } else {
                access_denied(manager_key);
            }
        } else if (user_input == 3) { // EDIT PROVIDER OR MEMBER
            display_menu_choice(vector_list, 9);
            display_menu_choice(vector_list, user_input);
            user_input_edit_info = ask_for_input();
            while (user_input_edit_info != 0) {
                user_input_edit_info =  edit_info_hub(user_input_edit_info, manager_key);
            }
        } else if (user_input == 4) { // GENERATE REPORT
            display_menu_choice(vector_list, 9);
            display_menu_choice(vector_list,user_input);
            user_input_reports = ask_for_input();
            if(manager_key) {
                while (user_input_reports != 0) {
                    user_input_reports = generate_reports_hub(user_input_reports);
                }
            } else {
                access_denied(manager_key);
            }
        } else if (user_input == 5) {
            display_menu_choice(vector_list, 9);
            display_procedure_directory();
        } else {
            display_menu_choice(vector_list, 9);
            error_prompt();
        }

    display_menu_choice(vector_list, 9);
    display_menu_choice(vector_list, 6);

        return user_input;
}


//populates the provider directory, the membership record, and the provider record
void application::populate_data(){
    //Loading in provider directory
    string pro_directory_file = "provider_directory.txt";
    pro_directory.load_from_file(pro_directory_file);

    //Loading current providers
    string provider_list_file = "current_providers.txt";
    providers.load_from_file(provider_list_file);

    //Loading ChocAn members
    string m_list_file = "member_list.txt";
    membership_list.load(m_list_file);

    //Loading Sample Data
    //provider jt = providers.retrieve(455303945);
    //jt.load_from_file("prov1services.txt");
    //provider jt2 = providers.retrieve(455303945);
    //jt2.display_summary();

    //provider ls = providers.retrieve(531209765);
    //ls.load_from_file("prov2services.txt");

    /*
    member jd;
    jd = membership_list.retrieve(jd, 123456789);
    jd.load_from_file("mem1services.txt");
    //jd.display_summary();
    member jd2;
    jd2 = membership_list.retrieve(jd2, 123456789);
    jd2.display_summary();
    */
}


//PROCEDURE DIRECTORY FUNCTIONS***************************
//displays the directory list of procedures
void application::display_procedure_directory() const{
    cout << setw(50) << "Procedure Directory\n";
    cout << setw(79) << setfill('-') << "" << "\n";
    cout << setw(37) << left << setfill(' ') << "Procedure Name"
         << setw(25) << "Procedure Code"
         << setw(20) << "Service Fee";
    cout << setw(80) << setfill('-') << "\n";
    cout << setfill(' ') << "\n";
    cout << pro_directory;
    cout << setw(79) << setfill('-') << "" << "\n";
}


//checks if procedure is in provider directory based on procedure code
bool application::search_procedure_directory(int pro_code){
    return pro_directory.search(pro_code);
}


//returns procedure information based on procedure code. This function is
//only called if a procedure has been previously located in the provider directory
procedure application::retrieve_procedure(int pro_code){
    return pro_directory.retrieve(pro_code);
}


//returns the number of procedures in directory list
int application::get_procedure_directory_size() const{
    return pro_directory.get_size();
}

//PROVIDER DIRECTORY FUNCTION******************************
//displays the current list of providers
void application::display_provider_directory() const{
    cout << "Current Providers and their information:\n";
    cout << providers;
}


//checks if provider is in provider directory based on provider code
bool application::search_provider_directory(int prov_code){
    return providers.search(prov_code);
}


//returns the number of providers in list
int application::get_provider_directory_size() const{
    return providers.get_size();
}

//FOR MEMBER LIST FUNCTIONS **********************************************************
void application::display_all_members() const
{
    cout << membership_list;
}

bool application::search_member(int mem_id)
{
    return membership_list.search(mem_id);
}

int application::get_member_list_size() const
{
    return membership_list.get_size();
}

//saves a member to the external data file 
void application::save_new_mem()
{
    string m_list_file = "member_list.txt";
    membership_list.save_new_member(m_list_file);
}

//delete a member from the member data base(member_list.txt)
void application::delete_mem()
{
	string mem_id;
	cout << "Enter in the member ID to be removed: ";
	cin >> mem_id;
	cin.ignore(100,'\n');

	membership_list.mem_delete_file(mem_id);
}

//updates all the info for a single member given the ID matches that member
void application::update_mem_all()
{
	string mem_id;
	cout << "Enter in the member ID you want to update: ";
	cin >> mem_id;
	cin.ignore(100,'\n');

	membership_list.update_mem_info(mem_id);
}
//