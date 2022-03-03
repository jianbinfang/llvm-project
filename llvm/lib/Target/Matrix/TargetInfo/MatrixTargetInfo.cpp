//===-- MatrixTargetInfo.cpp - Matrix Target Implementation -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Matrix.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target llvm::TheMatrixTarget, llvm::TheMatrixelTarget;

extern "C" void LLVMInitializeMatrixTargetInfo() {
  RegisterTarget<Triple::matrix,
        /*HasJIT=*/true> X(TheMatrixTarget, "matrix", "MATRIX (32-bit big endian)", "Matrix");

  RegisterTarget<Triple::matrixel,
        /*HasJIT=*/true> Y(TheMatrixelTarget, "matrixel", "MATRIX (32-bit little endian)", "Matrix");
}

