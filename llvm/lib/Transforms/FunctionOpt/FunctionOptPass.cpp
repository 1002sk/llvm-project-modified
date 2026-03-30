//===- FunctionOptPass.cpp - FunctionOpt module pass ---------------------===//



#include "llvm/Transforms/FunctionOpt/FunctionOpt.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TypeName.h"

// ADCEPass
#include "llvm/Transforms/Scalar/ADCE.h"
// AddDiscriminatorsPass
#include "llvm/Transforms/Utils/AddDiscriminators.h"
// AggressiveInstCombinePass
#include "llvm/Transforms/AggressiveInstCombine/AggressiveInstCombine.h"
// AlignmentFromAssumptionsPass
#include "llvm/Transforms/Scalar/AlignmentFromAssumptions.h"
// BDCEPass
#include "llvm/Transforms/Scalar/BDCE.h"
// BreakCriticalEdgesPass
#include "llvm/Transforms/Utils/BreakCriticalEdges.h"
// CallSiteSplittingPass
#include "llvm/Transforms/Scalar/CallSiteSplitting.h"
// ConstantHoistingPass
#include "llvm/Transforms/Scalar/ConstantHoisting.h"
// CoroElidePass
#include "llvm/Transforms/Coroutines/CoroElide.h"
// CorrelatedValuePropagationPass
#include "llvm/Transforms/Scalar/CorrelatedValuePropagation.h"
// DCEPass
#include "llvm/Transforms/Scalar/DCE.h"
// DivRemPairsPass
#include "llvm/Transforms/Scalar/DivRemPairs.h"
// DSEPass
#include "llvm/Transforms/Scalar/DeadStoreElimination.h"
// EarlyCSEPass
#include "llvm/Transforms/Scalar/EarlyCSE.h"
// EntryExitInstrumenterPass
#include "llvm/Transforms/Utils/EntryExitInstrumenter.h"
// FlattenCFGPass
#include "llvm/Transforms/Scalar/FlattenCFG.h"
// Float2IntPass
#include "llvm/Transforms/Scalar/Float2Int.h"
// GuardWideningPass
#include "llvm/Transforms/Scalar/GuardWidening.h"
// GVNPass, GVNHoistPass, GVNSinkPass
#include "llvm/Transforms/Scalar/GVN.h"
// InferAddressSpacesPass
#include "llvm/Transforms/Scalar/InferAddressSpaces.h"
// InjectTLIMappings
#include "llvm/Transforms/Utils/InjectTLIMappings.h"
// InstCombinePass
#include "llvm/Transforms/InstCombine/InstCombine.h"
// InstructionNamerPass
#include "llvm/Transforms/Utils/InstructionNamer.h"
// InstSimplifyPass
#include "llvm/Transforms/Scalar/InstSimplifyPass.h"
// IRCEPass
#include "llvm/Transforms/Scalar/InductiveRangeCheckElimination.h"
// JumpThreadingPass
#include "llvm/Transforms/Scalar/JumpThreading.h"
// LCSSAPass
#include "llvm/Transforms/Utils/LCSSA.h"
// LibCallsShrinkWrapPass
#include "llvm/Transforms/Utils/LibCallsShrinkWrap.h"
// LoadStoreVectorizerPass
#include "llvm/Transforms/Vectorize/LoadStoreVectorizer.h"
// LoopDataPrefetchPass
#include "llvm/Transforms/Scalar/LoopDataPrefetch.h"
// LoopDistributePass
#include "llvm/Transforms/Scalar/LoopDistribute.h"
// LoopFusePass
#include "llvm/Transforms/Scalar/LoopFuse.h"
// LoopLoadEliminationPass
#include "llvm/Transforms/Scalar/LoopLoadElimination.h"
// LoopSimplifyPass
#include "llvm/Transforms/Utils/LoopSimplify.h"
// LoopSinkPass
#include "llvm/Transforms/Scalar/LoopSink.h"
// LoopUnrollPass
#include "llvm/Transforms/Scalar/LoopUnrollPass.h"
// LoopVectorizePass
#include "llvm/Transforms/Vectorize/LoopVectorize.h"
// LoopVersioningPass
#include "llvm/Transforms/Utils/LoopVersioning.h"
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
// LowerInvokePass
#include "llvm/Transforms/Utils/LowerInvoke.h"
// LowerSwitchPass
#include "llvm/Transforms/Utils/LowerSwitch.h"
// MemCpyOptPass
#include "llvm/Transforms/Scalar/MemCpyOptimizer.h"
// MergeICmpsPass
#include "llvm/Transforms/Scalar/MergeICmps.h"
// UnifyFunctionExitNodesPass
#include "llvm/Transforms/Utils/UnifyFunctionExitNodes.h"
// MergedLoadStoreMotionPass
#include "llvm/Transforms/Scalar/MergedLoadStoreMotion.h"
// NaryReassociatePass
#include "llvm/Transforms/Scalar/NaryReassociate.h"
// NewGVNPass
#include "llvm/Transforms/Scalar/NewGVN.h"
// PartiallyInlineLibCallsPass
#include "llvm/Transforms/Scalar/PartiallyInlineLibCalls.h"
// PGOMemOPSizeOpt
#include "llvm/Transforms/Instrumentation/PGOInstrumentation.h"
// ReassociatePass
#include "llvm/Transforms/Scalar/Reassociate.h"
// RegToMemPass
#include "llvm/Transforms/Scalar/Reg2Mem.h"
// ScalarizerPass
#include "llvm/Transforms/Scalar/Scalarizer.h"
// SCCPPass
#include "llvm/Transforms/Scalar/SCCP.h"
// SeparateConstOffsetFromGEPPass
#include "llvm/Transforms/Scalar/SeparateConstOffsetFromGEP.h"
// SimplifyCFGPass
#include "llvm/Transforms/Scalar/SimplifyCFG.h"
// SLPVectorizerPass
#include "llvm/Transforms/Vectorize/SLPVectorizer.h"
// StraightLineStrengthReducePass
#include "llvm/Transforms/Scalar/StraightLineStrengthReduce.h"
// SpeculativeExecutionPass
#include "llvm/Transforms/Scalar/SpeculativeExecution.h"
// SROAPass
#include "llvm/Transforms/Scalar/SROA.h"
// TailCallElimPass
#include "llvm/Transforms/Scalar/TailRecursionElimination.h"

