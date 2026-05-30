
// Copyright 2022 NNTU-CS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "train.h"

int main() {
    srand(time(0));
    std::cout << "n\toff\ton\trandom\n";
    for (int n = 10; n <= 500; n += 10) {
        Train trainOff;
        for (int i = 0; i < n; ++i) trainOff.addCar(false);
        trainOff.getLength();
        int offOps = trainOff.getOpCount();

        Train trainOn;
        for (int i = 0; i < n; ++i) trainOn.addCar(true);
        trainOn.getLength();
        int onOps = trainOn.getOpCount();

        Train trainRnd;
        for (int i = 0; i < n; ++i) trainRnd.addCar(rand() % 2);
        trainRnd.getLength();
        int rndOps = trainRnd.getOpCount();

        std::cout << n << "\t" << offOps << "\t" << onOps << "\t" << rndOps << "\n";
    }
    return 0;
}
