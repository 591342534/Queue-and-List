#include <iostream>

enum ErrorCode{success, underflow, overflow};

const int maxQueue = 100;

template <class QueueEntry>
class MyQueue {
	public:
	MyQueue() {
		front = 0;
		rear = maxQueue - 1;
		count = 0;
	}
	bool empty() const {
		return count == 0;
	}
	ErrorCode append(const QueueEntry &item) {
		if (count >= maxQueue) return overflow;
		rear = (rear+1)%maxQueue;
		count++;
		entry[rear] = item;
		return success;
	} //入队 
	ErrorCode serve() {
		if (count <= 0) return underflow;
		front = (front+1)%maxQueue;
		count--;
		return success;
	} //出队
	ErrorCode retrieve(QueueEntry &item) const {
		if (count <= 0) return underflow;
		item = entry[front];
		return success;
	} //队首元素 
	bool full() const {
		return count >= maxQueue;
	}
	int size() const {
		return count;
	}
	void clear() {
		front = 0;
		rear = maxQueue-1;
		count = 0;
	} 
	ErrorCode retrieve_and_serve(QueueEntry &item) {
		if (count <= 0) return underflow;
		item = entry[front];
		front = (front+1)%maxQueue;
		count--;
		return success;
	}
	private:
	int front;
	int rear;
	QueueEntry entry[100];
	int count;
};

int main() {
	MyQueue<int> q;
	int item = 0;
	q.append(10);
	q.append(11);
	q.append(12);
	q.append(13);
	q.append(14);
	q.append(15);
	q.append(16);
	q.serve();
    q.serve();
    q.serve();
    q.serve();
    if (q.serve() != success) std::cout << "fail\n";
    if (q.serve() != success) std::cout << "fail\n";
	return 0;
}

