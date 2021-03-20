#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
//------*****-----*****-----******
//00000000000000000000000000000000


int8_t memory[0x600000];
int32_t PC = 0x400000;
int32_t OFFSET = 0x400000;
int32_t EOR = -1;
//int8_t * memory = (int8_t *)(malloc(8 * 0x600000));

int ToInt(string num){
    int result = 0, len = num.length(), m = 1;
    for (int i = len - 1; i >= 0; i--){
        if (num.substr(i, 1) == "1"){result += 1 * m;}
        m *= 2;
    }
    return result;
}

uint32_t ToUint(string num){
    int len = num.length();
    uint32_t m = 1, result = 0;
    for (int i = len - 1; i >= 0; i--){
        if (num.substr(i, 1) == "1"){result += 1 * m;}
        m *= 2;
    }
    return result;
}

int32_t $zero;
int32_t $at;
int32_t $v0;
int32_t $v1;
int32_t $a0;
int32_t $a1;
int32_t $a2;
int32_t $a3;
int32_t $t0;
int32_t $t1;
int32_t $t2;
int32_t $t3;
int32_t $t4;
int32_t $t5;
int32_t $t6;
int32_t $t7;
int32_t $s0;
int32_t $s1;
int32_t $s2;
int32_t $s3;
int32_t $s4;
int32_t $s5;
int32_t $s6;
int32_t $s7;
int32_t $t8;
int32_t $t9;
int32_t $k0;
int32_t $k1;
int32_t $gp;
int32_t $sp;
int32_t $fp;
int32_t $ra;
int32_t $lo;
int32_t $hi;

//int32_t stringToint32_t(string line){
//    return strtoul(line.c_str(), NULL, 10);
//}

int32_t & getValueFromRegister(string bin){
    if (bin == "00000"){return $zero;}
    else if (bin == "00001"){return $at;}
    else if (bin == "00010"){return $v0;}
    else if (bin == "00011"){return $v1;}
    else if (bin == "00100"){return $a0;}
    else if (bin == "00101"){return $a1;}
    else if (bin == "00110"){return $a2;}
    else if (bin == "00111"){return $a3;}
    else if (bin == "01000"){return $t0;}
    else if (bin == "01001"){return $t1;}
    else if (bin == "01010"){return $t2;}
    else if (bin == "01011"){return $t3;}
    else if (bin == "01100"){return $t4;}
    else if (bin == "01101"){return $t5;}
    else if (bin == "01110"){return $t6;}
    else if (bin == "01111"){return $t7;}
    else if (bin == "10000"){return $s0;}
    else if (bin == "10001"){return $s1;}
    else if (bin == "10010"){return $s2;}
    else if (bin == "10011"){return $s3;}
    else if (bin == "10100"){return $s4;}
    else if (bin == "10101"){return $s5;}
    else if (bin == "10110"){return $s6;}
    else if (bin == "10111"){return $s7;}
    else if (bin == "11000"){return $t8;}
    else if (bin == "11001"){return $t9;}
    else if (bin == "11010"){return $k0;}
    else if (bin == "11011"){return $k1;}
    else if (bin == "11100"){return $gp;}
    else if (bin == "11101"){return $sp;}
    else if (bin == "11110"){return $fp;}
    else if (bin == "11111"){return $ra;}
    else if (bin == "$hi"){return $hi;}
    else if (bin == "$lo"){return $lo;}
    else{return EOR;}
}


void writeByte(string value, int address){
    uint8_t tem = ToInt(value);
    memory[(int32_t)address - OFFSET] = tem;
}

void writeWord(string value, int address){
    for (int i = 0; i < 4; i++){
        uint8_t tem = ToInt(value.substr(i * 8, 8));
        memory[(int32_t)address - OFFSET + i] = tem;
    }
}

string fetchByte(int address){
    string result = to_string(memory[(int32_t)address - OFFSET]);
    return result;
}

