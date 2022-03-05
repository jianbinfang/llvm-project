//===-- MatrixSEISelDAGToDAG.cpp - A Dag to Dag Inst Selector for MatrixSE ----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Subclass of MatrixDAGToDAGISel specialized for matrix32.
//
//===----------------------------------------------------------------------===//

#include "MatrixSEISelDAGToDAG.h"

#include "MCTargetDesc/MatrixBaseInfo.h"
#include "Matrix.h"
#include "MatrixMachineFunction.h"
#include "MatrixRegisterInfo.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
using namespace llvm;

#define DEBUG_TYPE "matrix-isel"

bool MatrixSEDAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  Subtarget = &static_cast<const MatrixSubtarget &>(MF.getSubtarget());
  return MatrixDAGToDAGISel::runOnMachineFunction(MF);
}

void MatrixSEDAGToDAGISel::processFunctionAfterISel(MachineFunction &MF) {
}

//@selectNode
bool MatrixSEDAGToDAGISel::trySelect(SDNode *Node) {
  unsigned Opcode = Node->getOpcode();
  SDLoc DL(Node);

  ///
  // Instruction Selection not handled by the auto-generated
  // tablegen selection should be handled here.
  ///

  ///
  // Instruction Selection not handled by the auto-generated
  // tablegen selection should be handled here.
  ///
  EVT NodeTy = Node->getValueType(0);
  unsigned MultOpc;

  switch(Opcode) {
  default: break;

  }

  return false;
}

FunctionPass *llvm::createMatrixSEISelDag(MatrixTargetMachine &TM,
                                        CodeGenOpt::Level OptLevel) {
  return new MatrixSEDAGToDAGISel(TM, OptLevel);
}

