#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "mips.h" // for execute_syscall()
#include "types.h"

Word temp;
sDouble tmp;
Double tempp;

void execute_instruction(Instruction instruction,Processor* processor,Byte *memory) {
    
    /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
    switch(instruction.opcode) {
        case 0x0: // opcode == 0x0(SPECIAL)
            switch(instruction.rtype.funct) {
                case 0xc: // funct == 0xc (SYSCALL)
                    execute_syscall(processor);
                    processor->PC += 4;
                    break;
                case 0x24: // funct == 0x24 (AND)
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] & processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x0: 
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rt] << instruction.rtype.shamt;
                    processor->PC += 4;
                    break;
                case 0x2: 
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rt] >> instruction.rtype.shamt;
                    processor->PC += 4;
                    break;
                case 0x3: 
                    processor->R[instruction.rtype.rd] = ((sWord) processor->R[instruction.rtype.rt]) >> instruction.rtype.shamt;
                    processor->PC += 4;
                    break;
                case 0x8: 
                    processor->PC = processor->R[instruction.rtype.rs];
                    break;
                case 0x9:
                	temp = processor->PC += 4;
                    processor->PC = processor->R[instruction.rtype.rs];
                    processor->R[instruction.rtype.rd] = temp;
                    break;
                case 0x10: 
                    processor->R[instruction.rtype.rd] = processor->RHI;
                    processor->PC += 4;
                    break;
                case 0x12: 
                    processor->R[instruction.rtype.rd] = processor->RLO;
                    processor->PC += 4;
                    break;
                case 0x18:
                    tmp = ((sDouble)(sWord) processor->R[instruction.rtype.rs]) * ((sDouble)(sWord)processor->R[instruction.rtype.rt]);
                    processor->RLO = ((sWord)tmp);
                    processor->RHI = ((sWord)(tmp >> 32));
                    processor->PC += 4;
                    break;
                case 0x19:
                	tempp = ((Double)processor->R[instruction.rtype.rs]) * ((Double)processor->R[instruction.rtype.rt]);
                	processor->RLO = ((Word)tempp);
                	processor->RHI = ((Word)(tempp >> 32));
                	processor->PC += 4;
                	break;
                case 0x21: 
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] + processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x23: 
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] - processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x25: 
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] | processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x26: 
                    processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] ^ processor->R[instruction.rtype.rt];
                    processor->PC += 4;
                    break;
                case 0x27: 
                    processor->R[instruction.rtype.rd] = ~(processor->R[instruction.rtype.rs] | processor->R[instruction.rtype.rt]);
                    processor->PC += 4;
                    break;
                case 0x2a: 
                	if (((sWord) processor->R[instruction.rtype.rs]) < ((sWord) processor->R[instruction.rtype.rt]))
                	     processor->R[instruction.rtype.rd] = 1;
                	else
                	     processor->R[instruction.rtype.rd] = 0;
                	processor->PC += 4;
                	break;
                case 0x2b: 
                	if ((processor->R[instruction.rtype.rs]) < processor->R[instruction.rtype.rt])
                	     processor->R[instruction.rtype.rd] = 1;
                	else
                	     processor->R[instruction.rtype.rd] = 0;
                	processor->PC += 4;
                	break;
                default: // undefined funct
                    fprintf(stderr,"%s: pc=%08x,illegal function=%08x\n",__FUNCTION__,processor->PC,instruction.bits);
                    exit(-1);
                    break;
            }
            break;
        case 0x2: // opcode == 0x2 (J)
            processor->PC = ((processor->PC+4) & 0xf0000000) | (instruction.jtype.addr << 2);
            break;
        case 0x3: 
            processor->R[31] = processor->PC + 4;
        	processor->PC = ((processor->PC+4) & 0xf0000000) | (instruction.jtype.addr << 2);
            break;
        case 0xd: // opcode == 0xd (ORI)
            processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] | instruction.itype.imm;
            processor->PC += 4;
            break;
        case 0x4: 
            if (processor->R[instruction.itype.rt] == processor->R[instruction.itype.rs])
            	processor->PC = processor->PC + 4 + (((sWord)(sHalf)(instruction.itype.imm)) * 4);
            else
            	processor->PC += 4;
            break;
        case 0x5: 
        	if (processor->R[instruction.itype.rt] != processor->R[instruction.itype.rs])
        	    processor->PC = processor->PC + 4 + (((sWord)(sHalf)(instruction.itype.imm)) * 4);
        	else
        	   processor->PC += 4;
        	break;
        case 0x9: 
            processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm));
            processor->PC += 4;
            break;
        case 0xa: 
        	if (((sWord)processor->R[instruction.itype.rs]) < ((sWord)(sHalf)(instruction.itype.imm)))
        		processor->R[instruction.itype.rt] = 1;
        	else
        		processor->R[instruction.itype.rt] = 0;
        	processor->PC += 4;
        	break;
        case 0xb: 
        	if (processor->R[instruction.itype.rs] < ((sWord)(sHalf)(instruction.itype.imm)))
        	       processor->R[instruction.itype.rt] = 1;
        	else
        	       processor->R[instruction.itype.rt] = 0;
        	processor->PC += 4;
        	break;
        case 0xc: 
            processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] & instruction.itype.imm;
            processor->PC += 4;
            break;
        case 0xe: 
            processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] ^ instruction.itype.imm;
            processor->PC += 4;
            break;
        case 0xf: 
            processor->R[instruction.itype.rt] = instruction.itype.imm << 16;
            processor->PC += 4;
            break;
        case 0x20: 
        	processor->R[instruction.itype.rt] = (sWord)((sByte)(load(memory, processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm)), LENGTH_BYTE)));
            processor->PC += 4;
            break;
        case 0x21: 
        	processor->R[instruction.itype.rt] = (sWord)((sHalf)(load(memory, processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm)), LENGTH_HALF_WORD)));
            processor->PC += 4;
            break;
        case 0x23: 
        	processor->R[instruction.itype.rt] = load(memory, processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm)), LENGTH_WORD);
        	processor->PC += 4;
            break;
        case 0x24: 
            processor->R[instruction.itype.rt] = load(memory, processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm)), LENGTH_BYTE);
            processor->PC += 4;
            break;
        case 0x25: 
        	processor->R[instruction.itype.rt] = load(memory, processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm)), LENGTH_HALF_WORD);
            processor->PC += 4;
            break;
        case 0x28: 
            store(memory, processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm)), LENGTH_BYTE, processor->R[instruction.itype.rt]);
        	processor->PC += 4;
            break;
        case 0x29: 
        	store(memory, processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm)), LENGTH_HALF_WORD, processor->R[instruction.itype.rt]);
            processor->PC += 4;
            break;
        case 0x2b: 
        	store(memory, processor->R[instruction.itype.rs] + ((sWord)(sHalf)(instruction.itype.imm)), LENGTH_WORD, processor->R[instruction.itype.rt]);
            processor->PC += 4;
            break;
        default: // undefined opcode
            fprintf(stderr,"%s: pc=%08x,illegal instruction: %08x\n",__FUNCTION__,processor->PC,instruction.bits);
            exit(-1);
            break;
    }
}