string fetchword(int address){
    string result;
    for (int i = 0; i < 4; i++){
        result += to_string(memory[(int32_t)address - OFFSET + i]);
    }
    return result;
}



void MC_add(int32_t rs, int32_t rt,  int32_t &rd ){rd = rs + rt;}

void MC_addu(int32_t rs, int32_t rt,  int32_t &rd ){rd = (int32_t) ((uint32_t)rs + (uint32_t)rt);}

void MC_addi(int32_t rs, int32_t &rt,  int32_t imm ){rt = rs + imm;}

void MC_addiu(int32_t rs, int32_t &rt,  int32_t imm ){rt = (int32_t) ((uint32_t)rs + (uint32_t)imm);}

void MC_and(int32_t rs, int32_t rt,  int32_t &rd ){rd = rs & rt;}

void MC_andi(int32_t rs, int32_t &rt,  int32_t imm ){rt = rs & imm;}

void MC_clo(int32_t rs, int32_t &rd ){
    string tem = to_string(rs);
    int32_t count = 0;
    for (int i = 0; i < 32; i++){
        if (tem.substr(i, 1) == "1"){
            count += 1;
        }
    }
    rd = count;
}

void MC_clz(int32_t rs, int32_t &rd ){
    string tem = to_string(rs);
    int32_t count = 0;
    for (int i = 0; i < 32; i++){
        if (tem.substr(i, 1) == "0"){
            count += 1;
        }
    }
    rd = count;
}

void MC_div(int32_t rs, int32_t rt ){
    int32_t quo = rs / rt;
    int32_t rem = rs % rt;
    $lo = quo;
    $hi = rem;
}

void MC_divu(int32_t &rs, int32_t &rt ){
    uint32_t quo = rs / rt;
    uint32_t rem = rs % rt;
    $lo = (int32_t) quo;
    $hi = (int32_t) rem;
}

void MC_mult(int32_t rs, int32_t rt ){
    int64_t tem_rs = (int64_t) rs;
    int64_t tem_rt = (int64_t) rt;
    int64_t pro = tem_rs * tem_rt;
    int32_t low = (int32_t) pro;
    int32_t high = (int32_t)(pro >> 32);
    $lo = low;
    $hi = high;
}

void MC_multu(int32_t &rs, int32_t &rt ){
    uint64_t tem_rs = (uint64_t) rs;
    uint64_t tem_rt = (uint64_t) rt;
    uint64_t pro = tem_rs * tem_rt;
    uint32_t low = (uint32_t) pro;
    uint32_t high = (uint32_t)(pro >> 32);
    $lo = (int32_t) low;
    $hi = (int32_t) high;
}

void MC_mul(int32_t rs, int32_t rt,  int32_t &rd ){
    int64_t pro = rs * rt;
    rd = (int32_t) pro;
}

void MC_madd(int32_t rs, int32_t rt ){
    int64_t low = (int64_t) $lo;
    int64_t high = (int64_t) $hi;
    int64_t con = (high << 32) + low;
    int64_t result = con + (int64_t) rs * (int64_t) rt;
    $lo = (int32_t) result;
    $hi = (int32_t) (result >> 32);
}

void MC_maddu(int32_t rs, int32_t rt ){
    uint64_t low = (uint64_t) $lo;
    uint64_t high = (uint64_t) $hi;
    uint64_t con = (high << 32) + low;
    uint64_t result = con + (uint64_t) rs * (uint64_t) rt;
    $lo = (int32_t) result;
    $hi = (int32_t) (result >> 32);
}

void MC_msub(int32_t rs, int32_t rt ){
    int64_t low = (int64_t) $lo;
    int64_t high = (int64_t) $hi;
    int64_t con = (high << 32) + low;
    int64_t result = con - (int64_t) rs * (int64_t) rt;
    $lo = (int32_t) result;
    $hi = (int32_t) (result >> 32);
}

