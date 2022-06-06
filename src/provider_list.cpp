/*
 * @file provider_list.cpp
 * @Kay Randall @KALYPS0
 * @implementation file for provider list
 * @version 0.6 - add save to external file
 * @date 2022-03-10/
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "provider_list.h"

//adds provider to the provider_list in increasing order of provider ID
void provider_list::add_provider(const provider& new_provider){
    current_providers.push_back(new_provider);
}

//removes provider from the provider_list based on provider ID
bool provider_list::remove_provider(int provider_code){
     if(!current_providers.empty()){
        if(search(provider_code) == true){
            provider remove_provider = retrieve(remove_provider, provider_code);
            current_providers.remove(remove_provider);
            return true;
        }else{
            return false;
        }
    }else{
        cout << "There are no current providers.\n";
        return false;
    }
}

//removes all providers from provider_list
bool provider_list::remove_all(){
    if(!current_providers.empty()){
        current_providers.clear();
        cout << "All providers have been deleted.\n";
        return true;
    }else{
        cout << "There are no current providers.\n";
        return false;
    }
}

//searchs for provider based on provider ID
provider& provider_list::retrieve(provider& find_provider, int provider_code){
   
    for(auto it = current_providers.begin(); it != current_providers.end(); ++it){
        if(it->is_unique_ID(provider_code) == false){
            find_provider = *it;
        }
    }
    return find_provider;
}

//checks if procedure is in directory list based on procedure code
bool provider_list::search(int provider_code){
    if(!current_providers.empty()){
        for(auto it = current_providers.begin(); it != current_providers.end(); ++it){
            if(it->is_unique_ID(provider_code) == false){
                return true;
            }
        }
    }
    else{
        cout << "There are no current providers.\n";
    }
    return false;
     
}

//returns the number of providers in provider_list
int provider_list::get_size() const{
    return current_providers.size();
}

//displays all providers
void provider_list::display_all(ostream& out) const{
    if(!current_providers.empty()){
        cout << "List of current providers: \n\n";
        for(auto it = current_providers.begin(); it != current_providers.end(); ++it){
            cout << *it << endl;
        }
    }else{
        cout << "There are no current providers.\n";
    }
}

//display only providers that have performed services this week
void provider_list::display_selective() const{
    if(!current_providers.empty()){
        cout << "List of current providers that have services this week: \n\n";
        for(auto it = current_providers.begin(); it != current_providers.end(); ++it){
            if(it->get_num_services()!=0){
                cout << *it << endl;
            }
        }
    }else {
        cout << "There are no current providers.\n";
    }
}

//loads provider_list from external file
void provider_list::load_from_file(const string& file_name){
    //TODO
    ifstream in(file_name);

    string f_name, l_name, addr, cty, st, email, line;
    int id, zip, num_services;
    float payout;
    total_payout = 0.00;
    total_providers = 0;
    total_services = 0;

    //if there is no data in the external file, exit system
    if(!in){
        cerr << "Failed to open file " << file_name << " for reading." << endl;
        exit(1);
    }

    while(getline(in, line)){
        stringstream linestream(line);
        linestream >> id;
        linestream.ignore(1, ';');
        getline(linestream, f_name, ';');
        getline(linestream, l_name, ';');
        getline(linestream, addr, ';');
        getline(linestream, cty, ';');
        getline(linestream, st, ';');
        linestream >> zip;
        linestream.ignore(1, ';');
        getline(linestream, email, ';');
        linestream >> payout;
        linestream.ignore(1, ';');
        linestream >> num_services;
        provider new_prov(id, f_name, l_name, addr, cty, st, zip, email, payout, num_services);
        add_provider(new_prov);
        total_payout+=payout;
        total_providers++;
        total_services+=num_services;
    }

    //once all procedures have been added to the list, sort the list in
    //alphabetical order
    current_providers.sort();
}

void provider_list::save_to_file(const string & file_name){
    current_providers.sort();
    ofstream prov_list;
    prov_list.open(file_name);
    if(!current_providers.empty()){
        for(auto it = current_providers.begin(); it != current_providers.end(); ++it){
            it->display_for_save(prov_list);
            prov_list << '\n';
        }
    }
    prov_list.close();
}

bool provider_list::prov_delete_file(string prov_id)
{
    bool flag = false;
    string delete_line = prov_id; //keep the same 
    string line;
    string prov_file = "current_providers.txt";
    string temp_prov_file = "temp_prov.txt";
    ifstream file_in;
    file_in.open(prov_file);
    
    ofstream file_out;
    file_out.open(temp_prov_file);

    while(getline(file_in, line))
    {
        string id(line.begin(), line.begin() + line.find(";"));
        if(id != delete_line)
        {
            file_out << line << endl;
        }
        else
        {
            flag = true; //member remove successful
        }
    }

    file_out.close();
    file_in.close();

    remove("current_providers.txt");
    rename("temp_prov.txt", "current_providers.txt");
    return flag;
}

double provider_list::get_total_payout(){
    return total_payout;
}

int provider_list::get_total_providers(){
    return total_providers;
}

int provider_list::get_total_services(){
    return total_services;
}

ostream & operator << (ostream &out, const provider_list& source){
    //NOTE this operator is overloaded only to display full list, not selective list
    //must call display_selective() to display the selective list
    source.display_all(out);
    return out;
}
//