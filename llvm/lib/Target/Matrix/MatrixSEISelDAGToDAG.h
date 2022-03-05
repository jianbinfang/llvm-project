//===-- MatrixSEISelDAGToDAG.h - A Dag to Dag Inst Selector for MatrixSE -----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Subclass of MatrixDAGToDAGISel specialized for matrix32.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MATRIX_MATRIXSEISELDAGTODAG_H
#define LLVM_LIB_TARGET_MATRIX_MATRIXSEISELDAGTODAG_H

#include "MatrixConfig.h"

#include "MatrixISelDAGToDAG.h"

namespace llvm {

class MatrixSEDAGToDAGISel : public MatrixDAGToDAGISel {

public:
  explicit MatrixSEDAGToDAGISel(MatrixTargetMachine &TM, CodeGenOpt::Level OL)
      : MatrixDAGToDAGISel(TM, OL) {}

private:

  bool runOnMachineFunction(MachineFunction &MF) override;

  bool trySelect(SDNode *Node) override;

  void processFunctionAfterISel(MachineFunction &MF) override;

  // Insert instructions to initialize the global base register in the
  // first MBB of the function.
//  void initGlobalBaseReg(MachineFunction &MF);

};

FunctionPass *createMatrixSEISelDag(MatrixTargetMachine &TM,
                                  CodeGenOpt::Level OptLevel);

}

#endif

