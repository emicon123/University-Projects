#ifndef LYRICS_H
#define LYRICS_H

#include <QEventLoop>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextEdit>


class Lyrics : public QObject
{
	 
public:
	Lyrics();
    QString FetchLyrics(QString title, QString artist);

};

#endif // LYRICS_H
