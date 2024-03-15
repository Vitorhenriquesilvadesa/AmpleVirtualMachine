#include "VirtualMachine.h"

#include <iostream>
#include <cstring>
#include <memory>

#include "../Error.h"

namespace Ample::VM {
    void VirtualMachine::pushInt(const int operand) {
        this->integerStack.push_back(operand);
        intSp++;
    }

    void VirtualMachine::pushFloat(const float operand) {
        this->floatStack.push_back(operand);
        floatSp++;
    }

    [[nodiscard]] int VirtualMachine::popIntegerOperand() {
        return *intSp--;
    }

    [[nodiscard]] float VirtualMachine::popFloatOperand() {
        return *floatSp--;
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

    [[noreturn]] void VirtualMachine::execute() {
        using enum OpCode;

        for (;;) {
            switch (readByte()) {
                case RETURN:
                    returnOperation();
                    break;
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

    void VirtualMachine::returnOperation() const {
        std::cout << "return " << returnCode;
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
        pushFloat(left * right);
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
    }

    void VirtualMachine::movfOperation() {
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
