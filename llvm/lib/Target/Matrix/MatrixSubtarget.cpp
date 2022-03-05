//===-- MatrixSubtarget.cpp - Matrix Subtarget Information --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Matrix specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "MatrixSubtarget.h"

#include "MatrixMachineFunction.h"
#include "Matrix.h"
#include "MatrixRegisterInfo.h"

#include "MatrixTargetMachine.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "matrix-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "MatrixGenSubtargetInfo.inc"

extern bool FixGlobalBaseReg;

void MatrixSubtarget::anchor() { }

//@1 {
MatrixSubtarget::MatrixSubtarget(const Triple &TT, StringRef CPU,
                             StringRef FS, bool little, 
                             const MatrixTargetMachine &_TM) :
//@1 }
  // MatrixGenSubtargetInfo will display features by llc -march=matrix -mcpu=help
  MatrixGenSubtargetInfo(TT, CPU, /*TuneCPU*/ CPU, FS),
  IsLittle(little), TM(_TM), TargetTriple(TT), TSInfo(),
      InstrInfo(
          MatrixInstrInfo::create(initializeSubtargetDependencies(CPU, FS, TM))),
      FrameLowering(MatrixFrameLowering::create(*this)),
      TLInfo(MatrixTargetLowering::create(TM, *this)) {

}

bool MatrixSubtarget::isPositionIndependent() const {
  return TM.isPositionIndependent();
}

MatrixSubtarget &
MatrixSubtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS,
                                               const TargetMachine &TM) {
  if (TargetTriple.getArch() == Triple::matrix || TargetTriple.getArch() == Triple::matrixel) {
    if (CPU.empty() || CPU == "generic") {
      CPU = "matrix32II";
    }
    else if (CPU == "help") {
      CPU = "";
      return *this;
    }
    else if (CPU != "matrix32I" && CPU != "matrix32II") {
      CPU = "matrix32II";
    }
  }
  else {
    errs() << "!!!Error, TargetTriple.getArch() = " << TargetTriple.getArch()
           <<  "CPU = " << CPU << "\n";
    exit(0);
  }
  
  if (CPU == "matrix32I")
    MatrixArchVersion = Matrix32I;
  else if (CPU == "matrix32II")
    MatrixArchVersion = Matrix32II;

  if (isMatrix32I()) {
    HasCmp = true;
    HasSlt = false;
  }
  else if (isMatrix32II()) {
    HasCmp = false;
    HasSlt = true;
  }
  else {
    errs() << "-mcpu must be empty(default:matrix32II), matrix32I or matrix32II" << "\n";
  }

  // Parse features string.
  ParseSubtargetFeatures(CPU, /*TuneCPU*/ CPU, FS);
  // Initialize scheduling itinerary for the specified CPU.
  InstrItins = getInstrItineraryForCPU(CPU);

  return *this;
}

bool MatrixSubtarget::abiUsesSoftFloat() const {
//  return TM->Options.UseSoftFloat;
  return true;
}

const MatrixABIInfo &MatrixSubtarget::getABI() const { return TM.getABI(); }

