
#include "opcode.h"
#include "execute.h"
#include "cpu.h"
#include <stdio.h>

void doLoad8bitImmediate(uint8_t instruction)
{
  uint8_t immediate = readMemory(pc + 1);
  // Write to the correct register
  uint8_t* reg;
  switch(instruction)
  {
    case LD_B_d8:
      reg = &b_reg;
      break;
    case LD_D_d8:
      reg = &d_reg;
      break;
    case LD_H_d8:
      reg = &h_reg;
      break;
    case LD_C_d8:
      reg = &c_reg;
      break;
    case LD_E_d8:
      reg = &e_reg;
      break;
    case LD_L_d8:
      reg = &l_reg;
      break;
    case LD_A_d8:
      reg = &a_reg;
      break;
  }
  *reg = immediate;
  pc += LD_REGISTER_IMMEDIATE_LEN;
}

void doNop()
{
  // Only increment PC
  pc += NOP_ARGLEN;
}

void doHalt()
{
  // Increment the PC
  pc += HALT_ARGLEN;
  // TODO: Implement proper halting (will need interrupts first!)
  printf("HALT: q to quit\n");
  char c = getchar();
  if (c == 'q')
    program_state = OFF;
}

void doLoadRegisterRegister(uint8_t instruction)
{
  // Decode the instruction and move the data between the registers
  switch(instruction)
  {
    case LD_A_A:
      a_reg = a_reg;
      break;
    case LD_A_B:
      a_reg = b_reg;
      break;
    case LD_A_C:
      a_reg = c_reg;
      break;
    case LD_A_D:
      a_reg = d_reg;
      break;
    case LD_A_E:
      a_reg = e_reg;
      break;
    case LD_A_H:
      a_reg = h_reg;
      break;
    case LD_A_L:
      a_reg = l_reg;
      break;
    case LD_B_A:
      b_reg = a_reg;
      break;
    case LD_B_B:
      b_reg = b_reg;
      break;
    case LD_B_C:
      b_reg = c_reg;
      break;
    case LD_B_D:
      b_reg = d_reg;
      break;
    case LD_B_E:
      b_reg = e_reg;
      break;
    case LD_B_H:
      b_reg = h_reg;
      break;
    case LD_B_L:
      b_reg = l_reg;
      break;
    case LD_C_A:
      c_reg = a_reg;
      break;
    case LD_C_B:
      c_reg = b_reg;
      break;
    case LD_C_C:
      c_reg = c_reg;
      break;
    case LD_C_D:
      c_reg = d_reg;
      break;
    case LD_C_E:
      c_reg = e_reg;
      break;
    case LD_C_H:
      c_reg = h_reg;
      break;
    case LD_C_L:
      c_reg = l_reg;
      break;
    case LD_D_A:
      d_reg = a_reg;
      break;
    case LD_D_B:
      d_reg = b_reg;
      break;
    case LD_D_C:
      d_reg = c_reg;
      break;
    case LD_D_D:
      d_reg = d_reg;
      break;
    case LD_D_E:
      d_reg = e_reg;
      break;
    case LD_D_H:
      d_reg = h_reg;
      break;
    case LD_D_L:
      d_reg = l_reg;
      break;
    case LD_E_A:
      e_reg = a_reg;
      break;
    case LD_E_B:
      e_reg = b_reg;
      break;
    case LD_E_C:
      e_reg = c_reg;
      break;
    case LD_E_D:
      e_reg = d_reg;
      break;
    case LD_E_E:
      e_reg = e_reg;
      break;
    case LD_E_H:
      e_reg = h_reg;
      break;
    case LD_E_L:
      e_reg = l_reg;
      break;
    case LD_H_A:
      h_reg = a_reg;
      break;
    case LD_H_B:
      h_reg = b_reg;
      break;
    case LD_H_C:
      h_reg = c_reg;
      break;
    case LD_H_D:
      h_reg = d_reg;
      break;
    case LD_H_E:
      h_reg = e_reg;
      break;
    case LD_H_H:
      h_reg = h_reg;
      break;
    case LD_H_L:
      h_reg = l_reg;
      break;
    case LD_L_A:
      l_reg = a_reg;
      break;
    case LD_L_B:
      l_reg = b_reg;
      break;
    case LD_L_C:
      l_reg = c_reg;
      break;
    case LD_L_D: 
      l_reg = d_reg;
      break;
    case LD_L_E:
      l_reg = e_reg;
      break;
    case LD_L_H:
      l_reg = h_reg;
      break;
    case LD_L_L:
      l_reg = l_reg;
      break;
  }
  pc += LD_REGISTER_REGISTER_ARGLEN;
}

