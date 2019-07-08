#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDateTime>

// Zmienne użytkowe
static const size_t errorCodesSize = 6;
const std::string mediaPlayerErrorCodes[errorCodesSize] = {
	"NoError",
	"ResourceError",
	"FormatError",
	"NetworkError",
	"AccessDeniedError",
	"ServiceMissingError"
};

enum SeekState
{
	DEFAULT = 0,
	PLAYING = 1,
	PRESSED = 2,
	MOVING = 3,
};

// Funkcje użytkowe
static QString mstosms(qlonglong ms)
{
	return QDateTime::fromTime_t((ms + 500) / 1000).toString("mm:ss");
}



#endif // UTIL_H
