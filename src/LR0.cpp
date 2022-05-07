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

map<pair<string, string>, string > read_from_goto(char *filename)
{
    ifstream infile;
    string data1, data2, data3;
    map<pair<string, string>, string> output;
    output.clear();
    infile.open(filename);
    cout << "Reading from the goto file" << endl;
    infile >> data1;
    assert(data1 == "GOTO");
    infile >> data1;
    assert(data1 == "-------------------------------------------------");
    while (infile >> data1)
    {
        if (data1 == "@")
            break;
        infile >> data2;
        pair<string, string> tmp(data1, data2);
        infile >> data3;
        output[tmp] = data3;
    }
    cout << "read goto succeed!" << endl;
    infile.close();
    return output;
}

map<pair<string, string>, string > read_from_shift(char *filename)
{
    ifstream infile;
    string data1, data2, data3;
    map<pair<string, string>, string> output;
    output.clear();
    infile.open(filename);
    cout << "Reading from the shift file" << endl;
    infile >> data1;
    assert(data1 == "SHIFT");
    infile >> data1;
    assert(data1 == "-------------------------------------------------");
    while (infile >> data1)
    {
        if (data1 == "@")
            break;
        infile >> data2;
        pair<string, string> tmp(data1, data2);
        infile >> data3;
        output[tmp] = data3;
    }
    cout << "read shift succeed!" << endl;
    infile.close();
    return output;
}

map<string, pair<int, string> > read_from_reduce(char *filename)
{
    ifstream infile;
    string data1, data3;
    int data2;
    map<string, pair<int, string> > output;
    output.clear();
    infile.open(filename);
    cout << "Reading from the reduce file" << endl;
    infile >> data1;
    assert(data1 == "REDUCE");
    infile >> data1;
    assert(data1 == "-------------------------------------------------");
    while (infile >> data1)
    {
        if (data1 == "@")
            break;
        infile >> data2;
        infile >> data3;
        pair<int, string> tmp(data2, data3);
        output[data1] = tmp;
    }
    cout << "read reduce succeed!" << endl;
    infile.close();
    return output;
}

int main(int argc, char **argv)
{
    // true表示表达式正确, false为错误
    bool flag = true;
    vector<string> tokens = read_from_tokens(argv[1]);
    // pair<string,string> 对应动作表的行、列, vector<string> 为空格中的字符
    map<pair<string, string>, string > gotos = read_from_goto(argv[2]);
    map<pair<string, string>, string > shifts = read_from_shift(argv[3]);
    map<string, pair<int, string> > reduces = read_from_reduce(argv[4]);
    stack<string> state_stack;
    stack<string> remaining_input;
    state_stack.empty();
    remaining_input.empty();
    // init state_stack
    state_stack.push("0");
    // init remaining_input
    remaining_input.push("$");
    remaining_input.push("$");
    for (int i = 0; i < tokens.size(); i++)
    {
        remaining_input.push(tokens[tokens.size() - i - 1]);
    }
    while(!remaining_input.empty()){
        string tmp1 = state_stack.top();
        string tmp2 = remaining_input.top();
        pair<string, string> tmp(tmp1,tmp2);
        // shift
        if(shifts.find(tmp)!=shifts.end()){
            if(shifts[tmp]=="accept"){
                cout << "ACCEPT" << endl;
                break;
            }
            state_stack.push(shifts[tmp]);
            cout << "shift " << shifts[tmp] << endl;
            remaining_input.pop();
            continue;
        }
        if(gotos.find(tmp)!=gotos.end()){
            state_stack.push(gotos[tmp]);
            cout << "goto " << gotos[tmp] << endl;
            remaining_input.pop();
            continue;
        }
        if(reduces.find(tmp1)!=reduces.end()){
            int count_down = reduces[tmp1].first;
            while(count_down--){
                state_stack.pop();
            }
            remaining_input.push(reduces[tmp1].second);
            cout << "reduce " << reduces[tmp1].first << endl;
            continue;
        }
        cout << "meet error" << endl;
        break;
    }
    return 0;
}