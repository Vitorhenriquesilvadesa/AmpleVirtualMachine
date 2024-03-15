#ifndef PARSER_H
#define PARSER_H

#pragma once

#include "Lexer.h"

#include <memory>
#include <utility>

namespace Ample::Compiler {
    template<typename T>
    class ExpressionVisitor;

    template<typename T>
    class Expr {
    public:
        virtual ~Expr() = default;

        virtual T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) = 0;
    };

    template<typename T>
    class Assign final : Expr<T> {
    public:
        Assign(const Token &name, std::shared_ptr<Expr<T> > value)
            : name(name), value(std::move(value)) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const Token name;
        const std::shared_ptr<Expr<T> > value;
    };

    template<typename T>
    class Binary final : Expr<T> {
    public:
        Binary(std::shared_ptr<Expr<T> > left, const Token &oper, std::shared_ptr<Expr<T> > right)
            : left(std::move(left)), oper(oper), right(std::move(right)) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const std::shared_ptr<Expr<T> > left;
        const Token oper;
        const std::shared_ptr<Expr<T> > right;
    };

    template<typename T>
    class Ternary final : Expr<T> {
    public:
        Ternary(const std::shared_ptr<Expr<T> > &condition, const std::shared_ptr<Expr<T> > &left,
                const std::shared_ptr<Expr<T> > &right)
            : condition(condition),
              left(left),
              right(right) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const std::shared_ptr<Expr<T> > condition;
        const std::shared_ptr<Expr<T> > left;
        const std::shared_ptr<Expr<T> > right;
    };

    template<typename T>
    class Call final : Expr<T> {
    public:
        Call(const std::shared_ptr<Expr<T> > &callee, const Token &paren,
             const std::vector<std::shared_ptr<Expr<T> > > &arguments)
            : callee(callee),
              paren(paren),
              arguments(arguments) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const std::shared_ptr<Expr<T> > callee;
        const Token paren;
        const std::vector<std::shared_ptr<Expr<T> > > arguments;
    };

    template<typename T>
    class Get final : Expr<T> {
    public:
        Get(const std::shared_ptr<Expr<T> > &object, const Token &name)
            : object(object),
              name(name) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const std::shared_ptr<Expr<T> > object;
        const Token name;
    };

    template<typename T>
    class Grouping final : Expr<T> {
    public:
        explicit Grouping(const std::shared_ptr<Expr<T> > &expression)
            : expression(expression) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const std::shared_ptr<Expr<T> > expression;
    };

    template<typename T>
    class Literal final : Expr<T> {
    public:
        explicit Literal(const AmpleBaseType &value)
            : value(value) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const AmpleBaseType value;
    };

    template<typename T>
    class Logical final : Expr<T> {
    public:
        Logical(const std::shared_ptr<Expr<T> > &left, const Token &logical_operator,
                const std::shared_ptr<Expr<T> > &right)
            : left(left),
              logicalOperator(logical_operator),
              right(right) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const std::shared_ptr<Expr<T> > left;
        const Token logicalOperator;
        const std::shared_ptr<Expr<T> > right;
    };

    template<typename T>
    class Set final : Expr<T> {
    public:
        Set(const std::shared_ptr<Expr<T> > &object, const Token &name, const std::shared_ptr<Expr<T> > &value)
            : object(object),
              name(name),
              value(value) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const std::shared_ptr<Expr<T> > object;
        const Token name;
        const std::shared_ptr<Expr<T> > value;
    };

    template<typename T>
    class Super final : Expr<T> {
    public:
        Super(const Token &key_word, const Token &method)
            : keyWord(key_word),
              method(method) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const Token keyWord;
        const Token method;
    };

    template<typename T>
    class This final : Expr<T> {
    public:
        explicit This(const Token &key_word)
            : keyWord(key_word) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const Token keyWord;
    };

    template<typename T>
    class Unary final : Expr<T> {
    public:
        Unary(const Token &unary_operator, const std::shared_ptr<Expr<T> > &right)
            : unaryOperator(unary_operator),
              right(right) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const Token unaryOperator;
        const std::shared_ptr<Expr<T> > right;
    };

    template<typename T>
    class Variable final : Expr<T> {
    public:
        explicit Variable(const Token &name)
            : name(name) {
        }

        T accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) override;

        const Token name;
    };


    template<typename T>
    class ExpressionVisitor {
    public:
        virtual ~ExpressionVisitor() = default;

        virtual T visitAssignExpr(Ample::Compiler::Assign<T> &expr) = 0;

        virtual T visitBinaryExpr(Binary<T> &expr) = 0;

        virtual T visitTernaryExpr(Ternary<T> &expr) = 0;

        virtual T visitCallExpr(Call<T> &expr) = 0;

        virtual T visitGetExpr(Get<T> &expr) = 0;

        virtual T visitGroupingExpr(Grouping<T> &expr) = 0;

        virtual T visitLiteralExpr(Literal<T> &expr) = 0;

        virtual T visitLogicalExpr(Logical<T> &expr) = 0;

        virtual T visitSetExpr(Set<T> &expr) = 0;

        virtual T visitSuperExpr(Super<T> &expr) = 0;

        virtual T visitThisExpr(This<T> &expr) = 0;

        virtual T visitUnaryExpr(Unary<T> &expr) = 0;

        virtual T visitVariableExpr(Variable<T> &expr) = 0;
    };
}

#endif //PARSER_H
