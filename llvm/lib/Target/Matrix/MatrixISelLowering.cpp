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
  MachineFunction &MF = DAG.getMachineFunction();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  MatrixFunctionInfo *MatrixFI = MF.getInfo<MatrixFunctionInfo>();

  MatrixFI->setVarArgsFrameIndex(0);

  // Assign locations to all of the incoming arguments.
  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(),
                 ArgLocs, *DAG.getContext());
  MatrixCC MatrixCCInfo(CallConv, ABI.IsO32(), 
                    CCInfo);

  MatrixFI->setFormalArgInfo(CCInfo.getNextStackOffset(),
                           MatrixCCInfo.hasByValArg());

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
  // CCValAssign - represent the assignment of
  // the return value to a location
  SmallVector<CCValAssign, 16> RVLocs;
  MachineFunction &MF = DAG.getMachineFunction();

  // CCState - Info about the registers and stack slot.
  CCState CCInfo(CallConv, IsVarArg, MF, RVLocs,
                 *DAG.getContext());
  MatrixCC MatrixCCInfo(CallConv, ABI.IsO32(), 
                    CCInfo);

  // Analyze return values.
  MatrixCCInfo.analyzeReturn(Outs, Subtarget.abiUsesSoftFloat(),
                           MF.getFunction().getReturnType());

  SDValue Flag;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  // Copy the result values into the output registers.
  for (unsigned i = 0; i != RVLocs.size(); ++i) {
    SDValue Val = OutVals[i];
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");

    if (RVLocs[i].getValVT() != RVLocs[i].getLocVT())
      Val = DAG.getNode(ISD::BITCAST, DL, RVLocs[i].getLocVT(), Val);

    Chain = DAG.getCopyToReg(Chain, DL, VA.getLocReg(), Val, Flag);

    // Guarantee that all emitted copies are stuck together with flags.
    Flag = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }

//@Ordinary struct type: 2 {
  // The matrix ABIs for returning structs by value requires that we copy
  // the sret argument into $v0 for the return. We saved the argument into
  // a virtual register in the entry block, so now we copy the value out
  // and into $v0.
  if (MF.getFunction().hasStructRetAttr()) {
    MatrixFunctionInfo *MatrixFI = MF.getInfo<MatrixFunctionInfo>();
    unsigned Reg = MatrixFI->getSRetReturnReg();

    if (!Reg)
      llvm_unreachable("sret virtual register not created in the entry block");
    SDValue Val =
        DAG.getCopyFromReg(Chain, DL, Reg, getPointerTy(DAG.getDataLayout()));
    unsigned V0 = Matrix::V0;

    Chain = DAG.getCopyToReg(Chain, DL, V0, Val, Flag);
    Flag = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(V0, getPointerTy(DAG.getDataLayout())));
  }
//@Ordinary struct type: 2 }

  RetOps[0] = Chain;  // Update chain.

  // Add the flag if we have it.
  if (Flag.getNode())
    RetOps.push_back(Flag);

  // Return on Matrix is always a "ret $lr"
  return DAG.getNode(MatrixISD::Ret, DL, MVT::Other, RetOps);
}

MatrixTargetLowering::MatrixCC::MatrixCC(
  CallingConv::ID CC, bool IsO32_, CCState &Info,
  MatrixCC::SpecialCallingConvType SpecialCallingConv_)
  : CCInfo(Info), CallConv(CC), IsO32(IsO32_) {
  // Pre-allocate reserved argument area.
  CCInfo.AllocateStack(reservedArgArea(), Align(1));
}

template<typename Ty>
void MatrixTargetLowering::MatrixCC::
analyzeReturn(const SmallVectorImpl<Ty> &RetVals, bool IsSoftFloat,
              const SDNode *CallNode, const Type *RetTy) const {
  CCAssignFn *Fn;

  Fn = RetCC_Matrix;

  for (unsigned I = 0, E = RetVals.size(); I < E; ++I) {
    MVT VT = RetVals[I].VT;
    ISD::ArgFlagsTy Flags = RetVals[I].Flags;
    MVT RegVT = this->getRegVT(VT, IsSoftFloat);

    if (Fn(I, VT, RegVT, CCValAssign::Full, Flags, this->CCInfo)) {
#ifndef NDEBUG
      dbgs() << "Call result #" << I << " has unhandled type "
             << EVT(VT).getEVTString() << '\n';
#endif
      llvm_unreachable(nullptr);
    }
  }
}

void MatrixTargetLowering::MatrixCC::
analyzeCallResult(const SmallVectorImpl<ISD::InputArg> &Ins, bool IsSoftFloat,
                  const SDNode *CallNode, const Type *RetTy) const {
  analyzeReturn(Ins, IsSoftFloat, CallNode, RetTy);
}

void MatrixTargetLowering::MatrixCC::
analyzeReturn(const SmallVectorImpl<ISD::OutputArg> &Outs, bool IsSoftFloat,
              const Type *RetTy) const {
  analyzeReturn(Outs, IsSoftFloat, nullptr, RetTy);
}

unsigned MatrixTargetLowering::MatrixCC::reservedArgArea() const {
  return (IsO32 && (CallConv != CallingConv::Fast)) ? 8 : 0;
}

MVT MatrixTargetLowering::MatrixCC::getRegVT(MVT VT,
                                         bool IsSoftFloat) const {
  if (IsSoftFloat || IsO32)
    return VT;

  return VT;
}

