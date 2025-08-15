/*
SAMPLE GRADER for task COMMUNICATION

USAGE:
place together with your solution and communication.h in the same directory, then open the terminal in this directory (right-click onto an empty spot in the directory, left click on "Open in terminal") and enter:
g++ <flags> sample_grader.cpp <solution_file>
e.g.:
g++ -std=c++17 sample_grader.cpp communication.cpp
This will create a file a.out in the current directory which you can execute from the terminal as ./a.out

INPUT/OUTPUT:
The sample grader first expects on standard input the integers N and X (1 <= X <= N).
Then, the grader calls encode(N, X) and writes to standard output a protocol of all
calls to send by your program. For each call to send it expects the return value on
standard input.

Afterwards the grader calls decode(N) and writes to standard output a protocol of all
calls to receive by your program. Upon termination, it writes your verdict to standard
output.
*/
#include<vector>
#include<cstdio>
#include<set>
#include<cstdlib>
#include<cstdarg>
#include<cassert>
#include"communication.h"

using namespace std;

void __attribute__((noreturn)) __attribute__((format(printf, 1, 2))) result(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    fprintf(stdout, "\n");
    va_end(args);
    exit(0);
}

namespace
{
    enum { ENCODE, DECODE } current_phase;
    int N, X;
    vector<int> signals;
    size_t cursor = 0;
    bool flipped = false;
}

int send(int s)
{
    if(current_phase == DECODE or (s != 0 and s != 1))
        result("Invalid send.");

    printf("send(%d) -> ", s); fflush(stdout);
    int answer;
    if(scanf("%d", &answer) != 1 or (answer != 0 and answer != 1))
        result("Invalid reply to send.");

    bool flipped_now = (s != answer);
    if(flipped and flipped_now)
        result("Invalid reply to send");
    flipped = flipped_now;

    signals.push_back(answer);
    if(signals.size() > (size_t) 250)
        result("Looks (and smells) fishy.");
    return signals.back();
}

int receive()
{
    if(current_phase == ENCODE)  result("Invalid receive.");
    if(cursor >= signals.size()) result("Assistant waiting for Godot.");
    int r = signals[cursor++];
    printf("receive() -> %d\n", r);
    return r;
}

int main()
{
    if(scanf("%d %d", &N, &X) != 2 or X < 1 or X > N)
        result("Invalid input.");

    current_phase = ENCODE;
    encode(N, X);
    current_phase = DECODE;
    auto r = decode(N);

    if(r.first < 1 or r.first > N or r.second < 1 or r.second > N)
        result("Invalid answer.");

    if(r.first == X or r.second == X)
        result("Correct: %d signals sent.", (int) signals.size());
    else
        result("Wrong answer.");
}
