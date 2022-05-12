#include <bits/stdc++.h>

using namespace std;

long double dp[13][13][8200];
long double proc[13][13][8200];
bool dead[13] = {false};

long double shoot_pos[13];

int assigned_numbers[13] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};
int n;

