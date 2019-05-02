CXX = clang++
CXXFLAGS = -std=c++11 -fPIC $(shell pkg-config --cflags portaudiocpp) -Iinclude
LDFLAGS = $(shell pkg-config --libs portaudiocpp) -shared
PREFIX ?= /usr/local

all: libmusidy.so

SRCS = source/Instrument.cpp include/musidy/Instrument.hpp source/Musidy.cpp include/musidy/Musidy.hpp source/SoundSystem.cpp include/musidy/SoundSystem.hpp source/utils.cpp include/musidy/utils.hpp source/songCreation/chordProgressions.cpp include/musidy/songCreation/chordProgressions.hpp source/songCreation/MusicScore.cpp include/musidy/songCreation/MusicScore.hpp source/songCreation/noteUtils.cpp include/musidy/songCreation/noteUtils.hpp source/songCreation/ScoreGenerator.cpp include/musidy/songCreation/ScoreGenerator.hpp source/songCreation/ScorePlayer.cpp include/musidy/songCreation/ScorePlayer.hpp

%.o: %.c
	$(CXX) -c $(CXXFLAGS) $<

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^ -MF  ./.depend;

include .depend

libmusidy.so: source/Musidy.o source/SoundSystem.o source/Instrument.o source/songCreation/ScorePlayer.o source/songCreation/ScoreGenerator.o source/songCreation/noteUtils.o source/songCreation/MusicScore.o source/songCreation/chordProgressions.o
	$(CXX) $(LDFLAGS) $< -o libmusidy.so

clean:
	rm -rvf libmusidy.so source/*.o source/songCreation/*.o

