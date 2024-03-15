#include "Expression.h"

namespace Ample::Compiler {
    template<typename T>
    T Assign<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitAssignExpr(this);
    }

    template<typename T>
    T Binary<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitBinaryExpr(this);
    }

    template<typename T>
    T Ternary<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitTernaryExpr(this);
    }

    template<typename T>
    T Call<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitCallExpr(this);
    }

    template<typename T>
    T Get<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitGetExpr(this);
    }

    template<typename T>
    T Grouping<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitGroupingExpr(this);
    }

    template<typename T>
    T Literal<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitLiteralExpr(this);
    }

    template<typename T>
    T Logical<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitLogicalExpr(this);
    }

    template<typename T>
    T Set<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitSetExpr(this);
    }

    template<typename T>
    T Super<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitSuperExpr(this);
    }

    template<typename T>
    T This<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitThisExpr(this);
    }

    template<typename T>
    T Unary<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitUnaryExpr(this);
    }

    template<typename T>
    T Variable<T>::accept(std::shared_ptr<ExpressionVisitor<T> > &visitor) {
        return visitor->visitVariableExpr(this);
    }
}