void doRegisterIndirectToRegister(uint8_t instruction)
{
  uint16_t addr;
  uint8_t value;
  // Handle the special cases with register A
  if (instruction == LD_A_BC)
  {
    addr = (((uint16_t) b_reg) << 8) | c_reg;
    a_reg = readMemory(addr);
    pc += LD_REG_INDIRECT_REGISTER_ARGLEN;
    return;
  }
  else if (instruction == LD_A_DE)
  {
    addr = (((uint16_t) d_reg) << 8) | e_reg;
    a_reg = readMemory(addr);
    pc += LD_REG_INDIRECT_REGISTER_ARGLEN;
    return;
  }
  addr = (((uint16_t) h_reg) << 8) | l_reg;
  value = readMemory(addr);
  // Further decode instruction
  switch(instruction)
  {
    case LD_A_HL:
      a_reg = value;
      break;
    case LD_B_HL:
      b_reg = value;
      break;
    case LD_C_HL:
      c_reg = value;
      break;
    case LD_D_HL:
      d_reg = value;
      break;
    case LD_E_HL:
      e_reg = value;
      break;
    case LD_H_HL:
      h_reg = value;
      break;
    case LD_L_H:
      l_reg = value;
      break;
  }
  pc += LD_REG_INDIRECT_REGISTER_ARGLEN;
}

void doRegisterToRegisterIndirect(uint8_t instruction)
{
  uint16_t addr;
  uint8_t value;
  // Handle special cases with register A
  if (instruction == LD_BC_A)
  {
    addr = (((uint16_t) b_reg) << 8) | (c_reg);
    writeMemory(addr, a_reg);
    pc += LD_REG_INDIRECT_REGISTER_ARGLEN;
    return;
  }
  else if (instruction == LD_DE_A)
  {
    addr = (((uint16_t) d_reg) << 8) | (e_reg);
    writeMemory(addr, a_reg);
    pc += LD_REG_INDIRECT_REGISTER_ARGLEN;
    return;
  }
  addr = (((uint16_t) h_reg) << 8) | (l_reg);
  // Further decode instruction
  switch(instruction)
  {
    case LD_HL_A:
      value = a_reg;
      break;
    case LD_HL_B:
      value = b_reg;
      break;
    case LD_HL_C:
      value = c_reg;
      break;
    case LD_HL_D:
      value = d_reg;
      break;
    case LD_HL_E:
      value = e_reg;
      break;
    case LD_HL_H:
      value = h_reg;
      break;
    case LD_HL_L:
      value = l_reg;
      break;
  }
  writeMemory(addr, value);
  pc += LD_REG_INDIRECT_REGISTER_ARGLEN;
}

void doImmediateIndirect()
{
  // Get second argument
  uint8_t immediate = readMemory(pc + 1);
  uint16_t addr =(((uint16_t) h_reg) << 8) | (l_reg);
  writeMemory(addr, immediate);
  pc += LD_IMM_TO_INDIRECT_REGISTER_ARGLEN;
}

void doAddrToAcc()
{
  uint8_t lower = readMemory(pc + 1);
  uint8_t higher = readMemory(pc + 2);
  uint16_t addr = (((uint16_t) higher) << 8) | lower;
  uint8_t value = readMemory(addr);
  a_reg = value;
  pc += LD_ADDR_TO_REG_ARGLEN;
}

