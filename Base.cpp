//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

// może tu wsadzić klasę do polimorfii / dziedziczenia, która będzie obrabiać jakoś pieniądze? czy coś?

#include <cmath>

float checkCash(float cash) {
/// rounds up float values to 2 decimal points
    return std::roundf(cash*100)/100;
}
