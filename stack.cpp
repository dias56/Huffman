#include "stack.h"

stack::stack() {
    head = nullptr;
}

stack::~stack() {
    while(head != nullptr) {
        ListItem* tmp = head->next;
        delete head;
        head = tmp;
    }
}

void stack::push(Node* value) {
    ListItem* tmp = new ListItem(value, head);
    head = tmp;
}

void stack::pop() {
    ListItem* tmp = head->next;
    delete head;
    head = tmp;
}

Node* stack::top() {
    return head->value;
}

bool stack::is_empty() {
    return head == nullptr;
}