int check(Address address,Alignment alignment) {

    /* YOUR CODE HERE */
	if (address + alignment > MEMORY_SPACE || address > MEMORY_SPACE || address < 1){
		return 0;
	}else if (address % alignment != 0){
		return 0;
    }else
		return 1;
}

void store(Byte *memory,Address address,Alignment alignment,Word value) {
    if(!check(address,alignment)) {
        fprintf(stderr,"%s: bad write=%08x\n",__FUNCTION__,address);
        exit(-1);
    }
    if (alignment == 1){
    	memory[address] = (Byte) value;
    }
    else if (alignment == 2){
    	memory[address] = (Byte) value;
    	memory[address + 1] = (Byte) (value >> 8);
    }else{
    	memory[address] = (Byte) value;
    	memory[address + 1] = (Byte) (value >> 8);
    	memory[address + 2] = (Byte) (value >> 16);
    	memory[address + 3] = (Byte) (value >> 24);
    }
}

Word load(Byte *memory,Address address,Alignment alignment) {
    if(!check(address,alignment)) {
        fprintf(stderr,"%s: bad read=%08x\n",__FUNCTION__,address);
        exit(-1);
    }
    
    /* YOUR CODE HERE */
    
    // incomplete stub to let "simple" execute
    // (only handles size == SIZE_WORD correctly)
    // feel free to delete and implement your own way
    if (alignment == 1){
    	return *(Byte*)(memory+address);
    }else if (alignment == 2){
    	return *(Half*)(memory+address);
    }else
    	return *(Word*)(memory+address);
}
