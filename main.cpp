#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "order.h"
#include "table.h"
#include "restaurant.h"
using namespace std;

vector<string> split(const string& original, char deliminator) {
    if (original.empty())
      throw runtime_error("Please enter a command!");
    vector<string> s;
    int i = 0; int hilfs = 0;
    while (hilfs != -1) {
        hilfs = original.find(deliminator, i);
        s.push_back(original.substr(i, hilfs-i));
        i = hilfs + 1;
    }
    return s;
}

int main() {
  bool cont = true;
  string input; vector<string> s;
  //Enter name of restaurant and number of starting tables.
  Restaurant r{"Jake's Restaurant", vector<Table>(5)};
  cout << "Restaurant System - by Jake Henderson\n";
  while (cont) {
      cout << "> ";
      try {
        getline(cin, input, '\n');
        s = split(input, ' ');
        if (s.at(0) == "available_tables") {
          r.get_tables();
        } else if (s.at(0) == "take") {
          r.take_table(stoi(s.at(1)));
          r.get_tables();
        } else if (s.at(0) == "giveback") {
          r.return_table(stoi(s.at(1)));
          r.get_tables();
        } else if (s.at(0) == "order" || s.at(0) == "order_fast") {
          bool fast = false;
          if (s.at(0) == "order_fast")
            fast = true;
          if (int(s.size())==3) {
            r.make_order(stoi(s.at(1)), s.at(2), fast);
          } else if (int(s.size())>3) {
            string order {};
            size_t i {2}; bool first = true;
            while (i < (s.size()-1)) {
                if (!first) {
                    order.append(" ");
                }
                order.append(s.at(i));
                i++;
                first = false;
            }
            if (s.at(i).at(0) == '-') {
                double price = stod(s.at(i).substr(1));
                r.make_order(stoi(s.at(1)), order, fast, price);
            } else {
                order.append(" " + s.at(i));
                r.make_order(stoi(s.at(1)), order, fast);
            }
          } else {
            throw runtime_error("Improper use of order command. See >help.");
          }
        } else if (s.at(0) == "process") {
          cout << r.process() << '\n';
        } else if (s.at(0) == "restaurant") {
          cout << r << '\n';
        } else if (s.at(0) == "add_table") {
          if (static_cast<int>(s.size())==1) {
            ++r;
            r.get_tables();
          } else {
            r += stoi(s.at(1));
            r.get_tables();
          }
        } else if (s.at(0) == "open_orders") {
          if (static_cast<int>(s.size())==2) {
            cout << r[stoi(s.at(1))];
          } else {
            throw runtime_error("Improper use of open_orders command. See >help.");
          }
        } else if (s.at(0) == "stats") {
            r.stats();
        } else if (s.at(0) == "cancel_order") {
            if (int(s.size())>=3) {
                string order {};
                bool first = true;
                for (size_t i {2}; i < s.size(); i++) {
                    if (!first) {
                        order.append(" ");
                    } else {
                        first = false;
                    }
                    order.append(s.at(i));
                }
                r.cancel_order(stoi(s.at(1)), order);
            } else {
                throw runtime_error("Improper use of cancel_order command. See >help.");
            }
        } else if (s.at(0) == "help") {
          cout << "Available commads:\n"
               << "available_tables - show available tables\n"
               << "take [table number] - take a table\n"
               << "giveback [table number] - return a table\n"
               << "order [table number] [menu item] -[price - optional] - place a standard order at a table\n"
               << "order_fast [table number] [menu item] -[price - optional] - place an expidited order at a table\n"
               << "cancel_order [table number] [menu item] - cancel an order at a table\n"
               << "stats - display current statistics\n"
               << "process - prepare and deliver orders\n"
               << "restaurant - display current restaurant status\n"
               << "add_table [# of tables to add - optional] - add tables to the list\n"
               << "open_orders [table number] - display open orders at a table\n"
               << "help - show this help screen\n"
               << "exit - exit the program\n";
        } else if (s.at(0) == "exit") {
            cont = false;
        } else {
            throw runtime_error("Command not found! Enter help for list of commands.");
        }
      } catch (out_of_range& e) {
        cerr << "Error: Invalid number!" << '\n';
      } catch (invalid_argument& e) {
        cerr << "Error: Invalid argument!" << '\n';
      } catch (runtime_error& e) {
        cerr << "Error: " << e.what() << '\n';
      }
  }
  return 0;
}
