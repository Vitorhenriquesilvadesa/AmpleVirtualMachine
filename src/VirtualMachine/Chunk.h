//
// Created by vitor on 16/03/24.
//

#ifndef CHUNK_H
#define CHUNK_H
#include <cstdint>
#include <utility>
#include <vector>


namespace Ample::VM {
    struct Chunk {
        explicit Chunk(std::vector<uint8_t> program) : program(std::move(program)) {
        }

        std::vector<uint8_t> program;
    };
} // Ample::VM


#endif //CHUNK_H
