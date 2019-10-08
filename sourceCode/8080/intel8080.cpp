#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <thread>
#include <stdio.h>
#include "../../headerFiles/intel8080.h"	
#include "../../headerFiles/RAM.h"
#include "../../headerFiles/cdl.h"

using namespace std;

I8080::I8080(){

    //
    using a = I8080;

    lookup = {
        {"NOP", &a::NOP_op_handler, 4}
    };
}

void I8080::step(){
    clock();
}

void I8080::load_code(){
    writeMemory(0x0000,0x00);
    writeMemory(0x0001,0x00);
    writeMemory(0x0002,0x00);
    writeMemory(0x0003,0x00);
    writeMemory(0x0004,0xAC);
}

void I8080::draw_debug(){
    clear();
    draw_rect(1,1,11,4,"FLAGS");
    draw_text(2,2,"C P A Z S");
    draw_text(2,3,"");
    std::cout<<Flags.C<<" "<<Flags.P<<" "<<Flags.A<<" "<<Flags.Z<<" "<<Flags.S;

    draw_rect(1,4,11,9,"REGISTERS");
    draw_text(11,4,"╣");

    A = 16;

    draw_text(2,5,"A  ");
    printf("0x%02X",A);
    
    draw_text(2,6,"B  ");
    printf("0x%02X",B);
    draw_text(2,7,"C  ");
    printf("0x%02X",C);
    
    draw_text(2,8,"D  ");
    printf("0x%02X",D);
    draw_text(2,9,"E  ");
    printf("0x%02X",E);

    draw_text(2,10,"H  ");
    printf("0x%02X",H);
    draw_text(2,11,"L  ");
    printf("0x%02X",L);

    draw_text(1,24,"#");
}

void I8080::clock(){

    //std::cout<<std::to_string(clock_counter)<<" clocks"<<std::endl;
    
    if (cycles_counter == 0){
        current_opcode = readMemory(PC);
        cycles_counter = lookup[current_opcode].cycles;

        //std::cout<<"Get op on "<<std::to_string(PC)<<" = "<<std::to_string(current_opcode)<<"\t"<<lookup[current_opcode].name<<std::endl;
        PC++;
    }
    else if(cycles_counter == 1){
        (this->*lookup[current_opcode].operate)(current_opcode);
    }
    cycles_counter--;
    clock_counter++;
}



//Обработчики команд

void I8080::NOP_op_handler(uint8_t opcode){
    std::cout<<"NOP!"<<std::endl;
}
