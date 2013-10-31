#include "tree.h"
#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;


struct Node
{
    int datum;
    Node *left, *right;
    int count;
    /*Node (int datum):datum(datum), left(0), right (0){}
    ~Node()
    {
        datum=0;
        left=0;
        right=0;
    }*/
};

class Set::SetImplementation
{
public:    Node *root;
    void copySetImplementation(Node *&rootnew, Node *rootold);
    void deleteSetImplementation(Node *top);

    void unite(Node *top);
    void intersection(Node *top, SetImplementation &B, SetImplementation &C, SetImplementation &A);
    void intersection(Node *top,SetImplementation &C,Node *root);
    void difference(Node *top, Set &C, Set &A);

    void push (Node *&top, int data);
    void display (Node *top);
    Node *find (Node *top, int key);
    Node* copyNode(Node *nd);

    //Set::SetImpl;
    SetImplementation();
    SetImplementation(int t);
    SetImplementation (const SetImplementation &ob);
    ~SetImplementation();

    bool isEmpty()const;
    void push (int data);
    void display();
    int find (int key);

    Set unite(SetImplementation &A);
    Set intersection(SetImplementation &A);
    Set difference (SetImplementation &A);

    Set &operator= (const SetImplementation &t);
    bool nextDatum(bool start, int &datum) const;
};

//////////   Set /////////

Set::Set():
    pimpl(0)
{
    pimpl=new SetImplementation();
}

Set::Set(const Set &ob)
{
    pimpl=new SetImplementation();
    if (ob.pimpl->root==0)
        pimpl->root=0;
    else
    {
        pimpl->root=new Node;
        pimpl->root->datum=ob.pimpl->root->datum;
        (pimpl->root)->count=1;
        (pimpl->root)->left=0;
        (pimpl->root)->right=0;
        copySetImplementation(pimpl->root, ob.pimpl->root);
    }
}

/*Set::Set(const Set &ob)
{
    pimpl=new SetImplementation(pimpl->root);
    pimpl->root=pimpl->copyNode(ob.pimpl->root);
}*/

Set::~Set()
{
    delete pimpl;
    pimpl=0;
}

bool Set::isEmpty ()const
{
    return pimpl->isEmpty();
};

void Set::push (int data)
{
    pimpl->push(data);
};

void Set::display()
{
    pimpl->display();
}

int Set::find (int key)
{
    return pimpl->find(key);
}

Set Set::unite(const Set &A) const
{
    Set result;
    result.pimpl->unite(A.pimpl->root);
    return result;
}

Set Set::intersection(const Set &A) const
{
    Set result;
    result.pimpl->intersection(pimpl->root, *A.pimpl);
    return result;
}

Set Set::difference (const Set &A) const
{
    Set result;
    result.pimpl->difference(pimpl->root, *result.pimpl, *A.pimpl);
    return result;
}

Set &Set::operator= (const Set &t)
{
    pimpl->operator=(*t.pimpl);
    return *this;
}

bool Set::nextDatum(bool start, int &datum) const
{
    return pimpl->nextDatum(start, datum);
}
///////////// SetImplementation/////////
Set::SetImplementation::SetImplementation():
    root(0)
{
}

Set::SetImplementation::~SetImplementation()
{
    deleteSetImplementation(root);
}

void Set::SetImplementation::push (Node *&top, int data)
{
    if(top==0)
    {
        top=new Node;
        top->datum=data;
        top->count=1;
        top->left=0;
        top->right=0;
    }
    else if (data<top->datum)
        push(top->left, data);
    else if (data>top->datum)
        push(top->right, data);
    else top->count++;
}

Set::SetImplementation::SetImplementation(int t):
    root(0)
{
    for (int i=0; i<t ; i++ )
        push(root, rand()%10 -5);
}

void Set::SetImplementation::push (int data)
{
    push(root, data);
}

void Set::SetImplementation::copySetImplementation(Node *&rootnew, Node *rootold)
{
    if (rootold->left!=0)
    {
        push(rootnew, (rootold->left)->datum);
        copySetImplementation(rootnew, rootold->left);
    }
    if (rootold->right!=0)
    {
        push(rootnew, (rootold->right)->datum);
        copySetImplementation(rootnew, rootold->right);
    }
}


Set::SetImplementation::SetImplementation (const SetImplementation &ob)
{
    if (ob.root==0)
        root=0;
    else
    {
        root=new Node;
        root->datum=ob.root->datum;
        root->count=1;
        root->left=0;
        root->right=0;
        copySetImplementation(root, ob.root);
    }
}

void Set::SetImplementation::deleteSetImplementation(Node *top)
{
    if (top->left!=0) deleteSetImplementation(top->left);
    if (top->right!=0) deleteSetImplementation(top->right);
    delete top;
}

void Set::SetImplementation::display(Node *top)
{
    if(top!=0)
    {
        display(top->left);
        cout<<"\n Number: "<<top->datum<<" - "<<top->count<<" kol-vo";
        display(top->right);
    }
}

void Set::SetImplementation::display()
{
    display(root);
}

Node *Set::SetImplementation::find (Node*top, int key)
{
    if(top==0)
        return 0;
    else if (key<top->datum) return find (top->left, key);
    else if (key>top->datum) return find (top->right, key);
    else return top;
}

int Set::SetImplementation::find (int key)
{
    Node *top=find(root,key);
    if (top) return top->count;
    else return 0;
}
bool Set::SetImplementation::isEmpty() const
{
    return root==0;
}

Set Set::SetImplementation::unite(SetImplementation &A)
{
    SetImplementationl C;
    C.root=C.copyNode(root);
    C.unite(A.root);
    return C;
}

void Set::SetImplementation::unite(Node *top)
{
    if (!top)
        return;
    push(root, top->datum);
    unite(top->right);
    unite(top->left);
}
Set Set::SetImplementation::intersection(SetImplementation &A)
{
    SetImplementation C;
    intersection(root,C,A);
    return C;
}

void Set::SetImplementation::intersection(Node*top,SetImplementation &C,Node*root)
{
    if(!top)
        return;
    intersection(top->left,C,root);
    push(C.root,top->datum);
    intersection(top->right,C,root);
}

void Set::SetImplementation::difference(Node *top, Set &C, Set &A)
{
    if(!top)
        return;
    push(C.root, top->datum);
    difference(top->left,A);
    difference(top->right,A);

}

Set Set::SetImplementation::difference (SetImplementation &A)
{
    SetImplementation C;
    difference(root, C,A);
    return C;
}

Set& Set::SetImplementation::operator= (const SetImplementation &t)
{
    if(this==&t) return *this;
    deleteSetImplementation(root);
    copySetImplementation(root,t.root);
    return *this;
}

Node* Set::SetImplementation::copyNode(Node *nd)
{
    if (!nd)
        return NULL;
    Node *Nd=new Node;
    Nd->datum=Nd->datum;
    Nd->count=Nd->count;
    Nd->left=copyNode(Nd->left);
    Nd->right=copyNode(Nd->right);
    return Nd;
}

bool Set::SetImplementation::nextDatum(bool start, int &datum) const
{
    static Node *cur;
    if (start)
        cur=root;
    bool result=cur!=0;
    if (result)
    {
        datum=cur->datum;
        cur=cur->left;
        cur=cur->right;
    }
    return result;
}
