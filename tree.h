#ifndef TREE_H
#define TREE_H



class Set
{
    class SetImplementation;
    SetImplementation *pimpl;
public:
    Set();
    ~Set();
    bool isEmpty ()const;
    void push (int data);
    void display();
    int find (int key);
    Set unite(Set A);
    Set intersection(Set &A, Set &B);
    Set &operator= (const Set &t);
protected:
    bool nextDatum (bool start, int &datum) const;
};



#endif // TREE_H
