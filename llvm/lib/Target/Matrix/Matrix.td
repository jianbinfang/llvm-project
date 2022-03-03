//===-- Matrix.td - Describe the Matrix Target Machine ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "MatrixSchedule.td"
include "MatrixInstrInfo.td"

def MatrixInstrInfo : InstrInfo;
//===----------------------------------------------------------------------===//
// Matrix processors supported.
//===----------------------------------------------------------------------===//

// Will generate MatrixGenAsmWrite.inc included by MatrixInstPrinter.cpp, contents 
//  as follows,
// void MatrixInstPrinter::printInstruction(const MCInst *MI, raw_ostream &O) {...}
// const char *MatrixInstPrinter::getRegisterName(unsigned RegNo) {...}
def Matrix : Target {
// def MatrixInstrInfo : InstrInfo as before.
  let InstructionSet = MatrixInstrInfo;
}

