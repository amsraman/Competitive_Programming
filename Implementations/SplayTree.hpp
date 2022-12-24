template <typename T>
struct Node {
    int size; T val;
    Node *child[2] = {NULL, NULL}, *par = NULL;
    Node(T val): size(1), val(val) {};
    // Basic Tree Operations
    friend void refresh(Node *cur) {
        if(!cur) return;
        cur->size = 1 + (cur->child[0] ? cur->child[0]->size : 0) + (cur->child[1] ? cur->child[1]->size : 0);
    }
    friend void update_child(Node *cur, Node *kid, int ind) {
        cur->child[ind] = kid, refresh(cur);
        if(kid) kid->par = cur;
    }
    friend void zig(Node *cur) {
        Node *root = cur->par; int side = cur == root->child[0];
        update_child(root, cur->child[side], side ^ 1);
        update_child(cur, root, side);
        cur->par = NULL;
    }
    friend void zig_zig(Node *cur) {
        Node *parent = cur->par, *grand_parent = parent->par, *great_grandparent = grand_parent->par;
        int side = cur == parent->child[0];
        update_child(grand_parent, parent->child[side], side ^ 1);
        update_child(parent, cur->child[side], side ^ 1);
        update_child(parent, grand_parent, side);
        update_child(cur, parent, side);
        if(!great_grandparent) {
            cur->par = NULL;
            return;
        }
        update_child(great_grandparent, cur, grand_parent == great_grandparent->child[1]);
    }
    friend void zig_zag(Node *cur) {
        Node *parent = cur->par, *grand_parent = parent->par, *great_grandparent = grand_parent->par;
        int side = cur == parent->child[0];
        update_child(grand_parent, cur->child[side ^ 1], side);
        update_child(parent, cur->child[side], side ^ 1);
        update_child(cur, grand_parent, side ^ 1);
        update_child(cur, parent, side);
        if(!great_grandparent) {
            cur->par = NULL;
            return;
        }
        update_child(great_grandparent, cur, grand_parent == great_grandparent->child[1]);
    }
    friend void splay(Node *cur) {
        while(cur->par) {
            if(!cur->par->par) {
                zig(cur);
            } else {
                Node *parent = cur->par, *grand_parent = parent->par;
                if((cur == parent->child[0]) ^ (parent == grand_parent->child[0])) {
                    zig_zag(cur);
                } else {
                    zig_zig(cur);
                }
            }
        }
    }
    // Basic
    friend Node* join(Node *t1, Node *t2) {
        if(!t1) return t2;
        if(t1->child[1]) return join(t1->child[1], t2);
        splay(t1); update_child(t1, t2, 1);
        return t1;
    }
    friend pair<Node*, Node*> split(Node *cur) {
        if(!cur) return {NULL, NULL};
        splay(cur); Node *t2 = cur->child[1]; update_child(cur, NULL, 1);
        if(t2) t2->par = NULL;
        return {cur, t2};
    }
    // Size-Based
    friend Node* kth_smallest(Node *cur, int k) {
        if(!cur) return NULL;
        int left_sz = (cur->child[0] ? cur->child[0]->size : 0);
        if(k <= left_sz) {
            return kth_smallest(cur->child[0], k);
        } else if(left_sz + 1 < k) {
            return kth_smallest(cur->child[1], k - left_sz - 1);
        }
        splay(cur);
        return cur;
    }
    friend pair<Node*, Node*> split_by_size(Node *cur, int sz) {
        if(!cur || sz == 0) return {NULL, cur};
        return split(kth_smallest(cur, sz));
    }
};
typedef Node<int>* SplayTree;