void doAccToAddr()
{
  uint8_t lower = readMemory(pc + 1);
  uint8_t higher = readMemory(pc + 2);
  uint16_t addr = (((uint16_t) higher) << 8) | lower;
  writeMemory(addr, a_reg);
  pc += LD_ADDR_TO_REG_ARGLEN;
}

// Provide access to working ram over C
void doACIndirect()
{
  uint16_t addr = 0xff00 + c_reg;
  a_reg = readMemory(addr);
  pc += LD_A_C_ARGLEN;
}

void doCIndirectA()
{
  uint16_t addr = 0xff00 + c_reg;
  writeMemory(addr, a_reg);
  pc += LD_A_C_ARGLEN;
}


// Increment, decrement HL, otherwise normal memory op
void doHLDtoA()
{
  doRegisterIndirectToRegister(LD_A_HL);
  uint16_t higher = ((uint16_t) h_reg) << 8;
  uint8_t lower = l_reg;
  higher |= lower;
  higher--;
  h_reg = (uint8_t) (higher >> 8);
  l_reg = (uint8_t) higher;
  pc += LD_DEC_A_ARGLEN;
}

void doAtoHLD()
{
  doRegisterToRegisterIndirect(LD_HL_A);
  uint16_t higher = ((uint16_t) h_reg) << 8;
  uint8_t lower = l_reg;
  higher |= lower;
  higher--;
  h_reg = (uint8_t) (higher >> 8);
  l_reg = (uint8_t) higher;
  pc += LD_DEC_A_ARGLEN;
}

void doHLItoA()
{
  doRegisterIndirectToRegister(LD_A_HL);
  uint16_t higher = ((uint16_t) h_reg) << 8;
  uint8_t lower = l_reg;
  higher |= lower;
  higher++;
  h_reg = (uint8_t) (higher >> 8);
  l_reg = (uint8_t) higher;
  pc += LD_DEC_A_ARGLEN;
}

void doAtoHLI()
{
  doRegisterToRegisterIndirect(LD_HL_A);
  uint16_t higher = ((uint16_t) h_reg) << 8;
  uint8_t lower = l_reg;
  higher |= lower;
  higher++;
  h_reg = (uint8_t) (higher >> 8);
  l_reg = (uint8_t) higher;
  pc += LD_DEC_A_ARGLEN;
}

// Access to 0xff00 + n
void doAa8p()
{
  uint8_t offset = readMemory(pc + 1);
  uint16_t addr = 0xff00 + offset;
  writeMemory(addr, a_reg);
  pc += LD_A_a8p_ARGLEN;
}

// Read from 0xff00 + n
void doa8pA()
{
  uint8_t offset = readMemory(pc + 1);
  uint16_t addr = 0xff00 + offset;
  a_reg = readMemory(addr);
  pc += LD_A_a8p_ARGLEN;
}

void doLoadReg16b(uint8_t instruction)
{
  // Further decoding, little endian
  uint8_t high = readMemory(pc + 2);
  uint8_t low = readMemory(pc + 1);
  switch (instruction)
  {
    case LD_BC_d16:
      b_reg = high;
      c_reg = low;
      break;
    case LD_DE_d16:
      d_reg = high;
      e_reg = low;
      break;
    case LD_HL_d16:
      h_reg = high;
      l_reg = low;
      break;
    case LD_SP_d16:
      // Combine low and high
      stack_ptr = (((uint16_t) high) << 8) | low;
      break;
  }
  pc += LD_COMB_ARGLEN;
}

void doLoadHLSP()
{
  stack_ptr = (((uint16_t) h_reg) << 8) | l_reg;
  pc += LD_REG_SP_ARGLEN;
}

void doLoadHLSPN()
{
  uint16_t offset = readMemory(pc + 1);
  uint16_t value = stack_ptr + offset;
  // This instruction affects the Z H C S flags
  h_reg = (uint8_t) (value >> 8);
  l_reg = (uint8_t) value;
  flags = 0;
  // Check for carry
  if (stack_ptr + offset > 0xffff)
    flags |= 0x20;
  // Check for half carry
  if ((stack_ptr & 0xfff) + (offset & 0xfff) > 0xfff)
    flags |= 0x10;
  pc += LDHL_ARGLEN;
}

