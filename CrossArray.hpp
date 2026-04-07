#ifndef CROSSARRAY_HPP
#define CROSSARRAY_HPP

namespace sjtu {
    class CrossArray{
    private:
        int** data;
        int* lengths;
        int capacity;
        int count;
    public:
        explicit CrossArray(int lines) {
            capacity = lines;
            count = 0;
            data = new int*[capacity];
            lengths = new int[capacity];
            for (int i = 0; i < capacity; ++i) {
                data[i] = nullptr;
                lengths[i] = 0;
            }
        }

        CrossArray(const CrossArray & o) {
            capacity = o.capacity;
            count = o.count;
            data = new int*[capacity];
            lengths = new int[capacity];
            for (int i = 0; i < capacity; ++i) {
                lengths[i] = o.lengths[i];
                if (o.data[i] != nullptr) {
                    data[i] = new int[lengths[i]];
                    for (int j = 0; j < lengths[i]; ++j) {
                        data[i][j] = o.data[i][j];
                    }
                } else {
                    data[i] = nullptr;
                }
            }
        }

        CrossArray & operator=(const CrossArray & o) {
            if (this == &o) return *this;
            for (int i = 0; i < capacity; ++i) {
                if (data[i] != nullptr) {
                    delete[] data[i];
                }
            }
            delete[] data;
            delete[] lengths;

            capacity = o.capacity;
            count = o.count;
            data = new int*[capacity];
            lengths = new int[capacity];
            for (int i = 0; i < capacity; ++i) {
                lengths[i] = o.lengths[i];
                if (o.data[i] != nullptr) {
                    data[i] = new int[lengths[i]];
                    for (int j = 0; j < lengths[i]; ++j) {
                        data[i][j] = o.data[i][j];
                    }
                } else {
                    data[i] = nullptr;
                }
            }
            return *this;
        }

        CrossArray & WhichGreater(CrossArray & o) {
            int my_total = 0;
            for (int i = 0; i < capacity; ++i) {
                my_total += lengths[i];
            }
            int o_total = 0;
            for (int i = 0; i < o.capacity; ++i) {
                o_total += o.lengths[i];
            }
            if (o_total > my_total) {
                return o;
            }
            return *this;
        }

        bool IsSame(const CrossArray & o) {
            return this == &o;
        }

        bool InsertArrays(const int * Input, int size) {
            if (count >= capacity) {
                return false;
            }
            data[count] = new int[size];
            for (int i = 0; i < size; ++i) {
                data[count][i] = Input[i];
            }
            lengths[count] = size;
            count++;
            return true;
        }

        void AppendArrays(const int * Input, int Line, int size) {
            int old_size = lengths[Line];
            int new_size = old_size + size;
            int* new_arr = new int[new_size];
            for (int i = 0; i < old_size; ++i) {
                new_arr[i] = data[Line][i];
            }
            for (int i = 0; i < size; ++i) {
                new_arr[old_size + i] = Input[i];
            }
            if (data[Line] != nullptr) {
                delete[] data[Line];
            }
            data[Line] = new_arr;
            lengths[Line] = new_size;
        }

        void DoubleCrossLength() {
            int new_capacity = capacity * 2;
            int** new_data = new int*[new_capacity];
            int* new_lengths = new int[new_capacity];
            for (int i = 0; i < capacity; ++i) {
                new_data[i] = data[i];
                new_lengths[i] = lengths[i];
            }
            for (int i = capacity; i < new_capacity; ++i) {
                new_data[i] = nullptr;
                new_lengths[i] = 0;
            }
            delete[] data;
            delete[] lengths;
            data = new_data;
            lengths = new_lengths;
            capacity = new_capacity;
        }

        const int * AtArray(int i) {
            return data[i];
        }

        int & At(int i , int j) {
            return data[i][j];
        }

        ~CrossArray() {
            for (int i = 0; i < capacity; ++i) {
                if (data[i] != nullptr) {
                    delete[] data[i];
                }
            }
            delete[] data;
            delete[] lengths;
        }
    };
}

#endif