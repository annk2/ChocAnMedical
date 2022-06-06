/**
 * @file member_list.cpp
 * @author Andy Truong (truong7@pdx.edu)
 * @brief 
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "member_list.h"

//adds a member to the linked list
void member_list::add_member(const member & new_member)
{
    m_list.push_back(new_member);
}

//removes a member from the link list by member ID
bool member_list::remove_member(int mem_number)
{
    if(!m_list.empty())
    {
        if(search(mem_number) == true)
        {
            member remove_mem = retrieve(remove_mem, mem_number);
            m_list.remove(remove_mem);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout << "The Member List is empty" << endl;
        return false;
    }
}

//removes all members in the list
bool member_list::remove_all()
{
    if(!m_list.empty())
    {
        m_list.clear();
        cout << "All Member data has been deleted" << endl;
        return true;
    }
    else
    {
        cout << "The Member List is empty" << endl;
        return false;
    }
}

//gets the size of the members list 
int member_list::get_size() const
{
    int list_size = m_list.size();
    return list_size;
}

//displays all members in the list
void member_list::display_all(ostream & out) const
{
    cout << "List of members: " << endl << endl;
    if(!m_list.empty())
    {
        for(auto it = m_list.begin(); it != m_list.end(); ++it)
        {
            cout << *it << endl;
        }
    }
    else
    {
        cout << "The Member List is empty " << endl;
    }

}

//retrieves a member's info given the member ID and returns it
member& member_list::retrieve(member& find_member, int mem_number)
{
    for(auto it = m_list.begin(); it != m_list.end(); ++it)
    {
        if(it->is_unique_ID(mem_number) == false){
            find_member = *it;
        }
    }
    return find_member;
}

//searches for a member by ID to see if they exist
bool member_list::search(int member_code){
    if(!m_list.empty())
    {
        for(auto it = m_list.begin(); it != m_list.end(); ++it)
        {
            if(it->is_unique_ID(member_code) == false)
            {
                return true;
            }
        }
        return false;
    }
    else{
        cout << "The Member List is empty" << endl;
        return false;
    }     
}

//loads in the list of members from an external data file 
void member_list::load(const string & file_name)
{
    ifstream file_in(file_name);
 
    //member variables
    int mem_id;
    string first_name;
    string last_name;
    string address;
    string city;
    string state;
    int zip_code;
    string email;
    string member_status;
    int valid;
    float fee;
    
    string line;
 
    //error check for open file
    if(!file_in)
    {
        cerr << "Failed to open file " << file_name << " for reading.";
        exit(1);
    }

    while(getline(file_in, line))
    {
        stringstream linestream(line);
        linestream >> mem_id;
        linestream.ignore(1,';');
        getline(linestream, first_name, ';');
        getline(linestream, last_name, ';');
        getline(linestream, address, ';');
        getline(linestream, city, ';');
        getline(linestream, state, ';');
        linestream >> zip_code;
        linestream.ignore(1, ';');
        getline(linestream, email, ';');
        getline(linestream, member_status, ';'); 
        linestream >> valid;  
        linestream.ignore(1,';'); 
        linestream >> fee;
        member new_mem(mem_id, first_name, last_name, address, city, state, zip_code, email, member_status, valid, fee);
        add_member(new_mem); 
    }

    //<< and >> operator overloaded in both personal_info and member to sort
    m_list.sort();
}

void member_list::save_to_file(const string & file_name){
    m_list.sort();
    ofstream mem_list;
    mem_list.open(file_name);
    if(!m_list.empty()){
        for(auto it = m_list.begin(); it != m_list.end(); ++it){
            it->display_for_save(mem_list);
            mem_list << '\n';
        }
    }
    mem_list.close();
}

//writes to the external text file with a new members info
void member_list::save_new_member(const string & file_name) const
{
    fstream file_out;

    file_out.open(file_name, fstream::app);

    //create the new member and add info 
    member new_member;
    new_member.add_member();

    if(file_out.is_open())
    {
        file_out << new_member.gets_ID() << ';' << new_member.gets_fname() << ';' << new_member.gets_lname() << ';' 
        << new_member.gets_address() << ';' << new_member.gets_city() << ';' << new_member.gets_state() << ';' 
        << new_member.gets_zip_code() << ';' << new_member.gets_email() << ';' << new_member.gets_status() << ';' 
        << new_member.gets_validity() << ';' << new_member.gets_membership_fee() << endl;
        file_out.close();
    }
    return;
}

//keeps the same ID and is given option to update all info
void member_list::update_member_file(string same_id) 
{
    fstream file_out;

    string m_list_file = "member_list.txt";
    file_out.open(m_list_file, fstream::app);

    //create the new member and add info 
    member update_member;
    update_member.update_info(same_id);

    if(file_out.is_open())
    {
        file_out << update_member.gets_ID() << ';' << update_member.gets_fname() << ';' << update_member.gets_lname() << ';' 
        << update_member.gets_address() << ';' << update_member.gets_city() << ';' << update_member.gets_state() << ';' 
        << update_member.gets_zip_code() << ';' << update_member.gets_email() << ';' << update_member.gets_status() << ';' 
        << update_member.gets_validity() << ';' << update_member.gets_membership_fee() << endl;
        file_out.close();
    }
    return;
}

bool member_list::mem_delete_file(string mem_id)
{
    bool flag = false;
	string delete_line = mem_id; //keep the same 
	string line;
	string m_list_file = "member_list.txt";
	string m_temp_file = "mem_temp.txt";
	ifstream file_in;
	file_in.open(m_list_file);
	
	ofstream file_out;
	file_out.open(m_temp_file);

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

	remove("member_list.txt");
	rename("mem_temp.txt", "member_list.txt");
    return flag;
}

void member_list::update_mem_info(string m_id)
{
	//ONLY THING WE NEED IN THIS UPDATE FUNCTION 
	bool delete_flag = mem_delete_file(m_id);
	update_member_file(m_id);
    
    if(delete_flag == true)
        cout << "Member successfully updated " << endl;
}

ostream & operator << (ostream & out, const member_list & source)
{
    source.display_all(out);
    return out;
}
//
//