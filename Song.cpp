#include"Song.h"
#include<fstream>
#include<stdexcept>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<sstream>
#include<algorithm>
Song::Song(std::string _artist, std::string _title, std::string _lyrics)
{
    artist = _artist.substr(1, _artist.size() -2);
    title = _title.substr(1, _title.size() -1);

    std::stringstream ss(_lyrics);
    std::string line;

    while (std::getline(ss, line, '\0')) {

        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });

        line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) { return std::ispunct(c) || std::isdigit(c); }), line.end());
        //remove_if shifts all elements that do not match the condition to the front of the line
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            lyrics.push_back(word);
        }
    }
}

std::string Song::getArtist() const
{
	return artist;
}

std::string Song::getTitle() const
{
	return title;
}

std::vector<std::string> Song::getLyrics() const
{
	return lyrics;
}


//Song Collection -------------------------------------------------------

SongCollection::SongCollection(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) 
        throw std::runtime_error("Failed to open file: " + filename);

    std::string line;
    std::string artist;
    std::string title;
    std::string lyrics;
    bool is_lyrics = false;

    while (std::getline(file, line)) {
        if (line.find("ARTIST=") == 0) {
            artist = line.substr(7, line.size() - 7);
            is_lyrics = false;
        }
        else if (line.find("TITLE=") == 0) {
            title = line.substr(6, line.size() - 7);
            is_lyrics = false;
        }
        else if (line.find("LYRICS=") == 0) {
            lyrics = line.substr(8, line.size() - 8) + " ";
            is_lyrics = true;
        }
        else if (is_lyrics)
            lyrics += line + " ";

        if (is_lyrics && line == "" "") {
            //end of current song, add to collection
            songs.push_back(Song(artist, title, lyrics));
            is_lyrics = false;
        }

    }
}

void SongCollection::load_from_file(const std::string& filename)
{
    *this = SongCollection(filename);
}

const std::vector<Song>& SongCollection::get_songs() const {
    return songs;
}

std::set<std::string> SongCollection::get_unique_artists() const {
    std::set<std::string> unique_artists;
    const std::vector<Song>& song_list = get_songs();
    for (const Song& song : song_list) {
        unique_artists.insert(song.getArtist());
    }
    return unique_artists;
}

std::unordered_map<std::string, std::vector<Song>> SongCollection::group_by_artist() const
{
    std::unordered_map<std::string, std::vector<Song>> groups;
    for (const auto& song : songs)
        groups[song.getArtist()].push_back(song);
    return groups;
}

void SongCollection::print_top_ten_artists() const
{
    auto groups = group_by_artist();
    std::vector<std::pair<std::string, int>> artistCounts(groups.size());

    std::transform(groups.begin(), groups.end(), artistCounts.begin(),[](const auto& p) { return std::make_pair(p.first, p.second.size()); });
    std::partial_sort(artistCounts.begin(), artistCounts.begin() + 10, artistCounts.end(),[](const auto& p1, const auto& p2) { return p1.second > p2.second; });
    std::cout << "Top 10 Artists by Song Count: " << std::endl;
    for (int i = 0; i < std::min(10, static_cast<int>(artistCounts.size())); i++)
        std::cout << i + 1 << ". " << artistCounts[i].first << ": " << artistCounts[i].second << std::endl;
}

void SongCollection::sort_by_artist()
{
    std::sort(songs.begin(), songs.end(), [](const Song& s1, const Song& s2) {
            return s1.getArtist() < s2.getArtist();
        });
}

void SongCollection::sort_by_title()
{
    std::sort(songs.begin(), songs.end(),[](const Song& s1, const Song& s2) {
            return s1.getTitle() > s2.getTitle();
        });
}

void SongCollection::sort_by_lyrics()
{
    std::sort(songs.begin(), songs.end(),[](const Song& s1, const Song& s2) {
            return s1.getLyrics().size() < s2.getLyrics().size();
        });
}


