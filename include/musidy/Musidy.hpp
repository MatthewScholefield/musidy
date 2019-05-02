#pragma once

#include <musidy/Instrument.hpp>
#include <musidy/SoundSystem.hpp>
#include <musidy/songCreation/ScorePlayer.hpp>

/**
 * Dynamic music generation class
 * Holds all the components required for producing dynamic music
 */
class Musidy {
public:
    /**
     * Create a new dynamic music instance
     * @param instrumentFile The sf2 file that contains the instrument to be played on
     * @param gain The volume gain that the instrument should be played at
     */
    explicit Musidy(const std::string &instrumentFile, float gain = 0.f);

    /**
     * @return instrument used to produce sounds
     */
    Instrument &getInstrument();

    /**
     * @return interface to sound system
     */
    SoundSystem &getSoundSystem();

    /**
     * @return scorePlayer object used to generate notes on a high level
     */
    ScorePlayer &getScorePlayer();

private:
    Instrument instrument;
    SoundSystem soundSystem;
    ScorePlayer scorePlayer;
};
