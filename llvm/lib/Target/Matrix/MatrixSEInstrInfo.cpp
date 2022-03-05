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

const MatrixInstrInfo *llvm::createMatrixSEInstrInfo(const MatrixSubtarget &STI) {
  return new MatrixSEInstrInfo(STI);
}

