#pragma once

template<class T>
class DLList {
public:
    // **Important**
    // Normally you would make the Node struct PRIVATE
    // but for this assignment it is important to keep it 
    // PUBLIC
    // Also, the declaration of Node needs to come 
    // before everything else in the class, so leave it here
    // at the beginning.
    struct Node {
        Node* prev;
        Node* next;
        T value;

        Node(T v) : prev(nullptr), next(nullptr), value(v) {}
    };

private:
    // Put your private fields/methods here
    int theSize;
    Node* head;
    Node* tail;

public:
    DLList() {
        head = nullptr;
        tail = nullptr;
        theSize = 0;
    }

    ~DLList() {
        clear();
    }

    const Node* get_head() const {
        // implement get_head here
        return head;
    }

    void push_front(T item) {
        // implement push_front here
        Node* n = new Node(item);
        n->next = head;
        n->prev = nullptr;
        if (head != nullptr) {
            head->prev = n;
        }
        else {
            tail = n;
        }
        head = n;
        theSize++;
    }

    void push_back(T item) {
        // implement push_back here
        Node* n = new Node(item);
        n->prev = tail;
        n->next = nullptr;
        if (tail != nullptr) {
            tail->next = n;
        }
        else {
            head = n;
        }
        tail = n;
        theSize++;
    }

    void insert(T item, int position)
    {
        // implement insert here
        if (position <= 0) {
            push_front(item);
        }
        else if (position >= theSize) {
            push_back(item);
        }
        else {
            Node* curr = head;
            for (int i = 0; i < position; i++) {
                curr = curr->next;
            }
            Node* n = new Node(item);
            n->prev = curr->prev;
            n->next = curr;
            curr->prev->next = n;
            curr->prev = n;
            theSize++;
        }
    }

    void pop_front() {
        // implement pop_front here
        if (head  == nullptr) {
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        theSize--;
    }

    void pop_back() {
        // implement pop_back here
        if (tail == nullptr) {
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        theSize--;
    }

    void remove(int position)
    {
        // implement remove here
        if (position < 0 || position >= theSize) {
            return;
        }
        if (position == 0) {
            pop_front();
        }
        else if (position == theSize - 1) {
            pop_back();
        }
        else {
            Node* curr = head;
            for (int i = 0; i < position; i++) {
                curr = curr->next;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            theSize--;
        }
    }

    const T& front() const {
        // implement front here
        return head->value;
    }

    const T& back() const {
        // implement back here
        return tail->value;
    }

    const T& at(int index) const {
        Node* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->value;
    }

    bool contains(const T& item) const {
        Node* curr = head;
        while (curr != nullptr){
            if (curr->value == item) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    int size() const {
        // implement size here
        return theSize;
    }

    void clear() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        theSize = 0;
        // implement clear here
    }
};
