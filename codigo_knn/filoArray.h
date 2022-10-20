#pragma once

class filoArray {
    public:
        void initializeTo(float value);
        void insertValue(float value);
        float* getDataPointer();
    private:
        float data[100];
};
