#pragma once

template <class T>
class SLList {
public:
    struct Node {
        Node* next;
        T value;

        Node(T v) : next(nullptr), value(v) {}
    };

    SLList() {
        head = nullptr;
        theSize = 0;
    }

    ~SLList() {
        clear();
    }

    const Node* get_head() const {
        // implement get_head here
        return head;
    }

    void push_back(T item) {
        // implement push_back here
        if (head == nullptr) {
            head = new Node(item);
        }
        else {
           Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = new Node(item);
        }
        theSize ++;
    }

    void pop_back() {
        // implement pop_back here
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            theSize--;
            return;
        }
        Node * current = head;
        while (current-> next ->next != nullptr){
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        theSize--;
    }

    void push_front(T item) {
        // implement push_front here
        Node* n = new Node(item);
        n->next = head;
        head = n;
        theSize++;
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }
        Node * current = head -> next;
        delete head;
        head = current;
        theSize--;
    }

    const T& front() const {
        // implement front here
        return head -> value;
    }

    int size() const {
        // implement size here
        return theSize;
    }

    void clear()
    {
        // implement clear here
        while (head != nullptr) {
            Node * current = head;
            head = head -> next;
            delete current;
            theSize--;
        }
    }

private:
    Node* head;
    int theSize;
};
