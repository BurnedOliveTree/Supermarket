//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Shop.hpp"

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
            Shop simulation;
            simulation.run();
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
