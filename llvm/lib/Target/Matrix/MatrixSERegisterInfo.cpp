//===-- MatrixSERegisterInfo.cpp - MATRIX Register Information ------== -------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the MATRIX implementation of the TargetRegisterInfo
// class.
//
//===----------------------------------------------------------------------===//

#include "MatrixSERegisterInfo.h"

using namespace llvm;

#define DEBUG_TYPE "matrix-reg-info"

MatrixSERegisterInfo::MatrixSERegisterInfo(const MatrixSubtarget &ST)
  : MatrixRegisterInfo(ST) {}

const TargetRegisterClass *
MatrixSERegisterInfo::intRegClass(unsigned Size) const {
  return &Matrix::CPURegsRegClass;
}

