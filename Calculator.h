//
// Created by Woo Jin Seo on 2022/01/02.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "Token.h"
Token detectDigit(std::string input, int startIdx) {
    if (isdigit(input[startIdx]) == false) {
        Token token(input,TokenType::ERROR, input.size());
        return token;
    }

    std::string digits;
    int i = startIdx;
    for (; i < input.length(); i++) {
        if (isdigit(input[i])) {
            digits += input[i];
        } else {
            break;
        }
    }
    Token token(digits,TokenType::DIGITS, i);;
    return token;
}

Token detectPlus(std::string input, int startIdx) {
    if (input[startIdx] != '+') {
        Token token(input,TokenType::ERROR, input.size());
        return token;
    }
    Token token("+",TokenType::PLUS, startIdx + 1);
    return token;
}

Token detectMinus(std::string input, int startIdx) {
    if (input[startIdx] != '-') {
        Token token(input,TokenType::ERROR, input.size());
        return token;
    }
    Token token("-",TokenType::MINUS, startIdx + 1);
    return token;
}

Token detectMultiply(std::string input, int startIdx) {
    if (input[startIdx] != '*') {
        Token token(input,TokenType::ERROR, input.size());
        return token;
    }
    Token token("*",TokenType::MULTIPLY, startIdx + 1);
    return token;
}

Token detectDivide(std::string input, int startIdx) {
    if (input[startIdx] != '/') {
        Token token(input,TokenType::ERROR, input.size());
        return token;
    }
    Token token("/",TokenType::DIVIDE, startIdx + 1);
    return token;
}

Token detectOpen(std::string input, int startIdx) {
    if (input[startIdx] != '(') {
        Token token(input,TokenType::ERROR, input.size());
        return token;
    }
    Token token("(",TokenType::OPEN_PARENTHESES, startIdx + 1);;
    return token;
}

Token detectClose(std::string input, int startIdx) {
    if (input[startIdx] != ')') {
        Token token(input,TokenType::ERROR, input.size());
        return token;
    }
    Token token(")",TokenType::CLOSE_PARENTHESES, startIdx + 1);
    return token;
}

std::vector<Token> tokenizer(std::string input) {

    std::vector<Token> tokenList;
    for (int i = 0; i < input.length();) {
        if (isdigit(input[i])) {
            Token token = detectDigit(input, i);
            i = token.getLastIdx();
            tokenList.push_back(token);
        } else if (input[i] == '+') {
            Token token = detectPlus(input, i);
            i = token.getLastIdx();
            tokenList.push_back(token);
        } else if (input[i] == '-') {
            Token token = detectMinus(input, i);
            i = token.getLastIdx();
            tokenList.push_back(token);
        } else if (input[i] == '*') {
            Token token = detectMultiply(input, i);
            i = token.getLastIdx();
            tokenList.push_back(token);
        } else if (input[i] == '/') {
            Token token = detectDivide(input, i);
            i = token.getLastIdx();
            tokenList.push_back(token);
        } else if (input[i] == '(') {
            Token token = detectOpen(input, i);
            i = token.getLastIdx();
            tokenList.push_back(token);
        } else if (input[i] == ')') {
            Token token = detectClose(input, i);
            i = token.getLastIdx();
            tokenList.push_back(token);
        } else {
            i++;
        }
    }
    return tokenList;
}
//Shift F6 Replace all names at once

std::vector<Token> infixToPostfix(std::vector<Token> infix) {
    std::stack<Token> st;
    std::vector<Token> postfix;
    for (int i = 0; i < infix.size(); i++) {
        Token token = infix[i];
        if (token.getTokenType() == TokenType::DIGITS) {
            postfix.push_back(token);
        } else if (token.getTokenType() == TokenType::OPEN_PARENTHESES) {
            st.push(token);
        } else if (token.getTokenType() == TokenType::CLOSE_PARENTHESES) {
            while(!st.empty()) {
                Token top = st.top();
                if(top.getTokenType() != TokenType::OPEN_PARENTHESES) {
                    postfix.push_back(top);
                    st.pop();
                } else {
                    st.pop();
                    break;
                }
            }
        } else {
            while(!st.empty() && token.precedence() <= st.top().precedence()) {
                Token top = st.top();
                postfix.push_back(top);
                st.pop();
            }
            st.push(token);
        }
    }
    while (!st.empty()) {
        Token top = st.top();
        postfix.push_back(top);
        st.pop();
    }
    return postfix;
}

void printToken(std::vector<Token> tokenList) {
    for (int i = 0; i < tokenList.size(); ++i) {
        Token token = tokenList[i];
        std::cout << token.getValue() << ", " << (int) token.getTokenType() << "\n";
    }
}

float calculatePostfix(std::vector<Token>postfix) {
    std::stack<Token> st;
    float answer;
    for (int i = 0; i < postfix.size(); i++) {
        Token token = postfix[i];
        if (token.getTokenType() == TokenType::DIGITS) {
            st.push(token);
        } else {
            float value1;
            float value2;
            Token top = st.top();
            value1 = stof(top.getValue());
            st.pop();
            top = st.top();
            value2 = stof(top.getValue());
            st.pop();
            if (token.getTokenType() == TokenType::PLUS) {
                float value3;
                value3 = value1 + value2;
                std::string result = std::to_string(value3);
                Token convert(result,TokenType::DIGITS,0);
                st.push(convert);
            } else if (token.getTokenType() == TokenType::MINUS) {
                float value3;
                value3 = value2 - value1;
                std::string result = std::to_string(value3);
                Token convert(result,TokenType::DIGITS,0);
                st.push(convert);
            } else if (token.getTokenType() == TokenType::DIVIDE) {
                float value3;
                value3 = value2 / value1;
                std::string result = std::to_string(value3);
                Token convert(result,TokenType::DIGITS,0);
                st.push(convert);
            } else if (token.getTokenType() == TokenType::MULTIPLY) {
                float value3;
                value3 = value1 * value2;
                std::string result = std::to_string(value3);
                Token convert(result,TokenType::DIGITS,0);
                st.push(convert);
            }
        }
    }
    Token top = st.top();
    answer = stof(top.getValue());
    return answer;
}

#endif //CALCULATOR_CALCULATOR_H
