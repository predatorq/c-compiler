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
        if(data=="T_IntConstant"||data=="T_Identifier")
            output.push_back(data+tmp);
        else
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
    assert(data1 == "GRAMMAR_FOR_EXPERIMENT3");
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
    int t = 0;
    bool flag = true;
    vector<string> tokens = read_from_tokens(argv[1]);
    // pair<string,string> 对应预测分析表的行、列, vector<string> 为空格中的字符
    map<pair<string, string>, vector<string> > table = read_from_grammar(argv[2]);
    stack<string> syn;
    stack<string> input;
    stack<string> sem;
    sem.empty();
    syn.empty();
    input.empty();
    // init syn
    syn.push("#");
    syn.push("E");
    // init input
    input.push("#");
    for (int i = 0; i < tokens.size(); i++)
    {
        input.push(tokens[tokens.size() - i - 1]);
    }
    string match;
    cout << endl;
    cout << "ACTIONS" << endl;
    cout << "---------------------"<< endl;
    while (input.size() > 0)
    {
        string remain = input.top();
        input.pop();
        string parse = syn.top();
        syn.pop();

        if (remain == parse)
        {
            cout << "Match" << "  "<< remain << endl;
            match = remain.c_str();
            continue;
        }
        if (remain.substr(0,13)=="T_IntConstant"&&parse=="T_IntConstant"){
            cout << "Match" << "  "<< remain << endl;
            match = remain.c_str();
            continue;
        }
        if (remain.substr(0,12)=="T_Identifier"&&parse=="T_Identifier"){
            cout << "Match" << "  "<< remain << endl;
            match = remain.c_str();
            continue;
        }
        input.push(remain);

        if (parse.substr(0,5)=="Push:"){
            cout << parse << endl;
            sem.push(match);
            continue;
        }
        if (parse.substr(0,4)=="GEQ:"){
            string tmp1 = sem.top();
            sem.pop();
            string tmp2 = sem.top();
            sem.pop();
            string tmp3 = "t"+to_string(t);
            // cout << "tmp1" << tmp1 << endl;
            // cout << "tmp2" << tmp2 << endl;
            cout << "RPN: "<< parse.substr(4,1) << " "<< tmp1 << " "<<tmp2<< " "<<tmp3 << endl;
            t++;
            sem.push(tmp3);
            continue;
        }
        if(remain.substr(0,13)=="T_IntConstant"){
            remain = "T_IntConstant";
        }else if(remain.substr(0,12)=="T_Identifier"){
            remain = "T_Identifier";
        }
        pair<string, string> tmp(parse,remain);

        if (table.find(tmp) == table.end())
        {
            flag = false;
            cout << "Meet error!" << endl;
            break;
        }
        else
        {
            vector<string> tmp2 = table[tmp];
            if(tmp2.size()==1&&tmp2[0]=="e"){
                cout << parse << " -> " << "e"<<endl;
                continue;
            }
            for (int i = 0; i < tmp2.size(); i++)
            {
                syn.push(tmp2[tmp2.size() - i - 1]);
            }
            cout << parse << " -> ";
            for(string i: tmp2){
                cout << i << " ";
            }
            cout << endl;
            continue;

        }
    }
    if(flag){
        cout << "success" << endl;
    }

    return 0;
}