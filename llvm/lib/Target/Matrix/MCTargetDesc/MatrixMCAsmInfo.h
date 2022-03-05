//===-- MatrixMCAsmInfo.h - Matrix Asm Info ------------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the MatrixMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MATRIX_MCTARGETDESC_MATRIXMCASMINFO_H
#define LLVM_LIB_TARGET_MATRIX_MCTARGETDESC_MATRIXMCASMINFO_H

#include "MatrixConfig.h"

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

  class MatrixMCAsmInfo : public MCAsmInfoELF {
    void anchor() override;
  public:
    explicit MatrixMCAsmInfo(const Triple &TheTriple);
  };

} // namespace llvm

#endif

