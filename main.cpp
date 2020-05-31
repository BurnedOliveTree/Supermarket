//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Shop.hpp"
#include "Tests/TestInvoice.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void stupidTemporaryMethod() {
    unsigned long a;
    std::cout << "Podaj czas trwania [s]:" << std::endl;
    std::cin >> a;
    Shop simulation(a, 3);
    simulation.run();
}

void manualTest() {
    TestInvoice invoiceTest;
    invoiceTest.menu();
}

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
//            manualTest();
//            Shop simulation;  <- default code
//            simulation.run(); <- default code
            break;
        }
        case 2: {
            Shop simulation(argv[1]);
            simulation.run();
            break;
        }
        default: {
            Shop simulation(argv, argc);
            simulation.run();
        }
    }
    return 0;
}
