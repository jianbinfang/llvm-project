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

  void storeRegToStack(MachineBasicBlock &MBB,
                       MachineBasicBlock::iterator MI,
                       Register SrcReg, bool isKill, int FrameIndex,
                       const TargetRegisterClass *RC,
                       const TargetRegisterInfo *TRI,
                       int64_t Offset) const override;

  void loadRegFromStack(MachineBasicBlock &MBB,
                        MachineBasicBlock::iterator MI,
                        Register DestReg, int FrameIndex,
                        const TargetRegisterClass *RC,
                        const TargetRegisterInfo *TRI,
                        int64_t Offset) const override;

//@expandPostRAPseudo
  bool expandPostRAPseudo(MachineInstr &MI) const override;

  /// Adjust SP by Amount bytes.
  void adjustStackPtr(unsigned SP, int64_t Amount, MachineBasicBlock &MBB,
                      MachineBasicBlock::iterator I) const override;

  /// Emit a series of instructions to load an immediate. If NewImm is a
  /// non-NULL parameter, the last instruction is not emitted, but instead
  /// its immediate operand is returned in NewImm.
  unsigned loadImmediate(int64_t Imm, MachineBasicBlock &MBB,
                         MachineBasicBlock::iterator II, const DebugLoc &DL,
                         unsigned *NewImm) const;
private:
  void expandRetLR(MachineBasicBlock &MBB, MachineBasicBlock::iterator I) const;

  
};

}

#endif

