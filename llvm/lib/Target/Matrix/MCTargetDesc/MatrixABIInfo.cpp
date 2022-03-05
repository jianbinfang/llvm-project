//===---- MatrixABIInfo.cpp - Information about MATRIX ABI's ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MatrixConfig.h"

#include "MatrixABIInfo.h"
#include "MatrixRegisterInfo.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

static cl::opt<bool>
EnableMatrixS32Calls("matrix-s32-calls", cl::Hidden,
                    cl::desc("MATRIX S32 call: use stack only to pass arguments.\
                    "), cl::init(false));

namespace {
static const MCPhysReg O32IntRegs[4] = {Matrix::A0, Matrix::A1};
static const MCPhysReg S32IntRegs = {};
}

const ArrayRef<MCPhysReg> MatrixABIInfo::GetByValArgRegs() const {
  if (IsO32())
    return makeArrayRef(O32IntRegs);
  if (IsS32())
    return makeArrayRef(S32IntRegs);
  llvm_unreachable("Unhandled ABI");
}

const ArrayRef<MCPhysReg> MatrixABIInfo::GetVarArgRegs() const {
  if (IsO32())
    return makeArrayRef(O32IntRegs);
  if (IsS32())
    return makeArrayRef(S32IntRegs);
  llvm_unreachable("Unhandled ABI");
}

unsigned MatrixABIInfo::GetCalleeAllocdArgSizeInBytes(CallingConv::ID CC) const {
  if (IsO32())
    return CC != 0;
  if (IsS32())
    return 0;
  llvm_unreachable("Unhandled ABI");
}

MatrixABIInfo MatrixABIInfo::computeTargetABI() {
  MatrixABIInfo abi(ABI::Unknown);

  if (EnableMatrixS32Calls)
    abi = ABI::S32;
  else
    abi = ABI::O32;
  // Assert exactly one ABI was chosen.
  assert(abi.ThisABI != ABI::Unknown);

  return abi;
}

unsigned MatrixABIInfo::GetStackPtr() const {
  return Matrix::SP;
}

unsigned MatrixABIInfo::GetFramePtr() const {
  return Matrix::FP;
}

unsigned MatrixABIInfo::GetNullPtr() const {
  return Matrix::ZERO;
}

unsigned MatrixABIInfo::GetEhDataReg(unsigned I) const {
  static const unsigned EhDataReg[] = {
    Matrix::A0, Matrix::A1
  };

  return EhDataReg[I];
}

int MatrixABIInfo::EhDataRegSize() const {
  if (ThisABI == ABI::S32)
    return 0;
  else
    return 2;
}

