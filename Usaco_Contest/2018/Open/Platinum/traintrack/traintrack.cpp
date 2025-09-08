#include "grader.h"
#include <algorithm>
#define pb push_back
#define mp make_pair

using namespace std;

const int BUCKETS = 1000;

bool startpoint(int i) {
    return i % BUCKETS == 0;
}

int bucket(int i) {
    return i / BUCKETS;
}

void helpBessie(int ID) {
    int N = getTrainLength();
    int K = getWindowLength();
    bool afternoon = getCurrentPassIndex();
    int pos = getCurrentCarIndex();

    if (afternoon == false) {
        // We are in the morning
        
        int b = bucket(pos);
        if (startpoint(pos)) {
            set(b, ID);
        }
        else {
            set(b, min(get(b), ID));
        }
    }
    else {
        // We are in the afternoon, define the early and late buckets
    }
}