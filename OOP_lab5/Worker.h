#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#include "Reader.h"
#include "Writer.h"
#include "Multipliers.h"
#include <vector>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <atomic>
#include <thread>

class worker{
public:
    worker(reader &_read, writer &_write, unsigned int _numOfThreads) :
        read(_read), write(_write), numOfThreads(_numOfThreads) {};

    void Go();

protected:

    void Producer();

    void Consumer();

    void Pause();

    void Task(uint64_t &) ; // V

    void Signal();

    void PrintResult(string );

    unsigned int numOfThreads, paused = 0, completed = 0;
    writer &write;
    reader &read;
    atomic<bool> exit;
    atomic<bool> pause;
    atomic<bool> done;
    atomic<bool> eof;
    condition_variable cv_queue, cv_pause;
    mutex mx_queue, mx_pause, mx_print, mx_done;
    queue<uint64_t> num_queue;

};

#endif
