#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

#include "BaseType.h"


namespace Ample::Compiler {
    enum class TokenType {
        LeftParen, RightParen, LeftBrace, RightBrace, LeftBracket, RightBracket, Question, DoubleQuestion,
        Comma, Dot, Minus, Plus, Colon, DoubleColon, Semicolon, Slash, Star,

        // One or two character tokens.
        Bang, BangEqual,
        Equal, EqualEqual,
        Greater, GreaterEqual,
        Less, LessEqual,

        // Literals.
        Identifier, String, Int, Float,

        // Keywords.
        And, Class, Else, False, Def, For, If, AmpleNull, Or, Break, Continue,
        Return, Super, This, True, Var, While, Namespace, Abstract,
        EndOfFile, Print
    };

    static const std::unordered_map<TokenType, std::string> tokenStringMap = {
        {TokenType::LeftParen, "LeftParen"},
        {TokenType::RightParen, "RightParen"},
        {TokenType::LeftBrace, "LeftBrace"},
        {TokenType::RightBrace, "RightBrace"},
        {TokenType::LeftBracket, "LeftBracket"},
        {TokenType::RightBracket, "RightBracket"},
        {TokenType::Question, "Question"},
        {TokenType::DoubleQuestion, "DoubleQuestion"},
        {TokenType::Comma, "Comma"},
        {TokenType::Dot, "Dot"},
        {TokenType::Minus, "Minus"},
        {TokenType::Plus, "Plus"},
        {TokenType::Colon, "Colon"},
        {TokenType::DoubleColon, "DoubleColon"},
        {TokenType::Semicolon, "Semicolon"},
        {TokenType::Slash, "Slash"},
        {TokenType::Star, "Star"},
        {TokenType::Bang, "Bang"},
        {TokenType::BangEqual, "BangEqual"},
        {TokenType::Equal, "Equal"},
        {TokenType::EqualEqual, "EqualEqual"},
        {TokenType::Greater, "Greater"},
        {TokenType::GreaterEqual, "GreaterEqual"},
        {TokenType::Less, "Less"},
        {TokenType::LessEqual, "LessEqual"},
        {TokenType::Identifier, "Identifier"},
        {TokenType::String, "String"},
        {TokenType::Int, "Int"},
        {TokenType::Float, "Float"},
        {TokenType::And, "And"},
        {TokenType::Class, "Class"},
        {TokenType::Else, "Else"},
        {TokenType::False, "False"},
        {TokenType::Def, "Def"},
        {TokenType::For, "For"},
        {TokenType::If, "If"},
        {TokenType::AmpleNull, "AmpleNull"},
        {TokenType::Or, "Or"},
        {TokenType::Break, "Break"},
        {TokenType::Continue, "Continue"},
        {TokenType::Return, "Return"},
        {TokenType::Super, "Super"},
        {TokenType::This, "This"},
        {TokenType::True, "True"},
        {TokenType::Var, "Var"},
        {TokenType::While, "While"},
        {TokenType::Namespace, "Namespace"},
        {TokenType::Abstract, "Abstract"},
        {TokenType::EndOfFile, "EndOfFile"}
    };

    static std::string TokenTypeToString(const TokenType type) {
        return tokenStringMap.at(type);
    }


    struct Token final : AmpleBaseType {
        Token(const TokenType type, const std::string &lexeme, const void *literal, const unsigned int line)
            : type(type),
              lexeme(lexeme),
              literal(literal),
              line(line) {
        }

        const TokenType type;
        const std::string &lexeme;
        const void *literal;
        const unsigned int line;

        [[nodiscard]] std::string ToString() const override {
            return "Token { " + TokenTypeToString(type) + ", '" + lexeme + "', " +
                   std::to_string(reinterpret_cast<uintptr_t>(literal)) + " }";
        }

        ~Token() override = default;
    };
}
#endif //TOKEN_H
