#include <iostream>
#include <string>
#include <stdexcept>
#include "order.h"
using namespace std;

Order::Order(string n, double p) : name(n), price(p) {
    if (this->price < 0)
        throw runtime_error("Price isn't allowed!");
}

string Order::get_name() const {
    return this->name;
}

double Order::get_price() const {
    return this->price;
}

/* ostream& Order::print(ostream&) const {

} */

ostream& operator<<(ostream& o, Order& order) {
    o << "[" << order.get_name() << ", " << order.get_price() << "]";
    return o;
}
