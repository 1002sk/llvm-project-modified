//===- FunctionOptPass.cpp - FunctionOpt module pass ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// memo: -13

#include "llvm/Transforms/FunctionOpt/FunctionOpt.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TypeName.h"

// AggressiveInstCombinePass
#include "llvm/Transforms/AggressiveInstCombine/AggressiveInstCombine.h"
// CoroElidePass
#include "llvm/Transforms/Coroutines/CoroElide.h"
// InstCombinePass
#include "llvm/Transforms/InstCombine/InstCombine.h"
// ADCEPass
#include "llvm/Transforms/Scalar/ADCE.h"
// AlignmentFromAssumptionPass
#include "llvm/Transforms/Scalar/AlignmentFromAssumptions.h"
// AnnotationRemarksPass
#include "llvm/Transforms/Scalar/AnnotationRemarks.h"
// BDCEPass
#include "llvm/Transforms/Scalar/BDCE.h"
// CallSiteSplittingPass
#include "llvm/Transforms/Scalar/CallSiteSplitting.h"
// ConstantHoistingPass
#include "llvm/Transforms/Scalar/ConstantHoisting.h"
// ConstraintEliminationPass
#include "llvm/Transforms/Scalar/ConstraintElimination.h"
// CorrelatedValuePropagationPass
#include "llvm/Transforms/Scalar/CorrelatedValuePropagation.h"
// DCEPass
// RedundantDbgInstEliminationPass
#include "llvm/Transforms/Scalar/DCE.h"
// DSEPass
#include "llvm/Transforms/Scalar/DeadStoreElimination.h"
// DFAJumpThreadingPass
#include "llvm/Transforms/Scalar/DFAJumpThreading.h"
// DivRemPairsPass
#include "llvm/Transforms/Scalar/DivRemPairs.h"
// DropUnnecessaryAssumesPass
#include "llvm/Transforms/Scalar/DropUnnecessaryAssumes.h"
// EarlyCSEPass
#include "llvm/Transforms/Scalar/EarlyCSE.h"
// FlattenCFGPass
#include "llvm/Transforms/Scalar/FlattenCFG.h"
// Float2IntPass
#include "llvm/Transforms/Scalar/Float2Int.h"
// GuardWideningPass
#include "llvm/Transforms/Scalar/GuardWidening.h"
// GVNPass
// GVNHoistPass
// GVNSinkPass
#include "llvm/Transforms/Scalar/GVN.h"
// IRCEPass
#include "llvm/Transforms/Scalar/InductiveRangeCheckElimination.h"
// InferAddressSPacesPass
#include "llvm/Transforms/Scalar/InferAddressSpaces.h"
// InferAlignmentPass
#include "llvm/Transforms/Scalar/InferAlignment.h"
// InstSimplifyPass
#include "llvm/Transforms/Scalar/InstSimplifyPass.h"
// JumpTableToSwitchPass
#include "llvm/Transforms/Scalar/JumpTableToSwitch.h"
// JumpThreadingPass
#include "llvm/Transforms/Scalar/JumpThreading.h"
// LoopAccessInfoPrinterPass
#include "llvm/Transforms/Scalar/LoopAccessAnalysisPrinter.h"
// LoopDataPrefetchPass
#include "llvm/Transforms/Scalar/LoopDataPrefetch.h"
// LoopDistributePass
#include "llvm/Transforms/Scalar/LoopDistribute.h"
// LoopFusePass
#include "llvm/Transforms/Scalar/LoopFuse.h"
// LoopLoadEliminationPass
#include "llvm/Transforms/Scalar/LoopLoadElimination.h"
// LoopPassManager (just a pass manager, not a pass): Loop -> Function
#include "llvm/Transforms/Scalar/LoopPassManager.h"
// LoopSinkPass
#include "llvm/Transforms/Scalar/LoopSink.h"
// LoopUnrollPass
#include "llvm/Transforms/Scalar/LoopUnrollPass.h"
// LowerAtomicPass
#include "llvm/Transforms/Scalar/LowerAtomicPass.h"
// LowerConstantIntrinsicsPass
#include "llvm/Transforms/Scalar/LowerConstantIntrinsics.h"
// LowerExpectIntrinsicPass
#include "llvm/Transforms/Scalar/LowerExpectIntrinsic.h"
// LowerGuardIntrinsicPass
#include "llvm/Transforms/Scalar/LowerGuardIntrinsic.h"
// LowerMatrixIntrinsicsPass
#include "llvm/Transforms/Scalar/LowerMatrixIntrinsics.h"
// LowerWidenableConditionPass
#include "llvm/Transforms/Scalar/LowerWidenableCondition.h"
// MakeGuarsExplicitPass
#include "llvm/Transforms/Scalar/MakeGuardsExplicit.h"
// MemCpyOptPass
#include "llvm/Transforms/Scalar/MemCpyOptimizer.h"
// MergedLoadStoreMotionPass
#include "llvm/Transforms/Scalar/MergedLoadStoreMotion.h"
// MergeICmpsPass
#include "llvm/Transforms/Scalar/MergeICmps.h"
// NaryReassociatePass
#include "llvm/Transforms/Scalar/NaryReassociate.h"
// NewGVNPass
#include "llvm/Transforms/Scalar/NewGVN.h"
// PartiallyInlineLibCallsPass
#include "llvm/Transforms/Scalar/PartiallyInlineLibCalls.h"
// PlaceSafepointsPass
#include "llvm/Transforms/Scalar/PlaceSafepoints.h"
// ReassociatePass
#include "llvm/Transforms/Scalar/Reassociate.h"
// RegToMemPass
#include "llvm/Transforms/Scalar/Reg2Mem.h"
// ScalarizeMaskedMemIntrinPass
#include "llvm/Transforms/Scalar/ScalarizeMaskedMemIntrin.h"
// ScalarizerPass
#include "llvm/Transforms/Scalar/Scalarizer.h"
// SCCPPass
#include "llvm/Transforms/Scalar/SCCP.h"
// SeparateConstOffsetFromGEPPass
#include "llvm/Transforms/Scalar/SeparateConstOffsetFromGEP.h"
// SimplifyCFGPass
#include "llvm/Transforms/Scalar/SimplifyCFG.h"
// SinkingPass
#include "llvm/Transforms/Scalar/Sink.h"
// SpeculativeExecutionPass
#include "llvm/Transforms/Scalar/SpeculativeExecution.h"
// SROAPass
#include "llvm/Transforms/Scalar/SROA.h"
// StraightLineStrengthReducePass
#include "llvm/Transforms/Scalar/StraightLineStrengthReduce.h"
// StructurizeCFGPass
#include "llvm/Transforms/Scalar/StructurizeCFG.h"
// TailCallElimPass
#include "llvm/Transforms/Scalar/TailRecursionElimination.h"
// WarnMissedTransformationsPass
#include "llvm/Transforms/Scalar/WarnMissedTransforms.h"
// AddDiscriminatorsPass
#include "llvm/Transforms/Utils/AddDiscriminators.h"

