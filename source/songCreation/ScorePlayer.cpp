#include <climits>
#include <iostream>
#include "musidy/songCreation/ScorePlayer.hpp"
#include "musidy/songCreation/noteUtils.hpp"
#include "musidy/songCreation/ScoreGenerator.hpp"
#include "musidy/utils.hpp"

ScorePlayer::ScorePlayer(Instrument &instrument) :
        tonality(getRandomTonality()), chords(generateProgression(tonality)),
        score(ScoreGenerator(chords).generate()) {
    instrument.setScale(60, tonality);
}

void ScorePlayer::update(Instrument &instrument, double dt) {
    if ((noteTimer -= dt) < 0.0) {
        noteTimer = noteInterval;
        const auto &chordNotes = score.getCurrentNotes(SongPart::Chords);
        if (!chordNotes.empty() && onChord) {
            onChord(tonality, chordNotes[0].note);
        }
        const auto &melodyNotes = score.getCurrentNotes(SongPart::Melody);
        if (!melodyNotes.empty() && onNote) {
            onNote(tonality, melodyNotes[0].note);
        }
        score.playBeat(instrument);
        if (score.getNumLoops() > 0) {
            score = ScoreGenerator(getRandomTonality()).generate();
        }
    }
}

const std::vector<int> ScorePlayer::getProgression() const {
    return chords;
}

void ScorePlayer::setNoteInterval(float noteInterval) {
    this->noteInterval = noteInterval;
}

float ScorePlayer::getNoteInterval() const {
    return float(noteInterval);
}

void ScorePlayer::setChordHandler(const std::function<void(Tonality, int)> &chordHandler) {
    onChord = chordHandler;
}

void ScorePlayer::setNoteHandler(const std::function<void(Tonality, int)> &noteHandler) {
    onNote = noteHandler;
}
