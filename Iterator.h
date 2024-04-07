#pragma once
#include "Song.h"
#include <vector>

class SongCollectionIterator {

private:
    const std::vector<Song> songs;
    size_t current;

public:
    // Constructor
    SongCollectionIterator(const SongCollection& _songs): songs(_songs.songs), current(0){}

    // Iterator methods
    void first();
    void next();
    bool is_done() const;
    const Song& get_current() const;
};