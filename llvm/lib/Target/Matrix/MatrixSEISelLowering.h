//===-- MatrixISEISelLowering.h - MatrixISE DAG Lowering Interface ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Subclass of MatrixITargetLowering specialized for matrix32/64.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MATRIX_MATRIXSEISELLOWERING_H
#define LLVM_LIB_TARGET_MATRIX_MATRIXSEISELLOWERING_H

#include "MatrixConfig.h"

#include "MatrixISelLowering.h"
#include "MatrixRegisterInfo.h"

namespace llvm {
  class MatrixSETargetLowering : public MatrixTargetLowering  {
  public:
    explicit MatrixSETargetLowering(const MatrixTargetMachine &TM,
                                  const MatrixSubtarget &STI);

    SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;
  private:
  };
}

#endif // MatrixISEISELLOWERING_H

