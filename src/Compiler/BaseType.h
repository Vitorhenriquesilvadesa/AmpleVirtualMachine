#ifndef BASETYPE_H
#define BASETYPE_H
#include <string>

struct AmpleBaseType {
    virtual ~AmpleBaseType() = default;

    [[nodiscard]] virtual std::string ToString() const {
        return "";
    }
};

// ReSharper disable once CppClassCanBeFinal
class Object : AmpleBaseType {

};

#endif //BASETYPE_H
