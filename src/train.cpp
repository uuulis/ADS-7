// src/train.cpp
// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    countOp = 0;
    first = nullptr;
}

Train::~Train() {
    if (!first) return;
    Car* current = first;
    do {
        Car* next = current->next;
        delete current;
        current = next;
    } while (current != first);
}

void Train::addCar(bool light) {
    Car* newCar = new Car;
    newCar->light = light;
    newCar->next = nullptr;
    newCar->prev = nullptr;
    if (!first) {
        first = newCar;
        newCar->next = newCar;
        newCar->prev = newCar;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Car* current = first;
    // выключаем свет в первом вагоне
    current->light = false;
    int step = 1;
    while (true) {
        for (int i = 0; i < step; ++i) {
            current = current->next;
            ++countOp;
        }
        if (!current->light) {
            current->light = true;
            step = 1;
            current = first;
            ++countOp;
        } else {
            break;
        }
    }
    int length = 1;
    current = current->next;
    ++countOp;
    while (current != first) {
        ++length;
        current = current->next;
        ++countOp;
    }
    return length;
}

int Train::getOpCount() {
    return countOp;
}
