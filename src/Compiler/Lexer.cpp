#include "Lexer.h"
#include "../Error.h"


std::vector<Ample::Compiler::Token> Ample::Compiler::Lexer::scanTokens() {
    std::cout << "Scanning file." << std::endl;
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.emplace_back(TokenType::EndOfFile, "", nullptr, line);
    return tokens;
}

void Ample::Compiler::Lexer::scanToken() {
    switch (const char c = advance()) {
        case '(':
            makeToken(TokenType::LeftParen);
            break;
        case ')':
            makeToken(TokenType::RightParen);
            break;
        case '{':
            makeToken(TokenType::LeftBrace);
            break;
        case '}':
            makeToken(TokenType::RightBrace);
            break;
        case '[':
            makeToken(TokenType::LeftBracket);
            break;
        case ']':
            makeToken(TokenType::RightBracket);
            break;
        case ',':
            makeToken(TokenType::Comma);
            break;
        case '.':
            makeToken(TokenType::Dot);
            break;
        case '-':
            makeToken(TokenType::Minus);
            break;
        case '+':
            makeToken(TokenType::Plus);
            break;
        case ';':
            makeToken(TokenType::Semicolon);
            break;
        case '*':
            makeToken(TokenType::Star);
            break;
        case '!':
            makeToken(match('=') ? TokenType::BangEqual : TokenType::Bang);
            break;
        case '=':
            makeToken(match('=') ? TokenType::EqualEqual : TokenType::Equal);
            break;
        case '<':
            makeToken(match('=') ? TokenType::LessEqual : TokenType::Less);
            break;
        case '>':
            makeToken(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
            break;

        case ':':
            makeToken(match(':') ? TokenType::DoubleColon : TokenType::Colon);
            break;

        case '?':
            makeToken(match('?') ? TokenType::DoubleQuestion : TokenType::Question);
            break;

        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                makeToken(TokenType::Slash);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        case '"':
            string();
            break;

        case 'o':
            if (match('r')) {
                makeToken(TokenType::Or);
            }
            break;

        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                ERROR("Unexpected character at line " + line);
            }
            break;
    }
}

bool Ample::Compiler::Lexer::isAtEnd() const {
    return current >= sourceCode.length();
}

void Ample::Compiler::Lexer::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        ERROR("Unterminated string.");
    }

    advance();

    std::string value = sourceCode.substr(start + 1, current - start - 1);
    makeToken(TokenType::String, value);
}

void Ample::Compiler::Lexer::number() {
    bool isFloat = false;

    while (!isAtEnd() && (isDigit(peek()) || peek() == '.')) {
        if (peek() == '.') {
            if (isFloat) {
                ERROR("Error to parse number at line " + (line - 1));
            }
            isFloat = true;
        }

        advance();

        if (isFloat && peek() == '.') {
            ERROR("Error to parse number at line " + (line - 1));
        }
    }

    std::string number = sourceCode.substr(start, current - start);

    if (isFloat) {
        makeToken(TokenType::Float, number);
    } else {
        makeToken(TokenType::Int, number);
    }
}

void Ample::Compiler::Lexer::identifier() {
    while (isAlphaNumeric(peek())) advance();
    const std::string text = sourceCode.substr(start, current - start);
    TokenType type;

    try {
        type = keyWords.at(text);
    } catch ([[maybe_unused]] std::out_of_range &e) {
        type = TokenType::Identifier;
    }

    makeToken(type);
}

bool Ample::Compiler::Lexer::isAlpha(const char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Ample::Compiler::Lexer::isDigit(const char c) {
    return c >= '0' && c <= '9';
}

bool Ample::Compiler::Lexer::isAlphaNumeric(const char c) {
    return isAlpha(c) || isDigit(c);
}

void Ample::Compiler::Lexer::comment() {
    while (peek() != '\n' && !isAtEnd()) advance();
}

char Ample::Compiler::Lexer::advance() {
    return sourceCode[current++];
}

void Ample::Compiler::Lexer::makeToken(TokenType type, void *literal) {
    std::string text = sourceCode.substr(start, current - start);
    this->tokens.emplace_back(type, text, literal, line);
}

void Ample::Compiler::Lexer::makeToken(TokenType type, std::string &lexeme) {
    this->tokens.emplace_back(type, lexeme, nullptr, line);
}

void Ample::Compiler::Lexer::makeToken(const TokenType type) {
    makeToken(type, nullptr);
}

char Ample::Compiler::Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return sourceCode[current];
}

char Ample::Compiler::Lexer::peekNext() const {
    if (current + 1 >= sourceCode.length()) return '\0';
    return sourceCode[current + 1];
}

bool Ample::Compiler::Lexer::match(const char expected) {
    if (isAtEnd()) return false;
    if (sourceCode[current] != expected) return false;
    current++;
    return true;
}
