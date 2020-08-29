#ifndef TREE_H
#define TREE_H

class Tree : public Prop {
private:
    
public:
    Tree();
    Tree(char shape, bool climbable);
    virtual ~Tree();
    
    void print();
    
    virtual bool isTree();

    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
