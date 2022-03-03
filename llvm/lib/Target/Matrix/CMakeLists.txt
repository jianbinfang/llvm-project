add_llvm_component_group(Matrix)

set(LLVM_TARGET_DEFINITIONS MatrixOther.td)

# Generate MatrixGenRegisterInfo.inc and MatrixGenInstrInfo.inc which included by 
#  your hand code C++ files. 
# MatrixGenRegisterInfo.inc came from MatrixRegisterInfo.td, MatrixGenInstrInfo.inc 
#  came from MatrixInstrInfo.td.
tablegen(LLVM MatrixGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM MatrixGenInstrInfo.inc -gen-instr-info)
#tablegen(LLVM MatrixGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM MatrixGenMCPseudoLowering.inc -gen-pseudo-lowering)

# MatrixCommonTableGen must be defined
add_public_tablegen_target(MatrixCommonTableGen)

# MatrixCodeGen should match with LLVMBuild.txt MatrixCodeGen
add_llvm_target(MatrixCodeGen
  MatrixTargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  MatrixDesc
  MatrixInfo
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  Matrix
  )

# Should match with "subdirectories =  MCTargetDesc TargetInfo" in LLVMBuild.txt
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)

