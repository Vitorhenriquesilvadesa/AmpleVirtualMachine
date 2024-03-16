//
// Created by vitor on 16/03/24.
//

#ifndef OPCODE_H
#define OPCODE_H

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

        POP,

        POP_F,
    };
} // Ample::VM
#endif //OPCODE_H
