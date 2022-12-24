template <typename T, bool persistent = false>
struct Node {
    T val; int rank; Node *left, *right;
    Node(T val): val(val), rank(0), left(NULL), right(NULL) {};
    friend Node* meld(Node* h1, Node* h2) {
        if(!h1 || !h2) return (h1 ? h1 : h2);
        if(h1->val > h2->val) swap(h1, h2);
        Node* res = (persistent ? new Node(*h1) : h1);
        res->right = meld(h1->right, h2);
        if(!res->left || (res->right && res->left->rank < res->right->rank)) {
            swap(res->left, res->right);
        }
        res->rank = (res->right ? res->right->rank : 0) + 1;
        return res;
    }
    friend Node* insert(Node* h, T val) {
        return meld(h, new Node(val));
    }
    friend Node* pop(Node* h) {
        return (!h ? h : meld(h->left, h->right));
    }
};