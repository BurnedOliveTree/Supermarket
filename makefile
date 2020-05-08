CC = gcc

all: base.o product.o customer.o employee.o cashdesk.o shop.o test.o main.o
	$(CC) base.o product.o customer.o employee.o cashdesk.o shop.o test.o main.o -o all

%.o: %.cpp
	$(CC) -c $<

main.o: main.cpp
test.o: test.cpp
base.o: base.cpp
cashdesk.o: cashdesk.cpp
customer.o: customer.cpp
employee.o: employee.cpp
product.o: product.cpp
shop.o: shop.cpp

clean:
	rm *.o all
