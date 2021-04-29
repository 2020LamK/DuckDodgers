#ifndef DUCKDODGERS_QUEUE_H
#define DUCKDODGERS_QUEUE_H

using namespace std;

const int32_t
        QUEUE_SIZE = 64;

template <typename QueueType>
class Queue {
public:
    Queue(void) {
        data = new QueueType[QUEUE_SIZE];
        capacity = QUEUE_SIZE;

        count = tail = 0;
        head = capacity - 1;
    }

    ~Queue() {

        delete[] data;
    }

    void clear() {
        count = tail = 0;
        head = capacity - 1;
    }

    int32_t size() { return count; }
    bool isEmpty() { return !count; }

    void enqueue(const QueueType &d) {
        if (count == QUEUE_SIZE) {
            int tmpCap = 2 * capacity;
            QueueType *tmpData = new QueueType[tmpCap];

            if (tmpData == nullptr)
                throw overflow_error("Queue is full");

            for (int i = 0; i < capacity; i++)
                tmpData[i] = data[(head+i+1)%capacity];

            delete[] data;

            head = tmpCap - 1;
            tail = capacity;

            data = tmpData;
            capacity = tmpCap;
        }

        data[tail] = d;
        tail = (tail + 1) % QUEUE_SIZE;
        count++;
    }

    QueueType dequeue() {

        if (count == 0)
            throw underflow_error("Queue is empty");

        head = (head + 1) % QUEUE_SIZE;
        count--;

        return data[head];
    }

private:
    int32_t
            head, tail,
            count,
            capacity;
    QueueType
            *data;
};

#endif //DUCKDODGERS_QUEUE_H
