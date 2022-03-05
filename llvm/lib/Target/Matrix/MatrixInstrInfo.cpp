//===-- MatrixInstrInfo.cpp - Matrix Instruction Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Matrix implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "MatrixInstrInfo.h"

#include "MatrixTargetMachine.h"
#include "MatrixMachineFunction.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "MatrixGenInstrInfo.inc"

// Pin the vtable to this file.
void MatrixInstrInfo::anchor() {}

//@MatrixInstrInfo {
MatrixInstrInfo::MatrixInstrInfo(const MatrixSubtarget &STI)
    : 
      Subtarget(STI) {}

const MatrixInstrInfo *MatrixInstrInfo::create(MatrixSubtarget &STI) {
  return llvm::createMatrixSEInstrInfo(STI);
}

//@GetInstSizeInBytes {
/// Return the number of bytes of code the specified instruction may be.
unsigned MatrixInstrInfo::GetInstSizeInBytes(const MachineInstr &MI) const {
//@GetInstSizeInBytes - body
  switch (MI.getOpcode()) {
  default:
    return MI.getDesc().getSize();
  }
}

