//===-- MatrixTargetMachine.cpp - Define TargetMachine for Matrix -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Matrix target spec.
//
//===----------------------------------------------------------------------===//

#include "MatrixTargetMachine.h"
#include "Matrix.h"

#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "matrix"

extern "C" void LLVMInitializeMatrixTarget() {
}

