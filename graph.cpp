
#include "graph.h"

void Graph::InsertPlaceholder(const string &node_name) {
    Node *new_node = new PlaceholderNode(node_name, time_count_);
    nodes_[node_name] = new_node;
    delete_nodes_list_.emplace_back(new_node);
}

void Graph::InsertConstant(const string &node_name, float value) {
    Node *new_node = new ConstantNode(node_name, value, time_count_);
    nodes_[node_name] = new_node;
    delete_nodes_list_.emplace_back(new_node);
}

void Graph::InsertVariable(const string &node_name, float value) {
    Node *new_node = new VariableNode(node_name, value, time_count_);
    nodes_[node_name] = new_node;
    delete_nodes_list_.emplace_back(new_node);
}

void Graph::InsertOperation(const string &node_name, const string &operation_type, const string &input1,
                            const string &input2) {
    Node *new_node = nullptr;
    if (operation_type[0] == '+')
        new_node = new PlusNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type[0] == '-')
        new_node = new MinusNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type[0] == '*')
        new_node = new MultipleNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type[0] == '/')
        new_node = new DivisionNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == "==")
        new_node = new EqualNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == ">=")
        new_node = new GreaterAndEqualNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == "<=")
        new_node = new LessAndEqualNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == "!=")
        new_node = new NotEqualNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == ">")
        new_node = new GreaterNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == "<")
        new_node = new LessNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == "MAX")
        new_node = new MaximumNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == "MIN")
        new_node = new MinimumNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    else if (operation_type == "AVE")
        new_node = new AverageNode(node_name, nodes_[input1], nodes_[input2], time_count_);
    nodes_[node_name] = new_node;
    delete_nodes_list_.emplace_back(new_node);
}

void Graph::InsertOperation(const string &node_name, const string &operation_type, const string &input) {
    Node *new_node = nullptr;
    if (operation_type == "SIN") new_node = new SinNode(node_name, nodes_[input], time_count_);
    else if (operation_type == "LOG") new_node = new LogNode(node_name, nodes_[input], time_count_);
    else if (operation_type == "EXP") new_node = new ExpNode(node_name, nodes_[input], time_count_);
    else if (operation_type == "TANH")new_node = new TanhNode(node_name, nodes_[input], time_count_);
    else if (operation_type == "SIGMOID")new_node = new SigmoidNode(node_name, nodes_[input], time_count_);
    else if (operation_type == "PRINT")new_node = new PrintNode(node_name, nodes_[input], time_count_);
    nodes_[node_name] = new_node;
    delete_nodes_list_.emplace_back(new_node);
}

void Graph::InsertOperation(const string &node_name, const string &operation_type, const string &input1,
                            const string &input2,
                            const string &input3) {
    Node *new_node = nullptr;
    if (operation_type == "COND")
        new_node = new ConditionNode(node_name, nodes_[input1], nodes_[input2], nodes_[input3], time_count_);
    nodes_[node_name] = new_node;
    delete_nodes_list_.emplace_back(new_node);
}

void Graph::Eval(const string &node_name, const vector<pair<string, float>> &placeholder_initial_list) {

    time_count_++;        //更新当前操作次数

    for (const auto &i : placeholder_initial_list) {
        auto now = dynamic_cast<PlaceholderNode *>(nodes_[i.first]);
        now->set_val(i.second);        //为placeholder设值
    }

    try {
        nodes_[node_name]->cal();
        float temp_value = nodes_[node_name]->value();
        cout << std::fixed << setprecision(4) << temp_value << endl;
        result_.emplace_back(0, temp_value);
    }
    catch (int wa) {    //捕捉错误
        switch (wa) {
            case 1:
                result_.emplace_back(1, 0.0);
                cout << "ERROR: Placeholder missing" << endl;
                break;
            case 2:
                result_.emplace_back(2, 0.0);
                cout << "ERROR: Division by zero" << endl;
                break;
            case 3:
                result_.emplace_back(3, 0.0);
                cout << "ERROR: LOG operator's input must be positive" << endl;
                break;
        }
    }
}

void Graph::SetVariable(const string &node_name, float value) {
    time_count_++;
    result_.emplace_back(make_pair(-1, 0.0));
    auto var = dynamic_cast<VariableNode *>(nodes_[node_name]);
    var->set_val(value);
}

void Graph::SetVariableByRecord(const string &node_name, int history_record) {
    if (history_record > time_count_) {    //此操作在当前操作之前，无历史记录
        cout << "ERROR: This operation follows current operation" << endl;
        time_count_++;
        result_.emplace_back(make_pair(4, 0.0));
        return;
    }
    if (result_[history_record - 1].first != 0) {    //该操作没有输出
        time_count_++;
        result_.emplace_back(make_pair(5, 0.0));
        cout << "ERROR: This operation has no output" << endl;
        return;
    }
    SetVariable(node_name, result_[history_record - 1].second);
}

void Graph::SetVariableByVariable(const string &node_name, const string &node_name_to) {
    SetVariable(node_name, nodes_[node_name_to]->value());
}

void Graph::Clear() {
    for (auto &i : delete_nodes_list_) {
        delete i;        //根据list删除结点
    }
    nodes_.clear();
    delete_nodes_list_.clear();
}

Graph::~Graph() {
    for (auto &i : delete_nodes_list_) {    //如果已经Clear，则list为空，不会重复delete
        delete i;
    }
    nodes_.clear();
    delete_nodes_list_.clear();
}

void Graph::ShowHistory() {
    time_count_++;
    result_.emplace_back(make_pair(-1, 0));
    for (int i = 0; i < time_count_; ++i) {
        cout << "Operation[" << i + 1 << "] : ";
        int type_ = result_[i].first;
        switch (type_) {
            case -1:
                cout << "No output" << endl;
                break;
            case 0:
                cout << result_[i].second << endl;
                break;
            case 1:
                cout << "ERROR: Placeholder missing" << endl;
                break;
            case 2:
                cout << "ERROR: Division by zero" << endl;
                break;
            case 3:
                cout << "ERROR: LOG operator's input must be positive" << endl;
                break;
            case 4:
                cout << "ERROR: This operation follows current operation" << endl;
                break;
            case 5:
                cout << "ERROR: This operation has no output" << endl;
                break;
            default:
                break;
        }
    }
}

void Graph::QueryHistoryRecord(int history_record) {
    time_count_++;
    cout << "Operation[" << history_record << "] : ";
    history_record--;
    int type_ = result_[history_record].first;
    switch (type_) {
        case -1:
            cout << "No output" << endl;
            break;
        case 0:
            cout << result_[history_record].second << endl;
            break;
        case 1:
            cout << "ERROR: Placeholder missing" << endl;
            break;
        case 2:
            cout << "ERROR: Division by zero" << endl;
            break;
        case 3:
            cout << "ERROR: LOG operator's input must be positive" << endl;
            break;
        case 4:
            cout << "ERROR: This operation follows current operation" << endl;
            break;
        case 5:
            cout << "ERROR: This operation has no output" << endl;
            break;
        default:
            break;
    }
    result_.emplace_back(make_pair(-1, 0));
}



