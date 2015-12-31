/**
Дано число N < 10^6 и последовательность пар целых чисел из [­2^31..2^31] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi , Yi}.
Каждая пара чисел {Xi , Yi } определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма,
рассказанного на лекции:
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим
приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в
первом поддереве все ключи меньше x, а во втором больше или равны x.
Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел
вставьте на место узла P.
Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
Вычислить количество узлов в самом широком слое декартового дерева и 
количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу.
*/

#include <iostream>
#include <queue>

template <class T>
class TreeNode {
public:

    T data;
    int priority;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(const T &_data, int _priority = 0): data(_data), priority(_priority), left(NULL), right(NULL) {
    }

    // вывод
    void show(std::ostream &stream = std::cout) {
        static int listingLevel = 0;
        static bool listingLast[100] = {};

        int level = listingLevel;

        listingLast[level] = !left && !right;

        for(int i = 1; i < level; i++) {
            stream << (!listingLast[i-1] ? "|" : " ") << "  ";
        }

        if(level > 0) stream << (!listingLast[level-1] ? "├" : "└") << "──";
        stream << (left || right ? "┬" : "─") << " ";

        if(data)
            stream << data;
        stream << std::endl;

        if(left) {
            listingLevel = level + 1;
            listingLast[level] = !right;
            left->show(stream);
        }
        if(right) {
            listingLevel = level + 1;
            listingLast[level] = true;
            right->show(stream);
        }

        if(level == 0) {
            stream << std::endl;
            listingLevel = 0;
        }
    }
};

template <class T>
class NaiveTree {
private:
    TreeNode<T> *root;
public:
    NaiveTree() : root(NULL) {
    }

    ~NaiveTree() {
        std::queue<TreeNode<T> *> tmp;
        if(root != NULL) {
            tmp.push(root);
        }

        while(!tmp.empty()) {
            TreeNode<T> *cur = tmp.front();
            if(cur->left != NULL) {
                tmp.push(cur->left);
            }
            if(cur->right != NULL) {
                tmp.push(cur->right);
            }

            delete cur;
            tmp.pop();
        }
    }

    // задать корень
    void setRoot(TreeNode<T> *_root) {
        root = _root;
    }

    // добавление элемента в дерево
    void add(const T &data) {
        TreeNode<T> *node = new TreeNode<T>(data),
                    *curNode = root;

        if(curNode == NULL) {
            setRoot(node);
            return;
        }

        while(true) {
            if(data < curNode->data) {
                if(curNode->left != NULL) {
                    curNode = curNode->left;
                }
                else
                {
                    curNode->left = node;
                    return;
                }
            }
            else
            {
                if(curNode->right != NULL) {
                    curNode = curNode->right;
                }
                else
                {
                    curNode->right = node;
                    return;
                }
            }
        }
    }

    // возвращаем ширину
    int getMaxWidth() {
        int maxWidth = 0,
            curWidth = 0;

        std::queue<TreeNode<T> *> layerNodes;
        TreeNode<T> *cur = NULL;
        layerNodes.push(root);

        while(!layerNodes.empty()) {
            if((curWidth = layerNodes.size()) > maxWidth) {
                maxWidth = curWidth;
            }

            for(size_t i = 0; i < curWidth; i++) {
                cur = layerNodes.front();
                if(cur->left != NULL) {
                    layerNodes.push(cur->left);
                }
                if(cur->right != NULL) {
                    layerNodes.push(cur->right);
                }
                layerNodes.pop();
            }
        }

        return maxWidth;
    }

    // вывод дерева
    void show() {
        if(root != NULL) {
            root->show();
        }
    }
};

template <class T>
class TreapTree {
private:
    TreeNode<T> *root;
public:
    TreapTree() : root(NULL) {
    }

    ~TreapTree() {
        std::queue<TreeNode<T> *> tmp;
        if(root != NULL) {
            tmp.push(root);
        }

        while(!tmp.empty()) {
            TreeNode<T> *cur = tmp.front();
            if(cur->left != NULL) {
                tmp.push(cur->left);
            }
            if(cur->right != NULL) {
                tmp.push(cur->right);
            }

            delete cur;
            tmp.pop();
        }
    }

    // разделить и властвовать
    void split(TreeNode<T> *curNode, const T &data, TreeNode<T> *&left, TreeNode<T> *&right) {
        if(curNode == NULL) {
            left = NULL;
            right = NULL;
        }
        else if(curNode->data <= data) {
            split(curNode->right, data, curNode->right, right);
            left = curNode;
        }
        else
        {
            split(curNode->left, data, left, curNode->left);
            right = curNode;
        }
    }

    // задать корень
    void setRoot(TreeNode<T> *_root) {
        root = _root;
    }

    // добавление элемента в дерево
    void add(const T &data, int priority) {
        TreeNode<T> *node = new TreeNode<T>(data, priority),
                    *curNode = root,
                    *prevNode = root;

        if(curNode == NULL) {
            setRoot(node);
            return;
        }

        // Сначала спускаемся по дереву (как в обычном бинарном
        // дереве поиска по x), но останавливаемся на первом
        // элементе, в котором значение приоритета оказалось
        // меньше y.
        while(curNode != NULL && priority <= curNode->priority) {
            prevNode = curNode;
            if(data <= curNode->data) {
                curNode = curNode->left;
            }
            else
            {
                curNode = curNode->right;
            }
        }

        // Теперь разрезаем поддерево найденного элемента на T1 и
        // T2. Полученные T1 и T2 записываем в качестве левого и
        // правого сына добавляемого элемента.
        split(curNode, data, node->left, node->right);

        // Полученное дерево ставим на место элемента,
        // найденного в первом пункте.
        if(curNode == root) {
            root = node;
        }
        else if(data <= prevNode->data) {
            prevNode->left = node;
        }
        else
        {
            prevNode->right = node;
        }
    }

    // возвращаем ширину
    int getMaxWidth() {
        int maxWidth = 0,
            curWidth = 0;

        std::queue<TreeNode<T> *> layerNodes;
        TreeNode<T> *cur = NULL;
        layerNodes.push(root);

        while(!layerNodes.empty()) {
            if((curWidth = layerNodes.size()) > maxWidth) {
                maxWidth = curWidth;
            }

            for(size_t i = 0; i < curWidth; i++) {
                cur = layerNodes.front();
                if(cur->left != NULL) {
                    layerNodes.push(cur->left);
                }
                if(cur->right != NULL) {
                    layerNodes.push(cur->right);
                }
                layerNodes.pop();
            }
        }

        return maxWidth;
    }

    // вывод дерева
    void show() {
        if(root != NULL) {
            root->show();
        }
    }
};



int main() {
    NaiveTree<long> naive;
    TreapTree<long> treap;

    int n = 0;
    std::cin >> n;

    long data = 0;
    int priority = 0;

    for(int i = 0; i < n; i++) {
        if(std::cin >> data >> priority) {
            naive.add(data);
            treap.add(data, priority);
        }
    }

    // naive.show();
    // treap.show();

    std::cout << (treap.getMaxWidth() - naive.getMaxWidth());

    return 0;
}
