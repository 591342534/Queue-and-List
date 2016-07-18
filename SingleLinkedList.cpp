#include <iostream>
using namespace std;

enum Error_code {success, underflow, overflow};

template <class List_entry>
struct Node {
    List_entry entry;
    Node<List_entry> *next;
};

template <class List_entry>
class MyList {
	public:
    MyList() {
    	count = 0;
    	head = current = NULL;
    	curPosition = 0;
	}
    
	~MyList() {
    	this->clear();
	}
         // 拷贝构造函数和赋值运算符重载，注意深拷贝与浅拷贝的差异
    MyList(const MyList<List_entry> &cop) {
    	Node<List_entry> *new_node, *temp;
    	if (cop.size() != 0) {
    		temp = new Node<List_entry>;
    		cop.retrieve(0, temp->entry);
    		temp->next = NULL;
    		head = new_node = temp;
    		for (int i = 1; i < cop.size(); i++) {
    			temp = new Node<List_entry>;
    		    cop.retrieve(i, temp->entry);
    		    temp->next = NULL;
    		    new_node->next = temp;
    		    new_node = new_node->next;
			}
			count = cop.size();
		}
	}
	void operator =(const MyList<List_entry> &cop) {
		Node<List_entry> *new_node, *temp, *new_head;
    	if (cop.size() != 0) {
    		int n = cop.size(); 
    		temp = new Node<List_entry>;
    		cop.retrieve(0, temp->entry);
    		temp->next = NULL;
    		new_head = new_node = temp;
    		for (int i = 1; i < cop.size(); i++) {
    			temp = new Node<List_entry>;
    		    cop.retrieve(i, temp->entry);
    		    temp->next = NULL;
    		    new_node->next = temp;
    		    new_node = new_node->next;
			}
			clear();
			head = new_head;
			count = n;
		} else {
			clear();
		}
	}
        
		 // 清空list
    void clear() {
		while (head != NULL) {
			Node<List_entry> *temp = head;
			head = head->next;
			delete temp;
		} 
		count = 0;
	}
        
		 // 判断list是否为空
    bool empty() const {
    	return count == 0;
	}
         // 判断list是否已满
    bool full() const {
    	return false; 
	}
         // 获取list的元素数量
    int size() const {
    	return count;
	}
         // 在第position个位置插入值为entry的元素，如果position为0则插入在链表头，依次类推
         // 若position < 0 或者 position > count，则返回underflow
    Error_code insert(int position, const List_entry &entry) {
    	if (position < 0 || position > count) return underflow;
    	Node<List_entry> *temp = new Node<List_entry>;
    	temp->entry = entry;
        if (position == 0) {
			temp->next = head;
			head = temp;
		} else {
			Node<List_entry> *previous = head;
			for (int i = 0; i < position-1; i++) {
				previous = previous->next;
			}
			temp->next = previous->next;
			previous->next = temp;
		}
		count++;
		return success;
	}
         // 删除第position个位置的元素，并将该元素的值保存在entry中
         // 若position < 0 或者 position >= count，则返回underflow
    Error_code remove(int position, List_entry &entry) {
    	if (position < 0 || position >= count) return underflow;
    	Node<List_entry> *temp; 
        if (position == 0) {
        	temp = head;
        	entry = temp->entry;
        	head = head->next;
        	delete temp;
		} else {
			Node<List_entry> *previous = head;
			for (int i = 0; i < position-1; i++) {
				previous = previous->next;
			}
			temp = previous->next;
			entry = temp->entry;
			previous->next = temp->next;
			delete temp;
		}
		count--;
		return success;
	}
         // 获取第position个位置的元素，保存在entry中
         // 若position < 0 或者 position >= count，则返回underflow
    Error_code retrieve(int position, List_entry &entry) const {
        if (position < 0 || position >= count) return underflow;
        Node<List_entry> *previous = head;
        for (int i = 0; i < position; i++) previous = previous->next;
		entry = previous->entry; 
    	return success;
	}
         // 将第position个位置的元素替换为entry
         // 若position < 0 或者 position >= count，则返回underflow
    Error_code replace(int position, const List_entry &entry) {
        if (position < 0 || position >= count) return underflow;
        Node<List_entry> *previous = head;
        for (int i = 0; i < position; i++) previous = previous->next;
		previous->entry = entry; 
    	return success;
	}
         // 用visit函数遍历list内所有的元素
    void traverse(void (*visit)(List_entry &)) {
    	Node<List_entry> * temp = head;
    	while (temp != NULL) {
    		(*visit)(temp->entry);
    		temp = temp->next;
		}
	}

    protected:
    int count;    // 记录list内元素数量
    Node<List_entry> *head;      // 链表头指针
    mutable int curPosition;          // current指针的位置编号
    mutable Node<List_entry> *current;           // current指针
         // 设置current指针的位置，指向第position个位置
    void setPosition(int position) const {}
};


void print(int &n) {
	std::cout << n << " ";
}

//测试程序 
int main() {
	MyList<int> l;
	int n, m, i, j;
	do {
		cout << "---1,insert----2,remove---3,print\n"
		     << "---4,retrieve----5,replace---\n"
		     << "---6,empty---7,full---8,size---\n"
		     << "---9,clear\n"
		     << "------input a number------:";
		cin >> n;
		switch(n) {
			case 1: cout << "input two numbers for position and entry :";
					cin >> i >> j;
					l.insert(i, j);
			        break;
			case 2: cout << "input a number for position ";
					cin >> i;
					l.remove(i, m);
					cout << "the remove num " << m << "\n";
					break;
			case 3: l.traverse(print);
			        cout << "\n";
			        break;
			case 4: cout << "input a num for position and entry :";
			        cin >> i;
			        l.retrieve(i, j);
			        cout << "the number is " << j << "\n";
			        break;
			case 5: cout << "input two num for position and entry :";
			        cin >> i >> j;
			        l.replace(i, j);
			        break;
			case 6: if (l.empty() == true) cout << "it is empty.\n";
			        else cout << "not empty.\n";
			        break;
			case 7: if (l.full() == true) cout << "it is full.\n";
			        else cout << "not full\n";
					break;
			case 8: cout << "size :" << l.size() << "\n";
			        break;
			case 9: l.clear();
			        break;
			case 0: return 0;
		} 
		cout << "\n";
	} while (n != 0);
	return 0;
} 

