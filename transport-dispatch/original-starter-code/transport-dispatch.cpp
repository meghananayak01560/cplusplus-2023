#include <iostream>
#include <sstream>
#include <limits>
#include "functions.h"

using std::cout, std::cin, std::endl, std::exception, std::invalid_argument; 
using std::getline, std::string;


int main () { 
    LinkedList list;
    string line;
    
    getline (cin, line);    
    while (!line.empty()) {
        string operation;
        string location;
        int mapped_loc;

        get_op (line, &operation);
        if (operation == "insert" || operation == "add"){
            int insert_location = 0; 
            getline (cin, line);
            // cout << line << endl;
            get_loc (line, &location);
            mapped_loc = mapping(location);
            // cout << location << endl;
            if (mapped_loc != 0) { 
                if (list.link_list_empty()) {
                    {list.push(mapped_loc);}
                }
                else {
                    insert_location = list.find_closest_less_than(mapped_loc);
                    // cout << "location: " << location << "insert location: " << rev_mapping(insert_location) << endl;
                    if (insert_location != 0) {
                        list.insertNode(mapped_loc, insert_location);
                    }
                    else { list.push(mapped_loc); } // if adding first location then insert_location is 0 (default)
                }
            }
        }
        else if (operation == "push"){
            getline (cin, line);
            get_loc (line, &location);
            mapped_loc = mapping(location);
            if (mapped_loc != 0) {list.push(mapped_loc);}
        }
        else if (operation == "pop"){
            list.pop();
        }
        else if (operation == "clear"){
            list.~LinkedList();            
        }
        else if (operation == "print"){
            list.printLinkedList();
        }
        else if (operation == "locations") {
            print_inst_2();
        }
        else if (operation == "quit") {
            break;
        }
        else {
            cout << "operation type undefined, re-enter operation" << endl;
        } 
        getline (cin, line);
    }
    return 0;
}
