#makefile
CXXFLAGS += --std=c++17

GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: elsa

debug: CXXFLAGS += -g
debug: mainwin

elsa: main.o mainwin.o entrydialog.o store.o customer.o options.o desktop.o order.o
	$(CXX) $(CXXFLAGS) main.o mainwin.o entrydialog.o store.o customer.o options.o desktop.o order.o $(GTKFLAGS) -o elsa

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS) -o main.o

mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS) -o mainwin.o 

entrydialog.o: entrydialog.cpp *.h
	$(CXX) $(CXXFLAGS) -c entrydialog.cpp $(GTKFLAGS) -o entrydialog.o

store.o: store.cpp *.h
	$(CXX) $(CXXFLAGS) -c store.cpp $(GTKFLAGS) -o store.o

customer.o: customer.cpp *.h
	$(CXX) $(CXXFLAGS) -c customer.cpp $(GTKFLAGS) -o customer.o

options.o: options.cpp *.h
	$(CXX) $(CXXFLAGS) -c options.cpp $(GTKFLAGS) -o options.o

desktop.o: desktop.cpp *.h
	$(CXX) $(CXXFLAGS) -c desktop.cpp $(GTKFLAGS) -o desktop.o

order.o: order.cpp *.h
	$(CXX) $(CXXFLAGS) -c order.cpp $(GTKFLAGS) -o order.o
	 
clean:
	rm -f *.o *.gch elsa
