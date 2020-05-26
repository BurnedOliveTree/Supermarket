//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Shop.hpp"
#include "TestInvoice.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void stupidTemporaryMethod() {
    unsigned long a;
    cout << "Podaj czas trwania [s]:" << endl;
    cin >> a;
    Shop simulation(a);
    simulation.run();
}

void manualTest();

/**
        Kolejnosc argumentow:
                czas, ilosc kas, ilosc pracownikow, ilosc klientow, ...
            lub
                nazwa pliku z wartosciami (w powyzszej kolejnosci).
        Brak argumentow skutkuje wlaczeniem recznego sterowania.
 */
int main(int argc, char* argv[]) {
    switch(argc) {
        case 0: case 1: {
            stupidTemporaryMethod();
            // manualTest(); // temporarily commented
            break;
        }
        case 2: {
            Shop simulation(argv[1]);
            simulation.run();
            break;
        }
        default: {
            Shop simulation(argv);
            simulation.run();
        }
    }
    return 0;
}

void manualTest() {
    cout << "Brak podanych argumentow." << endl << "Inicjacja manualnego dostepu do programu." << endl;
    TestInvoice invoiceTest;
    invoiceTest.menu();
}
