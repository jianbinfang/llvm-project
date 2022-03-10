//===-- MatrixRegisterInfo.cpp - MATRIX Register Information -== --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the MATRIX implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "matrix-reg-info"

#include "MatrixRegisterInfo.h"

#include "Matrix.h"
#include "MatrixSubtarget.h"
#include "MatrixMachineFunction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

#define GET_REGINFO_TARGET_DESC
#include "MatrixGenRegisterInfo.inc"

using namespace llvm;

MatrixRegisterInfo::MatrixRegisterInfo(const MatrixSubtarget &ST)
  : MatrixGenRegisterInfo(Matrix::LR), Subtarget(ST) {}

//===----------------------------------------------------------------------===//
// Callee Saved Registers methods
//===----------------------------------------------------------------------===//
/// Matrix Callee Saved Registers
// In MatrixCallConv.td,
// def CSR_O32 : CalleeSavedRegs<(add LR, FP,
//                                   (sequence "S%u", 2, 0))>;
// llc create CSR_O32_SaveList and CSR_O32_RegMask from above defined.
const MCPhysReg *
MatrixRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_O32_SaveList;
}

const uint32_t *
MatrixRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID) const {
  return CSR_O32_RegMask; 
}

// pure virtual method
//@getReservedRegs {
BitVector MatrixRegisterInfo::
getReservedRegs(const MachineFunction &MF) const {
//@getReservedRegs body {
  static const uint16_t ReservedCPURegs[] = {
    Matrix::ZERO, Matrix::AT, Matrix::SP, Matrix::LR, /*Matrix::SW, */Matrix::PC
  };
  BitVector Reserved(getNumRegs());

  for (unsigned I = 0; I < array_lengthof(ReservedCPURegs); ++I)
    Reserved.set(ReservedCPURegs[I]);

  return Reserved;
}

//@eliminateFrameIndex {
//- If no eliminateFrameIndex(), it will hang on run. 
// pure virtual method
// FrameIndex represent objects inside a abstract stack.
// We must replace FrameIndex with an stack/frame pointer
// direct reference.
void MatrixRegisterInfo::
eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                    unsigned FIOperandNum, RegScavenger *RS) const {
  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  MatrixFunctionInfo *MatrixFI = MF.getInfo<MatrixFunctionInfo>();

  unsigned i = 0;
  while (!MI.getOperand(i).isFI()) {
    ++i;
    assert(i < MI.getNumOperands() &&
           "Instr doesn't have FrameIndex operand!");
  }

  LLVM_DEBUG(errs() << "\nFunction : " << MF.getFunction().getName() << "\n";
             errs() << "<--------->\n" << MI);

  int FrameIndex = MI.getOperand(i).getIndex();
  uint64_t stackSize = MF.getFrameInfo().getStackSize();
  int64_t spOffset = MF.getFrameInfo().getObjectOffset(FrameIndex);

  LLVM_DEBUG(errs() << "FrameIndex : " << FrameIndex << "\n"
                    << "spOffset   : " << spOffset << "\n"
                    << "stackSize  : " << stackSize << "\n");

  const std::vector<CalleeSavedInfo> &CSI = MFI.getCalleeSavedInfo();
  int MinCSFI = 0;
  int MaxCSFI = -1;

  if (CSI.size()) {
    MinCSFI = CSI[0].getFrameIdx();
    MaxCSFI = CSI[CSI.size() - 1].getFrameIdx();
  }

  // The following stack frame objects are always referenced relative to $sp:
  //  1. Outgoing arguments.
  //  2. Pointer to dynamically allocated stack space.
  //  3. Locations for callee-saved registers.
  // Everything else is referenced relative to whatever register
  // getFrameRegister() returns.
  unsigned FrameReg;

  FrameReg = Matrix::SP;

  // Calculate final offset.
  // - There is no need to change the offset if the frame object is one of the
  //   following: an outgoing argument, pointer to a dynamically allocated
  //   stack space or a $gp restore location,
  // - If the frame object is any of the following, its offset must be adjusted
  //   by adding the size of the stack:
  //   incoming argument, callee-saved register location or local variable.
  int64_t Offset;
    Offset = spOffset + (int64_t)stackSize;

  Offset    += MI.getOperand(i+1).getImm();

  LLVM_DEBUG(errs() << "Offset     : " << Offset << "\n" << "<--------->\n");

  // If MI is not a debug value, make sure Offset fits in the 16-bit immediate
  // field.
  if (!MI.isDebugValue() && !isInt<16>(Offset)) {
    errs() << "!!!ERROR!!! Not support large frame over 16-bit at this point.\n"
           << "Though CH3_5 support it."
           << "Reference: "
               "http://jonathan2251.github.io/lbd/backendstructure.html#large-stack\n"
           << "However the CH9_3, dynamic-stack-allocation-support bring instruction "
              "move $fp, $sp that make it complicated in coding against the tutoral "
              "purpose of Matrix.\n"
           << "Reference: "
               "http://jonathan2251.github.io/lbd/funccall.html#dynamic-stack-allocation-support\n";
    assert(0 && "(!MI.isDebugValue() && !isInt<16>(Offset))");
  }

  MI.getOperand(i).ChangeToRegister(FrameReg, false);
  MI.getOperand(i+1).ChangeToImmediate(Offset);
}
//}

bool
MatrixRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
MatrixRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

// pure virtual method
Register MatrixRegisterInfo::
getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = MF.getSubtarget().getFrameLowering();
  return TFI->hasFP(MF) ? (Matrix::FP) :
                          (Matrix::SP);
}

