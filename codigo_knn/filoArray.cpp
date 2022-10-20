#include "filoArray.h"
#include <Arduino.h>

void filoArray::initializeTo(float value) {
    for (int i = 0; i < 100; i++) {
        data[i] = value;
    }
}

void filoArray::insertValue(float value) {
    float arrCopy[100];

    for (int i = 0; i < 100; i++) arrCopy[i] = data[i];

    float lastVal = value;
    for (int i = 0; i < 100; i++) {
        data[i] = lastVal;

        lastVal = arrCopy[i];
    }
}

float* filoArray::getDataPointer() {
    return data;
}
