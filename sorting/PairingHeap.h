
#include <utility>
#include <stack>

template <class S, class T>
class PairingHeap
{
public:
    struct node
    {
        S key;
        T value;
private:
        node* parent;
        node* child;
        node* sibling;
        
        explicit node(S k, T v) : key(k), value(v), parent(nullptr), child(nullptr), sibling(nullptr) {}
        node() = delete;
        friend class PairingHeap;
    };

public:
    PairingHeap(bool minimumOnTop = true) : isMin(minimumOnTop), root(nullptr) {}

    ~PairingHeap()
    {
        //TODO: improve this
        while (!IsEmpty())
        {
            DeleteTop();
        }
    }

    node* FindTop() const
    {
        return root;
    }

    bool IsEmpty() const
    {
        return (nullptr == root);
    }

    void Delete(node* n)
    {
        DeleteWithTwoPass(n);
    }

    void DeleteTop()
    {
        DeleteWithTwoPass(root);
    }

    void Insert(std::pair<S, T> ip)
    {
        node* newNode = new node(ip.first, ip.second);
        root = merge(root, newNode);
    }

    void ChangePriority(node* nd, S priority)
    {
        //Todo: implement this.
        (void)nd;
        (void)priority;
    }

    void Merge(PairingHeap otherHeap)
    {
        root = merge(root, otherHeap.root);

        //No matter what we did, we need to invalidate the other heap.
        otherHeap.root = nullptr;
    }

private:

    node* merge(node* l, node* r)
    {
        //nullptr in nodes means the merge is a no-op in one direction.
        if (nullptr == l) return r;
        if (nullptr == r) return l;

        //Merging two non-empty heaps means finding the lesser of the two roots,
        //then making the greater of the two roots a child tree of the other.
        if (l->key <= r->key)
        {
            AddAsChild(l, r);
            return l;
        }
        else
        {
            AddAsChild(r, l);
            return r;
        }
    }

    void DeleteWithTwoPass(node* deleteMe)
    {
        if (deleteMe == nullptr) return;

        node* newRoot = nullptr;
        //Need to twopass the child nodes.
        if (nullptr != deleteMe->child)
        {
            newRoot = deleteMe->child;
            std::stack<node*> roots;
            while (newRoot != nullptr && newRoot->sibling != nullptr)
            {
                node* nextNode = newRoot->sibling->sibling;
                newRoot->sibling->sibling = nullptr;
                newRoot->sibling->parent = nullptr;
                node* sibNode = newRoot->sibling;
                newRoot->sibling = nullptr;
                newRoot->parent = nullptr;
                roots.push(merge(newRoot, sibNode));

                newRoot = nextNode;
            }

            if (nullptr != newRoot)
            {
                newRoot->parent = nullptr;
            }

            //newRoot may not be null at the end, but that's ok, we'll merge it in.
            while (!roots.empty())
            {
                newRoot = merge(newRoot, roots.top());
                roots.pop();
            }
            //Now we should have a new heap structure.

            //Only need to re-insert into the sib list if there was a child node.
            //And if there was a parent node...
            if (nullptr != deleteMe->parent)
            {
                //Insert newRoot at the beginning of the sib list.
                node* newSib = deleteMe->parent->child;
                deleteMe->parent->child = newRoot;
                newRoot->sibling = newSib;
                newRoot->parent = deleteMe->parent;
            }
        }
        else if (nullptr != deleteMe->parent)
        {
            if (deleteMe->parent->child == deleteMe)
            {
                deleteMe->parent->child = deleteMe->sibling;
            }
            else
            {
                node* sib = deleteMe->parent->child;
                while (sib->sibling != nullptr && sib->sibling != deleteMe) sib = sib->sibling;
                if (sib->sibling != nullptr) sib->sibling = deleteMe->sibling;
            }
        }
        
        if (nullptr == deleteMe->parent)
        {
            //Must be root! replace root.
            root = newRoot;
        }

        delete deleteMe;
    }

    void AddAsChild(node* parent, node* child)
    {
        child->parent = parent;
        if (nullptr == parent->child)
        {
            parent->child = child;
        }
        else
        {
            node* sib = parent->child;
            while (sib->sibling != nullptr) sib = sib->sibling;
            sib->sibling = child;         
        }
    }

    bool isMin;
    node* root;
};
