//===-- MatrixSEFrameLowering.h - Matrix32/64 frame lowering --------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_MATRIX_MATRIXSEFRAMELOWERING_H
#define LLVM_LIB_TARGET_MATRIX_MATRIXSEFRAMELOWERING_H

#include "MatrixConfig.h"

#include "MatrixFrameLowering.h"

namespace llvm {

class MatrixSEFrameLowering : public MatrixFrameLowering {
public:
  explicit MatrixSEFrameLowering(const MatrixSubtarget &STI);

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

};

} // End llvm namespace

#endif

