#include "Graph.h"
#include <stdio.h>

void Graph::newNode(string name, char ntype, float initValue)
{
    newNode(name, ntype, new Scalar<float>(initValue));
}

void Graph::newNode(string name, char ntype, Value *initValue) {
    Node *node = new Node(*this, name, ntype, nullptr); // nullptr means no mathFunc
    node->setValue(initValue);
    if (ntype != 'C')
        node->addAncestor(node);
    nodes[name] = node;
}

void Graph::newNode(string name, vector<string> fathers, MathFunc *func, bool printFlag) {
    Node *node = new Node(*this, name, 'I', func);
    for(auto name : fathers)
    {
        if(!nodes.count(name))
            throw "ERROR: Node " + name + " not found";
    }
    for(int i = 0; i < fathers.size(); i ++) {
        Node *father = nodes[fathers[i]];
        node->addFather(father);
        for(auto ancestor:father->ancestors) {
            node->addAncestor(ancestor);
        }
    }
    if (printFlag)
    {
        // node->prints.push_back(nodes[fathers[0]]);
        node->prints.insert(node);
    }
    for (auto father : node->fathers)
    {
        for (auto printNode : father->prints)
            node->prints.insert(printNode);
    }
    nodes[name] = node;
}

void Graph::editNode(string name, float initValue) {
    editNode(name, new Scalar<float>(initValue));
}

void Graph::editNode(string name, Value *newValue) {
    if(!nodes.count(name))
        throw "ERROR: Node " + name + " not found";
    if(nodes[name]->ntype != 'P' && nodes[name]->ntype != 'V')
        throw "ERROR: Edit non-Placeholder or non-Variable node" + name;
    if(GET_VALUE_S_F(nodes[name]->value) == GET_VALUE_S_F(newValue))
        return;
    nodes[name]->setValue(newValue);
    for (auto des : nodes[name]->descendants)
        des->updateFlag = 1;
}

void Graph::eval(string target, vector<string> inName, vector<Value*> inValue) {
    step ++;
    if(!nodes.count(target))
            throw "ERROR: Node " + target + " not found";
    Node &work = *nodes[target];

    for (auto ancestor : work.ancestors) {
        if (ancestor->ntype == 'P') {
            bool flag = false;
            for (auto name : inName)
                if(name == ancestor->name)
                    flag = true;
            if (flag == false)
                throw "ERROR: Placeholder missing";
        }
    }
    for(int i = 0; i < inName.size(); i ++) {
        editNode(inName[i], inValue[i]);
    }
    DFScompute(&work);
    for (auto printNode : work.prints)
    {
        cout << "PRINT operator: " << printNode->fathers[0]->name;
        printf(" = %.4f\n", GET_VALUE_S_F(printNode->fathers[0]->value));
    }
    printf("%.4f\n", GET_VALUE_S_F(work.value));
    // cout << "#  " << work.name << "$"<< GET_VALUE_S_F(work.value) << "@" << (work.func==nullptr?"0":work.func->name) << endl;
    ans.push_back(new Scalar<float>(GET_VALUE_S_F(work.value)));
}

Value* Graph::getAns(int step) {
    if (ans[step] != nullptr)
        return new Scalar<float> (GET_VALUE_S_F(ans[step])); // get one copy
    throw "ERROR: Step " +  to_string(step + 1) + " has no answer";
}

void Graph::DFScompute(Node *work) {
    if (work->updateFlag) {
        if (work->fathers.size() != 0)
        {
            for (auto father : work->fathers)
                DFScompute(father);
            vector<Value *> in;
            for(auto father : work->fathers)
                in.push_back(father->value);
            work->func->compute(in, work->value);
            // cout << "###" << work->name << "$"<< GET_VALUE_S_F(work->value) << "@" << work->func->name << endl;
            work->updateFlag = 0;
        }
        else{
            work->updateFlag = 0;
        }
    }
}