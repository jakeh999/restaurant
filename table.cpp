#include <iostream>
#include <string>
#include <stdexcept>
#include "table.h"
#include "order.h"
using namespace std;

Table::Table(bool free) {
    this->free = free;
}

bool Table::is_free() {
    return this->free;
}

void Table::take() {
    if (this->free)
        this->free = false;
    else
        throw runtime_error("Table is already occupied!");
}

void Table::giveback() {
    if (!this->free)
        this->free = true;
    else
        throw runtime_error("Table is free!");
}

Order Table::make_order(const string& s) {
    return Order(s);
}

ostream& operator<<(ostream& o, Table& table) {
    o << "[";
    if (table.is_free())
        o << "free]";
    else
        o << "occupied]";
    return o;
}
