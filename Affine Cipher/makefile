
main:  main.cpp affinecipher.o

		g++ affinecipher.o main.cpp -o main

caesarcipher.o: affinecipher.cpp
		g++ -c affinecipher.cpp -o affinecipher.o

clean:
		rm -f *.o main
