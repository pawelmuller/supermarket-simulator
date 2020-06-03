CC = g++

supermarket: main.o Shop.o Bill.o Product.o Customer.o Employee.o CashDesk.o StringOperations.o
	$(CC) main.o Shop.o Bill.o Product.o Customer.o Employee.o CashDesk.o StringOperations.o -o supermarket

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

StringOperations.o: AddOns/StringOperations.cpp AddOns/StringOperations.hpp
	$(CC) -Wall -c AddOns/StringOperations.cpp

clean:
	rm *.o supermarket