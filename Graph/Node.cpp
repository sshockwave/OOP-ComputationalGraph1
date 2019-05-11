#include "Node.h"

Node::Node(Graph &graph, string name, char ntype, MathFunc *func)
    : graph(graph), name(name), ntype(ntype), func(func)
{
    value = new Scalar<float>(0); // avoid nullptr. it will be set again in setValue
};

Node::~Node()
{
    if (this->value != nullptr)
        delete value;
    // other pointers will be deleted by other procedures
}

void Node::setValue(Value *value)
{
    // cleans the old value
    if (this->value != nullptr)
        delete this->value;
    this->value = value;
}

void Node::addFather(Node *father)
{
    this->fathers.push_back(father);
    father->children.push_back(this);
}

void Node::addAncestor(Node *ancestor)
{
    this->ancestors.insert(ancestor);
    ancestor->descendants.insert(this);
}