// IndVarSimplifyPass
#include "llvm/Transforms/Scalar/IndVarSimplify.h"
// LICMPass
#include "llvm/Transforms/Scalar/LICM.h"
// LoopDeletionPass
#include "llvm/Transforms/Scalar/LoopDeletion.h"
// GuardWideningPass
#include "llvm/Transforms/Scalar/GuardWidening.h"
// LoopIdiomRecognizePass
#include "llvm/Transforms/Scalar/LoopIdiomRecognize.h"
// LoopInstSimplifyPass
#include "llvm/Transforms/Scalar/LoopInstSimplify.h"
// LoopInterchangePass
#include "llvm/Transforms/Scalar/LoopInterchange.h"
// LoopPredicationPass
#include "llvm/Transforms/Scalar/LoopPredication.h"
// LoopStrengthReducePass
#include "llvm/Transforms/Scalar/LoopStrengthReduce.h"
// LoopRotatePass
#include "llvm/Transforms/Scalar/LoopRotation.h"
// LoopSimplifyCFGPass
#include "llvm/Transforms/Scalar/LoopSimplifyCFG.h"
// LoopUnrollAndJamPass
#include "llvm/Transforms/Scalar/LoopUnrollAndJamPass.h"
// LoopVersioningLICMPass
#include "llvm/Transforms/Scalar/LoopVersioningLICM.h"
// SimpleLoopUnswitchPass
#include "llvm/Transforms/Scalar/SimpleLoopUnswitch.h"


#include <cctype>
#include <string>
#include <vector>



using namespace llvm;


