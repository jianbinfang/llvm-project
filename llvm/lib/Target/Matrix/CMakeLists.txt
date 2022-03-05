add_llvm_component_group(Matrix)

set(LLVM_TARGET_DEFINITIONS MatrixOther.td)

# Generate MatrixGenRegisterInfo.inc and MatrixGenInstrInfo.inc which included by 
#  your hand code C++ files. 
# MatrixGenRegisterInfo.inc came from MatrixRegisterInfo.td, MatrixGenInstrInfo.inc 
#  came from MatrixInstrInfo.td.
tablegen(LLVM MatrixGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM MatrixGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM MatrixGenCodeEmitter.inc -gen-emitter)
tablegen(LLVM MatrixGenMCCodeEmitter.inc -gen-emitter)

tablegen(LLVM MatrixGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM MatrixGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM MatrixGenCallingConv.inc -gen-callingconv)
tablegen(LLVM MatrixGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM MatrixGenMCPseudoLowering.inc -gen-pseudo-lowering)

# MatrixCommonTableGen must be defined
add_public_tablegen_target(MatrixCommonTableGen)

# MatrixCodeGen should match with LLVMBuild.txt MatrixCodeGen
add_llvm_target(MatrixCodeGen
  MatrixAsmPrinter.cpp
  MatrixMCInstLower.cpp
  MatrixFrameLowering.cpp
  MatrixInstrInfo.cpp
  MatrixISelLowering.cpp
  MatrixMachineFunction.cpp
  MatrixRegisterInfo.cpp
  MatrixSEFrameLowering.cpp
  MatrixSEInstrInfo.cpp
  MatrixSEISelLowering.cpp
  MatrixSERegisterInfo.cpp
  MatrixSubtarget.cpp
  MatrixTargetObjectFile.cpp
  MatrixISelDAGToDAG.cpp
  MatrixSEISelDAGToDAG.cpp
  MatrixTargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  MatrixDesc
  MatrixInfo
  MatrixAsmPrinter
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  Matrix
  )

# Should match with "subdirectories =  MCTargetDesc TargetInfo" in LLVMBuild.txt
add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)

