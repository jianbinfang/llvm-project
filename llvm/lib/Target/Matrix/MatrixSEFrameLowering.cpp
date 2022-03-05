//===-- MatrixSEFrameLowering.cpp - Matrix Frame Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Matrix implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "MatrixSEFrameLowering.h"

#include "MatrixMachineFunction.h"
#include "MatrixSEInstrInfo.h"
#include "MatrixSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

MatrixSEFrameLowering::MatrixSEFrameLowering(const MatrixSubtarget &STI)
    : MatrixFrameLowering(STI, STI.stackAlignment()) {}

//@emitPrologue {
void MatrixSEFrameLowering::emitPrologue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {
}
//}

//@emitEpilogue {
void MatrixSEFrameLowering::emitEpilogue(MachineFunction &MF,
                                 MachineBasicBlock &MBB) const {
}
//}

const MatrixFrameLowering *
llvm::createMatrixSEFrameLowering(const MatrixSubtarget &ST) {
  return new MatrixSEFrameLowering(ST);
}

