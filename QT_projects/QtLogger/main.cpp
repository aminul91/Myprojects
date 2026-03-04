#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include "QtLogger.h"

int main(int argc, char *argv[])
{
    logger.log("Application started");

    int hr = 123;
    logger.log(QString("After DeleteChannel call: %1").arg(hr, 0, 16));

}
