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
         // �������캯���͸�ֵ��������أ�ע�������ǳ�����Ĳ���
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

    // ���list
    void clear() {
        int n;
        while (count != 0) remove(0, n);
    }

    // �ж�list�Ƿ�Ϊ��
    bool empty() const {
        return count == 0;
    }

    // �ж�list�Ƿ�����
    bool full() const {
        return false;
    }

    // ��ȡlist��Ԫ������
    int size() const {
        return count;
    }

    // �ڵ�position��λ�ò���ֵΪentry��Ԫ�أ����positionΪ0�����������ͷ����������
    // ��position < 0 ���� position > count���򷵻�underflow
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
    
    // ɾ����position��λ�õ�Ԫ�أ�������Ԫ�ص�ֵ������entry��
    // ��position < 0 ���� position >= count���򷵻�underflow
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

    // ��ȡ��position��λ�õ�Ԫ�أ�������entry��
    // ��position < 0 ���� position >= count���򷵻�underflow
    Error_code retrieve(int position, List_entry &entry) const {
        if (position < 0 || position >= count) return underflow;
        setPosition(position);
        entry = current->entry;
        return success;
    }

    // ����position��λ�õ�Ԫ���滻Ϊentry
    // ��position < 0 ���� position >= count���򷵻�underflow
    Error_code replace(int position, const List_entry &entry) {
        if (position < 0 || position >= count) return underflow;
        setPosition(position);
        current->entry = entry;
        return success;
    }

    // ��visit��������list�����е�Ԫ��
    void traverse(void (*visit)(List_entry &)) {
        setPosition(0);
        Node<List_entry> *temp = current;
        while (temp != NULL) {
            (*visit)(temp->entry);
            temp = temp->next;
        }
    }
    protected:
    int count;                                                            // ��¼list��Ԫ������
    mutable int curPosition;                                   // currentָ���λ�ñ��
    mutable Node<List_entry> *current;                 // currentָ��
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
