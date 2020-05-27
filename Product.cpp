//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Product.hpp"

using namespace std;

Product::Product(string argName, unsigned short argID, unsigned int argPrice, unsigned char argVAT, unsigned short argQuantity, Measure argMeasureUnits, unsigned short argReservedQuantity) {
    name = argName;
    ID = argID;
    price = argPrice;
    VAT = argVAT;
    quantity = argQuantity;
    reservedQuantity = argReservedQuantity;
    measureUnits = argMeasureUnits;
    return;
}


// Getters:
string Product::getName() const {
    return name;
}

unsigned short Product::getID() const {
    return ID;
}

unsigned int Product::getPrice() const {
    return price;
}

unsigned short Product::getVAT() const {
    return VAT;
}

unsigned short Product::getQuantity() const {
    return quantity;
}

unsigned short Product::getReservedQuantity() const {
    return reservedQuantity;
}


// Setters:
void Product::setName(string newName) {
    name = newName;
    return;
}

void Product::setID(unsigned short newID) {
    ID = newID;
    return;
}

void Product::setPrice(unsigned int newPrice) {
    price = newPrice;
    return;
}

void Product::setVAT(unsigned short newVAT) {
    VAT = newVAT;
    return;
}

void Product::setQuantity(unsigned short newQuantity) {
    quantity = newQuantity;
    return;
}

void Product::setReservedQuantity(unsigned short newReservedQuantity) {
    reservedQuantity = newReservedQuantity;
    return;
}


// Additional features:
string Product::getInfo() {
    string info = "";
    info = name + " (#" + to_string(ID) + "):\n" + "Price netto: " + to_string(price) + " gr\n";
    info += "Price brutto: " + to_string(calculatePriceBrutto()) + " gr (" + to_string(VAT) +"% VAT)\n";
    info += "At warehouse: " + to_string(quantity) + " pcs\n";
    info += "Reserved: " + to_string(reservedQuantity) + " pcs\n";
    return info;
}

int Product::calculatePriceBrutto() {
    float brutto = ((100 + VAT) * price);
    brutto /= 100;
    return ceil(brutto);
}
