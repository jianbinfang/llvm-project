//===-- MatrixMCTargetDesc.cpp - Matrix Target Descriptions -------------------===//
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

#include "MatrixMCTargetDesc.h"
#include "InstPrinter/MatrixInstPrinter.h"
#include "MatrixMCAsmInfo.h"
#include "llvm/MC/MachineLocation.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "MatrixGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MatrixGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "MatrixGenRegisterInfo.inc"

//@1 {
/// Select the Matrix Architecture Feature for the given triple and cpu name.
/// The function will be called at command 'llvm-objdump -d' for Matrix elf input.
static std::string selectMatrixArchFeature(const Triple &TT, StringRef CPU) {
  std::string MatrixArchFeature;
  if (CPU.empty() || CPU == "generic") {
    if (TT.getArch() == Triple::matrix || TT.getArch() == Triple::matrixel) {
      if (CPU.empty() || CPU == "matrix32II") {
        MatrixArchFeature = "+matrix32II";
      }
      else {
        if (CPU == "matrix32I") {
          MatrixArchFeature = "+matrix32I";
        }
      }
    }
  }
  return MatrixArchFeature;
}
//@1 }

static MCInstrInfo *createMatrixMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitMatrixMCInstrInfo(X); // defined in MatrixGenInstrInfo.inc
  return X;
}

static MCRegisterInfo *createMatrixMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitMatrixMCRegisterInfo(X, Matrix::SW); // defined in MatrixGenRegisterInfo.inc
  return X;
}

static MCSubtargetInfo *createMatrixMCSubtargetInfo(const Triple &TT,
                                                  StringRef CPU, StringRef FS) {
  std::string ArchFS = selectMatrixArchFeature(TT,CPU);
  if (!FS.empty()) {
    if (!ArchFS.empty())
      ArchFS = ArchFS + "," + FS.str();
    else
      ArchFS = FS.str();
  }
  return createMatrixMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, ArchFS);
// createMatrixMCSubtargetInfoImpl defined in MatrixGenSubtargetInfo.inc
}

static MCAsmInfo *createMatrixMCAsmInfo(const MCRegisterInfo &MRI,
                                      const Triple &TT,
                                      const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new MatrixMCAsmInfo(TT);

  unsigned SP = MRI.getDwarfRegNum(Matrix::SP, true);
  MCCFIInstruction Inst = MCCFIInstruction::createDefCfaRegister(nullptr, SP);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

static MCInstPrinter *createMatrixMCInstPrinter(const Triple &T,
                                              unsigned SyntaxVariant,
                                              const MCAsmInfo &MAI,
                                              const MCInstrInfo &MII,
                                              const MCRegisterInfo &MRI) {
  return new MatrixInstPrinter(MAI, MII, MRI);
}

namespace {

class MatrixMCInstrAnalysis : public MCInstrAnalysis {
public:
  MatrixMCInstrAnalysis(const MCInstrInfo *Info) : MCInstrAnalysis(Info) {}
};
}

static MCInstrAnalysis *createMatrixMCInstrAnalysis(const MCInstrInfo *Info) {
  return new MatrixMCInstrAnalysis(Info);
}

//@2 {
extern "C" void LLVMInitializeMatrixTargetMC() {
  for (Target *T : {&TheMatrixTarget, &TheMatrixelTarget}) {
    // Register the MC asm info.
    RegisterMCAsmInfoFn X(*T, createMatrixMCAsmInfo);

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(*T, createMatrixMCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createMatrixMCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(*T,
	                                        createMatrixMCSubtargetInfo);
    // Register the MC instruction analyzer.
    TargetRegistry::RegisterMCInstrAnalysis(*T, createMatrixMCInstrAnalysis);
    // Register the MCInstPrinter.
    TargetRegistry::RegisterMCInstPrinter(*T,
	                                      createMatrixMCInstPrinter);
  }

}
//@2 }

