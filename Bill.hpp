//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Bill_hpp
#define Bill_hpp

#include "Customer.hpp"
#include "Product.hpp"

#include <iostream>
#include <map>
#include <vector>
#include <chrono>

using namespace std;

class Bill {
protected:
    chrono::time_point<chrono::high_resolution_clock> date;
    unsigned short ID;
    Customer buyer;
    Customer seller;
    map<unsigned short, unsigned short> products;
    vector<Product> *stock;
        
public:
    /**
     Bill object constructor:
     @param argDate Type time_t specifies bill date.
     @param argID Integer to numerate bills.
     @param argBuyer Class Customer object.
     @param argSeller Class Customer object.
     @param argProducts Map containing product ID and quantity (both unsigned short type).
     */
    Bill(chrono::time_point<chrono::high_resolution_clock> argDate = chrono::steady_clock::now(), unsigned short argID = 0, Customer argBuyer = 0, Customer argSeller = 0, map<unsigned short, unsigned short> argProducts = map<unsigned short, unsigned short>());
    
    
    // Getters:
    chrono::time_point<chrono::high_resolution_clock> getDate() const;
    unsigned short getID() const;
    Customer getBuyer() const;
    Customer getSeller() const;
    map<unsigned short, unsigned short> getProducts() const;

    // Setters:
    /**
     Sets date attribute to given argument.
     @param newDate New date of bill.
     */
    void setDate(chrono::time_point<chrono::high_resolution_clock> newDate);
    
    /**
     Sets buyer attribute to given argument.
     @param newBuyer New buyer object.
     */
    void setBuyer(Customer newBuyer);
    
    /**
     Sets seller attribute to given argument.
     @param newSeller New seller object.
    */
    void setSeller(Customer newSeller);
    
    /**
     Sets number attribute to given argument.
     @param newID New number.
     */
    void setID(unsigned short newID);
    
    /**
     Sets stock.
     @param argStock Pointer to stock.
     */
    void setStock(vector<Product> *argStock);
    
    /**
     Replaces all the existing products with the new ones.
     @param newProducts New products map.
     */
    void setProducts(map<unsigned short, unsigned short> newProducts);
    

    // Tools to edit products:
    /**
     Adds product to the bill. If already exist will stack with prevoiusy added.
     @param newProductID New product ID.
     @param newQuantity Quantity of the ne product.
     */
    void addProduct(unsigned short newProductID, unsigned short newQuantity);
    
    /**
     Removes specified product from the bill (if exist).
     */
    void removeProduct(unsigned short newProductID, unsigned short newQuantity);
};




class Invoice: public Bill {
    public:
    using Bill::Bill;
    
    /**
     Generates ASCII representation of the bill.
     */
    string generate() const;
    
    /**
     Saves ASCII representation of the bill to file.
     @param filename String filename to use. Remember about extension (preferred .txt).
     */
    void save(string filename);
};




class Receipt: public Bill {
    public:
    using Bill::Bill;
    
    /**
     Generates ASCII representation of the bill.
     */
    string generate() const;
    
    /**
     Saves ASCII representation of the bill to file.
     @param filename String filename to use. Remember about extension (preferred .txt).
     */
    void save(string filename);
};

#endif /* Bill_hpp */
