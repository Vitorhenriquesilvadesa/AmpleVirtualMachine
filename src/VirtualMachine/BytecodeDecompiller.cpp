#include "BytecodeDecompiller.h"

#include <iostream>
#include <cstring>

#include "OpCode.h"

using enum Ample::VM::OpCode;

void Ample::VM::BytecodeDecompiller::disassemblyInstruction(const uint8_t instruction) {
    switch (instruction) {
        case RETURN:
            std::cout << "RETURN" << std::endl;
            return;
        case PUSH_CONST:
            std::cout << "PUSH_CONST" << std::endl;
            break;
        case LOAD_CONST:
            std::cout << "LOAD_CONST" << std::endl;
        case ADD:
            std::cout << "ADD" << std::endl;
            break;
        case ADD_F:
            std::cout << "ADD_F" << std::endl;
            break;
        case SUB:
            std::cout << "SUB" << std::endl;
            break;
        case SUB_F:
            std::cout << "SUB_F" << std::endl;
            break;
        case MUL:
            std::cout << "MUL" << std::endl;
            break;
        case MUL_F:
            std::cout << "MUL_F" << std::endl;
            break;
        case DIV:
            std::cout << "DIV" << std::endl;
            break;
        case DIV_F:
            std::cout << "DIV_F" << std::endl;
            break;
        case CAST_TO_I:
            std::cout << "CAST_TO_I" << std::endl;
            break;
        case CAST_TO_F:
            std::cout << "CAST_TO_F" << std::endl;
            break;
        case MOV:
            std::cout << "MOV" << std::endl;
            break;
        case MOV_F:
            std::cout << "MOV_F" << std::endl;
            break;
        case PUSH:
            std::cout << "PUSH" << std::endl;
            break;
        case PUSH_F:
            std::cout << "PUSH_F" << std::endl;
            break;
        case READ:
            std::cout << "READ" << std::endl;
            break;
        case PRINT:
            std::cout << "PRINT" << std::endl;
            break;
        default: break;
    }
}


void Ample::VM::BytecodeDecompiller::disassemblyInstruction(const uint8_t instruction, const uint8_t *arg,
                                                            const uint8_t argSize) {
    switch (instruction) {
        case PUSH_CONST:
            std::cout << "PUSH_CONST" << std::endl;
            break;
        case LOAD_CONST:
            std::cout << "LOAD_CONST" << std::endl;
        case PUSH:
            std::cout << "PUSH" << std::endl;
            break;
        case PUSH_F:
            if (argSize == sizeof(float)) {
                float floatValue;
                std::memcpy(&floatValue, arg, sizeof(float));
                std::cout << "PUSH_F " << floatValue << std::endl;
                break;
            }
        default: break;
    }
}
