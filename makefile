CC = g++

supermarket: main.o Shop.o Base.o Bill.o Product.o Customer.o Employee.o CashDesk.o TestInvoice.o
	$(CC) main.o Shop.o Base.o Bill.o Product.o Customer.o Employee.o CashDesk.o TestInvoice.o -o supermarket

main.o: main.cpp
	$(CC) -Wall -c main.cpp
	
%.o: %.cpp %.hpp
	$(CC) -Wall -c $<

Shop.o: Shop.cpp Shop.hpp
Bill.o: Bill.cpp Bill.hpp
Product.o: Product.cpp Product.hpp
Customer.o: Customer.cpp Customer.hpp
Employee.o: Employee.cpp Employee.hpp
CashDesk.o: CashDesk.cpp CashDesk.hpp

TestInvoice.o: Tests/TestInvoice.cpp Tests/TestInvoice.hpp
	$(CC) -Wall -c Tests/TestInvoice.cpp

clean:
	rm *.o supermarket
