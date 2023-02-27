struct Node {
    unsigned char symbol;
    int frequency;
    Node* left;
    Node* right;
    bool used = false;
};

class stack {
private:
    struct ListItem {
        Node* value;
        ListItem* next;

        ListItem(Node* value, ListItem* next)
                : value(value), next(next)
        {}
    };

    ListItem* head;
public:
    stack();
    ~stack();

    void push(Node* value);
    void pop();
    Node* top();
    bool is_empty();
};
