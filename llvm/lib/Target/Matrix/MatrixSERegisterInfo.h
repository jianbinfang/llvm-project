//===-- MatrixSERegisterInfo.h - Matrix32 Register Information ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Matrix32/64 implementation of the TargetRegisterInfo
// class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MATRIX_MATRIXSEREGISTERINFO_H
#define LLVM_LIB_TARGET_MATRIX_MATRIXSEREGISTERINFO_H

#include "MatrixConfig.h"

#include "MatrixRegisterInfo.h"

namespace llvm {
class MatrixSEInstrInfo;

class MatrixSERegisterInfo : public MatrixRegisterInfo {
public:
  MatrixSERegisterInfo(const MatrixSubtarget &Subtarget);

  const TargetRegisterClass *intRegClass(unsigned Size) const override;
};

} // end namespace llvm

#endif