#include <cctype>
#include <string>
#include <vector>

using namespace llvm;


void addPassByName(const std::string &pass_name, FunctionPassManager &FPM){
    if(pass_name == "InstSimplifyPass")
        return FPM.addPass(InstSimplifyPass());
    else if(pass_name == "DSEPass")
        return FPM.addPass(DSEPass());
    else if(pass_name == "AggressiveInstCombinePass")
        return FPM.addPass(AggressiveInstCombinePass());
    

    llvm::outs() << "Pass " << pass_name << " not found or not implemented\n";
    return;
}

void callPasses(Function &F, Module &M, ModuleAnalysisManager &MAM, std::string &&opt_arg, bool debug_mode){
    
    if(debug_mode)
        llvm::outs() << "Running passes on function: " << F.getName() << "\n";
    
    FunctionAnalysisManager &FAM = MAM.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();
    FunctionPassManager FPM;

    auto pos = opt_arg.find(" ");
    while(pos != std::string::npos){
        std::string token = opt_arg.substr(0, pos);
        addPassByName(token, FPM);
        opt_arg = opt_arg.erase(0, pos + 1);
        pos = opt_arg.find(" ");
    }
    addPassByName(opt_arg, FPM);






    auto PA = FPM.run(F, FAM);

    if (debug_mode)
        llvm::outs() << "okay, PA = "<< (PA.areAllPreserved() ? "Nochange" : "Changed") <<"\n";

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
    if(F == nullptr)
        return;
    
    if(debug_mode)
        llvm::outs() << "Found! Function name: " << function_name << "\n";

    callPasses(*F, M, MAM, std::move(arg.erase(0, pos+1)), debug_mode);
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
    if(Option.empty())
        return PreservedAnalyses::all();

    parseArg(Option, M, MAM);

    return PreservedAnalyses::none();
}