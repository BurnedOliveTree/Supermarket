//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Base.hpp"
#include "Product.hpp"
#include "Customer.hpp"
#include "Employee.hpp"
#include "CashDesk.hpp"
#include "Shop.hpp"
#include "Tests/TestInvoice.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

vector<string> readFile(string filename);
vector<unsigned int> handleArgs(int argc, char *argv[]);
vector<unsigned int> strVectorToIntVector(vector<string> stringData);

int main(int argc, char* argv[]) {
    // vector<unsigned int> givenArguments = handleArgs(argc, argv);
    Shop simulation;
    simulation.run(20);
    return 0;
}

vector<unsigned int> handleArgs(int argc, char *argv[]) {
    vector<string> stringData;
    
    // No arguments given. Manual tests.
    if (argc == 0 || argc == 1) {
        cout << "Brak podanych argumentow." << endl << "Inicjacja manualnego dostepu do programu." << endl;
        TestInvoice invoiceTest;
        invoiceTest.menu();
        return {0};
    }
    // One argument given: assumed it's file name.
    else if (argc == 2) {
        stringData = readFile(argv[1]);
    }
    // Additional arguments passed.
    else {
        for (int i = 1; i < argc; i++)
            stringData.push_back(argv[i]);
    }
    return {1};
    // return strVectorToIntVector(stringData);
}

vector<string> readFile(string filename) {
    // TO DO
    return {"When life gives you lemons, don't make lemonade."};
}

vector<unsigned int> strVectorToIntVector(vector<string> stringData) {
    // TO DO
    return {42};
}

/*
 File handling:
 
 if (argc == 0 || argc == 1) { // Sth went wrong: no args
    TestInvoice invoiceTest;
    invoiceTest.menu();
    return -1;
} else if (argc == 2) { // Filename
    string line = "";
    ifstream file;
    file.open(argv[0]);
    if (file >> line) {
        string singleData = "";
        stringstream buffer(line);
        while (getline(buffer, singleData, ',')) {
            rawData.push_back(singleData);
            cout << singleData << endl;
        }
    } else cout << "File error." << endl;
    file.close();
}*/
