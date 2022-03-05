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

#include "MatrixSubtarget.h"
#include "MatrixTargetObjectFile.h"
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
  // Register the target.
  //- Big endian Target Machine
  RegisterTargetMachine<MatrixebTargetMachine> X(TheMatrixTarget);
  //- Little endian Target Machine
  RegisterTargetMachine<MatrixelTargetMachine> Y(TheMatrixelTarget);
}

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options,
                                     bool isLittle) {
  std::string Ret = "";
  // There are both little and big endian matrix.
  if (isLittle)
    Ret += "e";
  else
    Ret += "E";

  Ret += "-m:m";

  // Pointers are 32 bit on some ABIs.
  Ret += "-p:32:32";

  // 8 and 16 bit integers only need to have natural alignment, but try to
  // align them to 32 bits. 64 bit integers have natural alignment.
  Ret += "-i8:8:32-i16:16:32-i64:64";

  // 32 bit registers are always available and the stack is at least 64 bit
  // aligned.
  Ret += "-n32-S64";

  return Ret;
}

static Reloc::Model getEffectiveRelocModel(bool JIT,
                                           Optional<Reloc::Model> RM) {
  if (!RM.hasValue() || JIT)
    return Reloc::Static;
  return *RM;
}

// DataLayout --> Big-endian, 32-bit pointer/ABI/alignment
// The stack is always 8 byte aligned
// On function prologue, the stack is created by decrementing
// its pointer. Once decremented, all references are done with positive
// offset from the stack/frame pointer, using StackGrowsUp enables
// an easier handling.
// Using CodeModel::Large enables different CALL behavior.
MatrixTargetMachine::MatrixTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Optional<Reloc::Model> RM,
                                     Optional<CodeModel::Model> CM,
                                     CodeGenOpt::Level OL, bool JIT,
                                     bool isLittle)
  //- Default is big endian
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options, isLittle), TT,
                        CPU, FS, Options, getEffectiveRelocModel(JIT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      isLittle(isLittle), TLOF(std::make_unique<MatrixTargetObjectFile>()),
      ABI(MatrixABIInfo::computeTargetABI()),
      DefaultSubtarget(TT, CPU, FS, isLittle, *this) {
  // initAsmInfo will display features by llc -march=matrix -mcpu=help on 3.7 but
  // not on 3.6
  initAsmInfo();
}

MatrixTargetMachine::~MatrixTargetMachine() {}

void MatrixebTargetMachine::anchor() { }

MatrixebTargetMachine::MatrixebTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         Optional<Reloc::Model> RM,
                                         Optional<CodeModel::Model> CM,
                                         CodeGenOpt::Level OL, bool JIT)
    : MatrixTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT, false) {}

void MatrixelTargetMachine::anchor() { }

MatrixelTargetMachine::MatrixelTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         Optional<Reloc::Model> RM,
                                         Optional<CodeModel::Model> CM,
                                         CodeGenOpt::Level OL, bool JIT)
    : MatrixTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT, true) {}

const MatrixSubtarget *
MatrixTargetMachine::getSubtargetImpl(const Function &F) const {
  std::string CPU = TargetCPU;
  std::string FS = TargetFS;

  auto &I = SubtargetMap[CPU + FS];
  if (!I) {
    // This needs to be done before we create a new subtarget since any
    // creation will depend on the TM and the code generation flags on the
    // function that reside in TargetOptions.
    resetTargetOptions(F);
    I = std::make_unique<MatrixSubtarget>(TargetTriple, CPU, FS, isLittle,
                                         *this);
  }
  return I.get();
}

namespace {
//@MatrixPassConfig {
/// Matrix Code Generator Pass Configuration Options.
class MatrixPassConfig : public TargetPassConfig {
public:
  MatrixPassConfig(MatrixTargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  MatrixTargetMachine &getMatrixTargetMachine() const {
    return getTM<MatrixTargetMachine>();
  }

  const MatrixSubtarget &getMatrixSubtarget() const {
    return *getMatrixTargetMachine().getSubtargetImpl();
  }
};
} // namespace

TargetPassConfig *MatrixTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new MatrixPassConfig(*this, PM);
}