void MC_msubu(int32_t rs, int32_t rt ){
    uint64_t low = (uint64_t) $lo;
    uint64_t high = (uint64_t) $hi;
    uint64_t con = (high << 32) + low;
    uint64_t result = con + (uint64_t) rs * (uint64_t) rt;
    $lo = (int32_t) result;
    $hi = (int32_t) (result >> 32);
}

void MC_nor(int32_t rs, int32_t rt,  int32_t &rd ){rd = ~(rs | rt);}

void MC_or(int32_t rs, int32_t rt,  int32_t &rd ){rd = rs | rt;}

void MC_ori(int32_t rs, int32_t &rt,  int32_t imm ){rt = rs | imm;}

void MC_sll(int32_t rt, int32_t &rd,  int32_t shamt ){
    uint32_t tem_rt = (uint32_t) rt;
    rd = (int32_t) (tem_rt << shamt);
}

void MC_sllv(int32_t rs, int32_t rt,  int32_t &rd ){
    uint32_t tem_rs = (uint32_t) rs;
    uint32_t tem_rt = (uint32_t) rt;
    rd = (int32_t) (tem_rt << tem_rs);
}

void MC_sra(int32_t rs, int32_t &rd,  int32_t shamt ){rd = rs >> shamt;}

void MC_srav(int32_t rs, int32_t rt,  int32_t &rd ){rd = rt >> rs;}

void MC_srl(int32_t rt, int32_t &rd,  int32_t shamt ){
    uint32_t tem_rt = (uint32_t) rt;
    rd = (int32_t) (tem_rt >> shamt);
}

void MC_srlv(int32_t rs, int32_t rt,  int32_t &rd ){
    uint32_t tem_rs = (uint32_t) rs;
    uint32_t tem_rt = (uint32_t) rt;
    rd = (int32_t) (tem_rt >> tem_rs);
}

void MC_sub(int32_t rs, int32_t rt,  int32_t &rd ){rd = rs - rt;}

void MC_subu(int32_t rs, int32_t rt,  int32_t &rd ){rd = (int32_t) ((uint32_t) rs - (uint32_t) rt);}

void MC_xor(int32_t rs, int32_t rt,  int32_t &rd ){rd = rs ^ rt;}

void MC_xori(int32_t rs, int32_t &rt,  int32_t imm ){rt = rs ^ imm;}

void MC_lui(int32_t &rt, int32_t imm ){rt = (imm << 16);}

void MC_slt(int32_t rs, int32_t rt,  int32_t &rd ){rd = rs < rt? 1:0;}

void MC_sltu(int32_t rs, int32_t rt,  int32_t &rd ){rd = (int32_t) ((uint32_t) rs < (uint32_t) rt? 1:0);}

void MC_slti(int32_t rs, int32_t &rt,  int32_t imm ){rt = rs < imm? 1:0;}

void MC_sltiu(int32_t rs, int32_t &rt,  int32_t imm ){rt = (int32_t) ((uint32_t)rs < (uint32_t)imm? 1:0);}

void MC_beq(int32_t rs, int32_t rt,  int32_t offset ){
    if (rs == rt){PC += offset * 4;}
}

void MC_bgez(int32_t rs, int32_t offset ){
    if (rs >= 0){PC += offset * 4;}
}

void MC_bgezal(int32_t rs, int32_t offset ){
    if (rs >= 0){
        $ra = PC;
        PC += offset * 4;
    }
}

void MC_bgtz(int32_t rs, int32_t offset ){
    if (rs > 0){PC += offset * 4;}
}

void MC_blez(int32_t rs, int32_t offset ){
    if (rs <= 0){PC += offset * 4;}
}

void MC_bltzal(int32_t rs, int32_t offset ){
    if (rs < 0){
        $ra = PC;
        PC += offset * 4;
    }
}

void MC_bltz(int32_t rs, int32_t offset ){
    if (rs < 0){PC += offset * 4;}
}

void MC_bne(int32_t rs, int32_t rt,  int32_t offset ){
    if (rs != rt){PC += offset * 4;}
}

void MC_j(int32_t target ){PC = target;}

