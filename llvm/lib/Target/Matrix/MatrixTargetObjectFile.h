//===-- llvm/Target/MatrixTargetObjectFile.h - Matrix Object Info ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0TARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_CPU0_CPU0TARGETOBJECTFILE_H

#include "MatrixConfig.h"

#include "MatrixTargetMachine.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {
class MatrixTargetMachine;
  class MatrixTargetObjectFile : public TargetLoweringObjectFileELF {
    MCSection *SmallDataSection;
    MCSection *SmallBSSSection;
    const MatrixTargetMachine *TM;

  public:

    void Initialize(MCContext &Ctx, const TargetMachine &TM) override;

  };
} // end namespace llvm

#endif

