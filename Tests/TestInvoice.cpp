//
//  TestInvoice.cpp
//
//  Created by Paweł Müller on 08/04/2020.
//

#include "TestInvoice.hpp"
#include "../Product.hpp"
#include "../Bill.hpp"
#include "../Customer.hpp"

#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

TestInvoice::TestInvoice() {
    productsPointer = &products;
    //  argName, argID, argPrice, argVAT, argQuantity, argMeasureUnits
    products.push_back(Product("Jablka", 1, 120, 5, 10000, g));
    products.push_back(Product("Pomidory", 2, 720, 5, 50000, g));
    products.push_back(Product("Patelnia", 3, 6599, 23, 10));
    products.push_back(Product("Puszka kukurydzy", 4, 567, 23, 70));
    products.push_back(Product("Mentha rotundifolia (L.) Huds.", 5, 60, 5, 500, g));

    Customer seller1(true, 1, "Supermarket", "5351638772", "Poziomkowa", "15A", "00-009", "Szczebrzeszyn", "Atlantyda");
    Customer seller2(true, 2, "DeutschMart", "DE7573850993", "Grossestrasse", "1", "17-120", "Berlin", "Deutschland");
    Customer buyer1(false, 3, "Anna Nowak", "0", "Jablkowa", "199/13", "14-900", "Swinoujscie", "Atlantyda");
    Customer buyer2(true, 4, "John Doe", "8889997766", "Baker Street", "221b", "NW1 6XE", "London", "United Kingdom");

    sellers.push_back(seller1);
    sellers.push_back(seller2);
    buyers.push_back(buyer1);
    buyers.push_back(buyer2);

    buyers[0].addToBasket(&products[0], 1760);
    buyers[0].addToBasket(&products[1], 345);
    buyers[0].addToBasket(&products[2], 3);
    buyers[0].addToBasket(&products[3], 2);
    
    buyers[1].addToBasket(&products[4], 331);
    buyers[1].addToBasket(&products[3], 20);
    buyers[1].addToBasket(&products[2], 1);
    buyers[1].addToBasket(&products[1], 543);
    buyers[1].addToBasket(&products[0], 990);

    Invoice invoice1(chrono::steady_clock::now(), 1490, buyers[0], sellers[1]);
    invoices.push_back(invoice1);
    cout << invoice1.generate();
    invoice1.save("Logs/invoice1.txt");
    cout << endl << endl;
    
    Receipt receipt1(chrono::steady_clock::now(), 53342, buyers[1], sellers[0]);
    receipts.push_back(receipt1);
    cout << receipt1.generate();
    receipt1.save("Logs/receipt1.txt");

    cout << endl << endl;

}

void TestInvoice::menu() {
    string txtMenu = "", clear = "";
    for (int i = 0; i < 50; ++i) clear += "\n";
    txtMenu += "Menu testowania: \n";
    txtMenu += "1. Edytuj sprzedawcow. \n";
    txtMenu += "2. Edytuj nabywcow. \n";
    txtMenu += "3. Edytuj faktury. \n";
    txtMenu += "0. Wyjdz z programu. \n";
    txtMenu += "Twoj wybor: ";

    enum Possibilities {exit, editSellers, editBuyers, editInvoices};
    int choice = 0;
    bool isCorrect = true;
    
    do {
        if (isCorrect) cout << clear + txtMenu;
        else cout << clear + "Niepoprawny wybor. Prosze sprobowac ponownie.\n\n" + txtMenu;
        cin >> choice;
        isCorrect = true;
        switch(choice) {
            case editSellers:
                editElementMenu("sprzedawce", '0');
                break;
            case editBuyers:
                editElementMenu("nabywce", '1');
                break;
            case editInvoices:
                editElementMenu("fakture", '2');
                break;
            case exit:
                break;
            default:
                isCorrect = false;
        }
    } while(choice != exit);
    return;
}

