//===-- MatrixISelLowering.cpp - Matrix DAG Lowering Implementation -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Matrix uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//
#include "MatrixISelLowering.h"

#include "MCTargetDesc/MatrixBaseInfo.h"
#include "MatrixMachineFunction.h"
#include "MatrixTargetMachine.h"
#include "MatrixTargetObjectFile.h"
#include "MatrixSubtarget.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "matrix-lower"

//@3_1 1 {
const char *MatrixTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case MatrixISD::JmpLink:           return "MatrixISD::JmpLink";
  case MatrixISD::TailCall:          return "MatrixISD::TailCall";
  case MatrixISD::Hi:                return "MatrixISD::Hi";
  case MatrixISD::Lo:                return "MatrixISD::Lo";
  case MatrixISD::GPRel:             return "MatrixISD::GPRel";
  case MatrixISD::Ret:               return "MatrixISD::Ret";
  case MatrixISD::EH_RETURN:         return "MatrixISD::EH_RETURN";
  case MatrixISD::DivRem:            return "MatrixISD::DivRem";
  case MatrixISD::DivRemU:           return "MatrixISD::DivRemU";
  case MatrixISD::Wrapper:           return "MatrixISD::Wrapper";
  default:                         return NULL;
  }
}
//@3_1 1 }

//@MatrixTargetLowering {
MatrixTargetLowering::MatrixTargetLowering(const MatrixTargetMachine &TM,
                                       const MatrixSubtarget &STI)
    : TargetLowering(TM), Subtarget(STI), ABI(TM.getABI()) {

  // Matrix Custom Operations

  // Operations not directly supported by Matrix.

//- Set .align 2
// It will emit .align 2 later
  setMinFunctionAlignment(Align(2));

}

const MatrixTargetLowering *MatrixTargetLowering::create(const MatrixTargetMachine &TM,
                                                     const MatrixSubtarget &STI) {
  return llvm::createMatrixSETargetLowering(TM, STI);
}

//===----------------------------------------------------------------------===//
//  Lower helper functions
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Misc Lower Operation implementation
//===----------------------------------------------------------------------===//

#include "MatrixGenCallingConv.inc"

//===----------------------------------------------------------------------===//
//@            Formal Arguments Calling Convention Implementation
//===----------------------------------------------------------------------===//

//@LowerFormalArguments {
/// LowerFormalArguments - transform physical registers into virtual registers
/// and generate load operations for arguments places on the stack.
SDValue
MatrixTargetLowering::LowerFormalArguments(SDValue Chain,
                                         CallingConv::ID CallConv,
                                         bool IsVarArg,
                                         const SmallVectorImpl<ISD::InputArg> &Ins,
                                         const SDLoc &DL, SelectionDAG &DAG,
                                         SmallVectorImpl<SDValue> &InVals)
                                          const {

  return Chain;
}
// @LowerFormalArguments }

//===----------------------------------------------------------------------===//
//@              Return Value Calling Convention Implementation
//===----------------------------------------------------------------------===//

SDValue
MatrixTargetLowering::LowerReturn(SDValue Chain,
                                CallingConv::ID CallConv, bool IsVarArg,
                                const SmallVectorImpl<ISD::OutputArg> &Outs,
                                const SmallVectorImpl<SDValue> &OutVals,
                                const SDLoc &DL, SelectionDAG &DAG) const {
  return DAG.getNode(MatrixISD::Ret, DL, MVT::Other,
                     Chain, DAG.getRegister(Matrix::LR, MVT::i32));
}

