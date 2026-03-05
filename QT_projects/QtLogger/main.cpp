#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include "QtLogger.h"
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> stopFlag(false); // atomic lock use here to get the updated value
//std::mutex mtx;
/*
A workwer thread example thread safe
*/
void workerFunction()
{
    for (int i = 1; i <= 10; i++)
    {
        if (stopFlag)   // check stop signal
            break;

        {

            logger.log(QString("Worker count: %1").arg(i));
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    //std::lock_guard<std::mutex> lock(mtx);
    logger.log("Worker finished.");
}
int main(int argc, char *argv[])
{

    logger.log("Application started");

    std::thread worker(workerFunction);

    // Main thread work
    for (int i = 1; i <= 5; i++)
    {
        {
            //std::lock_guard<std::mutex> lock(mtx);
            logger.log(QString("Main count: %1").arg(i));
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Stop worker early if needed
     stopFlag = true;

    if (worker.joinable())
    {
        logger.log(QString("Main waiting for worker..."));
        worker.join();
    }
    logger.log("Program finished.");
}
