#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Token.h"

namespace Ample::Compiler {


    static std::unordered_map<std::string, TokenType> keyWords = {
        {"and", TokenType::And},
        {"class", TokenType::Class},
        {"else", TokenType::Else},
        {"false", TokenType::False},
        {"for", TokenType::For},
        {"break", TokenType::Break},
        {"continue", TokenType::Continue},
        {"function", TokenType::Def},
        {"if", TokenType::If},
        {"null", TokenType::AmpleNull},
        {"or", TokenType::Or},
        {"print", TokenType::Print},
        {"return", TokenType::Return},
        {"super", TokenType::Super},
        {"this", TokenType::This},
        {"true", TokenType::True},
        {"var", TokenType::Var},
        {"while", TokenType::While},
        {"namespace", TokenType::Namespace},
    };

    class Lexer {
    public:
        explicit Lexer(std::string &sourceCode) : sourceCode(sourceCode) {
        }

        std::vector<Token> scanTokens();

    private:
        std::string &sourceCode;
        std::vector<Token> tokens;
        int start = 0;
        int current = 0;
        int line = 1;

        void scanToken();

        [[nodiscard]] bool isAtEnd() const;

        void string();

        void number();

        void identifier();

        static bool isAlpha(char c);

        static bool isDigit(char c);

        static bool isAlphaNumeric(char c);

        void comment();

        char advance();

        void makeToken(TokenType type, void *literal);

        void makeToken(TokenType type, std::string &lexeme);

        void makeToken(TokenType type);

        [[nodiscard]] char peek() const;

        [[nodiscard]] char peekNext() const;

        bool match(char expected);
    };
}

#endif //LEXER_H
