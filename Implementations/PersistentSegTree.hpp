template <class B>
struct PersistentSegTree : public B {
    using T_q = typename B::T_q;
    struct Node {
        T_q val; Node *left, *right;
        Node(T_q val): val(val), left(NULL), right(NULL) {};
        Node(T_q val, Node *left, Node *right): val(val), left(left), right(right) {};
    };
    int n; vector<Node*> roots;
    PersistentSegTree(const vector<T_q> & init): n((int) init.size()) {
        roots.push_back(bld(init, 0, n - 1));
    };
    Node* bld(const vector<T_q> & init, int lo, int hi) {
        if(lo == hi) {
            return new Node(init[lo]);
        }
        int mid = lo + (hi - lo) / 2;
        Node *left_child = bld(init, lo, mid), *right_child = bld(init, mid + 1, hi);
        return new Node(B::comb(left_child->val, right_child->val), left_child, right_child);
    }
    T_q qry(Node *cur, int lo, int hi, int lo_ind, int hi_ind) {
        if(lo_ind > hi || hi_ind < lo) {
            return B::e_q;
        }
        if(lo <= lo_ind && hi_ind <= hi) {
            return cur->val;
        }
        int mid = lo_ind + (hi_ind - lo_ind) / 2;
        return B::comb(qry(cur->left, lo, hi, lo_ind, mid), qry(cur->right, lo, hi, mid + 1, hi_ind));
    }
    Node* upd(Node *cur, int lo, int hi, int pos, T_q val) {
        if(lo == hi) {
            return new Node(val);
        }
        int mid = lo + (hi - lo) / 2;
        Node *res_left = cur->left, *res_right = cur->right;
        if(pos <= mid) res_left = upd(res_left, lo, mid, pos, val);
        else res_right = upd(res_right, mid + 1, hi, pos, val);
        return new Node(B::comb(res_left->val, res_right->val), res_left, res_right);
    }
    T_q qry(int version, int lo, int hi) {
        return qry(roots[version], lo, hi, 0, n - 1);
    }
    void upd(int version, int pos, T_q val) {
        roots.push_back(upd(roots[version], 0, n - 1, pos, val));
    }
};

struct MaxInt {
    using T_q = int;
    const T_q e_q = 0;
    T_q comb(T_q a, T_q b) {
        return max(a, b);
    }
};