//===-- MatrixInstrInfo.h - Matrix Instruction Information ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Matrix implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MATRIX0_MATRIX0INSTRINFO_H
#define LLVM_LIB_TARGET_MATRIX0_MATRIX0INSTRINFO_H

#include "MatrixConfig.h"

#include "Matrix.h"
#include "MatrixRegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "MatrixGenInstrInfo.inc"

namespace llvm {

class MatrixInstrInfo : public MatrixGenInstrInfo {
  virtual void anchor();
protected:
  const MatrixSubtarget &Subtarget;
public:
  explicit MatrixInstrInfo(const MatrixSubtarget &STI);

  static const MatrixInstrInfo *create(MatrixSubtarget &STI);

  /// getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
  /// such, whenever a client has an instance of instruction info, it should
  /// always be able to get register info as well (through this method).
  ///
  virtual const MatrixRegisterInfo &getRegisterInfo() const = 0;

  /// Return the number of bytes of code the specified instruction may be.
  unsigned GetInstSizeInBytes(const MachineInstr &MI) const;

protected:
};
const MatrixInstrInfo *createMatrixSEInstrInfo(const MatrixSubtarget &STI);
}

#endif

