//===-- MatrixMCTargetDesc.h - Matrix Target Descriptions -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Matrix specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_MCTARGETDESC_CPU0MCTARGETDESC_H
#define LLVM_LIB_TARGET_CPU0_MCTARGETDESC_CPU0MCTARGETDESC_H

#include "MatrixConfig.h"
#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class Target;
class Triple;

extern Target TheMatrixTarget;
extern Target TheMatrixelTarget;

} // End llvm namespace

// Defines symbolic names for Matrix registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "MatrixGenRegisterInfo.inc"

// Defines symbolic names for the Matrix instructions.
#define GET_INSTRINFO_ENUM
#include "MatrixGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "MatrixGenSubtargetInfo.inc"

#endif

