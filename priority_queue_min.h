#include "stack.h"


using namespace std;

class Priority_Queue_Min {
private:
    Node ** heap;
    int heap_size;
    int max_size;
    string* coding = new string[256];
    void Sift_Up(int index);
    void Sift_Down(int index);

public:
    Priority_Queue_Min(int n, unsigned char* symbols, int* frequencies);
    ~Priority_Queue_Min ();

    void print_tree();
    Node* Extract_Min();
    void Insert(Node * new_elem);
    Node* Build_Huffman_Tree();
    void Gen_Huffman_leaf(Node* v);
    string Encode(unsigned char c);
    string Decode(string str, Node* v);
};
