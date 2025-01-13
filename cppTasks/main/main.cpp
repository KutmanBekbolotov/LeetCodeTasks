#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    while (current) {
        Node* nextTemp = current->next;
        current->next = prev;
        prev = current;
        current = nextTemp;
    }
    return prev;
}

bool isPalindrome(Node* head) {
    if (!head || !head->next) return true;

    Node* middle = findMiddle(head);

    Node* secondHalf = reverseList(middle);

    Node* firstHalf = head;
    Node* tempSecondHalf = secondHalf;
    bool isPal = true;

    while (tempSecondHalf) {
        if (firstHalf->data != tempSecondHalf->data) {
            isPal = false;
            break;
        }
        firstHalf = firstHalf->next;
        tempSecondHalf = tempSecondHalf->next;
    }

    reverseList(secondHalf);

    return isPal;
}

void append(Node*& head, int value) {
    if (!head) {
        head = new Node(value);
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new Node(value);
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    Node* head = nullptr;

    append(head, 1);
    append(head, 2);
    append(head, 3);
    append(head, 2);
    append(head, 1);

    std::cout << "Исходный список: ";
    printList(head);

    if (isPalindrome(head)) {
        std::cout << "Список является палиндромом." << std::endl;
    } else {
        std::cout << "Список не является палиндромом." << std::endl;
    }

    return 0;
}
