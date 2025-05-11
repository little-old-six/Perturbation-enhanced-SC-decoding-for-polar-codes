#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
using namespace std;



std::vector<int> countRightSubtrees(int n) {
    int N = std::pow(2, n);  
    std::vector<int> rightSubtreeCounts(N, 0);

    for (int i = 0; i < N; ++i) {
        int node = i + N; 
        int rightCount = 0;

        while (node > 1) {
            if (node % 2 == 1) {
                ++rightCount;
            }
            node /= 2;
        }

        rightSubtreeCounts[i] = rightCount;
    }

    return rightSubtreeCounts;
}

int main() {
    int n = 12;

    cout << "Enter n: ";
    cin >> n;


    std::vector<int> result = countRightSubtrees(n);


    cout << "\nn = " << n << "\n";
    cout << "N = " << pow(2,n) << "\n\n";


    // 输出结果
    std::cout << "Number of required g-functions for estimating each bit：\n";
    for (int count : result) {
        std::cout << count << ", ";
    }
    std::cout << "\n\n";


    system("pause");
    getchar();
    return 0;
}
