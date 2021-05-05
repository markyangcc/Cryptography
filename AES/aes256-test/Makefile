XX = g++
CXXFLAGS = -Wall -g

all:	encrypt decrypt aes256.o

encrypt:	encrypt.cpp \
			aes256.o

		$(CXX) $(CXXFLAGS) encrypt.cpp aes256.o -o encrypt

decrypt:	decrypt.cpp \
			aes256.o

		$(CXX) $(CXXFLAGS) decrypt.cpp aes256.o -o decrypt


aes256.o:	aes256.cpp
		$(CXX) $(CXXFLAGS) -c aes256.cpp -o aes256.o

clean:
	rm *.o *.dat *.file encrypt decrypt
