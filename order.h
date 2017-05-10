#include <iostream>
#include <string>
using namespace std;

class Order {
    private:
        string name;
        double price;
    
    public:
        Order(string, double = 10);
        string get_name() const;
        double get_price() const;
        //ostream& print(ostream&) const;
};

ostream& operator<<(ostream&, Order&);

