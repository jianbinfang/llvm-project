//===-- MatrixTargetMachine.h - Define TargetMachine for Matrix -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Matrix specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MATRIX_MATRIXTARGETMACHINE_H
#define LLVM_LIB_TARGET_MATRIX_MATRIXTARGETMACHINE_H

#include "MatrixConfig.h"

#include "MCTargetDesc/MatrixABIInfo.h"
#include "MatrixSubtarget.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class formatted_raw_ostream;
class MatrixRegisterInfo;

class MatrixTargetMachine : public LLVMTargetMachine {
  bool isLittle;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  // Selected ABI
  MatrixABIInfo ABI;
  MatrixSubtarget DefaultSubtarget;

  mutable StringMap<std::unique_ptr<MatrixSubtarget>> SubtargetMap;
public:
  MatrixTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                    CodeGenOpt::Level OL, bool JIT, bool isLittle);
  ~MatrixTargetMachine() override;

  const MatrixSubtarget *getSubtargetImpl() const {
    return &DefaultSubtarget;
  }

  const MatrixSubtarget *getSubtargetImpl(const Function &F) const override;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
  bool isLittleEndian() const { return isLittle; }
  const MatrixABIInfo &getABI() const { return ABI; }
};

/// MatrixebTargetMachine - Matrix32 big endian target machine.
///
class MatrixebTargetMachine : public MatrixTargetMachine {
  virtual void anchor();
public:
  MatrixebTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                      CodeGenOpt::Level OL, bool JIT);
};

/// MatrixelTargetMachine - Matrix32 little endian target machine.
///
class MatrixelTargetMachine : public MatrixTargetMachine {
  virtual void anchor();
public:
  MatrixelTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                      CodeGenOpt::Level OL, bool JIT);
};
} // End llvm namespace

#endif

