#ifndef filo_array
#define filo_array

class filoArray {
    public:
        void initializeTo(float value);
        void insertValue(float value);
        float* getDataPointer();
    private:
        float data[100];
};

#endif
