//
//  main.cpp
//  Zadanie 3
//
//  Created by Paweł Müller on 03/04/2020.
//

#include "Product.hpp"
#include "Invoice.hpp"
#include "Consumer.hpp"
//#include "TestInvoice.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 Kilka komentarzy od autora:
 - Przepraszam za bałagan na gicie, obiecuję, że posprzątam.
 - Przepraszam za lekkie opóźnienie - linker płatał figle.
 - Ceny wyświetlane na fakturach są podawane w groszach, aby nie uzywać do tego typu float. W finalnej wersji projektu będą oczywiście w złotówkach.
 */

int main() {
    TestInvoice invoiceTest;
    invoiceTest.menu();
    return 0;
}
