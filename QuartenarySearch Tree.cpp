#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename Value>
struct QuadNode
{
    T key;
    Value value;
    QuadNode *children[4];

    QuadNode(T _key, Value _value) : key(_key), value(_value)
    {
        for (int i = 0; i < 4; ++i)
            children[i] = nullptr;
    }
};

template <typename T, typename Value>
class QuadTree
{
    QuadNode<T, Value> *root;

public:
    QuadTree() : root(nullptr) {}

    QuadTree(const std::vector<std::pair<T, Value>> &objects)
    {
        root = nullptr;
        for (const auto &obj : objects)
        {
            insert(obj.first, obj.second);
        }
    }

    void insert(T key, Value value)
    {
        root = insertRecursive(root, key, value);
    }

    void remove(T key)
    {
        root = removeRecursive(root, key);
    }

    // Recursive insertion function
    QuadNode<T, Value> *insertRecursive(QuadNode<T, Value> *node, T key, Value value)
    {
        if (node == nullptr)
            return new QuadNode<T, Value>(key, value);

        if (key < node->key / 2)
            node->children[0] = insertRecursive(node->children[0], key, value);
        else if (key < node->key)
            node->children[1] = insertRecursive(node->children[1], key, value);
        else if (key < 2 * node->key)
            node->children[2] = insertRecursive(node->children[2], key, value);
        else
            node->children[3] = insertRecursive(node->children[3], key, value);

        return node;
    }

    // Recursive removal function
    QuadNode<T, Value> *removeRecursive(QuadNode<T, Value> *node, T key)
    {
        if (node == nullptr){
            return nullptr;
        }

        if (key < node->key / 2)
            node->children[0] = removeRecursive(node->children[0], key);
        else if (key < node->key)
            node->children[1] = removeRecursive(node->children[1], key);
        else if (key < 2 * node->key)
            node->children[2] = removeRecursive(node->children[2], key);
        else //(key >= 2 * node->key)
            node->children[3] = removeRecursive(node->children[3], key);
        if (node->key == key) 
        {
            // Node with the key found, perform deletion
            if (node->children[2] != nullptr)
            {
                QuadNode<T, Value> *successor = findMin(node->children[2]);
                node->key = successor->key;
                node->children[2] = removeRecursive(node->children[2], successor->key);
            }
            else if (node->children[3] != nullptr)
            {
                QuadNode<T, Value> *successor = findMin(node->children[3]);
                node->key = successor->key;
                node->children[3] = removeRecursive(node->children[3], successor->key);
            }
            else
            {
                // Node has no children
                delete node;
                cout << "Key is deleted from the tree" << endl;
                return nullptr;
            }
        }

        return node;
    }

    // Find the minimum key in a subtree
    QuadNode<T, Value> *findMin(QuadNode<T, Value> *node)
    {
        while (node->children[0] != nullptr)
        {
            node = node->children[0];
        }
        return node;
    }

    void printPreOrder() const
    {
        printPreOrderRecursive(root);
        std::cout << std::endl;
    }

    void printPostOrder() const
    {
        printPostOrderRecursive(root);
        std::cout << std::endl;
    }

private:
    // Recursive pre-order printing function
    void printPreOrderRecursive(const QuadNode<T, Value> *node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->key << " " << node->value << endl;
        printPreOrderRecursive(node->children[0]);
        printPreOrderRecursive(node->children[1]);
        printPreOrderRecursive(node->children[2]);
        printPreOrderRecursive(node->children[3]);
    }

    // Recursive post-order printing function
    void printPostOrderRecursive(const QuadNode<T, Value> *node) const
    {
        if (node == nullptr)
            return;

        printPostOrderRecursive(node->children[0]);
        printPostOrderRecursive(node->children[1]);
        printPostOrderRecursive(node->children[2]);
        printPostOrderRecursive(node->children[3]);
        std::cout << node->key << " " << node->value << endl;
    }
};

int main()
{
    try
    {
        std::vector<std::pair<int, string>> initialObjects = {{5, "Ai"}, {1, "Bi"}, {22, "Ci"}, {25, "Ei"}, {12, "Fi"}, {35, "Gi"}, {10, "Hi"}};
        QuadTree<int, string> quadTree(initialObjects);

        int flag = 1, choice, node;
        string value;
        while(flag == 1){
            cout << "1 for Insert" << endl;
            cout << "2 for Delete" << endl;
            cout << "3 for Pre-order" << endl;
            cout << "4 for Post-order" << endl;
            cout << "5 for Exit" << endl;
            cout << "Enter the choice you want to select : ";
            cin >> choice;
            switch(choice){
                case 1:
                    cout << "Enter the node you want to insert: ";
                    cin >> node;
                    cout << "Enter the value you want to insert: ";
                    cin >> value;
                    quadTree.insert(node, value);
                    cout << "After the process Pre-order traversal:" << endl;
                    quadTree.printPreOrder();
                    break;
                case 2:
                    cout << "Enter the node you want to delete: ";
                    cin >> node;
                    quadTree.remove(node);
                    cout << "After the process Pre-order traversal:" << endl;
                    quadTree.printPreOrder();
                    break;
                case 3:
                    cout << "Pre-order traversal:" << endl;
                    quadTree.printPreOrder();
                    break;
                case 4:
                    cout << "Post-order traversal:" << endl;
                    quadTree.printPostOrder();
                    break;
                case 5:
                    flag = 0;
                    break;
                default:
                    cout << "Entered wrong choice: " << endl;
                    break;
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "An unexpected error occurred." << endl;
        return 1;
    }
    
    return 0;
}
