#pragma once

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QThread>
#include <QMutex>

class QtLogger
{
public:
    explicit QtLogger(const QString& filename)
        : logFile(filename)
    {
        logFile.open(QIODevice::Append | QIODevice::Text);
    }

    void log(const QString& message)
    {
        QMutexLocker locker(&mutex);

        if (!logFile.isOpen())
            return;

        QTextStream out(&logFile);

        QString timestamp =
            QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss.zzz");

        QString threadId =
            QString::number((quintptr)QThread::currentThreadId(), 16);

        out << "[" << timestamp << "]"
            << "[Thread " << threadId << "] "
            << message << "\n";

        out.flush();
    }

private:
    QFile logFile;
    QMutex mutex;
};


// ✅ Global logger instance (C++17 required)
inline QtLogger logger("C:/Target/qt_log.txt");
