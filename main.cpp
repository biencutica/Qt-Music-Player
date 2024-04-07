#include <iostream>
#include "Iterator.h"

int main() {
    try {
        SongCollection songs("songs.txt");
        SongCollectionIterator iter(songs);

        for (iter.first(); !iter.is_done(); iter.next()) {
            const Song& song = iter.get_current(); // get the current song from the iterator
            std::cout << "Title: " << song.getTitle() << std::endl;
            std::cout << "Artist: " << song.getArtist() << std::endl;
            std::cout << "Lyrics: ";
            const std::vector<std::string>& lyrics = song.getLyrics();
            for (const std::string& word : lyrics)
                std::cout << word << " ";
            std::cout << "\n"<< "\n";
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
