#include <iomanip>
#include <iostream>

#include "src/VirtualMachine/VirtualMachine.h"
#include "src/VirtualMachine/OpCode.h"

void floatToBytes(float num, unsigned char *byteArray) {
    const auto ptr = reinterpret_cast<unsigned char *>(&num);
    for (int i = 0; i < sizeof(float); ++i) {
        byteArray[i] = ptr[i];
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(ptr[i]) << ", ";
    }
}

int main() {
    using namespace Ample::VM;

    auto VM = VirtualMachine();

    const auto chunk = Chunk({
        0x10, 0xC3, 0xF5, 0x48, 0x40,
        0x10, 0xC3, 0xF5, 0x48, 0x40,
        0x08, 0x00
    });

    VM.attachChunk(&chunk);
    VM.execute();

    return 0;
}