void addPassByName(const std::string &pass_name, FunctionPassManager &FPM){

    // EntryExitInstrumenterPassは引数が必要 (bool PostInlining)
    // SROAPassは引数が必要 (SROAOptions PreserveCFG)
    // ここでSROAOptionsは実質bool
    #define FUNCTION_PASS_LIST(v) \
        v(ADCEPass)\
        v(AddDiscriminatorsPass)\
        v(AggressiveInstCombinePass)\
        v(AlignmentFromAssumptionsPass)\
        v(BDCEPass)\
        v(BreakCriticalEdgesPass)\
        v(CallSiteSplittingPass)\
        v(ConstantHoistingPass)\
        v(CoroElidePass)\
        v(CorrelatedValuePropagationPass)\
        v(DCEPass)\
        v(DivRemPairsPass)\
        v(DSEPass)\
        v(EarlyCSEPass)\
        v(FlattenCFGPass)\
        v(Float2IntPass)\
        v(GuardWideningPass)\
        v(GVNPass)\
        v(GVNHoistPass)\
        v(GVNSinkPass)\
        v(InferAddressSpacesPass)\
        v(InjectTLIMappings)\
        v(InstCombinePass)\
        v(InstructionNamerPass)\
        v(InstSimplifyPass)\
        v(IRCEPass)\
        v(JumpThreadingPass)\
        v(LCSSAPass)\
        v(LibCallsShrinkWrapPass)\
        v(LoadStoreVectorizerPass)\
        v(LoopDataPrefetchPass)\
        v(LoopDistributePass)\
        v(LoopFusePass)\
        v(LoopLoadEliminationPass)\
        v(LoopSimplifyPass)\
        v(LoopSinkPass)\
        v(LoopUnrollPass)\
        v(LoopVectorizePass)\
        v(LoopVersioningPass)\
        v(LowerConstantIntrinsicsPass)\
        v(LowerExpectIntrinsicPass)\
        v(LowerGuardIntrinsicPass)\
        v(LowerMatrixIntrinsicsPass)\
        v(LowerWidenableConditionPass)\
        v(LowerInvokePass)\
        v(LowerSwitchPass)\
        v(MemCpyOptPass)\
        v(MergeICmpsPass)\
        v(UnifyFunctionExitNodesPass)\
        v(MergedLoadStoreMotionPass)\
        v(NaryReassociatePass)\
        v(NewGVNPass)\
        v(PartiallyInlineLibCallsPass)\
        v(PGOMemOPSizeOpt)\
        v(ReassociatePass)\
        v(RegToMemPass)\
        v(ScalarizerPass)\
        v(SCCPPass)\
        v(SeparateConstOffsetFromGEPPass)\
        v(SimplifyCFGPass)\
        v(SLPVectorizerPass)\
        v(StraightLineStrengthReducePass)\
        v(SpeculativeExecutionPass)\
        v(TailCallElimPass)\

    // LICMPassは引数が必要 (LICMOptions Opts)
    #define LOOP_PASS_LIST(v)\
        v(IndVarSimplifyPass)\
        v(LoopDeletionPass)\
        v(GuardWideningPass)\
        v(LoopIdiomRecognizePass)\
        v(LoopInstSimplifyPass)\
        v(LoopInterchangePass)\
        v(LoopPredicationPass)\
        v(LoopStrengthReducePass)\
        v(LoopRotatePass)\
        v(LoopSimplifyCFGPass)\
        v(LoopUnrollAndJamPass)\
        v(LoopVersioningLICMPass)\
        v(SimpleLoopUnswitchPass)\

    #define HANDLE_FUNCTION_PASS(PassClass) \
        if(pass_name == #PassClass) return FPM.addPass(PassClass());

    #define HANDLE_LOOP_PASS(PassClass) \
        if(pass_name == #PassClass) return FPM.addPass(createFunctionToLoopPassAdaptor(PassClass(), false));

    FUNCTION_PASS_LIST(HANDLE_FUNCTION_PASS)
    LOOP_PASS_LIST(HANDLE_LOOP_PASS)

    if(pass_name == "EntryExitInstrumenterPass_T") return FPM.addPass(EntryExitInstrumenterPass(true));
    if(pass_name == "EntryExitInstrumenterPass_F") return FPM.addPass(EntryExitInstrumenterPass(false));
    if(pass_name == "SROAPass_T") return FPM.addPass(SROAPass(SROAOptions::PreserveCFG));
    if(pass_name == "SROAPass_F") return FPM.addPass(SROAPass(SROAOptions::ModifyCFG));
    if(pass_name == "LICMPass") return FPM.addPass(createFunctionToLoopPassAdaptor(LICMPass(LICMOptions()), true));
    
    #undef HANDLE_FUNCTION_PASS

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