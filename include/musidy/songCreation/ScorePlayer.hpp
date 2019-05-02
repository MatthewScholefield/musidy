#pragma once

#include <vector>
#include <stdexcept>
#include <functional>
#include "musidy/Instrument.hpp"
#include "MusicScore.hpp"

/**
 * Plays a dynamically generated song on the given instrument
 */
class ScorePlayer {
public:
    /**
     * Create a new song generator
     * @param instrument The instrument to initialize
     * @param particles The particles system to visualize to
     */
    explicit ScorePlayer(Instrument &instrument);

    /**
     * Update the song with the given delta time
     * @param instrument The instrument to play on
     * @param dt Amount of time of the song to play
     */
    void update(Instrument &instrument, double dt);

    /**
     * @return The chord progression that's being played
     */
    const std::vector<int> getProgression() const;

    /**
     * Set the delay time between beats
     * @param noteInterval Time to set as separation between notes
     */
    void setNoteInterval(float noteInterval);

    /**
     * Get the delay time between beats
     * @return Separation between notes
     */
    float getNoteInterval() const;

    /**
     * Set a function to be called on every new chord
     * @param chordHandler A function that receives the tonality
     *                     and the root chord note as an integer
     */
    void setChordHandler(const std::function<void(Tonality, int)> &chordHandler);

    /**
    * Set a function to be called on every new note
    * @param chordHandler A function that receives the tonality and note as an integer
    */
    void setNoteHandler(const std::function<void(Tonality, int)> &noteHandler);

private:
    double noteInterval = 0.4;
    double noteTimer = 0.0;

    Tonality tonality;
    std::vector<int> chords;
    std::function<void(Tonality, int)> onChord;
    std::function<void(Tonality, int)> onNote;
    MusicScore score;
};
