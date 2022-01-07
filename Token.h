//
// Created by Woo Jin Seo on 2022/01/02.
//

#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H
#include <string>

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
    std::string value;
    TokenType tokenType;
    int lastIdx;
public:
    //default constructor()
    Token() = default;

    //constructor ()
    Token(const std::string & value, TokenType tokenType, int lastIdx)
    : value(value), tokenType(tokenType), lastIdx(lastIdx) {

    }

    // copy constructor
    Token(Token const& token) = default;

    const std::string & getValue() const {
        return value;
    }

    TokenType getTokenType() const {
        return tokenType;
    }

    int getLastIdx() const {
        return lastIdx;
    }

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

#endif //CALCULATOR_TOKEN_H