void doLoadSP16()
{
  uint16_t addr_low = readMemory(pc + 1);
  uint16_t addr_high = readMemory(pc + 2);
  uint16_t addr = (addr_high << 8) | addr_low;
  writeMemory(addr, stack_ptr);
  pc += LD_d16_SP_ARGLEN;
}

void doPush(uint8_t instruction)
{
  switch(instruction)
  {
    case PUSH_AF:
      // Save both regs on stack, decrement twice
      writeMemory(stack_ptr, a_reg);
      stack_ptr -= 1;
      writeMemory(stack_ptr, flags);
      stack_ptr -= 1;
      break;
    case PUSH_BC:
      writeMemory(stack_ptr, b_reg);
      stack_ptr -= 1;
      writeMemory(stack_ptr, c_reg);
      stack_ptr -= 1;
      break;
    case PUSH_DE: 
      writeMemory(stack_ptr, d_reg);
      stack_ptr -= 1;
      writeMemory(stack_ptr, e_reg);
      stack_ptr -= 1;
      break;
    case PUSH_HL:
      writeMemory(stack_ptr, h_reg);
      stack_ptr -= 1;
      writeMemory(stack_ptr, l_reg);
      stack_ptr -= 1;
      break;
  }
  pc += PUSH_REGS_ARGLEN;
}

void doPop(uint8_t instruction)
{
  switch(instruction)
  {
    // Determine registers to pop into
    case POP_AF:
      stack_ptr += 1;
      flags = readMemory(stack_ptr);
      stack_ptr += 1;
      a_reg = readMemory(stack_ptr);
      break;
    case POP_BC:
      stack_ptr += 1;
      c_reg = readMemory(stack_ptr);
      stack_ptr += 1;
      b_reg = readMemory(stack_ptr);
      break;
    case POP_DE: 
      stack_ptr += 1;
      e_reg = readMemory(stack_ptr);
      stack_ptr += 1;
      d_reg = readMemory(stack_ptr);
      break;
    case POP_HL:
      stack_ptr += 1;
      l_reg = readMemory(stack_ptr);
      stack_ptr += 1;
      h_reg = readMemory(stack_ptr);
      break;
  }
 pc += POP_REGS_ARGLEN;
}

void add(uint8_t instruction)
{
  uint8_t summand = 0;
  uint16_t addr = 0;
  // Determine summand
  switch(instruction)
  {
    case ADD_AA:
      summand = a_reg;
      break;
    case ADD_AB:
      summand = b_reg;
      break;
    case ADD_AC:
      summand = c_reg;
      break;
    case ADD_AD:
      summand = d_reg;
      break;
    case ADD_AE:
      summand = e_reg;
      break;
    case ADD_AH:
      summand = h_reg;
      break;
    case ADD_AL: 
      summand = l_reg;
      break;
    case ADD_A_IND:
      addr = (((uint16_t) h_reg) << 8) | l_reg;
      summand = readMemory(addr);
      break;
    case ADD_A_d8:
      summand = readMemory(pc + 1);
      break;
  }
  // Set flags
  // Carry flag
  if (((uint16_t) a_reg) + summand > 0xff)
  {
    flags |= 0x10;
  }
  else
  {
    flags &= ~(0x10);
  }
  // Clear the n flag
  flags &= ~(0x40);
  // Half carry flag
  if (((a_reg & 0xf) + (summand & 0xf)) & 0x10) 
  {
    flags |= 0x20;
  }
  else
  {
    flags &= ~(0x20);
  }
  if (a_reg + summand == 0)
  {
    flags |= 0x80;
  }
  else
  {
    flags &= ~(0x80);
  }
  a_reg += summand;
  if (instruction != ADD_A_d8)
  {
    pc += ALU_REG_ARGLEN;
  }
  else
  {
    pc += ALU_IMM_ARGLEN;
  }
}

