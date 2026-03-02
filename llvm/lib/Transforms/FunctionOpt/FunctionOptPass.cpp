//===- FunctionOptPass.cpp - FunctionOpt module pass ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/FunctionOpt/FunctionOpt.h"

#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

void callPasses(){

}

Function* findFunctionByName(Module &M, const std::string &name, const bool &debug_mode){
    if(Function *F = M.getFunction(name)){
        if(F->isDeclaration()){
            if(debug_mode){
                llvm::outs() << "Function " << name << " is a declaration\n";
            }
            return nullptr;
        }
        return F;
    }
    if(debug_mode)
        llvm::outs() << "Function " << name << " not found in the module\n";
    return nullptr;
}

void parseArgFunction(std::string &arg, Module &M, ModuleAnalysisManager &MAM, const bool &debug_mode){
    auto pos = arg.find(" ");
    std::string function_name = arg.substr(0, pos);
    Function *F = findFunctionByName(M, function_name, debug_mode);
    if(F != nullptr)
        llvm::outs() << "Found! Function name: " << function_name << "\n";
    return;
}

// If the first character is ;, enable debug output
// Format: function_name pass1 pass2 ... passN;function_name2 pass1 pass2 ... passN;
void parseArg(std::string arg, Module &M, ModuleAnalysisManager &MAM){
    bool debug_mode = false;
    if(arg.empty())
        return;
    if(arg[0] == ';'){
        llvm::outs() << "Debug output enabled\n";
        arg = arg.erase(0, 1);
        debug_mode = true;
    }
    auto pos = arg.find(";");
    while(pos != std::string::npos){
        std::string token = arg.substr(0, pos);
        parseArgFunction(token, M, MAM, debug_mode);
        arg = arg.erase(0, pos + 1);
        pos = arg.find(";");
    }
    parseArgFunction(arg, M, MAM, debug_mode);
}

PreservedAnalyses FunctionOptPass::run(Module &M, ModuleAnalysisManager &MAM) {
    if (!Option.empty())
        llvm::outs() << "FunctionOptPass option: " << Option << "\n";
    if(Option.empty())
        return PreservedAnalyses::all();

    parseArg(Option, M, MAM);

    return PreservedAnalyses::all();
}