#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H
#include <cstdint>
#include <vector>

#include "BytecodeDecompiller.h"
#include "Chunk.h"

namespace Ample::VM {

    enum class NativeType {
        Boolean, Char, Integer, Float, Long, String, Object, Array,
    };

    class VirtualMachine {
    public:
        VirtualMachine(): mRegister(nullptr), mRegisterSize(0) {
            this->decompiller = BytecodeDecompiller();
            this->pc = &program[0];
            this->integerStack = std::vector<int>(256);
            this->floatStack = std::vector<float>(256);
            this->intSp = 0;
            this->floatSp = 0;
            this->returnCode = 0;
        }

        void execute();

        void attachChunk(const Chunk *chunk);

    private:
        uint8_t *pc;
        int intSp;
        int floatSp;
        uint8_t *mRegister;
        size_t mRegisterSize;
        std::vector<uint8_t> program;
        std::vector<int> integerStack;
        std::vector<float> floatStack;
        int returnCode;
        BytecodeDecompiller decompiller;
        static constexpr size_t stackMaxSize = 256;


        void pushInt(int operand);

        void pushFloat(float operand);

        [[nodiscard]] int popIntegerOperand();

        [[nodiscard]] float popFloatOperand();

        void pushConstOperation();

        void pushIntOperation();

        void pushFloatOperation();

        void readOperation() const;

        void printOperation() const;

        void returnOperation() const;

        void addOperation();

        void addfOperation();

        void subOperation();

        void subfOperation();

        void divOperation();

        void divfOperation();

        void mulOperation();

        void mulfOperation();

        void castToIntegerOperation();

        void castToFloatOperation();

        void movOperation();

        void movfOperation();

        uint8_t readByte();

        int readInt();

        float readFloat();

        [[nodiscard]] uint8_t peekByte() const;
    };
} // Ample::VM

#endif //VIRTUALMACHINE_H
