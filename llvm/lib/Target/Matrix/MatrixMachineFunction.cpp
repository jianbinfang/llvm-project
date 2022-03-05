//===-- MatrixMachineFunctionInfo.cpp - Private data used for Matrix ----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MatrixMachineFunction.h"

#include "MatrixInstrInfo.h"
#include "MatrixSubtarget.h"
#include "llvm/IR/Function.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

bool FixGlobalBaseReg;

MatrixFunctionInfo::~MatrixFunctionInfo() {}

void MatrixFunctionInfo::anchor() { }

