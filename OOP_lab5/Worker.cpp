#include "Worker.h"
#include <iostream>

using namespace std;

void worker::Go() {
    exit = false;
    pause = false;
    done = false;
    eof = false;
    if (numOfThreads < 1 || numOfThreads > 8)
        numOfThreads = 1;
    vector<thread> threads(numOfThreads);
    for (int i = 0; i < numOfThreads; ++i){
        threads[i] = thread(&worker::Consumer, this);
    }
    thread prod(&worker::Producer, this);

    Signal();

    for (int i = 0; i < numOfThreads; ++i){
        threads[i].join();
    }

    prod.join();

    write.Close();
}

void worker::Signal() {
    cout << "Enter pause, resume or exit\n";
    while (!done) {
        string sig;
        cin >> sig;
        if (sig == "exit") {
            exit = true;
            unique_lock<mutex> mx(mx_queue);
            while (!num_queue.empty())
                num_queue.pop();
            cv_queue.notify_all();
            break;
        }
        else
        if (sig == "pause") {
            pause = true;
            cv_queue.notify_all();
        }
        else
        if (sig == "resume") {
            pause = false;
            cv_pause.notify_all();
        }
    }
}

void worker::Producer() {
    while (!exit && !read.IsFileEnd()) {
        uint64_t num = read.Read();
        {
            unique_lock<mutex> mx(mx_queue);
            num_queue.push(num);
        }
        cv_queue.notify_one();
    }
    eof = true;
    read.Close();
}

void worker::Consumer() {
    while (!exit){
        unique_lock<mutex> mx(mx_queue);
        while (!exit && !pause && num_queue.empty() && !eof)
            cv_queue.wait(mx);
        if (eof && num_queue.empty())
            break;
        if (pause)
            Pause();
        while (!num_queue.empty()) {
            uint64_t num = num_queue.front();
            num_queue.pop();
            mx.unlock();
            Task(num);
            if (exit)
                break;
            if (pause)
                Pause();
            mx.lock();
        }
    }
    if (!exit){
        unique_lock<mutex> mxd(mx_done);
        ++completed;
        if (completed == numOfThreads){
            done = true;
            cout << "Done!\nEnter any symbol to finish\n";
        }
    }
}

void worker::PrintResult(string str) {
    unique_lock<mutex> mx(mx_print);
    write.Print(str);
}

void worker::Pause() {
    unique_lock<mutex> mx(mx_pause);
    ++paused;
    if (paused == numOfThreads)
        write.Close();
    while (pause)
        cv_pause.wait(mx);
    if (paused == numOfThreads)
        write.Open();
    --paused;
}

void worker::Task(uint64_t & num) {
    multipliers mul(num);
    mul.Factorization();
    PrintResult(mul.Get_Factorization_Str() + '\n');
};
