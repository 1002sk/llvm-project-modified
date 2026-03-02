//===- FunctionOpt.h - FunctionOpt module pass -----------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_FUNCTIONOPT_FUNCTIONOPT_H
#define LLVM_TRANSFORMS_FUNCTIONOPT_FUNCTIONOPT_H

#include "llvm/IR/PassManager.h"
#include <string>
#include <vector>

namespace llvm {
class Module;

struct FunctionOptPass : PassInfoMixin<FunctionOptPass> {
  explicit FunctionOptPass(std::string Option = "")
      : Option(std::move(Option)) {}

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM);

private:
  std::string Option;
};


} // namespace llvm

#endif // LLVM_TRANSFORMS_FUNCTIONOPT_FUNCTIONOPT_H