void TestInvoice::editElementMenu(string text, char elementChoice) {
    Customer newConsumer;
    Invoice newInvoice;
    int chosenElement = 0;
    
    string txtMenu = "", clear = "", message = "";
    for (int i = 0; i < 50; ++i) clear += "\n";
    txtMenu += "Tryb edycji: \n";
    txtMenu += "1. Dodaj " + text +". \n";
    txtMenu += "2. Usun " + text +". \n";
    txtMenu += "3. Modyfikuj " + text +". \n";
    txtMenu += "0. Wroc do poprzedniego menu. \n";
    txtMenu += "Twoj wybor: ";
    
    enum Possibilities {back, addElement, removeElement, editElement};
    int choice = 0;
    bool printMessage = false;
    
    do {
        if (printMessage) cout << clear + message + txtMenu;
        else cout << clear + txtMenu;
        cin >> choice;
        printMessage = false;
        switch(choice) {
            case addElement:
                switch (elementChoice) {
                    case '0':
                        sellers.push_back(newConsumer);
                        editConsumer(sellers.back());
                        break;
                    case '1':
                        buyers.push_back(newConsumer);
                        editConsumer(buyers.back());
                        break;
                    case '2':
                        invoices.push_back(newInvoice);
                        editInvoice(invoices.back());
                        break;
                }
                break;
            case removeElement:
                switch (elementChoice) {
                    case '0':
                        chosenElement = consumerChoice(sellers);
                        if (chosenElement == -1) {
                            message = "Brak sprzedawcow.\n\n";
                            printMessage = true;
                            break;
                        }
                        sellers.erase(sellers.begin() + chosenElement);
                        break;
                    case '1':
                        chosenElement = consumerChoice(buyers);
                        if (chosenElement == -1) {
                            message = "Brak kupcow.\n\n";
                            printMessage = true;
                            break;
                        }
                        buyers.erase(buyers.begin() + chosenElement);
                        break;
                    case '2':
                        chosenElement = invoiceChoice(invoices);
                        if (chosenElement == -1) {
                            message = "Brak faktur.\n\n";
                            printMessage = true;
                            break;
                        }
                        invoices.erase(invoices.begin() + chosenElement);
                        break;
                }
                break;
            case editElement:
                switch (elementChoice) {
                    case '0':
                        chosenElement = consumerChoice(sellers);
                        if (chosenElement == -1) {
                            message = "Brak sprzedawcow.\n\n";
                            printMessage = true;
                            break;
                        }
                        editConsumer(sellers[chosenElement]);
                        break;
                    case '1':
                        chosenElement = consumerChoice(buyers);
                        if (chosenElement == -1) {
                            message = "Brak kupcow.\n\n";
                            printMessage = true;
                            break;
                        }
                        editConsumer(buyers[chosenElement]);
                        break;
                    case '2':
                        chosenElement = invoiceChoice(invoices);
                        if (chosenElement == -1) {
                            message = "Brak faktur.\n\n";
                            printMessage = true;
                            break;
                        }
                        editInvoice(invoices[chosenElement]);
                        break;
                }
                break;
            case back:
                break;
            default:
                message = "Niepoprawny wybor. Prosze sprobowac ponownie.\n\n";
                printMessage = true;
        }
    } while(choice != back);
    return;
}

int TestInvoice::consumerChoice(vector<Customer> list) {
    string output = "";
    int choice = 0;
    
    if (list.empty()) {
        return -1;
    }
    
    output += "Wybierz indeks:\n";
    for (int i = 0; i < list.size(); i++) {
        output += to_string(i) + ". " + list[i].getName() + "\n";
    }
    output += "Twoj wybor: ";
    cout << output;
    cin >> choice;
    return choice;
}

int TestInvoice::invoiceChoice(vector<Invoice> list) {
    string output = "";
    int choice = 0;
    
    if (list.empty()) {
        return -1;
    }
    
    output += "Wybierz indeks:\n";
    for (int i = 0; i < list.size(); i++) {
        output += to_string(i) + ". Faktura nr:" + to_string(list[i].getID()) + "\n";
    }
    output += "Twoj wybor: ";
    cout << output;
    cin >> choice;
    return choice;
}

