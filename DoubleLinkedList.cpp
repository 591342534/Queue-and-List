#include <iostream>
using namespace std;
 
enum Error_code {success, underflow, overflow};

template <class List_entry>
struct Node {
    List_entry entry;
    Node<List_entry> *next;
    Node<List_entry> *back;
};

template <class List_entry>
class MyList {
    public:
    MyList() {
        count = curPosition = 0;
        current = NULL;
    } 
    ~MyList() {
        clear();
    }
         // 拷贝构造函数和赋值运算符重载，注意深拷贝与浅拷贝的差异
    MyList(const MyList<List_entry> &cop) {
        count = curPosition = 0;
        current = NULL;
        if (cop.size() != 0) {
            for (int i = 0; i < cop.size(); i++) {
                Node<List_entry> *temp = new Node<List_entry>;
                cop.retrieve(i, temp->entry);
                Node<List_entry> *following, *preceding;
                if (i == 0) {
                   if (count == 0) following = NULL;
                   else {
                   setPosition(0);
                   following = current;
                   }
                   preceding = NULL;
                } else {
                   setPosition(i-1);
                   preceding = current;
                   following = preceding->next;
                }
                temp->next = following;
                temp->back = preceding;
                if (preceding != NULL) preceding->next = temp;
                if (following != NULL) following->back = temp;
                current = temp;
                curPosition = i;
            }
            count = cop.size();
        }
    }
    void operator =(const MyList<List_entry> &cop) {
        if (cop.size() != 0) {
            MyList<List_entry> t(cop);
            int _count = cop.size();
            clear();
            for (int i = 0; i < t.size(); i++) {
                Node<List_entry> *temp = new Node<List_entry>;
                t.retrieve(i, temp->entry);
                Node<List_entry> *following, *preceding;
                if (i == 0) {
                   if (count == 0) following = NULL;
                   else {
                   setPosition(0);
                   following = current;
                   }
                   preceding = NULL;
                } else {
                   setPosition(i-1);
                   preceding = current;
                   following = preceding->next;
                }
                temp->next = following;
                temp->back = preceding;
                if (preceding != NULL) preceding->next = temp;
                if (following != NULL) following->back = temp;
                current = temp;
                curPosition = i;
            }
            count = _count;
        } else clear();
    }

    // 清空list
    void clear() {
        int n;
        while (count != 0) remove(0, n);
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
        Node<List_entry> *following, *preceding;
        if (position == 0) {
            if (count == 0) following = NULL;
            else {
                setPosition(0);
                following = current;
            }
            preceding = NULL;
        } else {
            setPosition(position-1);
            preceding = current;
            following = preceding->next;
        }
        temp->next = following;
        temp->back = preceding;
        if (preceding != NULL) preceding->next = temp;
        if (following != NULL) following->back = temp;
        current = temp;
        curPosition = position;
        count++;
        return success;
    }
    
    // 删除第position个位置的元素，并将该元素的值保存在entry中
    // 若position < 0 或者 position >= count，则返回underflow
    Error_code remove(int position, List_entry &entry) {
        if (position < 0 || position >= count) return underflow;
        Node<List_entry> *temp, *following, *preceding;
        setPosition(position);
        temp = current;
        if (current->next == NULL) {
            current = current->back;
            if (current != NULL) curPosition--;
        } else current = current->next;
        entry = temp->entry;
        preceding = temp->back;
        following = temp->next;
        if (preceding != NULL) preceding->next = following;
        if (following != NULL) following->back = preceding;
        delete temp;
        count--;
        return success;
    }

    // 获取第position个位置的元素，保存在entry中
    // 若position < 0 或者 position >= count，则返回underflow
    Error_code retrieve(int position, List_entry &entry) const {
        if (position < 0 || position >= count) return underflow;
        setPosition(position);
        entry = current->entry;
        return success;
    }

    // 将第position个位置的元素替换为entry
    // 若position < 0 或者 position >= count，则返回underflow
    Error_code replace(int position, const List_entry &entry) {
        if (position < 0 || position >= count) return underflow;
        setPosition(position);
        current->entry = entry;
        return success;
    }

    // 用visit函数遍历list内所有的元素
    void traverse(void (*visit)(List_entry &)) {
        setPosition(0);
        Node<List_entry> *temp = current;
        while (temp != NULL) {
            (*visit)(temp->entry);
            temp = temp->next;
        }
    }
    protected:
    int count;                                                            // 记录list内元素数量
    mutable int curPosition;                                   // current指针的位置编号
    mutable Node<List_entry> *current;                 // current指针
    void setPosition(int position) const {
        if (curPosition <= position) {
            for (; curPosition != position; curPosition++) 
                current = current->next;
        } else {
            for (; curPosition != position; curPosition--) 
                current = current->back;
        }
    }
};              
