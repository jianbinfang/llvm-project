# MCTargetDesc/CMakeLists.txt
add_llvm_component_library(LLVMMatrixDesc
  MatrixMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  MatrixInfo
  Support

  ADD_TO_COMPONENT
  Matrix
  )

