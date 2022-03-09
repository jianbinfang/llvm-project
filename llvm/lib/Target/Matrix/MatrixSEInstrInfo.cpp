//===-- MatrixSEInstrInfo.cpp - Matrix32/64 Instruction Information -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Matrix32/64 implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "MatrixSEInstrInfo.h"

#include "InstPrinter/MatrixInstPrinter.h"
#include "MatrixMachineFunction.h"
#include "MatrixTargetMachine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

MatrixSEInstrInfo::MatrixSEInstrInfo(const MatrixSubtarget &STI)
    : MatrixInstrInfo(STI),
      RI(STI) {}

const MatrixRegisterInfo &MatrixSEInstrInfo::getRegisterInfo() const {
  return RI;
}

//@expandPostRAPseudo
/// Expand Pseudo instructions into real backend instructions
bool MatrixSEInstrInfo::expandPostRAPseudo(MachineInstr &MI) const {
//@expandPostRAPseudo-body
  MachineBasicBlock &MBB = *MI.getParent();

  switch (MI.getDesc().getOpcode()) {
  default:
    return false;
  case Matrix::RetLR:
    expandRetLR(MBB, MI);
    break;
  }

  MBB.erase(MI);
  return true;
}

void MatrixSEInstrInfo::expandRetLR(MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator I) const {
  BuildMI(MBB, I, I->getDebugLoc(), get(Matrix::RET)).addReg(Matrix::LR);
}

const MatrixInstrInfo *llvm::createMatrixSEInstrInfo(const MatrixSubtarget &STI) {
  return new MatrixSEInstrInfo(STI);
}

