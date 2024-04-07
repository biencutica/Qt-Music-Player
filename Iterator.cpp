#include "Iterator.h"


void SongCollectionIterator::first()
{
	current = 0;
}

void SongCollectionIterator::next()
{
	current++;
}

bool SongCollectionIterator::is_done() const
{
	return current >= songs.size();
}

const Song& SongCollectionIterator::get_current() const
{
	if (is_done()) {
		throw std::out_of_range("Iterator is done.");
	}
	return songs[current];
}
