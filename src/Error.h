#ifndef ERROR_H
#define ERROR_H

#include <iostream>

#define ERROR(x) std::cerr << x << std::endl; \
    exit(EXIT_FAILURE);

#endif //ERROR_H
