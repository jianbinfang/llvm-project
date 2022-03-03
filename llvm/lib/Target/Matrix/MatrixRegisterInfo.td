//===-- MatrixRegisterInfo.td - Matrix Register defs -----------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the MATRIX register file
//===----------------------------------------------------------------------===//

// We have banks of 16 registers each.
class MatrixReg<bits<16> Enc, string n> : Register<n> {
  // For tablegen(... -gen-emitter)  in CMakeLists.txt
  let HWEncoding = Enc;
  
  let Namespace = "Matrix";
}

// Matrix CPU Registers
class MatrixGPRReg<bits<16> Enc, string n> : MatrixReg<Enc, n>;

// Co-processor 0 Registers
class MatrixC0Reg<bits<16> Enc, string n> : MatrixReg<Enc, n>;

//===----------------------------------------------------------------------===//
//@Registers
//===----------------------------------------------------------------------===//
// The register string, such as "9" or "gp" will show on "llvm-objdump -d"
//@ All registers definition
let Namespace = "Matrix" in {
  //@ General Purpose Registers
  def ZERO : MatrixGPRReg<0,  "zero">, DwarfRegNum<[0]>;
  def AT   : MatrixGPRReg<1,  "1">,    DwarfRegNum<[1]>;
  def V0   : MatrixGPRReg<2,  "2">,    DwarfRegNum<[2]>;
  def V1   : MatrixGPRReg<3,  "3">,    DwarfRegNum<[3]>;
  def A0   : MatrixGPRReg<4,  "4">,    DwarfRegNum<[4]>;
  def A1   : MatrixGPRReg<5,  "5">,    DwarfRegNum<[5]>;
  def T9   : MatrixGPRReg<6,  "t9">,   DwarfRegNum<[6]>;
  def T0   : MatrixGPRReg<7,  "7">,    DwarfRegNum<[7]>;
  def T1   : MatrixGPRReg<8,  "8">,    DwarfRegNum<[8]>;
  def S0   : MatrixGPRReg<9,  "9">,    DwarfRegNum<[9]>;
  def S1   : MatrixGPRReg<10, "10">,   DwarfRegNum<[10]>;
  def GP   : MatrixGPRReg<11, "gp">,   DwarfRegNum<[11]>;
  def FP   : MatrixGPRReg<12, "fp">,   DwarfRegNum<[12]>;
  def SP   : MatrixGPRReg<13, "sp">,   DwarfRegNum<[13]>;
  def LR   : MatrixGPRReg<14, "lr">,   DwarfRegNum<[14]>;
  def SW   : MatrixGPRReg<15, "sw">,   DwarfRegNum<[15]>;
//  def MAR  : Register< 16, "mar">,  DwarfRegNum<[16]>;
//  def MDR  : Register< 17, "mdr">,  DwarfRegNum<[17]>;

  def PC   : MatrixC0Reg<0, "pc">,  DwarfRegNum<[20]>;
  def EPC  : MatrixC0Reg<1, "epc">, DwarfRegNum<[21]>;
}

//===----------------------------------------------------------------------===//
//@Register Classes
//===----------------------------------------------------------------------===//

def CPURegs : RegisterClass<"Matrix", [i32], 32, (add
  // Reserved
  ZERO, AT, 
  // Return Values and Arguments
  V0, V1, A0, A1, 
  // Not preserved across procedure calls
  T9, T0, T1,
  // Callee save
  S0, S1,
  // Reserved
  GP, FP, 
  SP, LR, SW)>;

//@Status Registers class
def SR     : RegisterClass<"Matrix", [i32], 32, (add SW)>;

//@Co-processor 0 Registers class
def C0Regs : RegisterClass<"Matrix", [i32], 32, (add PC, EPC)>;

