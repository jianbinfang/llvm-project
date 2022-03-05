# MCTargetDesc/CMakeLists.txt
add_llvm_component_library(LLVMMatrixDesc
  MatrixABIInfo.cpp
  MatrixMCAsmInfo.cpp
  MatrixMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  MatrixInfo
  MatrixAsmPrinter
  Support

  ADD_TO_COMPONENT
  Matrix
  )