void adc(uint8_t instruction)
{
  uint8_t summand = 0;
  uint16_t addr = 0;
  // Determine summand
  switch(instruction)
  {
    case ADC_AA:
      summand = a_reg;
      break;
    case ADC_AB:
      summand = b_reg;
      break;
    case ADC_AC:
      summand = c_reg;
      break;
    case ADC_AD:
      summand = d_reg;
      break;
    case ADC_AE:
      summand = e_reg;
      break;
    case ADC_AH:
      summand = h_reg;
      break;
    case ADC_AL: 
      summand = l_reg;
      break;
    case ADC_A_IND:
      addr = (((uint16_t) h_reg) << 8) | l_reg;
      summand = readMemory(addr);
      break;
    case ADC_A_d8:
      summand = readMemory(pc + 1);
      break;
  }
  // Add carry flag
  if (flags & 0x10)
    summand += 1;
  // Set flags
  // Carry flag
  if (((uint16_t) a_reg) + summand > 0xff)
  {
    flags |= 0x10;
  }
  else
  {
    flags &= ~(0x10);
  }
  // Clear the n flag
  flags &= ~(0x40);
  // Half carry flag
  if (((a_reg & 0xf) + (summand & 0xf)) & 0x10) 
  {
    flags |= 0x20;
  }
  else
  {
    flags &= ~(0x20);
  }
  if (a_reg + summand == 0)
  {
    flags |= 0x80;
  }
  else
  {
    flags &= ~(0x80);
  }
  a_reg += summand;
  if (instruction != ADC_A_d8)
  {
    pc += ALU_REG_ARGLEN;
  }
  else
  {
    pc += ALU_IMM_ARGLEN;
  }
}

void sub(uint8_t instruction)
{
  uint8_t arg = 0;
  uint16_t addr = 0;
  // Determine arg
  switch(instruction)
  {
    case SUB_AA:
      arg = a_reg;
      break;
    case SUB_AB:
      arg = b_reg;
      break;
    case SUB_AC:
      arg = c_reg;
      break;
    case SUB_AD:
      arg = d_reg;
      break;
    case SUB_AE:
      arg = e_reg;
      break;
    case SUB_AH:
      arg = h_reg;
      break;
    case SUB_AL: 
      arg = l_reg;
      break;
    case SUB_A_IND:
      addr = (((uint16_t) h_reg) << 8) | l_reg;
      arg = readMemory(addr);
      break;
    case SUB_A_d8:
      arg = readMemory(pc + 1);
      break;
  }
  // Set flags
  // Carry flag
  if ((int)(a_reg) - (int)(arg) < 0)
  {
    flags |= 0x10;
  }
  else
  {
    flags &= ~(0x10);
  }
  // Set the n flag
  flags |= 0x40;
  // Half carry flag
  if ((int)(a_reg & 0xf) - (int)(arg & 0xf) < 0)
  {
    flags |= 0x20;
  }
  else
  {
    flags &= ~(0x20);
  }
  if (a_reg - arg == 0)
  {
    flags |= 0x80;
  }
  else
  {
    flags &= ~(0x80);
  }
  a_reg -= arg;
  if (instruction != SUB_A_d8)
  {
    pc += ALU_REG_ARGLEN;
  }
  else
  {
    pc += ALU_IMM_ARGLEN;
  }
}

void sbc(uint8_t instruction)
{
  uint8_t arg = 0;
  uint16_t addr = 0;
  // Determine arg
  switch(instruction)
  {
    case SBC_AA:
      arg = a_reg;
      break;
    case SBC_AB:
      arg = b_reg;
      break;
    case SBC_AC:
      arg = c_reg;
      break;
    case SBC_AD:
      arg = d_reg;
      break;
    case SBC_AE:
      arg = e_reg;
      break;
    case SBC_AH:
      arg = h_reg;
      break;
    case SBC_AL: 
      arg = l_reg;
      break;
    case SBC_A_IND:
      addr = (((uint16_t) h_reg) << 8) | l_reg;
      arg = readMemory(addr);
      break;
  }
  // Add carry flag
  if (flags & 0x10)
    arg += 1;
  // Flags
  if ((int)(a_reg) - (int)(arg) < 0)
  {
    flags |= 0x10;
  }
  else
  {
    flags &= ~(0x10);
  }
  // Set the n flag
  flags |= 0x40;
  // Half carry flag
  if ((int)(a_reg & 0xf) - (int)(arg & 0xf) < 0)
  {
    flags |= 0x20;
  }
  else
  {
    flags &= ~(0x20);
  }
  if (a_reg - arg == 0)
  {
    flags |= 0x80;
  }
  else
  {
    flags &= ~(0x80);
  }
  a_reg -= arg;
  pc += ALU_REG_ARGLEN;
}

