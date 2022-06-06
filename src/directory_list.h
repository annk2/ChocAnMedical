/**
 * @file directory_list.h
 * @Natasha Naylor @nnaylor
 * @header file for the directory_list class
 * @version 0.3 -finished
 * @date 2022-02-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DIRECTORY_LIST_H
#define DIRECTORY_LIST_H

#include "procedure.h"
#include <list>
#include <fstream>
#include <sstream>

class directory_list: public procedure{

public:

    //adds procedure to the end of directory list. Once all procedures are in
    //the procedure_list, it will be sorted into alphabetical order
    void add_procedure(const procedure& new_procedure);
    
    //removes procedure from directory list based on procedure code
    bool remove_procedure(int pro_code);

    //removes all procedures from directory list
    bool remove_all();

    //searchs for procedure based on procedure code
    procedure retrieve(int pro_code);

    //checks if procedure is in directory list based on procedure code
    bool search(int pro_code);

    //returns the number of procedures in directory list
    int get_size() const;

    //displays all procedures alphabetically by procedure name
    void display_all(ostream& out) const;

    //loads directory list from external file
    void load_from_file(const string& file_name);

    //overloaded insertion operator
    friend ostream& operator << (ostream& out, const directory_list& source);
   
protected:
    list <procedure> procedure_list; //list of procedures

};



#endif
//