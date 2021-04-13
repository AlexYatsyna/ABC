
#ifndef RISCV_SIM_EXECUTOR_H
#define RISCV_SIM_EXECUTOR_H

#include "Instruction.h"

class Executor
{
public:
    void Execute(InstructionPtr& instr, Word ip)
    {
        /* YOUR CODE HERE */
        Word data,secondValue;
        if(instr -> _imm)
        {
            secondValue=instr->_imm.value();
        }
        else
        {
            secondValue=instr->_src2Val;
        }
        switch (instr->_aluFunc)
        {
        case AluFunc::Add:
            data = instr->_src1Val + secondValue;
            break;
        case AluFunc::Sub:
            data = instr->_src1Val - secondValue;
            break;
        case AluFunc::And:
            data = instr->_src1Val & secondValue;
            break;
        case AluFunc::Or:
            data = instr->_src1Val | secondValue;
            break;
        case AluFunc::Xor:
            data = instr->_src1Val ^ secondValue;
            break;
        case AluFunc::Slt:
            data = (int32_t)instr->_src1Val < (int32_t)secondValue;
            break;
        case AluFunc::Sltu:
            data = instr->_src1Val < secondValue;
            break;
        case AluFunc::Sll:
            data = instr->_src1Val << (secondValue & 31);
            break;
        case AluFunc::Srl:
            data = (uint)(instr->_src1Val >> (secondValue & 31));
            break;
        case AluFunc::Sra:
            data =(int32_t)instr->_src1Val >> (int32_t)(secondValue & 31);
            break; 
        default:
            break;
        }
        bool br = false;
        switch (instr->_brFunc)
        {
        case BrFunc::Eq:
            br = instr->_src1Val == instr->_src2Val;
            break;
        case BrFunc::Neq:
            br = instr->_src1Val != instr->_src2Val;
            break;
        case BrFunc::Lt:
            br = (int32_t)instr->_src1Val < (int32_t)instr->_src2Val;
            break;
        case BrFunc::Ltu:
            br = instr->_src1Val < instr->_src2Val;
            break;
        case BrFunc::Ge:
            br = (int32_t)instr->_src1Val >= (int32_t)instr->_src2Val;
            break;
        case BrFunc::Geu:
            br = instr->_src1Val >= instr->_src2Val;
            break;
        case BrFunc::AT:
            br = true;
            break;
        case BrFunc::NT:
            br=false;
            break;       
        default:
            break;
        }

        instr->_data = data;
        if(!br)
        {
            instr->_nextIp = ip + 4;
        }

        switch (instr->_type)
        {
        case IType::Ld:
            instr->_addr = data;
            break;
        case IType::St:
            instr->_addr = data;
            instr->_data = instr->_src2Val;
            break;
        case IType::Csrr:
            instr->_data = instr->_csrVal;
            break;
        case IType::Csrw:
            instr->_data = instr->_src1Val;
            break;
        case IType::J:
            instr->_data = ip + 4;
            if(br)
            {
                instr->_nextIp = ip + instr->_imm.value();
            }
            break;
        case IType::Jr:
            instr->_data = ip + 4;
            if(br)
            {
                instr->_nextIp = instr->_imm.value() + instr->_src1Val;
            }
            break;
        case IType::Auipc:
            instr->_data = ip + instr->_imm.value();
            break;
        case IType::Br:
            if(br)
            {
                instr->_nextIp = ip + instr->_imm.value();
            }
        default:
            break;
        }

    }

private:
    /* YOUR CODE HERE */

};

#endif // RISCV_SIM_EXECUTOR_H
