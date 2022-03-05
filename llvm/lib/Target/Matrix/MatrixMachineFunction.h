//===-- MatrixMachineFunctionInfo.h - Private data used for Matrix ----*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Matrix specific subclass of MachineFunctionInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MATRIX_MATRIXMACHINEFUNCTION_H
#define LLVM_LIB_TARGET_MATRIX_MATRIXMACHINEFUNCTION_H

#include "MatrixConfig.h"

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/CodeGen/PseudoSourceValue.h"
#include "llvm/Target/TargetMachine.h"
#include <map>

namespace llvm {

//@1 {
/// MatrixFunctionInfo - This class is derived from MachineFunction private
/// Matrix target-specific information for each MachineFunction.
class MatrixFunctionInfo : public MachineFunctionInfo {
public:
  MatrixFunctionInfo(MachineFunction& MF)
  : MF(MF), 
    VarArgsFrameIndex(0), 
    EmitNOAT(false),
    MaxCallFrameSize(0)
    {}

  ~MatrixFunctionInfo();

  int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }
  void setVarArgsFrameIndex(int Index) { VarArgsFrameIndex = Index; }

  bool getEmitNOAT() const { return EmitNOAT; }
  void setEmitNOAT() { EmitNOAT = true; }

private:
  virtual void anchor();

  MachineFunction& MF;

    /// VarArgsFrameIndex - FrameIndex for start of varargs area.
  int VarArgsFrameIndex;

  bool EmitNOAT;
  unsigned MaxCallFrameSize;
};
//@1 }

} // end of namespace llvm

#endif // MATRIX_MACHINE_FUNCTION_INFO_H

