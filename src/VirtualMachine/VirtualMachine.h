#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H
#include <cstdint>
#include <vector>

namespace Ample::VM {
    enum OpCode {
        /** 0x00 */
        RETURN = 0x00,

        /** 0x01 */
        PUSH_CONST,

        /** 0x02 */
        LOAD_CONST,

        /** 0x03 */
        ADD, // Soma os dois inteiros mais acima da pilha de inteiros

        /** 0x04 */
        ADD_F, // Soma os dois floats mais acima da pilha de pontos flutuantes

        /** 0x05 */
        SUB,

        /** 0x06 */
        SUB_F,

        /** 0x07 */
        MUL,

        /** 0x08 */
        MUL_F,

        /** 0x09 */
        DIV,

        /** 0x0A */
        DIV_F,

        /** 0x0B */
        CAST_TO_I, // Faz o cast do valor no topo da pilha de float para inteiro e o move para %S

        /** 0x0C */
        CAST_TO_F, // Faz o cast do valor no topo da pilha de inteiros para float e o move para %S

        /** 0x0D */
        MOV, // Move a constante %M para a pilha de inteiros

        /** 0x0E */
        MOV_F, // Move a constante %M para a pilha de floats

        /** 0x0F */
        PUSH,

        /** 0x10 */
        PUSH_F,

        /** 0x11 */
        MOVE_CONST,

        /** 0x12 */
        READ,

        /** 0x13 */
        PRINT,
    };

    enum class NativeType {
        Boolean, Char, Integer, Float, Long, String, Object, Array,
    };

    class VirtualMachine {
    public:
        VirtualMachine(): mRegister(nullptr), mRegisterSize(0) {
            this->pc = &program[0];
            this->integerStack = std::vector<int>(256);
            this->floatStack = std::vector<float>(256);
            this->intSp = &integerStack[0];
            this->floatSp = &floatStack[0];
            this->returnCode = 0;
        }

        void pushInt(int operand);

        void pushFloat(float operand);

        [[nodiscard]] int popIntegerOperand();

        [[nodiscard]] float popFloatOperand();

        void pushConstOperation();

        void pushIntOperation();

        void pushFloatOperation();

        void readOperation() const;

        void printOperation() const;

        [[noreturn]] void execute();

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

    private:
        uint8_t *pc;
        int *intSp;
        float *floatSp;
        uint8_t *mRegister;
        size_t mRegisterSize;
        std::vector<uint8_t> program;
        std::vector<int> integerStack;
        std::vector<float> floatStack;
        int returnCode;
        static constexpr size_t stackMaxSize = 256;
    };
} // Ample::VM

#endif //VIRTUALMACHINE_H
