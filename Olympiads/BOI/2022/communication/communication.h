#include <utility>

/**
 * use this function in encode when you want to send a certain signal
 * (it might come out wrong, and the return value tells you which signal
 * was actually sent)
 */
int send(int);

/**
 * use this function in decode; it returns the next signal that was actually
 * sent during the corresponding call of encode
 */
int receive();

/**
 * implement these two functions yourself
 */
void encode(int, int);
std::pair<int, int> decode(int);