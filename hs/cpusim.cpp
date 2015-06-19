// Martin Giger
#include <iostream>
#include <string>
#include <sstream>
#include "cpusim_lib.cpp"

// Arrays for opcode prettyfication, where opnames holds the string
// representation of an opcode and required_ops containes the number of required
// arguments for an operation
std::string opnames [256];
int         required_ops [256] = { };

void fetch();
void decode();
void disassemble();
void execute();

/**
 * Converts an integer to a std::string using stringstreams
 */
std::string to_string(unsigned int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

/**
 * Set the values for the opnames and required_ops arrays according to spec
 */
void init_arrays() {
    for(unsigned int i = 0; i < 256; ++i) {
        opnames[i] = "illegal";
    }
    opnames[1]  = "add";
    opnames[2]  = "sub";
    opnames[3]  = "mul";
    opnames[4]  = "div";
    opnames[5]  = "mod";
    opnames[6]  = "set";
    opnames[16] = "jmp";
    opnames[17] = "jge";
    opnames[18] = "jle";
    opnames[19] = "jgr";
    opnames[20] = "jls";
    opnames[21] = "jeq";
    opnames[22] = "jne";
    opnames[33] = "out";
    opnames[34] = "in";
    opnames[48] = "hlt";

    required_ops[1]  = 3;
    required_ops[2]  = 3;
    required_ops[3]  = 3;
    required_ops[4]  = 3;
    required_ops[5]  = 3;
    required_ops[6]  = 3;
    required_ops[16] = 1;
    required_ops[17] = 3;
    required_ops[18] = 3;
    required_ops[19] = 3;
    required_ops[20] = 3;
    required_ops[21] = 3;
    required_ops[22] = 3;
    required_ops[33] = 1;
    required_ops[34] = 1;
}

int main(void) {
    init_arrays();

    fetch();
    decode();
    disassemble();
    execute();
    return 0;
}

/**
 * Reads in the input and stores it in the memory. The process is stopped once
 * 0 is read.
 */
void fetch() {
    unsigned int input_buffer;
    unsigned int i = -1;
    do {
        std::cin >> std::hex >> input_buffer;
        memory_write(++i, input_buffer);
    } while(i < 256 && input_buffer != 0);
}

/**
 * Decodes the stored operation into opcode and three arguments
 */
void decode_instruction(unsigned int instruction,
                        unsigned int& opcode,
                        unsigned int& op1,
                        unsigned int& op2,
                        unsigned int& op3) {
    opcode = instruction / 16777216;
    instruction = instruction % 16777216;
    op1 = instruction / 65536;
    instruction = instruction % 65536;
    op2 = instruction / 256;
    instruction = instruction % 256;
    op3 = instruction;
}

/**
 * Decodes the contents of the memory and passes it to cpusim_outdecode
 */
void decode() {
    unsigned int i = -1;
    unsigned int buffer = 0;
    unsigned int opcode, op1, op2, op3;
    do {
        if(buffer != 0) {
            decode_instruction(buffer, opcode, op1, op2, op3);
            cpusim_outdecode(opcode, op1, op2, op3);
        }

        buffer = memory_read(++i);
    } while(i < 256 && buffer != 0);
}

/**
 * Returns pretty concatenation of the instruction and its arguments. Arguments
 * are only printed as declared as needed by the last argument.
 */
std::string prettify_instruction(std::string& instruction,
                                 unsigned int op1,
                                 unsigned int op2,
                                 unsigned int op3,
                                 unsigned int num_ops) {
    std::string ret = instruction;
    if(num_ops > 0) {
        ret += " " + to_string(op1);
        if(num_ops > 1) {
            ret += ", " + to_string(op2);
            if(num_ops = 3) {
                ret += ", " + to_string(op3);
            }
        }
    }
    return ret;
}

/**
 * Disassembles the contents of the memory, using the opnames array and the
 * prettify_instruction method.
 */
void disassemble() {
    unsigned int i = -1;
    unsigned int buffer = 0;
    unsigned int opcode, op1, op2, op3;
    std::string op;
    do {
        if(buffer != 0) {
            decode_instruction(buffer, opcode, op1, op2, op3);
            if(opcode < 256) {
                op = prettify_instruction(opnames[opcode], op1, op2, op3, required_ops[opcode]);
            }
            else {
                op = "illegal";
            }
            cpu::aout << op << std::endl;
        }
        buffer = memory_read(++i);
    } while(i < 256 && buffer != 0);
}

/**
 * Executes the contents of the memory
 */
void execute() {
    unsigned int pc = 0;
    bool          exit = false;
    unsigned int opcode, op1, op2, op3;
    do {
        decode_instruction(memory_read(pc), opcode, op1, op2, op3);
        switch(opcode) {
            case 1: // add
                memory_write(op3, memory_read(op1) + memory_read(op2));
                break;
            case 2: // sub
                memory_write(op3, memory_read(op1) - memory_read(op2));
                break;
            case 3: // mul
                memory_write(op3, memory_read(op1) * memory_read(op2));
                break;
            case 4: // div
                memory_write(op3, memory_read(op1) / memory_read(op2));
                break;
            case 5: // mod
                memory_write(op3, memory_read(op1) % memory_read(op2));
                break;
            case 6: // set
                memory_write(op1, op2 + op3 * 256);
                break;
            case 16: // jmp
                pc = op1 - 1;
                break;
            case 17: // jge
                if(memory_read(op2) >= memory_read(op3)) {
                    pc = op1 - 1;
                }
                break;
            case 18: // jle
                if(memory_read(op2) <= memory_read(op3)) {
                    pc = op1 - 1;
                }
                break;
            case 19: // jgr
                if(memory_read(op2) > memory_read(op3)) {
                    pc = op1 - 1;
                }
                break;
            case 20: // jls
                if(memory_read(op2) < memory_read(op3)) {
                    pc = op1 - 1;
                }
                break;
            case 21: // jeq
                if(memory_read(op2) == memory_read(op3)) {
                    pc = op1 - 1;
                }
                break;
            case 22: // jne
                if(memory_read(op2) != memory_read(op3)) {
                    pc = op1 - 1;
                }
                break;
            case 33: // out
                cpusim_out(memory_read(op1));
                break;
            case 34: // in
                unsigned int in;
                std::cin >> in;
                memory_write(op1, in);
                break;
            case 48: // hlt
            default:
                exit = true;
        }
        ++pc;
    } while(pc < 256 && !exit);
}