void TestInvoice::editConsumer(Customer &consumer) {
    string txtMenu = "", clear = "";
    for (int i = 0; i < 50; ++i) clear += "\n";
    txtMenu += "Edycja konsumenta: \n";
    txtMenu += "1. Edytuj status biznesu. \n";
    txtMenu += "2. Edytuj nazwe. \n";
    txtMenu += "3. Edytuj NIP. \n";
    txtMenu += "4. Edytuj ulice. \n";
    txtMenu += "5. Edytuj numer budynku. \n";
    txtMenu += "6. Edytuj kod pocztowy. \n";
    txtMenu += "7. Edytuj miasto. \n";
    txtMenu += "8. Edytuj kraj. \n";
    txtMenu += "0. Wroc do poprzedniego menu. \n";
    txtMenu += "Twoj wybor: ";

    enum Possibilities {exit, isBusiness, name, taxNumber, street, buildingNumber, postcode, city, country};
    int choice = 0;
    bool isCorrect = true;
    
    string newString = "";
    bool newBool = false;
    
    do {
        newString = "";
        if (isCorrect) cout << clear + "Business status: " + to_string(consumer.getIsBusiness()) + "\n" +  consumer.getInfo() + "\n\n"+ txtMenu;
        else cout << clear + "Niepoprawny wybor. Prosze sprobowac ponownie.\n\n" + txtMenu;
        cin >> choice;
        isCorrect = true;
        cin.ignore();
        switch(choice) {
            case isBusiness:
                cout << "Czy konsument jest klientem biznesowym? (1/0):";
                cin >> newBool;
                consumer.setIsBusiness(newBool);
                break;
            case name:
                cout << "Podaj nowa nazwe:";
                getline(cin, newString);
                consumer.setName(newString);
                break;
            case taxNumber:
                cout << "Podaj nowy NIP:\n";
                getline(cin, newString);
                consumer.setTaxNumber(newString);
                break;
            case street:
                cout << "Podaj ulice:\n";
                getline(cin, newString);
                consumer.setStreet(newString);
                break;
            case buildingNumber:
                cout << "Podaj nowy numer budynku:\n";
                getline(cin, newString);
                consumer.setBuildingNumber(newString);
                break;
            case postcode:
                cout << "Podaj nowy kod pocztowy:\n";
                getline(cin, newString);
                consumer.setPostcode(newString);
                break;
            case city:
                cout << "Podaj nowe miasto:\n";
                getline(cin, newString);
                consumer.setCity(newString);
                break;
            case country:
                cout << "Podaj nowy kraj:\n";
                getline(cin, newString);
                consumer.setCountry(newString);
                break;
            case exit:
                break;
            default:
                isCorrect = false;
        }
    } while(choice != exit);
    return;
}

void TestInvoice::editInvoice(Invoice &invoice) {
    string txtMenu = "", clear = "", message = "";
    for (int i = 0; i < 50; ++i) clear += "\n";
    txtMenu += "Edycja konsumenta: \n";
    txtMenu += "1. Edytuj status platnosci. \n";
    txtMenu += "2. Edytuj numer. \n";
    txtMenu += "3. Edytuj nabywce. \n";
    txtMenu += "4. Edytuj sprzedawce. \n";
    txtMenu += "0. Wroc do poprzedniego menu. \n";
    txtMenu += "Twoj wybor: ";

    enum Possibilities {exit, isPayed, number, buyer, seller, products};
    int choice = 0;
    bool printMessage = false;
    
    string newString = "";
    bool newBool = false;
    int newInt = 0, chosenConsumer = 0;
    
    do {
        newString = "";
        if (printMessage) cout << clear + message + txtMenu;
        else cout << clear + invoice.generate() + "\n\n"+ txtMenu;
        cin >> choice;
        printMessage = false;
        cin.ignore();
        switch(choice) {
            case isPayed:
                cout << "Czy faktura jest zaplacona (wywalone)? (1/0):";
                cin >> newBool;
                //invoice.setIsPayed(newBool);
                break;
            case number:
                cout << "Podaj nowy numer:\n";
                cin >> newInt;
                invoice.setID(newInt);
                break;
            case buyer:
                cout << "Wybierz nabywce:\n";
                chosenConsumer = consumerChoice(buyers);
                if (chosenConsumer == -1) {
                    message = "Brak nabywcow.";
                    printMessage = true;
                    break;
                }
                invoice.setBuyer(buyers[chosenConsumer]);
                break;
            case seller:
                cout << "Wybierz sprzedawce:\n";
                chosenConsumer = consumerChoice(sellers);
                if (chosenConsumer == -1) {
                    message = "Brak sprzedawcow.";
                    printMessage = true;
                    break;
                }
                invoice.setSeller(sellers[chosenConsumer]);
                break;
            
            case exit:
                break;
            default:
                message = "Niepoprawny wybor. Prosze sprobowac ponownie.\n\n";
                printMessage = false;
        }
    } while(choice != exit);
    return;
}

void TestInvoice::showInvoice(Invoice invoice) {
    cout << invoice.generate();
    return;
}
