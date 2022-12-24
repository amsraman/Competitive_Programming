template <class B>
struct PersistentSegTree : public B {
    using T_q = typename B::T_q;
    using T_u = typename B::T_u;
    struct Node {
        T_q val; T_u lazy; Node *left, *right;
        Node(T_q val): val(val), lazy(B::e_u), left(NULL), right(NULL) {};
        Node(T_q val, T_u lazy): val(val), lazy(lazy), left(NULL), right(NULL) {};
        Node(T_q val, T_u lazy, Node *left, Node *right): val(val), lazy(lazy), left(left), right(right) {};
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
        return new Node(B::comb(left_child->val, right_child->val), B::e_u, left_child, right_child);
    }
    Node* app(Node *cur, T_u delta, int lo, int hi) {
        return new Node(B::upd(cur->val, delta, lo, hi), B::comb_upd(delta, cur->lazy), cur->left, cur->right);
    }
    void push(Node *cur, int lo, int hi) {
        if(lo != hi) {
            int mid = lo + (hi - lo) / 2;
            cur->left = app(cur->left, cur->lazy, lo, mid);
            cur->right = app(cur->right, cur->lazy, mid + 1, hi);
        }
        cur->lazy = B::e_u;
    }
    T_q qry(Node *cur, int lo, int hi, int lo_ind, int hi_ind) {
        if(lo <= lo_ind && hi_ind <= hi) {
            return cur->val;
        }
        int mid = lo_ind + (hi_ind - lo_ind) / 2;
        if(cur->lazy != B::e_u) push(cur, lo_ind, hi_ind);
        T_q op1 = (lo <= mid ? qry(cur->left, lo, hi, lo_ind, mid) : B::e_q);
        T_q op2 = (mid < hi ? qry(cur->right, lo, hi, mid + 1, hi_ind) : B::e_q);
        return B::comb(op1, op2);
    }
    Node* upd(Node *cur, int lo, int hi, int lo_ind, int hi_ind, T_u delta) {
        if(lo <= lo_ind && hi_ind <= hi) {
            return app(cur, delta, lo_ind, hi_ind);
        }
        int mid = lo_ind + (hi_ind - lo_ind) / 2;
        if(cur->lazy != B::e_u) push(cur, lo_ind, hi_ind);
        Node *res_left = cur->left, *res_right = cur->right;
        if(lo <= mid) res_left = upd(cur->left, lo, hi, lo_ind, mid, delta);
        if(mid < hi) res_right = upd(cur->right, lo, hi, mid + 1, hi_ind, delta);
        return new Node(B::comb(res_left->val, res_right->val), B::e_u, res_left, res_right);
    }
    T_q qry(int version, int lo, int hi) {
        return qry(roots[version], lo, hi, 0, n - 1);
    }
    void upd(int version, int lo, int hi, T_u delta) {
        roots.push_back(upd(roots[version], lo, hi, 0, n - 1, delta));
    }
};

struct MaxInt {
    using T_q = int; const T_q e_q = 0;
    using T_u = int; const T_u e_u = 0;
    T_q comb(T_q a, T_q b) {
        return (a > b ? a : b);
    }
    T_q upd(T_q a, T_u b, int l, int r) {
        return a + b;
    }
    T_u comb_upd(T_u a, T_u b) {
        // a after b
        return a + b;
    }
};