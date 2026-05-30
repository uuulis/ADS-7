
// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car;
    newCar->light = light;
    newCar->next = nullptr;
    newCar->prev = nullptr;
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
        return;
    }
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Car* cur = first;
    cur->light = true;
    while (true) {
        int steps = 0;
        do {
            cur = cur->next;
            ++steps;
            ++countOp;
        } while (!cur->light);
        cur->light = false;
        for (int j = 0; j < steps; ++j) {
            cur = cur->prev;
            ++countOp;
        }
        if (!cur->light) return steps;
    }
}
