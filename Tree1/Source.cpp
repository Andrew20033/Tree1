#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <climits>

class Node
{
public:
    Node(std::string const& eng, std::string const& rus) : _eng(eng), _rus(rus), num(0), left(nullptr), right(nullptr) {}
    void insert(std::string const& eng, std::string const& rus)
    {
        if (eng < _eng)
        {
            if (!left)
            {
                left = new Node(eng, rus);
            }
            else
            {
                left->insert(eng, rus);
            }
        }
        else if (eng > _eng)
        {
            if (!right)
            {
                right = new Node(eng, rus);
            }
            else
            {
                right->insert(eng, rus);
            }
        }
    }
    std::string find(std::string const& eng) 
    {
        std::string ret;
        if (eng == _eng)
        {
            ret = _rus;
            ++num;
        }
        else if (eng < _eng && left)
        {
            ret = left->find(eng);
        }
        else if (eng > _eng && right)
        {
            ret = right->find(eng);
        }
        return ret;
    }
    ~Node()
    {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
        //std::cout << _eng << " deleted" << std::endl;
    }
    friend class Tree;
private:
    std::string _eng;
    std::string _rus;
    int num;
    Node* left;
    Node* right;
};

class Tree
{
public:
    Tree() : root(nullptr) {}
    void insert(std::string const& eng, std::string const& rus)
    {
        if (!root)
        {
            root = new Node(eng, rus);
        }
        else
        {
            root->insert(eng, rus);
        }
    }
    std::string find(std::string const& eng) const
    {
        std::string ret;
        if (root)
        {
            ret = root->find(eng);
        }

        return ret;
    }
    std::multimap<int, std::string> unpopular() const 
    {
        std::multimap<int, std::string> mmin = { std::make_pair(INT_MAX, ""), std::make_pair(INT_MAX, "") , std::make_pair(INT_MAX, "") };
        if (root)
        {
            std::queue<Node*> que;
            que.push(root);
            while (!que.empty())
            {
                Node* node = que.front();
                que.pop();
                //
                {
                    auto it = --mmin.end();
                    if (node->num < it->first)
                    {
                        mmin.erase(it);
                        mmin.emplace(node->num, node->_eng);
                    }
                }
                if (node->left)
                {
                    que.push(node->left);
                }
                if (node->right)
                {
                    que.push(node->right);
                }
            }
        }

        return mmin;
    }
    ~Tree()
    {
        delete root;
        root = nullptr;
    }
private:
    Node* root;
};

int main()
{
    Tree dct;

    dct.insert("w1", "t1"); 
    dct.insert("w2", "t2");
    dct.insert("w1", "t111");
    dct.insert("w3", "t3");
    dct.insert("w4", "t4");


    std::cout << dct.find("w1") << std::endl;
    std::cout << dct.find("w2") << std::endl;
    std::cout << dct.find("w2") << std::endl;


    auto mmap = dct.unpopular();
    std::cout << "three unpopular words:\n";
    for (auto const& val : mmap)
    {
        if (val.first != INT_MAX)
        {
            std::cout << val.second << " - " << val.first << std::endl;
        }
    }
}