add_llvm_component_library(LLVMMatrixAsmPrinter
  MatrixInstPrinter.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  Matrix
  )

