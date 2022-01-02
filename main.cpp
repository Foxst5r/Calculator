#include <iostream>
#include <vector>
#include "Token.h"
#include "Calculator.h"
using namespace std;

int main() {
    string input = "";
    cout << "Enter: ";
    getline(cin, input);
    vector<Token> tokenList = tokenizer(input);
    vector<Token> postfix = infixToPostfix(tokenList);
    printToken(tokenList);
    cout << "\n";
    printToken(postfix);
    float calc = calculatePostfix(postfix);
    cout << "\n";
    cout << calc;

}

//Command A- select all
//Command + Shift + a == open action finder
//E.g format entire code at once

//git status
//git add .
//git commit -m "msg"
//git push origin master