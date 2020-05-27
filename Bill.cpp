//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Bill.hpp"
#include "Customer.hpp"
#include "AddOns/StringOperations.hpp"

#include <utility>
#include <fstream>
#include <exception>

using namespace std;

Bill::Bill(chrono::time_point<chrono::high_resolution_clock> argDate, unsigned short argID, Customer argBuyer, Customer argSeller) {
    date = argDate;
    ID = argID;
    buyer = argBuyer;
    seller = argSeller;
}


// Getters:
chrono::time_point<chrono::high_resolution_clock> Bill::getDate() const {
    return date;
}

unsigned short Bill::getID() const {
    return ID;
}

Customer Bill::getBuyer() const {
    return buyer;
}

Customer Bill::getSeller() const {
    return seller;
}

map<unsigned short, unsigned short> Bill::getProducts() const {
    return products;
}


// Setters:
void Bill::setDate(chrono::time_point<chrono::high_resolution_clock> newDate) {
    date = newDate;
}

void Bill::setBuyer(Customer newBuyer) {
    buyer = newBuyer;
}

void Bill::setSeller(Customer newSeller) {
    seller = newSeller;
}

void Bill::setID(unsigned short newID) {
    ID = newID;
}

void Bill::setStock(vector<Product> *argStock) {
    stock = argStock;
}



/*   =======================   INVOICE   =======================   */

string Invoice::generate() const {
    char invoiceWidth = 78;

    vector<Product> stockList = *stock;

    string output = stringAlign("_", 2, invoiceWidth, "_");

    output += "\n";
    output += "|" + stringAlign("INVOICE", 2, invoiceWidth - 2) + "|\n";
    output += "|" + stringAlign("#" + to_string(ID), 2, invoiceWidth - 2) + "|\n";

    output += "|" + stringAlign("BILL FROM:", 2, (invoiceWidth - 4) / 2) + "  " + stringAlign("BILL TO:", 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getName(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getName(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getStreet() + " " + seller.getBuildingNumber(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getStreet() + " " + buyer.getBuildingNumber(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getCity() + " " + seller.getPostcode(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getCity() + " " + buyer.getPostcode(), 2, (invoiceWidth - 4) / 2) + "|\n";
    output += "|" + stringAlign(seller.getTaxNumber(), 2, (invoiceWidth - 4) / 2) + "  " + stringAlign(buyer.getTaxNumber()!="0"?buyer.getTaxNumber():" ", 2, (invoiceWidth - 4) / 2) + "|\n";

    output += "|" + stringAlign("_", 2, invoiceWidth - 2, "_") + "|\n";

    output += "| NAME                   | QTY | NETTO | BRUTTO | VAT | VAT AMT | BRUTTO AMT |\n";
    for (auto productPair:products) {
        for (Product product: stockList) {
            if (product.getID() == productPair.first) {
                output += "|";
                output += stringAlign(product.getName(), 0, 24);
                output += "|";
                output += stringAlign(to_string(product.getQuantity()), 0, 5);
                output += "|";
                output += stringAlign(to_string(product.getPrice()), 0, 7);
                output += "|";
                output += stringAlign(to_string(product.calculatePriceBrutto()), 0, 8);
                output += "|";
                output += stringAlign(to_string(product.getVAT()) + " %", 1, 5);
                output += "|";
                output += stringAlign(to_string(product.getVAT() * product.getQuantity() * product.getPrice()), 0, 9);
                output += "|";
                output += stringAlign(to_string(product.calculatePriceBrutto() * product.getQuantity()), 0, 12);
                output += "|\n";
                break;
            }
        }
    }
    output += "|" + stringAlign(".", 2, invoiceWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("SUMMARY: ", 1, invoiceWidth - 14) + "XXXXXXXXXXXX|\n";
    output += "|" + stringAlign("TMS: TTTTT   ID: " + to_string(ID), 2, invoiceWidth - 2) + "|\n";

    output += stringAlign("¯", 0, invoiceWidth, "¯") += "\n";
    return output;
}

void Invoice::save(string filename) {
    fstream file;
    file.open(filename, ios::out);
    file << generate();
    file.close();
}





/*   =======================   RECEIPT   =======================   */

string Receipt::generate() const {
    char receiptWidth = 40;
    
    vector<Product> stockList = *stock;
    string output = stringAlign("_", 0, 40, "_");
    
    output += "\n";
    output += "|" + stringAlign(seller.getName(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getStreet() + " " + seller.getBuildingNumber(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getCity() + " " + seller.getPostcode(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(seller.getTaxNumber(), 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("RECEIPT", 2, receiptWidth - 2) + "|\n";
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "| NAME          QTY  x PRICE   VALUE   |\n";

    for (auto productPair:products) {
        for (Product product: stockList) {
            if (product.getID() == productPair.first) {
                output += "|";
                output += stringAlign(product.getName(), 0, 14);
                output += " ";
                output += stringAlign(to_string(product.getQuantity()), 0, 5);
                output += "x ";
                output += stringAlign(to_string(product.calculatePriceBrutto()), 0, 7);
                output += " ";
                output += stringAlign(to_string(product.calculatePriceBrutto() * product.getQuantity()), 0, 8);
                output += "|\n";
                break;
            }
        }
    }
    
    output += "|" + stringAlign(".", 2, receiptWidth - 2, ".") + "|\n";
    output += "|" + stringAlign("SUMMARY: ", 1, receiptWidth - 10) + "XXXXXXXX|\n";
    output += "|" + stringAlign("TMS: TTTTT   ID: ", 0, receiptWidth - 2) + "|\n";

    output += stringAlign("¯", 0, receiptWidth, "¯") += "\n";
    return output;
}

void Receipt::save(string filename) {
    fstream file;
    file.open(filename, ios::out);
    file << generate();
    file.close();
}
