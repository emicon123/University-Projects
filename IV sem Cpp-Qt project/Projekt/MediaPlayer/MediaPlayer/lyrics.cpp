#include "lyrics.h"

Lyrics::Lyrics()
{

}

QString Lyrics::FetchLyrics(QString title, QString artist)
{
     // Zwraca wartosc tekstu
     QString lyrics = "";
     QNetworkAccessManager manager;


     // utworzenie petli eventow na stosie
     QEventLoop eventLoop;
     QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

     // HTTP request
     QString host = "https://api.musixmatch.com/ws/1.1/matcher.lyrics.get?format=json";
     QString q_track = "&q_track=" + title + ";";
     QString q_artist = "&q_artist=" + artist + "";
     QString q_apikey = "&apikey=12c62feb63b58d86cd0ce1762c8223aa";

     // Budowanie adresu URL z wczesniejszych argumentow
     QUrl url(host + q_track + q_artist + q_apikey);
     QNetworkRequest request(url);
     request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
     request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
     request.setRawHeader("Accept", "application/json");
     request.setRawHeader("Content-Type", "application/json");


     QNetworkReply* reply = manager.get(request);
     eventLoop.exec(); // blokowanie stosu dopoki metoda finished() nie zostanie wywolana

     // Przetwarzanie danych zwrotnych i czyszczenie stosu
     if (reply->error() == QNetworkReply::NoError)
     {
          QByteArray ba = reply->readAll();
          QJsonDocument doc = QJsonDocument::fromJson(ba.toStdString().c_str());
          QJsonObject json = doc.object();
          QJsonObject msg = json["message"].toObject();
          QJsonObject body = msg["body"].toObject();
          QJsonObject lyr = body["lyrics"].toObject();
          lyrics = lyr["lyrics_body"].toString();
     }

     reply->deleteLater();

     return lyrics;
}
