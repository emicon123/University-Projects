#include "songinformation.h"

SongInformation::SongInformation()
{

}

SongInformation::SongInformation(QMediaPlayer& player)
{
	albumArtist = player.metaData("AlbumArtist").value<QString>();
	albumTitle = player.metaData("AlbumTitle").value<QString>();
	audioBitRate = player.metaData("AudioBitRate").value<uint>();
	audioCodec = player.metaData("AudioCodec").value<QString>();
	author = player.metaData("Author").value<QStringList>();
	averageLevel = player.metaData("AverageLevel").value<uint>();
	channelCount = player.metaData("ChannelCount").value<uint>();
	contributingArtist = player.metaData("ContributingArtist").value<QStringList>();
	description = player.metaData("Description").value<QString>();
	duration = player.metaData("Duration").value<qlonglong>();
	genre = player.metaData("Genre").value<QStringList>();
	peakValue = player.metaData("PeakValue").value<uint>();
	sampleRate = player.metaData("SampleRate").value<uint>();
	thumbnailImage = player.metaData("ThumbnailImage").value<QImage>();
	title = player.metaData("Title").value<QString>();
	trackNumber = player.metaData("TrackNumber").value<uint>();
	url = player.media().canonicalUrl().toString();
	year = player.metaData("Year").value<uint>();
 }

QString SongInformation::FetchLyrics()
{
	QString lyricartist = "";
    if (albumArtist == "")
    {
        if (!contributingArtist.empty())
        {
            for (int index = 0; index < contributingArtist.size(); ++index)
            {
                if (index == 0)
                {
					lyricartist += contributingArtist.at(index);
				}
                else
                {
					lyricartist += (", " + contributingArtist.at(index));
				}
			}
		}
	}
    else
    {
		lyricartist = albumArtist;
	}
    return lyricsAPI.FetchLyrics(title, lyricartist);
}
