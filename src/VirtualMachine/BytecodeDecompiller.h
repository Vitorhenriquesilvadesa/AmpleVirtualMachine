#ifndef BYTECODEDECOMPILLER_H
#define BYTECODEDECOMPILLER_H
#include <cstdint>

namespace Ample::VM {
    class BytecodeDecompiller {
    public:
        explicit BytecodeDecompiller(): bytecodeVersion(0) {
        }

        static void disassemblyInstruction(uint8_t instruction) ;
        static void disassemblyInstruction(uint8_t instruction, const uint8_t* arg, uint8_t argSize) ;

    private:
        int bytecodeVersion;
    };
} // Ample::VM

#endif //BYTECODEDECOMPILLER_H
