/**
 * @file directory_list.cpp

 * @Natasha Naylor @nnaylor
 * @implementation file for directory_list class 
 * @version 0.3 -finished

 * @date 2022-02-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "directory_list.h"


//adds procedure to the end of directory list. Once all procedures are in
//the procedure_list, it will be sorted into alphabetical order
void directory_list::add_procedure(const procedure& new_procedure){
    procedure_list.push_back(new_procedure);
}


//removes procedure from directory list based on procedure code
//NOTE: if you want to use this function to remove, you MUST overload == operator
//(see procedure.cpp, line 41)
bool directory_list::remove_procedure(int pro_code){
    if(!procedure_list.empty()){
        if(search(pro_code) == true){
            procedure remove_pro = retrieve(pro_code);
            procedure_list.remove(remove_pro);
            return true;
        }
        else{
            return false;
        }
    }
    else{
        cout << "The Provider Directory is empty" << endl;
        return false;
    }
}


//removes all procedures from directory list
bool directory_list::remove_all(){
    if(!procedure_list.empty()){
        procedure_list.clear();
        cout << "All Provider Directory data has been deleted" << endl;
        return true;
    }
    else{
        cout << "The Provider Directory is empty" << endl;
        return false;
    }
}


//returns the procedure information based on procedure code. This function is
//only called if a procedure has been previously found in the directory_list
procedure directory_list::retrieve(int pro_code){
    procedure find_procedure;
    for(auto it = procedure_list.begin(); it != procedure_list.end(); ++it){
        if(it->is_unique_code(pro_code) == false){
            find_procedure = *it;
        }
    }
    return find_procedure;
}


//checks if procedure is in directory list based on procedure code
bool directory_list::search(int pro_code){
    if(!procedure_list.empty()){
        for(auto it = procedure_list.begin(); it != procedure_list.end(); ++it){
            if(it->is_unique_code(pro_code) == false){
                return true;
            }
        }
        return false;
    }
    else{
        cout << "The Provider Directory is empty" << endl;
        return false;
    }     
}


//returns the number of procedures in directory list
int directory_list::get_size() const{
    return procedure_list.size();
}


//displays all procedures alphabetically by procedure name
void directory_list::display_all(ostream& out) const{
    if(!procedure_list.empty()){
        for(auto it = procedure_list.begin(); it != procedure_list.end(); ++it){
            cout << *it;
        }
    }
    else{
        cout << "The Provider Directory is empty" << endl;
    }
}


//loads directory list from external file
void directory_list::load_from_file(const string& file_name){
    ifstream in(file_name);

    string pro_name;
    int pro_code;
    float fee;
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
        procedure new_pro(pro_name, pro_code, fee);
        add_procedure(new_pro);
    }

    //once all procedures have been added to the list, sort the list in
    //alphabetical order
    //NOTE: To use sort() you MUST overload at least the < and > operators
    //(see procedure.cpp line 48)
    procedure_list.sort();
}


//overloaded insertion operator
ostream& operator << (ostream& out, const directory_list& source){
    source.display_all(out);
    return out;
}
//