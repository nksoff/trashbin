/**
Дано число N < 10^6 и последовательность целых чисел из [­2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то
узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке in­order (слева направо).
*/

#include <iostream>
#include <queue>

template <class T>
class TreeNode {
private:
    T _data;
    TreeNode<T> *_left;
    TreeNode<T> *_right;
public:
    TreeNode(const T &data): _data(data), _left(NULL), _right(NULL) {
    }

    // возвращает данные
    const T &getData() const {
        return _data;
    }

    // сохраняет данные
    void setData(const T &data) {
        _data = data;
    }

    // возвращает левое поддерево
    TreeNode<T> *getLeft() const {
        return _left;
    }

    // задает левое поддерево
    void setLeft(TreeNode<T> *left) {
        _left = left;
    }

    // возвращает правое поддерево
    TreeNode<T> *getRight() const {
        return _right;
    }

    // задает правое поддерево
    void setRight(TreeNode<T> *right) {
        _right = right;
    }
};

template <class T>
class NaiveTree {
private:
    TreeNode<T> *_root;
public:
    NaiveTree() : _root(NULL) {
    }

    ~NaiveTree() {
        std::queue<TreeNode<T> *> tmp;
        tmp.push(_root);

        while(!tmp.empty()) {
            TreeNode<T> *cur = tmp.front();
            if(cur->getLeft() != NULL) {
                tmp.push(cur->getLeft());
            }
            if(cur->getRight() != NULL) {
                tmp.push(cur->getRight());
            }

            delete cur;
            tmp.pop();
        }
    }

    // задать корень
    void setRoot(TreeNode<T> *root) {
        _root = root;
    }

    // вывод узла в порядке in-order
    void inOrder(TreeNode<T> *node) {
        if(node == NULL) {
            return;
        }

        if(node->getLeft() != NULL) {
            inOrder(node->getLeft());
        }
        
        std::cout << node->getData() << " ";

        if(node->getRight() != NULL) {
            inOrder(node->getRight());
        }
    }

    // вывод всего дерева в порядке in-order
    void inOrder() {
        return inOrder(_root);
    }

    // добавление элемента в дерево
    void add(const T &data) {
        TreeNode<T> *node = new TreeNode<T>(data),
                    *curNode = _root;

        if(curNode == NULL) {
            setRoot(node);
            return;
        }

        while(true) {
            if(data < curNode->getData()) {
                if(curNode->getLeft() != NULL) {
                    curNode = curNode->getLeft();
                }
                else
                {
                    curNode->setLeft(node);
                    return;
                }
            }
            else
            {
                if(curNode->getRight() != NULL) {
                    curNode = curNode->getRight();
                }
                else
                {
                    curNode->setRight(node);
                    return;
                }
            }
        }
    }
};

int main() {
    int n = 0;
    std::cin >> n;

    NaiveTree<long> tree;

    long tmp;
    for(int i = 0; i < n; i++) {
        std::cin >> tmp;
        tree.add(tmp);
    }

    tree.inOrder();

    return 0;
}
