#include "Parser.h"

Parser::Parser(Graph &graph) : graph(graph)
{
    // get some MathFunc objects
    mathFuncs.push_back(&__Print__);
    mathFuncs.push_back(&__Exp__);
    mathFuncs.push_back(&__Sigmoid__);
    mathFuncs.push_back(&__Log__);
    mathFuncs.push_back(&__Sin__);
    mathFuncs.push_back(&__Tanh__);
    mathFuncs.push_back(&__Minus__);
    mathFuncs.push_back(&__Plus__);
    mathFuncs.push_back(&__Sub__);
    mathFuncs.push_back(&__Mult__);
    mathFuncs.push_back(&__Div__);
    mathFuncs.push_back(&__Smaller__);
    mathFuncs.push_back(&__SmallerEqual__);
    mathFuncs.push_back(&__Equal__);
    mathFuncs.push_back(&__LargerEqual__);
    mathFuncs.push_back(&__Larger__);
    mathFuncs.push_back(&__Cond__);
}

istream &operator>>(istream &input, Parser &parser)
{
    while (1) // discard '\n'
    {
        getline(input, parser.tmp_line);
        if (parser.tmp_line.size() != 0)
            break;
    }
    parser.parse();
}

void Parser::parse(const string &line)
{
    tmp_line = line;
    parse();
}

void Parser::split(const string &line, vector<string> &tokens)
{
    string::size_type index1, index2;
    index1 = 0;
    index2 = line.find(" ");

    while (string::npos != index2) // successfully found index2
    {
        string token = line.substr(index1, index2 - index1);
        if (token != "")
            tokens.push_back(token);

        index1 = index2 + 1; // skip the " "
        index2 = line.find(" ", index1);
    }
    if (index1 != line.length()) // get the last substr
        tokens.push_back(line.substr(index1));
    return;
}

void Parser::parse()
{
    tmp_tokens.clear();                // clean tmp_tokens before getting new tokens
    this->split(tmp_line, tmp_tokens); // get new tokens
    try
    {
        if (mod == 1)
        {
            cmdBase();
        }
        else if (mod == 2)
        {
            cmdInter();
        }
        else if (mod == 3)
        {
            // operator>> already makes tmp_tokens.size() >= 1
            string cmd = tmp_tokens[0];
            if (cmd == "EVAL")
            {
                cmdEval();
            }
            else if (cmd == "SETCONSTANT")
            {
                cmdSetCon();
            }
            else if (cmd == "SETANSWER")
            {
                cmdSetAns();
            }
            else
            {
                throw "ERROR: Unknown command " + cmd;
            }
        }
    }
    catch (const invalid_argument &e) // mainly stof failed
    {
        cout << "ERROR: " << e.what() << '\n';
    }
    catch (const string &e) // may be node not found, or unkown command
    {
        cout << e << '\n';
    }
    catch (const char *e) // may be placeholder missing, log non-positive, etc
    {
        cout << e << '\n';
    }
}

void Parser::setMod(int mod)
{
    this->mod = mod;
}

void Parser::cmdBase()
{
    if (tmp_tokens.size() < 2)
    {
        throw "ERROR: Bad token num";
    }
    string nodename = *tmp_tokens.begin();
    string ntype = *(tmp_tokens.begin() + 1);
    if (ntype == "P")
    {
        graph.newNode(nodename, 'P', (float)0.);
    }
    else if (tmp_tokens.size() != 3)
    {
        throw "ERROR: Bad token num";
    }
    else if (ntype == "V" || ntype == "C")
    {
        graph.newNode(nodename, ntype[0],
                      (stof(*(tmp_tokens.begin() + 2))));
    }
    else
    {
        throw "ERROR: Unknown command";
    }
}

void Parser::cmdInter()
{
    if (tmp_tokens.size() <= 3)
        throw "ERROR: Bad token num";

    int i;
    for (i = 0; i < mathFuncs.size(); i++)
        if (mathFuncs[i]->match(graph, tmp_tokens))
            break;

    if (i == mathFuncs.size())
        throw "ERROR: Unknown math function";
}

void Parser::cmdEval()
{
    if (tmp_tokens.size() < 2 || // size = 2 means no placeholder to fill
        tmp_tokens.size() >= 3 && tmp_tokens.size() != 3 + 2 * stoi(tmp_tokens[2]))
        throw "ERROR: Bad token num";

    vector<string> inName;
    vector<Value *> inValue;
    for (int i = 3; i + 1 < tmp_tokens.size(); i += 2)
    {
        inName.push_back(tmp_tokens[i]);
        inValue.push_back(new Scalar<float>(stof(tmp_tokens[i + 1])));
    }
    graph.eval(tmp_tokens[1], inName, inValue);
}

void Parser::cmdSetCon()
{
    if (tmp_tokens.size() != 3)
        throw "ERROR: Bad token num";
    graph.noAnsStep(); // graph.step++
    graph.editNode(tmp_tokens[1], stof(tmp_tokens[2]));
}

void Parser::cmdSetAns()
{
    if (tmp_tokens.size() != 3)
        throw "ERROR: Bad token num";
    graph.noAnsStep(); // graph.step++
    int ansIndex = stoi(tmp_tokens[2]) - 1; // counts from 0
    graph.editNode(tmp_tokens[1], graph.getAns(ansIndex));
}