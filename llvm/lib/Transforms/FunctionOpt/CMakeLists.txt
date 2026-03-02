add_llvm_component_library(LLVMFunctionOpt
  FunctionOptPass.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/FunctionOpt

  COMPONENT_NAME
  FunctionOpt

  LINK_COMPONENTS
  Core
  Support
  )