void land(uint8_t instruction)
{
  uint8_t arg = 0;
  uint16_t addr = 0;
  // Determine arg
  switch(instruction)
  {
    case AND_AA:
      arg = a_reg;
      break;
    case AND_AB:
      arg = b_reg;
      break;
    case AND_AC:
      arg = c_reg;
      break;
    case AND_AD:
      arg = d_reg;
      break;
    case AND_AE:
      arg = e_reg;
      break;
    case AND_AH:
      arg = h_reg;
      break;
    case AND_AL: 
      arg = l_reg;
      break;
    case AND_A_IND:
      addr = (((uint16_t) h_reg) << 8) | l_reg;
      arg = readMemory(addr);
      break;
    case AND_A_d8:
      arg = readMemory(pc + 1);
      break;
  }
  // Flags
  flags = 0;
  if (!(a_reg & arg))
  {
    flags |= 0x80;
  }
  flags |= 0x20;
  a_reg &= arg;
  if (instruction != AND_A_d8)
  {
    pc += ALU_REG_ARGLEN;
  }
  else
  {
    pc += ALU_IMM_ARGLEN;
  }
}

void lor(uint8_t instruction)
{
  uint8_t arg = 0;
  uint16_t addr = 0;
  // Determine arg
  switch(instruction)
  {
    case OR_AA:
      arg = a_reg;
      break;
    case OR_AB:
      arg = b_reg;
      break;
    case OR_AC:
      arg = c_reg;
      break;
    case OR_AD:
      arg = d_reg;
      break;
    case OR_AE:
      arg = e_reg;
      break;
    case OR_AH:
      arg = h_reg;
      break;
    case OR_AL: 
      arg = l_reg;
      break;
    case OR_A_IND:
      addr = (((uint16_t) h_reg) << 8) | l_reg;
      arg = readMemory(addr);
      break;
    case OR_A_d8:
      arg = readMemory(pc + 1);
      break;
  }
  // Flags
  flags = 0;
  if (!(a_reg | arg))
  {
    flags |= 0x80;
  }
  a_reg |= arg;
  if (instruction != OR_A_d8)
  {
    pc += ALU_REG_ARGLEN;
  }
  else
  {
    pc += ALU_IMM_ARGLEN;
  }
}

void lxor(uint8_t instruction)
{
  uint8_t arg = 0;
  uint16_t addr = 0;
  // Determine arg
  switch(instruction)
  {
    case XOR_AA:
      arg = a_reg;
      break;
    case XOR_AB:
      arg = b_reg;
      break;
    case XOR_AC:
      arg = c_reg;
      break;
    case XOR_AD:
      arg = d_reg;
      break;
    case XOR_AE:
      arg = e_reg;
      break;
    case XOR_AH:
      arg = h_reg;
      break;
    case XOR_AL: 
      arg = l_reg;
      break;
    case XOR_A_IND:
      addr = (((uint16_t) h_reg) << 8) | l_reg;
      arg = readMemory(addr);
      break;
    case XOR_A_d8:
      arg = readMemory(pc + 1);
      break;
  }
  // Flags
  flags = 0;
  if (!(a_reg ^ arg))
  {
    flags |= 0x80;
  }
  a_reg ^= arg;
  if (instruction != XOR_A_d8)
  {
    pc += ALU_REG_ARGLEN;
  }
  else
  {
    pc += ALU_IMM_ARGLEN;
  }
}
