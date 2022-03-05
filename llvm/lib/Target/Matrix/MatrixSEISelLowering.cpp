//===-- MatrixSEISelLowering.cpp - MatrixSE DAG Lowering Interface --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Subclass of MatrixTargetLowering specialized for matrix32.
//
//===----------------------------------------------------------------------===//
#include "MatrixMachineFunction.h"
#include "MatrixSEISelLowering.h"

#include "MatrixRegisterInfo.h"
#include "MatrixTargetMachine.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "matrix-isel"

static cl::opt<bool>
EnableMatrixTailCalls("enable-matrix-tail-calls", cl::Hidden,
                    cl::desc("MATRIX: Enable tail calls."), cl::init(false));

//@MatrixSETargetLowering {
MatrixSETargetLowering::MatrixSETargetLowering(const MatrixTargetMachine &TM,
                                           const MatrixSubtarget &STI)
    : MatrixTargetLowering(TM, STI) {
//@MatrixSETargetLowering body {
  // Set up the register classes
  addRegisterClass(MVT::i32, &Matrix::CPURegsRegClass);

// must, computeRegisterProperties - Once all of the register classes are 
//  added, this allows us to compute derived properties we expose.
  computeRegisterProperties(Subtarget.getRegisterInfo());
}

SDValue MatrixSETargetLowering::LowerOperation(SDValue Op,
                                             SelectionDAG &DAG) const {

  return MatrixTargetLowering::LowerOperation(Op, DAG);
}

const MatrixTargetLowering *
llvm::createMatrixSETargetLowering(const MatrixTargetMachine &TM,
                                 const MatrixSubtarget &STI) {
  return new MatrixSETargetLowering(TM, STI);
}

