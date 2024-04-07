#include "song.h"


std::string Song::display_string() const{
    std::string result = "\nTitle: " + title;
    result +="\nArtist: " + artist;
    result +="\nDuration: " + duration;
    result+="\nLink: " + link;
    return result;
}
