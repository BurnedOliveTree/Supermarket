//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#ifndef Invoice_hpp
#define Invoice_hpp

#include "Customer.hpp"
#include "Product.hpp"
#include "Bill.hpp"

#include <iostream>
#include <map>
#include <vector>
#include <ctime>

using namespace std;

class Invoice: public Bill {
    public:
    using Bill::Bill;
    
    /**
     Generates ASCII representation of the bill.
     */
    string generate();
    
    /**
     Saves ASCII representation of the bill to file.
     @param filename String filename to use. Remember about extension (preferred .txt).
     */
    void save(string filename);
};

#endif /* Invoice_hpp */
