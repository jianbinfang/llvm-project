//===-- MatrixSEInstrInfo.h - Matrix32/64 Instruction Information ---*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_MATRIX_MATRIXSEINSTRINFO_H
#define LLVM_LIB_TARGET_MATRIX_MATRIXSEINSTRINFO_H

#include "MatrixConfig.h"

#include "MatrixInstrInfo.h"
#include "MatrixSERegisterInfo.h"
#include "MatrixMachineFunction.h"

namespace llvm {

class MatrixSEInstrInfo : public MatrixInstrInfo {
  const MatrixSERegisterInfo RI;

public:
  explicit MatrixSEInstrInfo(const MatrixSubtarget &STI);

  const MatrixRegisterInfo &getRegisterInfo() const override;

  
};

}

#endif

