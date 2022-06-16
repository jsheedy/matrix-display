# bitboard.o:
# 	gcc -c
# CPPFLAGS=-g $(shell root-config --cflags)

# this works and makes a binary but
# ❯ ./bitboard
# zsh: exec format error: ./bitboard

CPPFLAGS=-g
CXX=g++
# CXX=${HOME}/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++
# LDFLAGS=-g $(shell root-config --ldflags)
LDFLAGS=-g
#  -I$(HOME)/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I$(HOME)/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard -I${HOME}/Documents/Arduino/libraries/FastLED/src/
# LDLIBS=$(shell root-config --libs)
LDLIBS=
SRCS=bitboard.cpp driver.cpp
OBJS=bitboard.o driver.o
# OBJS=$(subst .cpp, .o, $(SRCS))

bitboard: $(OBJS)
	$(CXX) $(LDFLAGS) -o bitboard $(OBJS) $(LDLIBS)

%.o: %.CPPFLAGS
	$(CXX) $(CPPFLAGS) -c $<

bitboard.o: bitboard.cpp
	$(CXX) $(CPPFLAGS) -c bitboard.cpp

driver.o: driver.cpp
	$(CXX) $(CPPFLAGS) -c driver.cpp

# all: bitboard.o
# 	gcc -o bitboard bitboard.h bitbo

clean:
	rm *.o bitboard

build: u_cube.ino
	arduino-cli compile --warnings all --fqbn adafruit:avr:itsybitsy32u4_5V  .

upload: build
	arduino-cli upload -v  --fqbn adafruit:avr:itsybitsy32u4_5V -programmer list