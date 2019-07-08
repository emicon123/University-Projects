#ifndef SONGINFORMATION_H
#define SONGINFORMATION_H

#include <QMediaPlayer>
#include <QImage>

#include "lyrics.h"

class SongInformation
{
public:
	SongInformation();
	SongInformation(QMediaPlayer &player);
    QString FetchLyrics();
	Lyrics lyricsAPI;

public:
	QString albumArtist;
	QString albumTitle;
	uint audioBitRate;
	QString audioCodec;
	QStringList author;
	uint averageLevel;
	uint channelCount;
	QStringList contributingArtist;
	QString description;
	qlonglong duration;
	QStringList genre;
	QString lyrics;
	uint peakValue;
	uint sampleRate;
	QImage thumbnailImage;
	QString title;
	uint trackNumber;
	QString url;
	uint year;

};

#endif // SONGINFORMATION_H
