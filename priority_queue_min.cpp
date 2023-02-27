#include <iostream>
#include "priority_queue_min.h"

using namespace std;

void Priority_Queue_Min::Sift_Up(int index) {
    while (heap[index]->frequency < heap[(index - 1) / 2]->frequency) {
        swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void Priority_Queue_Min::Sift_Down(int index) {
    while(index * 2 + 1 < heap_size) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int to = left;

        if(right < heap_size && heap[right]->frequency < heap[left]->frequency) {
            to = right;
        }

        if(heap[index]->frequency <= heap[to]->frequency) {
            break;
        }

        swap(heap[index], heap[to]);
        index = to;
    }
}

Priority_Queue_Min::Priority_Queue_Min(int n, unsigned char *symbols, int *frequencies) {
    heap = new Node*[n];
    max_size = n;
    heap_size = n;
    for(int index = 0; index < n; ++index) {
        heap[index] = new Node({symbols[index], frequencies[index], nullptr, nullptr});
    }
    for(int index = n - 1; index >= 0; --index) {
        Sift_Down(index);
    }
}

Priority_Queue_Min::~Priority_Queue_Min() {
    delete[] heap;
}

void Priority_Queue_Min::print_tree() {
    for(int index = 0; index < heap_size; ++index) {
        std::cout << heap[index]->symbol << ' ' << heap[index]->frequency << '\n';
    }
}

Node *Priority_Queue_Min::Extract_Min() {
    if(heap_size > 0) {
        Node* min = heap[0];
        swap(heap[0], heap[heap_size - 1]);
        heap_size--;
        Sift_Down(0);
        return min;
    }
}

void Priority_Queue_Min::Insert(Node *new_elem) {
    if(heap_size + 1 < max_size) {
        heap[heap_size] = new_elem;
        Sift_Up(heap_size);
        heap_size++;
    }
}

Node *Priority_Queue_Min::Build_Huffman_Tree() {
    while(heap_size > 1) {
        Node* first = Extract_Min();
        Node* second = Extract_Min();
        Node* newNode = new Node({'*', first->frequency + second->frequency, first, second});
        Insert(newNode);
    }
    return Extract_Min();
}

void Priority_Queue_Min::Gen_Huffman_leaf(Node *v) {
    stack st;
    string code;
    st.push(v);
    while(!st.is_empty()) {
        Node* cur = st.top();
        cur->used = true;
        if(cur->left == nullptr && cur->right == nullptr) {
            cout << cur->symbol << ' ' << cur->frequency << ' ' << code << '\n';
            coding[cur->symbol] = code;
            code.pop_back();
            st.pop();
        } else {
            if(cur->left != nullptr && !cur->left->used) {
                st.push(cur->left);
                code += '1';
            }
            else if(cur->right != nullptr && !cur->right->used) {
                st.push(cur->right);
                code += '0';
            }
            else {
                code.pop_back();
                st.pop();
            }
        }
    }
}

string Priority_Queue_Min::Encode(unsigned char c) {
    return coding[c];
}

string Priority_Queue_Min::Decode(string str, Node* v) {
    string out;
    int index = 0;
    Node* cur = v;
    while (index < str.size() && cur != nullptr) {
        if(cur->left == nullptr && cur->right == nullptr) {
            out += cur->symbol;
            cur = v;
        }
        if(str[index] == '1') {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
        ++index;
    }
    if(cur != nullptr && cur->left == nullptr && cur->right == nullptr) {
        out += cur->symbol;
    }
    return out;
}
