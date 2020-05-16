//
//  PROIekt - symulacja supermarketu
//
//  Created by Ksawery Chodyniecki and Paweł Müller.
//

#include "Base.hpp"

float checkCash(float cash) {
/// rounds up float values to 2 decimal points
    return roundf(cash*100)/100;
}
