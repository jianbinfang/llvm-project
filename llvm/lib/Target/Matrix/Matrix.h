//===-- Matrix.h - Top-level interface for Matrix representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM Matrix back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MATRIX_MATRIX_H
#define LLVM_LIB_TARGET_MATRIX_MATRIX_H

#include "MatrixConfig.h"
#include "MCTargetDesc/MatrixMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class MatrixTargetMachine;
  class FunctionPass;

} // end namespace llvm;

#endif

