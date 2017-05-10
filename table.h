#include <iostream>
using namespace std;

class Order;

class Table {
    private:
        bool free;

    public:
        Table(bool = true);
        bool is_free();
        void take();
        void giveback();
        Order make_order(const string&);
        //ostream& print(ostream&) const;
};

ostream& operator<<(ostream&, Table&);
