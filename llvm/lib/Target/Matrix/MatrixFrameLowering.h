//===-- MatrixFrameLowering.h - Define frame lowering for Matrix ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_LIB_TARGET_MATRIX_MATRIXFRAMELOWERING_H
#define LLVM_LIB_TARGET_MATRIX_MATRIXFRAMELOWERING_H

#include "MatrixConfig.h"

#include "Matrix.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
  class MatrixSubtarget;

class MatrixFrameLowering : public TargetFrameLowering {
protected:
  const MatrixSubtarget &STI;

public:
  explicit MatrixFrameLowering(const MatrixSubtarget &sti, unsigned Alignment)
    : TargetFrameLowering(StackGrowsDown, Align(Alignment), 0, Align(Alignment)),
      STI(sti) {
  }

  static const MatrixFrameLowering *create(const MatrixSubtarget &ST);

  bool hasFP(const MachineFunction &MF) const override;

};

/// Create MatrixFrameLowering objects.
const MatrixFrameLowering *createMatrixSEFrameLowering(const MatrixSubtarget &ST);

} // End llvm namespace

#endif