void MC_jal(int32_t target ){
    $ra = PC;
    PC = target;
}


void MC_jalr(int32_t rs, int32_t &rd ){
    rd = PC;
    PC = rs;
}

void MC_jr(int32_t rs ){
    PC = rs;
}

void MC_teq(int32_t rs, int32_t rt ){
    if (rs == rt){
        cout << "Trap Exception" << endl;
    }

}

void MC_teqi(int32_t rs, int32_t imm ){
    if (rs == (int32_t)imm){
        cout << "Trap Exception" << endl;
    }
}

void MC_tne(int32_t rs, int32_t rt ){
    if (rs != rt){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tnei(int32_t rs, int32_t imm ){
    if (rs != (int32_t)imm){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tge(int32_t rs, int32_t rt ){
    if (rs >= rt){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tgeu(int32_t rs, int32_t rt ){
    if ((uint32_t)rs >= (uint32_t)rt){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tgei(int32_t rs, int32_t imm ){
    if (rs >= imm){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tgeiu(int32_t rs, int32_t imm ){
    if ((uint32_t)rs >= (uint32_t)imm){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tlt(int32_t rs, int32_t rt ){
    if (rs < rt){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tltu(int32_t rs, int32_t rt ){
    if ((uint32_t)rs < (uint32_t)rt){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tlti(int32_t rs, int32_t imm ){
    if (rs < imm){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_tltiu(int32_t rs, int32_t imm ){
    if ((uint32_t)rs < (uint32_t)imm){
        cout << "Trap Exception" << endl;
    }
    PC -= 1;
}

void MC_lb(int32_t &rt, int32_t address ){
    rt = (int32_t) (ToInt(fetchByte(address)));
}

void MC_lbu(int32_t &rt, int32_t address ){
    rt = (uint32_t) (ToInt(fetchByte(address)));
}

void MC_lh(int32_t &rt, int32_t address ){
    rt = (int32_t)((ToInt(fetchByte(address)) << 8) + ToInt(fetchByte(address + 1)));
}

void MC_lhu(int32_t &rt, int32_t address ){
    rt = (int32_t)((ToUint(fetchByte(address)) << 8) + ToUint(fetchByte(address + 1)));
}

void MC_lw(int32_t &rt, int32_t address ){
    rt = (int32_t) (ToUint(fetchword(address)));
}

void MC_lwl(int32_t &rt, int32_t address ){
    int c = 0;
    uint32_t tem = 0;
    while (address % 4 != 0){
        tem >>= 8;
        tem += ToUint(fetchByte(address)) << (c * 8);
        address -= 1;
        c += 1;
    }
    rt = (int32_t) (((uint32_t)(rt) << 24 >> 24) + tem);
}

void MC_lwr(int32_t &rt, int32_t address ){
    int c = 0;
    uint32_t tem = 0;
    while (address % 4 != 0){
        tem >>= 8;
        tem += ToUint(fetchByte(address)) << (c * 8);
        address += 1;
        c += 1;
    }
    rt = (int32_t) (((uint32_t)(rt) >> 24 << 24) + tem);
}

void MC_ll(int32_t rt, int32_t address ){
    rt = (int32_t) (ToUint(fetchword(address)));
}

void MC_sb(int32_t &rt, int32_t address ){
    int8_t tem = (int8_t) rt;
    writeByte(to_string(tem), address);
}

void MC_sh(int32_t &rt, int32_t address ){
    int16_t tem = (int16_t) rt;
    writeByte(to_string(tem), address);
    writeByte(to_string((tem >> 8)), address);
}

void MC_sw(int32_t &rt, int32_t address ){
    int32_t tem = (int32_t) rt;
    writeWord(to_string(tem), address);
}

void MC_swl(int32_t &rt, int32_t address ){// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int c = 0;
    uint32_t tem = 0;
    while (address % 4 != 0){
        tem >>= 8;
        tem += ToUint(fetchByte(address)) << (c * 8);
        address -= 1;
        c += 1;
    }
    writeWord(to_string(((int32_t)(rt) << 24 >> 24) + tem), address);
}

void MC_swr(int32_t &rt, int32_t address ){// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int c = 0;
    uint32_t tem = 0;
    while (address % 4 != 0){
        tem >>= 8;
        tem += ToUint(fetchByte(address)) << (c * 8);
        address -= 1;
        c += 1;
    }
    writeWord(to_string(((int32_t)(rt) >> 24 << 24) + tem), address);
}

void MC_sc(int32_t &rt, int32_t address ){
    MC_sw(rt, address);
    rt = 1;
}

void MC_mfhi(int32_t &rd ){
    rd = getValueFromRegister("$hi");
}

void MC_mflo(int32_t &rd ){
    rd = getValueFromRegister("$lo");
}

void MC_mthi(int32_t rd ){
    $hi = rd;
}

void MC_mtlo(int32_t rs ){
    $lo = rs;
}

void MC_syscall(){
    string result;
    int start, count = 0;
    int32_t tem = getValueFromRegister("00010");
    if (tem == 1){
        cout << to_string(getValueFromRegister("00001")) << endl;
    }else if (tem == 4){
        start = getValueFromRegister("00001");
        while (count < 4){
            cout << fetchByte(start);
            count += 1;
            start += 1;
        }
    }else if (tem == 5){

    }else if (tem == 8){

    }else if (tem == 9){

    }else if (tem == 10){

    }else if (tem == 11){

    }else if (tem == 12){

    }else if (tem == 13){

    }else if (tem == 14){

    }else if (tem == 15){

    }else if (tem == 16){

    }else if (tem == 17){

    }
}


void MC_operate(string code){
    cout << code << endl;
}


int32_t ToTarget(int32_t bin){// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return bin;
}

void GetOffSpace(string &s){
    string beg;
    if(!s.empty()){
        s.erase(0, s.find_first_not_of("\t"));
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }
}

vector <string> split(string line){
    string MC_op, MC_rd, MC_rs, MC_rt, MC_rshamt, MC_rdunc;
    vector <string> MC_rset;
    MC_rset.push_back(line.substr(0, 6));
    MC_rset.push_back(line.substr(6, 5));
    MC_rset.push_back(line.substr(11, 5));
    MC_rset.push_back(line.substr(16, 5));
    MC_rset.push_back(line.substr(21,5));
    MC_rset.push_back(line.substr(26, 6));
    return MC_rset;
}

void splitOff(string line){
    vector <string> MC_line;
    if (line == "00000000000000000000000000001100"){MC_syscall();}


    MC_line = split(line);
    if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "100000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =   "add"+ MC_rd + MC_rs + MC_rt;
        MC_add(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "100001"){
             int32_t MC_rs =(uint32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(uint32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(uint32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =   "addu" + MC_rd + MC_rs + MC_rt;
        MC_addu(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "100100"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "and" + MC_rd + MC_rs + MC_rt;
        MC_and(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "011010"){
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[2]);
        //    MC_code =  "div" + MC_rd + MC_rs;
        MC_div(MC_rd, MC_rs);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "011011"){
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[2]);
        //    MC_code =  "divu" + MC_rd + MC_rs;
        MC_divu(MC_rd, MC_rs);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "011000"){
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[2]);
        //    MC_code =  "mult" + MC_rd + MC_rs;
        MC_mult(MC_rd, MC_rs);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "011001"){
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[2]);
        //    MC_code =  "multu" + MC_rd + MC_rs;
             MC_multu(MC_rd, MC_rs);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "100111"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "nor" + MC_rd + MC_rs + MC_rt;
             MC_nor(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "100101"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "or" + MC_rd + MC_rs + MC_rt;
             MC_or(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[1] == "00000" && MC_line[5] == "000000"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
             int32_t MC_shamt = ToInt(MC_line[4]);
        //    MC_code =  "sll" + MC_rd + MC_rt + MC_shamt;
             MC_sll(MC_rt, MC_rd, MC_shamt);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "000100"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "sllv" + MC_rd + MC_rs + MC_rt;
             MC_sllv(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[1] == "00000" && MC_line[5] == "000011"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
             int32_t MC_shamt = ToInt(MC_line[4]);
        //    MC_code =  "sra" + MC_rd + MC_rt + MC_shamt;
             MC_sra(MC_rt, MC_rd, MC_shamt);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "000111"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "srav" + MC_rd + MC_rt + MC_rs;
             MC_srav(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[1] == "00000" && MC_line[5] == "000010"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
             int32_t MC_shamt = ToInt(MC_line[3]);
        //    MC_code =  "srl" + MC_rd + MC_rs + MC_shamt;
             MC_srl(MC_rt, MC_rd, MC_shamt);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "000110"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "srav" + MC_rd + MC_rt + MC_rs;
             MC_srav(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "100010"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "sub" + MC_rd + MC_rs + MC_rt;
             MC_sub(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "100011"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "subu" + MC_rd + MC_rs + MC_rt;
             MC_subu(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "100110"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "xor" + MC_rd + MC_rs + MC_rt;
             MC_xor(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "101010"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "slt" + MC_rd + MC_rs + MC_rt;
             MC_slt(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[4] == "00000" && MC_line[5] == "101011"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "sltu" + MC_rd + MC_rs + MC_rt;
             MC_sltu(MC_rs, MC_rt,  MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[2] == "00000" && MC_line[4] == "00000" && MC_line[5] == "001001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "jalr" + MC_rs + MC_rd;
             MC_jalr(MC_rs, MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[2] == "00000" && MC_line[3] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "001000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
        //    MC_code =  "jr" + MC_rs;
             MC_jr(MC_rs);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "110100"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "teq" + MC_rs + MC_rt;
             MC_teq(MC_rs, MC_rt);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "110110"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "tne" + MC_rs + MC_rt;
             MC_tne(MC_rs, MC_rt);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "110000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "tge" + MC_rs + MC_rt;
             MC_tge(MC_rs, MC_rt);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "110001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "tgeu" + MC_rs + MC_rt;
             MC_tgeu(MC_rs, MC_rt);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "110010"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "tlt" + MC_rs + MC_rt;
             MC_tlt(MC_rs, MC_rt);
    }else if (MC_line[0] == "000000" && MC_line[3] == "00000" && MC_line[4] == "00000" && MC_line[5] == "110011"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "tltu" + MC_rs + MC_rt;
             MC_tltu(MC_rs, MC_rt);
    }else if (MC_line[0] == "000000" && MC_line[1] == "00000" && MC_line[2] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "010000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "mfhi" + MC_rs;
             MC_mfhi(MC_rs);
    }else if (MC_line[0] == "000000" && MC_line[1] == "00000" && MC_line[2] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "010010"){
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "mflo" + MC_rd;
             MC_mflo(MC_rd);
    }else if (MC_line[0] == "000000" && MC_line[2] == "00000" && MC_line[3] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "010001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
        //    MC_code =  "mthi" + MC_rs;
             MC_mthi(MC_rs);
    }else if (MC_line[0] == "000000" && MC_line[2] == "00000" && MC_line[3] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "001011"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
        //    MC_code =  "mtlo" + MC_rs;
             MC_mtlo(MC_rs);
    }else if (MC_line[0] == "001000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "addi" + MC_rt + MC_rs + MC_imm;
             MC_addi(MC_rs, MC_rt, MC_imm);
    }else if (MC_line[0] == "001001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "addiu" + MC_rt + MC_rs + MC_imm;
             MC_addiu(MC_rs, MC_rt, MC_imm);
    }else if (MC_line[0] == "001100"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "andi" + MC_rt + MC_rs + MC_imm;
             MC_andi(MC_rs, MC_rt, MC_imm);
    }else if (MC_line[0] == "011100" && MC_line[2] == "00000" && MC_line[4] == "00000" && MC_line[5] == "100001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "clo" + MC_rd + MC_rs;
             MC_clo(MC_rs, MC_rd);
    }else if (MC_line[0] == "011100" && MC_line[2] == "00000" && MC_line[4] == "00000" && MC_line[5] == "100000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "clz" + MC_rd + MC_rs;
             MC_clz(MC_rs, MC_rd);
    }else if (MC_line[0] == "011100" && MC_line[4] == "00000" && MC_line[5] == "000010"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_rd =(int32_t) getValueFromRegister(MC_line[3]);
        //    MC_code =  "mul" + MC_rd + MC_rs + MC_rt;
             MC_mul(MC_rs, MC_rt, MC_rd);
    }else if (MC_line[0] == "011100" && MC_line[3] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "000000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
        //    MC_code =  "madd" + MC_rs + MC_rt;
             MC_madd(MC_rs, MC_rt);
    }else if (MC_line[0] == "011100" && MC_line[3] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "000001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
        //    MC_code =  "maddu" + MC_rs + MC_rt;
             MC_maddu(MC_rs, MC_rt);
    }else if (MC_line[0] == "011100" && MC_line[3] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "000100"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
        //    MC_code =  "msub" + MC_rs + MC_rt;
             MC_msub(MC_rs, MC_rt);
    }else if (MC_line[0] == "011100" && MC_line[3] == "00000"  && MC_line[4] == "00000" && MC_line[5] == "000101"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
        //    MC_code =  "msubu" + MC_rs + MC_rt;
             MC_msubu(MC_rs, MC_rt);
    }else if (MC_line[0] == "001101"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]);
        //    MC_code =  "ori" + MC_rt + MC_rs + MC_imm;
             MC_ori(MC_rs, MC_rt, MC_imm);
    }else if (MC_line[0] == "001110"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]);
        //    MC_code =  "xori" + MC_rt + MC_rs + MC_imm;
             MC_xori(MC_rs, MC_rt, MC_imm);
    }else if (MC_line[0] == "001111" && MC_line[1] == "00000"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "lui" + MC_rt + MC_imm;
             MC_lui(MC_rt, MC_imm);
    }else if (MC_line[0] == "001010"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_imm = ToInt(MC_line[4] + MC_line[5]  );
        //    MC_code =  "slti" + MC_rt + MC_rs + MC_imm;
             MC_slti(MC_rs, MC_rt, MC_imm);
    }else if (MC_line[0] == "001011"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_imm = ToInt(MC_line[4] + MC_line[5]  );
        //    MC_code =  "sltiu" + MC_rt + MC_rs + MC_imm;
             MC_sltiu(MC_rs, MC_rt, MC_imm);
    }else if (MC_line[0] == "000100"){// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "beq" + MC_rs + MC_rt + MC_imm;
             MC_beq(MC_rs, MC_rt, MC_offset);
    }else if (MC_line[0] == "000001" && MC_line[2] == "00001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_label = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "bgez" + MC_rs + MC_label;
             MC_bgez(MC_rs, MC_label);
    }else if (MC_line[0] == "000001" && MC_line[2] == "10001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_label = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "bgezal" + MC_rs + MC_label;
             MC_bgezal(MC_rs, MC_label);
    }else if (MC_line[0] == "000111" && MC_line[2] == "00000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_label = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "bgtz" + MC_rs + MC_label;
             MC_bgtz(MC_rs,  MC_label);
    }else if (MC_line[0] == "000110" && MC_line[2] == "00000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_label = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "blez" + MC_rs + MC_label;
             MC_blez(MC_rs, MC_label);
    }else if (MC_line[0] == "000001" && MC_line[2] == "10000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_label = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "bltzal" + MC_rs + MC_label;
             MC_bltzal(MC_rs, MC_label);
    }else if (MC_line[0] == "000001" && MC_line[2] == "00000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_label = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "bltz" + MC_rd + MC_label;
             MC_bltz(MC_rs, MC_label);
    }else if (MC_line[0] == "000101"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[4] + MC_line[5]  );
        //    MC_code =  "bne" + MC_rs + MC_rt + MC_offset;
             MC_bne(MC_rs, MC_rt, MC_offset);
    }else if (MC_line[0] == "000010"){
             int32_t MC_target =(int32_t) ToInt(MC_line[1] +MC_line[2] + MC_line[3] + MC_line[4] + MC_line[5]);
        //    MC_code =  "j" + MC_rtarget;
             MC_j(MC_target);
    }else if (MC_line[0] == "000011"){
             int32_t MC_target =(int32_t) ToInt(MC_line[1] +MC_line[2] + MC_line[3] + MC_line[4] + MC_line[5]);
        //    MC_code =  "jal" + MC_rtarget;
             MC_jal(MC_target);
    }else if (MC_line[0] == "000001" && MC_line[2] == "01100"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "teqi" + MC_rs + MC_imm;
             MC_teqi(MC_rs, MC_imm);
    }else if (MC_line[0] == "000001" && MC_line[2] == "01110"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "tnei" + MC_rs + MC_imm;
             MC_tnei(MC_rs, MC_imm);
    }else if (MC_line[0] == "000001" && MC_line[2] == "01000"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "tgei" + MC_rs + MC_imm;
             MC_tgei(MC_rs, MC_imm);
    }else if (MC_line[0] == "000001" && MC_line[2] == "01001"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "tgeiu" + MC_rs + MC_imm;
             MC_tgeiu(MC_rs, MC_imm);
    }else if (MC_line[0] == "000001" && MC_line[2] == "01010"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "tlti" + MC_rs + MC_imm;
             MC_tlti(MC_rs, MC_imm);
    }else if (MC_line[0] == "000001" && MC_line[2] == "01011"){
             int32_t MC_rs =(int32_t) getValueFromRegister(MC_line[1]);
             int32_t MC_imm = ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "tltiu" + MC_rs + MC_imm;
             MC_tltiu(MC_rs, MC_imm);
    }else if (MC_line[0] == "100000"){// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "lb" + MC_rt + MC_offset;
             MC_lb(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "100100"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "lbu" + MC_rt + MC_offset;
             MC_lbu(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "100001"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "lh" + MC_rt + MC_offset;
             MC_lh(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "100101"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "lhu" + MC_rt + MC_offset;
             MC_lhu(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "100011"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);

             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "lw" + MC_rt + MC_offset;
             MC_lw(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "100010"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "lwl" + MC_rt + MC_offset;
             MC_lwl(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "100110"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "lwr" + MC_rt + MC_offset;
             MC_lwr(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "110000"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "ll" +  MC_rt + MC_offset;
             MC_ll(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "101000"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "sb" + MC_rt + MC_offset;
             MC_sb(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "101001"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "sh" + MC_rt + MC_offset;
             MC_sh(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "101011"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "sw" + MC_rt + MC_offset;
             MC_sw(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "101010"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "swl" + MC_rt + MC_offset;
             MC_swl(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "101110"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "swr" +  MC_rt + MC_offset;
             MC_swr(MC_rt, PC + MC_offset);
    }else if (MC_line[0] == "111000"){
             int32_t MC_rt =(int32_t) getValueFromRegister(MC_line[2]);
             int32_t MC_offset =(int32_t) ToInt(MC_line[3] + MC_line[4] + MC_line[5]  );
        //    MC_code =  "sc" +  MC_rt + MC_offset;
             MC_sc(MC_rt, PC + MC_offset);
    }
}

void process(){
    string line, MC_code;
    vector <string> ALL;
    int count = 0;
    while (count <= 5 && cin.good()){
        getline(cin, line);
        if (line.empty()){
            count += 1;
            continue;
        }else {count = 0;}
        ALL.push_back(line);
    }

    for (int i = 0; i < ALL.size(); i++){
        //    MC_code =  splitOff(ALL[i]);

    }

}




int main()
{
    process();
    return 0;
}
