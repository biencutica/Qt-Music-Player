#ifndef SONG_H
#define SONG_H
#include<iostream>
#include<string>

class Song
{
public:
    Song() : title(""), artist(""), duration(""), link(""){}
    Song(const std::string& _title, const std::string& _artist, const std::string& _duration, const std::string& _link)
        : title(_title), artist(_artist), duration(_duration), link(_link) {}

    //getters
    std::string get_title() const{return title;}
    std::string get_artist() const{return artist;}
    std::string get_duration() const{return duration;}
    std::string get_link() const{return link;}

    //setters
    void set_title(std::string newtitle){title = newtitle;}
    void set_artist(std::string newartist){artist = newartist;}
    void set_duration(std::string newduration) {duration = newduration;}
    void set_link(std::string newlink) { link = newlink;}

    std::string display_string() const;

private:
    std::string title;
    std::string artist;
    std::string duration;
    std::string link;
};

#endif // SONG_H
