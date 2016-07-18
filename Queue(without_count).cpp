#include <iostream>
using namespace std;

enum ErrorCode{success, underflow, overflow};

const int maxQueue = 5;

template <class QueueEntry>
class MyQueue {
	public:
	MyQueue() {
		front = 0;
		rear = maxQueue - 1;
	}
	bool empty() const {
		return (rear+1)%maxQueue == front;
	}
	ErrorCode append(const QueueEntry &item) {
		if (this->full() == true) return overflow;
		rear = (rear+1)%maxQueue;
		entry[rear] = item;
		return success;
	} //入队 
	ErrorCode serve() {
		if (this->empty() == true) return underflow;
		front = (front+1)%maxQueue;
		return success;
	} //出队
	ErrorCode retrieve(QueueEntry &item) const {
		if (this->empty() == true) return underflow;
		item = entry[front];
		return success;
	} //队首元素 
	bool full() const {
		return (rear+2)%maxQueue == front;
	}
	int size() const {
		if (this->full() == true) return maxQueue-1;
		else if (this->empty() == true) return 0;
		else if (rear >= front) return rear-front+1;
		else return maxQueue+1+rear-front;
	}
	void clear() {
		front = 0;
		rear = maxQueue-1;
	} 
	ErrorCode retrieve_and_serve(QueueEntry &item) {
		if (this->empty() == true) return underflow;
		item = entry[front];
		front = (front+1)%maxQueue;
		return success;
	}
	private:
	int front;
	int rear;
	QueueEntry entry[5];
};

//测试 
int main() {
	MyQueue<int> q;
	int item = 0;
		cout << q.size() << " "; //0 
	q.append(10);
	cout << q.size() << " "; //1
	q.append(11);
		cout << q.size() << " "; //2
	q.append(13);
		cout << q.size() << " "; //3
	q.append(14); 
		cout << q.size() << " "; //4 
	q.append(15);
		cout << q.size() << " ";  //4
	q.serve();
	q.serve();
		cout << q.size() << " "; //2
		q.serve();
			cout << q.size() << " ";//1
			cout << "\n";
				q.append(10); 
	cout << q.size() << " "; //2
	q.append(11);
		cout << q.size() << " "; //3
	q.append(13);
		cout << q.size() << " "; //4
	q.append(14); 
		cout << q.size() << " "; //4
	q.append(15);
		cout << q.size() << " "; //4
	q.serve();
	q.serve();
		cout << q.size() << " "; //2
		q.serve();
			cout << q.size() << " ";//1
	return 0;
}


