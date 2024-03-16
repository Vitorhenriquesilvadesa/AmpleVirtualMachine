#include "VirtualMachine.h"

#include <iostream>
#include <cstring>
#include <memory>

#include "OpCode.h"
#include "../Error.h"

namespace Ample::VM {
    void VirtualMachine::pushInt(const int operand) {
        if (intSp >= 255) {
            ERROR("Stack overflow error.");
        }

        this->integerStack.push_back(operand);
        intSp++;

        std::cout << "PUSH " << operand << std::endl;
    }

    void VirtualMachine::pushFloat(const float operand) {
        if (floatSp >= 255) {
            ERROR("Stack overflow error.");
        }

        this->floatStack.push_back(operand);
        floatSp++;

        std::cout << "PUSH_F " << operand << std::endl;
    }

    [[nodiscard]] int VirtualMachine::popIntegerOperand() {
        if (intSp <= 0) {
            ERROR("Stack underflow error.");
        }

        const int value = integerStack[integerStack.size() - intSp--];
        std::cout << "POP_F " << value << std::endl;

        return value;
    }

    [[nodiscard]] float VirtualMachine::popFloatOperand() {
        if (floatSp <= 0) {
            ERROR("Stack underflow error.");
        }

        const float value = floatStack[floatStack.size() - floatSp--];
        std::cout << "POP_F " << value << std::endl;

        return value;
    }

    void VirtualMachine::pushConstOperation() {
        switch (peekByte()) {
            case PUSH: {
                const int value = readInt();
                pushInt(value);
                break;
            }
            case PUSH_F: {
                const float value = readFloat();
                pushFloat(value);
                break;
            }
            default:
                ERROR("Invalid constant type");
        }
    }

    void VirtualMachine::pushIntOperation() {
        const int value = readInt();
        pushInt(value);
        std::cout << value << std::endl;
    }

    void VirtualMachine::pushFloatOperation() {
        const float value = readFloat();
        pushFloat(value);
    }

    void VirtualMachine::readOperation() const {
        // TODO Make readOpetation member function
    }

    void VirtualMachine::printOperation() const {
        // TODO Make readOperation member function
    }

    void VirtualMachine::execute() {
        using enum OpCode;


        for (;;) {
            const uint8_t instruction = readByte();

            if (pc == program.data() + static_cast<std::ptrdiff_t>(program.size())) break;

            switch (instruction) {
                case RETURN:
                    returnOperation();
                    return;
                case PUSH_CONST:
                    pushConstOperation();
                    break;
                case LOAD_CONST:
                    break;
                case ADD:
                    addOperation();
                    break;
                case ADD_F:
                    addfOperation();
                    break;
                case SUB:
                    subOperation();
                    break;
                case SUB_F:
                    subfOperation();
                    break;
                case MUL:
                    mulOperation();
                    break;
                case MUL_F:
                    BytecodeDecompiller::disassemblyInstruction(MUL_F);
                    mulfOperation();
                    break;
                case DIV:
                    divOperation();
                    break;
                case DIV_F:
                    divfOperation();
                    break;
                case CAST_TO_I:
                    castToIntegerOperation();
                    break;
                case CAST_TO_F:
                    castToFloatOperation();
                    break;
                case MOV:
                    movOperation();
                    break;
                case MOV_F:
                    movfOperation();
                    break;
                case PUSH:
                    pushIntOperation();
                    break;
                case PUSH_F:
                    BytecodeDecompiller::disassemblyInstruction(PUSH_F, pc, sizeof(float));
                    pushFloatOperation();
                    break;
                case READ:
                    readOperation();
                    break;
                case PRINT:
                    printOperation();
                    break;
                default: break;
            }
        }
    }

    void VirtualMachine::attachChunk(const Chunk *chunk) {
        this->program = chunk->program;
        this->pc = &program[0];
    }

    void VirtualMachine::returnOperation() const {
        std::cout << "Exiting with return code " << returnCode;
        exit(EXIT_SUCCESS);
    }

    void VirtualMachine::addOperation() {
        const int left = popIntegerOperand();
        const int right = popIntegerOperand();
        pushInt(left + right);
    }

    void VirtualMachine::addfOperation() {
        const float left = popFloatOperand();
        const float right = popFloatOperand();
        pushFloat(left + right);
    }

    void VirtualMachine::subOperation() {
        const int left = popIntegerOperand();
        const int right = popIntegerOperand();
        pushInt(left - right);
    }

    void VirtualMachine::subfOperation() {
        const float left = popFloatOperand();
        const float right = popFloatOperand();
        pushFloat(left - right);
    }

    void VirtualMachine::divOperation() {
        const int left = popIntegerOperand();
        const int right = popIntegerOperand();
        pushInt(left / right);
    }

    void VirtualMachine::divfOperation() {
        const float left = popFloatOperand();
        const float right = popFloatOperand();
        pushFloat(left / right);
    }

    void VirtualMachine::mulOperation() {
        const int left = popIntegerOperand();
        const int right = popIntegerOperand();
        pushInt(left * right);
    }

    void VirtualMachine::mulfOperation() {
        const float left = popFloatOperand();
        const float right = popFloatOperand();
        const float result = left * right;
        pushFloat(result);
    }

    void VirtualMachine::castToIntegerOperation() {
        const float value = popFloatOperand();
        const auto convertedValue = static_cast<int>(value);
        mRegisterSize = sizeof(float);
        std::memcpy(mRegister, &convertedValue, sizeof(float));
    }

    void VirtualMachine::castToFloatOperation() {
        const int value = popIntegerOperand();
        const auto convertedValue = static_cast<float>(value);
        mRegisterSize = sizeof(float);
        std::memcpy(mRegister, &convertedValue, sizeof(float));
    }

    void VirtualMachine::movOperation() {
        if (mRegisterSize != sizeof(int)) {
            ERROR("Invalid size for MOV operation");
        }
        int value;
        std::memcpy(&value, mRegister, sizeof(int));
        pushInt(value);
    }

    void VirtualMachine::movfOperation() {
        if (mRegisterSize != sizeof(float)) {
            ERROR("Invalid size for MOV operation");
        }
        float value;
        std::memcpy(&value, mRegister, sizeof(float));
        pushFloat(value);
    }

    uint8_t VirtualMachine::readByte() {
        return *pc++;
    }

    int VirtualMachine::readInt() {
        int value;
        std::memcpy(&value, pc, sizeof(int));
        pc += sizeof(int);
        return value;
    }

    float VirtualMachine::readFloat() {
        float value;
        std::memcpy(&value, pc, sizeof(float));
        pc += sizeof(float);
        return value;
    }

    uint8_t VirtualMachine::peekByte() const {
        return *pc;
    }
} // Ample::VM
