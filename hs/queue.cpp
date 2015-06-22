/**
 * CS Exercise 13.1
 * Title: queue
 * Author: Martin Giger
 * Date: 22.06.2015
 * Based on the provided template
 */
#include <iostream>

class Queue {
public:
    // PRE:  -
    // POST: Valid and empty queue.
    Queue() : first(0), last(0) { };

    // PRE:  Valid queue.
    // POST: Valid queue with new node having value i added at end of queue.
    void enqueue(int value) {
        Node* newNode = new Node(value, 0);
        if(this->last) {
            this->last->next = newNode;
        }

        if(!this->first) {
            this->first = newNode;
        }
        this->last = newNode;
    };

    // PRE:  Valid and non-empty queue.
    // POST: Removed first node from queue and freed the unused memory.
    //       Returns content of first node.
    int dequeue() {
        Node* oldFirst = this->first;
        if(oldFirst) {
            if(this->first != this->last) {
                this->first = oldFirst->next;
            }
            else {
                this->first = 0;
                this->last = 0;
            }

            int ret = oldFirst->value;

            delete oldFirst;

            return ret;
        }
        return 0;
    };

    // PRE:  Valid queue.
    // POST: Returns true if queue is empty, false otherwise.
    bool is_empty() const {
        return this->first == 0 && this->last == 0;
    };

    // PRE:  Valid queue.
    // POST: Outputs queue content in seqeuence from first to last.
    void print(std::ostream& os) const;

    // PRE:  -
    // POST: New queue containing copy of queue other.
    Queue(const Queue& other): first(0), last(0) {
        Node* curr = other.first;
        while(curr) {
            this->enqueue(curr->value);
            curr = curr->next;
        }
    };

    // PRE:  Valid queue.
    // POST: Queue is emptied (memory is freed) and initialized with elements
    //       from queue other.
    void operator=(const Queue& other) {
        while(!this->is_empty()) {
            this->dequeue();
        }

        Node* curr = other.first;
        while(curr) {
            this->enqueue(curr->value);
            curr = curr->next;
        }
    };

    // PRE:  Valid queue.
    // POST: Queue is emptied and memory is freed.
    ~Queue() {
        while(this->is_empty()) {
            this->dequeue();
        }
    };

private:
    struct Node {
        Node(const int _value, Node* _next) : value(_value), next(_next) { }
        int value;
        Node* next;
    };

    // Class invariant: (!first == !last)
    Node* first; // pointer to first element of queue or 0 is queue is empty.
    Node* last;  // pointer to last element of queue or 0 if queue is empty.
};

void Queue::print(std::ostream& os) const
{
    Node* curr = this->first;
    while(curr) {
        os << curr->value << " ";
        curr = curr->next;
    }
}

std::ostream& operator<<(std::ostream& os, const Queue& q) {
    q.print(os);
    return os;
}

int main() {
    // Uncomment to test queue operations
    Queue a;
    a.enqueue(6);
    a.enqueue(-2);
    a.enqueue(43);
    while (!a.is_empty()) {
        std::cout << a.dequeue() << std::endl;
    }

    // Uncomment to test print operation
    Queue b;
    std::cout << b << std::endl;
    b.enqueue(4);
    std::cout << b << std::endl;
    b.enqueue(6);
    std::cout << b << std::endl;

    // Uncomment to test copy, assignment
    a.enqueue(3);
    a.enqueue(-1);
    a.enqueue(7);
    Queue c(a);
    std::cout << c << std::endl;
    a.dequeue();
    c.dequeue();

    c = b;
    std::cout << c << std::endl;
    b.dequeue();
    c.dequeue();
}
