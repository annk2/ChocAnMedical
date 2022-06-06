/**
 * @file service.cpp
 * @author your name (you@domain.com)
 * @Anna Kawasaki @annk2
 * @implementation file for service class
 * @version 0.1
 * @date 2022-02-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "service.h"

service::service() : current_date(""), DOS(""), member_id(0), member_name(""), provider_id(0), provider_name(""), comments("") {}

service::service(procedure &proc, int m_id, string &m_name, int p_id, string &p_name): procedure(proc), current_date(""), DOS(""), member_id(m_id), member_name(m_name), provider_id(p_id), provider_name(p_name), comments("") {}

service::service(procedure &proc, string cur_date, string dos, int m_id, string m_name, int p_id, string p_name, string com): procedure(proc), current_date(cur_date), DOS(dos), member_id(m_id), member_name(m_name), provider_id(p_id), provider_name(p_name), comments(com) {}

//display (manager version, displays all information)
void service::display(ostream &out) const
{
        display_normal(out);
        out << endl << endl;
        out << "Date of Service: " << DOS << endl;
        out << "Date Entered: " << current_date << endl;
        out << "Member Name: " << member_name << endl;
        out << "Member ID: " << member_id << endl;
        out << "Provider ID: " << provider_id << endl;
        out << "Provider Name: " << provider_name << endl;
        out << "Comments: " << endl
            << comments << endl << endl;
}

//display (provider version)
void service::display_prov(ostream &out) const
{
        display_normal(out);
        out << endl;
        out << "Date of Service: " << DOS << endl;
        out << "Date Entered: " << current_date << endl;
        out << "Member Name: " << member_name << endl;
        out << "Member ID: " << member_id << endl;
        out << "Comments: " << endl
            << comments << endl << endl;
}

//display (member version)
void service::display_mem(ostream &out) const
{
        out << "Service Name: ";
        display_name();
        out << endl;
        out << "Date of Service: " << DOS << endl;
        out << "Provider Name: " << provider_name << endl;
        out << endl;
}

//compares DOS, used for sorting
int service::compare_DOS(const service &to_compare) const
{
        string reformat_DOS = reformat_date(DOS);
        string reformat_to_compare = reformat_date(to_compare.DOS);

        if (reformat_DOS > reformat_to_compare){
                return 1;
        }
        if (reformat_DOS < reformat_to_compare){
                return -1;
        }
        return 0;
}

// overloaded comparison operator
//compares all information for service
bool service::operator==(const service &to_compare) const
{
        return (current_date == to_compare.current_date && DOS == to_compare.DOS &&
                member_id == to_compare.member_id && provider_id == to_compare.provider_id &&
                comments == to_compare.comments);
}

// checks if service DOS is before another
bool service::operator<(const service &to_compare) const
{
        return (compare_DOS(to_compare) == -1);
}

// checks if service DOS is after another
bool service::operator>(const service &to_compare) const
{
        return (compare_DOS(to_compare) == 1);
}

//reformat date so can be properly compared
//returns date in this format: YYYYMMDD
string service::reformat_date(const string &date) const
{
        string temp, reformatted, month, day, year = "";
        int size = (int)date.size();
        int del_count = 0;

        for (int i = 0; i < size; i++)
        {
                if (date[i] != '-')
                {
                        temp += date[i];
                }
                else
                {
                        if (del_count == 0)
                        {
                                month = temp;
                                temp = "";
                        }
                        else if (del_count == 1)
                        {
                                day = temp;
                                temp = "";
                        }
                        ++del_count;
                }
        }
        year = temp;
        reformatted.append(year);
        reformatted.append(month);
        reformatted.append(day);
        return reformatted;
}

//checks if date entered is in proper format and is valid
bool service::is_valid_date(string &date)
{
        if (date.size() != 10)
                return false;
        if (!isdigit(date[0]) || !isdigit(date[1])
         || !isdigit(date[3]) || !isdigit(date[4])
         || !isdigit(date[6]) || !isdigit(date[7])
         || !isdigit(date[8]) || !isdigit(date[9]))
                return false;
        if(date[2] != '-' || date[5] != '-')
                return false;

        int mon = stoi(date.substr(0,2));
        int day = stoi(date.substr(3,2));
        int yr = stoi(date.substr(6,4)); 

        if(mon < 1 || mon > 12)
                return false;
        if(day < 1 || day > 31)
                return false;

        //validate year?

        return true;
}

// this function will read in the relevant dates for a service
// we can rename the function to make it more clear -nnaylor
void service::read_date()
{ 
        bool flag = true;
    
        do{
                cout << "Current Date: ";
                cin >> current_date;
                cin.ignore(100, '\n');
                if(!(flag = is_valid_date(current_date)))
                                cout << "ERROR: Invalid date. Please use MM-DD-YYYY format." << endl;
        }while(!flag);

        do{
                cout << "Date of Service: "; // HAVE TO VALIDATE FORMATTING
                cin >> DOS;
                cin.ignore(100, '\n');
                if(!(flag = is_valid_date(DOS)))
                                cout << "ERROR: Invalid date. Please use MM-DD-YYYY format." << endl;
        }while(!flag);
}

void service::read_comment()
{
        cout << "Comments: " << endl;
        getline(cin, comments);
}

//uses manager display function (displays all information)
ostream &operator<<(ostream &out, const service &source)
{
        source.display(out);
        return out;
}
//