#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

enum class TokenType {
    DIGITS,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    OPEN_PARENTHESES,
    CLOSE_PARENTHESES,
    ERROR
};

// 123, DIGITS
class Token {
public:
    // constructor()
    Token() = default;

    // copy constructor
    Token(Token const& token) = default;

    string value;
    TokenType tokenType;
    int lastIdx;

    int precedence() {
        if (this->tokenType == TokenType::PLUS || this->tokenType == TokenType::MINUS) {
            return 1;
        } else if (this->tokenType == TokenType::MULTIPLY || this->tokenType == TokenType::DIVIDE) {
            return 2;
        } else
        {
            return 0;
        }
    }

    bool isOperator() {
        if (this->tokenType == TokenType::PLUS
            || this->tokenType == TokenType::MINUS
            || this->tokenType == TokenType::MULTIPLY
            || this->tokenType == TokenType::DIVIDE) {
            return true;
        } else {
            return false;
        }
    }
};


Token detectDigit(string input, int startIdx) {
    if (isdigit(input[startIdx]) == false) {
        Token token;
        token.tokenType = TokenType::ERROR;
        token.lastIdx = input.size();
        return token;
    }

    string digits;
    int i = startIdx;
    for (; i < input.length(); i++) {
        if (isdigit(input[i])) {
            digits += input[i];
        } else {
            break;
        }
    }
    Token token;
    token.value = digits;
    token.tokenType = TokenType::DIGITS;
    token.lastIdx = i;
    return token;
}

Token detectPlus(string input, int startIdx) {
    if (input[startIdx] != '+') {
        Token token;
        token.tokenType = TokenType::ERROR;
        token.lastIdx = input.size();
        return token;
    }
    Token token;
    token.value = "+";
    token.tokenType = TokenType::PLUS;
    token.lastIdx = startIdx + 1;
    return token;
}

Token detectMinus(string input, int startIdx) {
    if (input[startIdx] != '-') {
        Token token;
        token.tokenType = TokenType::ERROR;
        token.lastIdx = input.size();
        return token;
    }
    Token token;
    token.value = "-";
    token.tokenType = TokenType::MINUS;
    token.lastIdx = startIdx + 1;
    return token;
}

Token detectMultiply(string input, int startIdx) {
    if (input[startIdx] != '*') {
        Token token;
        token.tokenType = TokenType::ERROR;
        token.lastIdx = input.size();
        return token;
    }
    Token token;
    token.value = "*";
    token.tokenType = TokenType::MULTIPLY;
    token.lastIdx = startIdx + 1;
    return token;
}

Token detectDivide(string input, int startIdx) {
    if (input[startIdx] != '/') {
        Token token;
        token.tokenType = TokenType::ERROR;
        token.lastIdx = input.size();
        return token;
    }
    Token token;
    token.value = "/";
    token.tokenType = TokenType::DIVIDE;
    token.lastIdx = startIdx + 1;
    return token;
}

Token detectOpen(string input, int startIdx) {
    if (input[startIdx] != '(') {
        Token token;
        token.tokenType = TokenType::ERROR;
        token.lastIdx = input.size();
        return token;
    }
    Token token;
    token.value = "(";
    token.tokenType = TokenType::OPEN_PARENTHESES;
    token.lastIdx = startIdx + 1;
    return token;
}

Token detectClose(string input, int startIdx) {
    if (input[startIdx] != ')') {
        Token token;
        token.tokenType = TokenType::ERROR;
        token.lastIdx = input.size();
        return token;
    }
    Token token;
    token.value = ")";
    token.tokenType = TokenType::CLOSE_PARENTHESES;
    token.lastIdx = startIdx + 1;
    return token;
}

vector<Token> tokenizer(string input) {

    vector<Token> tokenList;
    for (int i = 0; i < input.length();) {
        if (isdigit(input[i])) {
            Token token = detectDigit(input, i);
            i = token.lastIdx;
            tokenList.push_back(token);
        } else if (input[i] == '+') {
            Token token = detectPlus(input, i);
            i = token.lastIdx;
            tokenList.push_back(token);
        } else if (input[i] == '-') {
            Token token = detectMinus(input, i);
            i = token.lastIdx;
            tokenList.push_back(token);
        } else if (input[i] == '*') {
            Token token = detectMultiply(input, i);
            i = token.lastIdx;
            tokenList.push_back(token);
        } else if (input[i] == '/') {
            Token token = detectDivide(input, i);
            i = token.lastIdx;
            tokenList.push_back(token);
        } else if (input[i] == '(') {
            Token token = detectOpen(input, i);
            i = token.lastIdx;
            tokenList.push_back(token);
        } else if (input[i] == ')') {
            Token token = detectClose(input, i);
            i = token.lastIdx;
            tokenList.push_back(token);
        } else {
            i++;
        }
    }
    return tokenList;
}
//Shift F6 Replace all names at once

vector<Token> infixToPostfix(vector<Token> infix) {
    stack<Token> st;
    vector<Token> postfix;
    for (int i = 0; i < infix.size(); i++) {
        Token token = infix[i];
        if (token.tokenType == TokenType::DIGITS) {
            postfix.push_back(token);
        } else if (token.tokenType == TokenType::OPEN_PARENTHESES) {
            st.push(token);
        } else if (token.tokenType == TokenType::CLOSE_PARENTHESES) {
            while(!st.empty()) {
                Token top = st.top();
                if(top.tokenType != TokenType::OPEN_PARENTHESES) {
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

void printToken(vector<Token> tokenList) {
    for (int i = 0; i < tokenList.size(); ++i) {
        Token token = tokenList[i];
        cout << token.value << ", " << (int) token.tokenType << "\n";
    }
}

float calculatePostfix(vector<Token>postfix) {
    stack<Token> st;
    float answer;
    for (int i = 0; i < postfix.size(); i++) {
        Token token = postfix[i];
        if (token.tokenType == TokenType::DIGITS) {
            st.push(token);
        } else {
            float value1;
            float value2;
            Token top = st.top();
            value1 = stof(top.value);
            st.pop();
            top = st.top();
            value2 = stof(top.value);
            st.pop();
            if (token.tokenType == TokenType::PLUS) {
                float value3;
                value3 = value1 + value2;
                string result = to_string(value3);
                Token convert;
                convert.value = result;
                convert.tokenType = TokenType::DIGITS;
                st.push(convert);
            } else if (token.tokenType == TokenType::MINUS) {
                float value3;
                value3 = value2 - value1;
                string result = to_string(value3);
                Token convert;
                convert.value = result;
                convert.tokenType = TokenType::DIGITS;
                st.push(convert);
            } else if (token.tokenType == TokenType::DIVIDE) {
                float value3;
                value3 = value2 / value1;
                string result = to_string(value3);
                Token convert;
                convert.value = result;
                convert.tokenType = TokenType::DIGITS;
                st.push(convert);
            } else if (token.tokenType == TokenType::MULTIPLY) {
                float value3;
                value3 = value1 * value2;
                string result = to_string(value3);
                Token convert;
                convert.value = result;
                convert.tokenType = TokenType::DIGITS;
                st.push(convert);
            }
        }
    }
    Token top = st.top();
    answer = stof(top.value);
    return answer;
}

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

//