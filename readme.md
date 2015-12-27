Żeby skompilować projekt można go albo dodać do eclipsa (może wymagać Makefile ) i następnie skonfigurować go by uruchamiał claraVSclarans


przykładowy Makefile działający na Macu

```Makefile
CXX=/usr/local/bin/gcc-4.8


CXXFLAGS=-lstdc++  -Wall

all:	main.o algorytm.o  algorytm.o algorytmClara.o algorytmClarans.o  algorytmPam.o readingModule.o 
		$(CXX)    -o  claraVSclarans  algorytm.o algorytmClara.o algorytmClarans.o  algorytmPam.o readingModule.o main.o  $(CXXFLAGS)
main.o:	main.cpp
		$(CXX) -o main.o -c main.cpp $(CXXFLAGS) 
algorytm.o: algorytm.cpp algorytm.h
		$(CXX) -o  algorytm.o -c algorytm.cpp $(CXXFLAGS) 
algorytmClara.o: algorytmClara.cpp algorytmClara.h
		$(CXX) -o  algorytmClara.o -c algorytmClara.cpp $(CXXFLAGS) 

algorytmClarans.o: algorytmClarans.cpp algorytmClarans.h
		$(CXX) -o  algorytmClarans.o -c algorytmClarans.cpp $(CXXFLAGS)

algorytmPam.o: algorytmPam.cpp algorytmPam.h
		$(CXX) -o  algorytmPam.o -c algorytmPam.cpp $(CXXFLAGS)
		
readingModule.o: readingModule.cpp readingModule.h
		$(CXX) -o  readingModule.o -c readingModule.cpp $(CXXFLAGS)

clean:
		rm -f *.o
```

warto podmienić ścieżkę kompilatora ```CXX``` na prawdziwą w danym systemie

w elipsie ustawiamy tak by wykonywał operację `make all`