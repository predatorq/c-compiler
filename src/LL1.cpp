#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <stack>
using namespace std;

vector<string> read_from_tokens(char *filename)
{
    ifstream infile;
    string data, tmp;
    vector<string> output;
    output.clear();
    infile.open(filename);
    cout << "Reading from the token file" << endl;
    infile >> data;
    assert(data == "TOKEN-TYPE");
    infile >> data;
    assert(data == "TOKEN-VALUE");
    infile >> data;
    assert(data == "-------------------------------------------------");
    while (infile >> data)
    {
        infile >> tmp;
        output.push_back(data);
    }
    cout << "read tokens succeed!" << endl;
    infile.close();
    return output;
}

map<pair<string, string>, vector<string> > read_from_grammar(char *filename)
{
    ifstream infile;
    string data1, data2, data3;
    pair<string, string> tmp;
    map<pair<string, string>, vector<string> > output;
    output.clear();
    infile.open(filename);
    cout << "Reading from the grammar file" << endl;
    infile >> data1;
    assert(data1 == "GRAMMAR_FOR_EXPERIMENT2");
    infile >> data1;
    assert(data1 == "-------------------------------------------------");
    while (infile >> data1)
    {
        if (data1 == "@")
            break;
        infile >> data2;
        pair<string, string> tmp(data1, data2);
        vector<string> tmp2;
        tmp2.empty();
        while (infile >> data3)
        {
            if (data3 == "@")
                break;
            tmp2.push_back(data3);
            // cout << data3 << endl;
        }
        output[tmp] = tmp2;
    }
    cout << "read grammars succeed!" << endl;
    infile.close();
    return output;
}

int main(int argc, char **argv)
{
    // true表示表达式正确, false为错误
    bool flag = true;
    vector<string> tokens = read_from_tokens(argv[1]);
    // pair<string,string> 对应预测分析表的行、列, vector<string> 为空格中的字符
    map<pair<string, string>, vector<string> > table = read_from_grammar(argv[2]);
    stack<string> parse_stack;
    stack<string> remaining_input;
    parse_stack.empty();
    remaining_input.empty();
    // init parse_stack
    parse_stack.push("$");
    parse_stack.push("E");
    // init remaining_input
    remaining_input.push("$");
    for (int i = 0; i < tokens.size(); i++)
    {
        remaining_input.push(tokens[tokens.size() - i - 1]);
    }

    while (remaining_input.size() > 0)
    {
        string remain = remaining_input.top();
        remaining_input.pop();
        string parse = parse_stack.top();
        parse_stack.pop();
        // cout << parse << "   "<< remain << endl;
        pair<string, string> tmp(parse,remain);
        if (remain == parse)
        {
            cout << "Match" << "  "<<remain << endl;
            continue;
        }
        remaining_input.push(remain);
        if (table.find(tmp) == table.end())
        {
            flag = false;
            cout << "Meet error!" << endl;
            break;
        }
        else
        {
            vector<string> tmp2 = table[tmp];
            if(tmp2.size()==1&&tmp2[0]=="e")continue;
            for (int i = 0; i < tmp2.size(); i++)
            {
                parse_stack.push(tmp2[tmp2.size() - i - 1]);
            }
            cout << parse << "->";
            for(string i: tmp2){
                cout << i;
            }
            cout << endl;

        }
    }

    return 0;
}