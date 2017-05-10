#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <climits>
#include "table.h"
#include "order.h"
#include "restaurant.h"
using namespace std;

Restaurant::Restaurant(string strName, vector<Table> vctTables) {
  this->name = strName;
  this->tables = vctTables;
}

void Restaurant::take_table(int intTable) {
  if ((intTable-1) >= int(this->tables.size())||intTable<1)
    throw runtime_error("Table " + to_string(intTable) + " doesn't exist!");
  else
    this->tables.at(intTable-1).take();
}

void Restaurant::return_table(int intTable) {
  if ((intTable-1) >= int(this->tables.size())||intTable<1)
    throw runtime_error("Table " + to_string(intTable) + " doesn't exist!");
  else
    this->tables.at(intTable-1).giveback();
}

void Restaurant::get_tables() {
  for (size_t i {0}; i < this->tables.size(); i++) {
    if (this->tables.at(i).is_free()) {
      cout << (i+1) << ' ';
    }
  }
  cout << '\n';
}

void Restaurant::make_order(int intTable, const string& strOrder, double dblPrice) {
  if ((intTable-1) >= int(this->tables.size())||intTable<1)
    throw runtime_error("Table " + to_string(intTable) + " doesn't exist!");
  if (this->tables.at(intTable-1).is_free())
    throw runtime_error("Table " + to_string(intTable) + " has no customers!");
  if (this->om.find(intTable) == this->om.end()) {
    this->om.insert({intTable, vector<Order>({Order(strOrder, dblPrice)})});
  } else {
    this->om[intTable].push_back(Order(strOrder, dblPrice));
  }
}

string Restaurant::process() {
  if (this->om.empty())
    throw runtime_error("No orders!");
  string strProcess;
  unordered_map<int, vector<Order>>::iterator it = this->om.begin();
  strProcess.append("Prepare ");
  while (it != this->om.end()) {
    for (size_t i {0}; i < it->second.size(); i++) {
      strProcess.append(it->second.at(i).get_name());
      if ((i+1) < it->second.size()) {
        strProcess.append(", ");
      }
    }
    if (++it != this->om.end()) {
      strProcess.append(", ");
    }
  }
  strProcess.append(".\n");
  it = this->om.begin();
  while (it != this->om.end()) {
    strProcess.append("Deliver ");
    for (size_t i {0}; i < it->second.size(); i++) {
      strProcess.append(it->second.at(i).get_name());
      if ((i+1) < it->second.size()) {
        strProcess.append(", ");
      }
    }
    strProcess.append(" to table " + to_string(it->first) + '.');
    if (++it != this->om.end()) {
      strProcess.append("\n");
    }
  }
  this->om.clear();
  return strProcess;
}

void Restaurant::stats() {
   if (this->om.empty()) {
    throw runtime_error("No current orders!");
   }
   double min {INT_MAX}, max {0}; int table_min = 0, table_max = 0; int total = 0;
   for (auto& it: this->om) {
     if (min > static_cast<int>(it.second.size())) {
        min = static_cast<int>(it.second.size());
        table_min = it.first;
     }
     if (max < static_cast<int>(it.second.size())) {
        max = static_cast<int>(it.second.size());
        table_max = it.first;
     }
     total += static_cast<int>(it.second.size());
   }
   cout << "Minimum Orders: " << min << " for Table " << table_min << '\n'
        << "Maximum Orders: " << max << " for Table " << table_max << '\n'
        << "Total Orders: " << total << '\n'
        << "Average Orders: " << (total/static_cast<double>(this->om.size())) << '\n';
}

ostream& Restaurant::print(ostream& o) {
  o << '{' << this->name << ", Table {";
  for (size_t i {0}; i < this->tables.size(); i++) {
    o << int(i+1) << ' ' << this->tables.at(i);
    if ((i+1) < this->tables.size()) {
      o << ", ";
    }
  }
   o << "} Orders {";
   unordered_map<int, vector<Order>>::iterator it = this->om.begin();
   while (it != this->om.end()) {
     o << "Table " << it->first << ": {";
     for (size_t i {0}; i < it->second.size(); i++) {
       o << it->second.at(i);
       if ((i+1) < it->second.size()) {
         o << ", ";
       }
     }
     o << '}';
     if (++it != this->om.end()) {
       o << ", ";
     }
   }
  o << '}';
  return o;
}

Restaurant& Restaurant::operator++() {
    this->tables.push_back(Table());
    return *this;
}

Restaurant& Restaurant::operator+=(const int& n) {
    if (n<1)
      throw runtime_error("Invalid number of tables to add!");
    for (size_t i {0}; i < static_cast<size_t>(n); i++) {
        this->tables.push_back(Table());
    }
    return *this;
}

string Restaurant::operator[](const int& intTable) {
  if ((intTable-1) >= int(this->tables.size())||intTable<1)
    throw runtime_error("Table " + to_string(intTable) + " doesn't exist!");
  if (this->tables.at(intTable-1).is_free())
    throw runtime_error("Table " + to_string(intTable) + " has no customers!");

   string helper {};
   double sum = 0;
   unordered_map<int, vector<Order>>::iterator it = this->om.find(intTable);
   if (it != this->om.end()) {
     for (size_t i {0}; i < it->second.size(); i++) {
       helper.append(it->second.at(i).get_name() + ": " + to_string(it->second.at(i).get_price()) + '\n');
       sum += it->second.at(i).get_price();
     }
     helper.append("Sum: " + to_string(sum) + '\n');
   } else {
     throw runtime_error("Table " + to_string(intTable) + " doesn't have any orders!");
   }
   return helper;
}

ostream& operator<<(ostream& o, Restaurant& r) {
  r.print(o);
  return o;
}
