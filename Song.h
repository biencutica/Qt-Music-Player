#pragma once
#include<iostream>
#include<set>
#include<unordered_map>
#include<vector>

class Song {
protected:
	std::string artist;
	std::string title;

private:
	std::vector<std::string> lyrics;

public:
	Song(std::string _artist, std::string _title, std::string _lyrics);
	std::string getArtist() const;
	std::string getTitle() const;
	std::vector<std::string> getLyrics() const;
};

class SongCollection {
	friend class SongCollectionIterator;
public:
	SongCollection(const std::string& file);
	void load_from_file(const std::string& filename);
	const std::vector<Song>& get_songs() const;
	std::set<std::string> get_unique_artists() const;
	std::unordered_map<std::string, std::vector<Song>> group_by_artist() const;
	void print_top_ten_artists() const;
	void sort_by_artist();
	void sort_by_title();
	void sort_by_lyrics();
	
private:
	std::vector<Song> songs;
};