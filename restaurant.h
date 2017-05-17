#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Table;
class Order;

class Restaurant {
  private:
    string name;
    vector<Table> tables;
    unordered_map<int, vector<Order>> om;
  public:
    Restaurant(string, vector<Table>);
    void take_table(int);
    void return_table(int);
    void make_order(int, const string&, bool, double = 10);
    void cancel_order(int, const string&);
    string process();
    void get_tables();
    void stats();
    ostream& print(ostream&);
    Restaurant& operator++();
    Restaurant& operator+=(const int&);
    string operator[](const int&);
};

ostream& operator<<(ostream&, Restaurant&);
