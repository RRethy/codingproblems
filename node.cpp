template <class T>
struct Node {
    T value;
    Node<T> *l;
    Node<T> *r;

    ~Node() {
      delete l;
      delete r;
    }
};
