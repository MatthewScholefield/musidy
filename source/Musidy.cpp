
#include <musidy/Musidy.hpp>

#include "musidy/Musidy.hpp"

Musidy::Musidy(const std::string &instrumentFile, float gain) :
        instrument(instrumentFile, gain),
        soundSystem([&](float *f, size_t n) { instrument.render(f, n); }),
        scorePlayer(instrument) {}

Instrument &Musidy::getInstrument() {
    return instrument;
}

SoundSystem &Musidy::getSoundSystem() {
    return soundSystem;
}

ScorePlayer &Musidy::getScorePlayer() {
    return scorePlayer;
}
