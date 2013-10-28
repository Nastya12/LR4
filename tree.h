#ifndef TREE_H
#define TREE_H



class Set
{
    class SetImplementation;
    SetImplementation *pimpl;
public:
    Set();
    Set(const Set &ob);
    ~Set();
    bool isEmpty ()const;
    void push (int data);
    void display();
    int find (int key);
    Set unite(const Set &A)const;
    Set intersection(const Set &A) const;
    Set difference (const Set &A) const;
    Set &operator= (const Set &t);
protected:
    bool nextDatum (bool start, int &datum) const;
};



#endif // TREE_H
