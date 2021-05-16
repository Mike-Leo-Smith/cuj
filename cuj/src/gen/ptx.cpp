#if CUJ_ENABLE_CUDA

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4141)
#pragma warning(disable: 4244)
#pragma warning(disable: 4624)
#pragma warning(disable: 4626)
#pragma warning(disable: 4996)
#endif

#include <llvm/Analysis/TargetTransformInfo.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Transforms/IPO.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <cuj/gen/ptx.h>

CUJ_NAMESPACE_BEGIN(cuj::gen)

void PTXGenerator::generate(const ir::Program &prog, OptLevel opt)
{
    LLVMInitializeNVPTXTargetInfo();
    LLVMInitializeNVPTXTarget();
    LLVMInitializeNVPTXTargetMC();
    LLVMInitializeNVPTXAsmPrinter();

    std::string err;
    const char *target_triple = "nvptx64-nvidia-cuda";
    auto target = llvm::TargetRegistry::lookupTarget(target_triple, err);
    if(!target)
        throw CUJException(err);
    
    auto machine = target->createTargetMachine(target_triple, "", {}, {}, {});
    auto data_layout = machine->createDataLayout();

    LLVMIRGenerator ir_gen;
    ir_gen.set_target(LLVMIRGenerator::Target::PTX);
    ir_gen.generate(prog, &data_layout);

    auto llvm_module = ir_gen.get_module();
    llvm_module->setDataLayout(data_layout);

    llvm::PassManagerBuilder pass_mgr_builder;
    switch(opt)
    {
    case OptLevel::O0: pass_mgr_builder.OptLevel = 0; break;
    case OptLevel::O1: pass_mgr_builder.OptLevel = 1; break;
    case OptLevel::O2: pass_mgr_builder.OptLevel = 2; break;
    case OptLevel::O3: pass_mgr_builder.OptLevel = 3; break;
    }
    pass_mgr_builder.Inliner = llvm::createFunctionInliningPass(
        pass_mgr_builder.OptLevel, 0, false);
    machine->adjustPassManager(pass_mgr_builder);

    llvm::legacy::PassManager passes;
    passes.add(
        createTargetTransformInfoWrapperPass(machine->getTargetIRAnalysis()));
    pass_mgr_builder.populateModulePassManager(passes);

    llvm::SmallString<8> output_buf;
    llvm::raw_svector_ostream output_stream(output_buf);
    if(machine->addPassesToEmitFile(
        passes, output_stream, nullptr, llvm::CGFT_AssemblyFile))
        throw CUJException("ptx file emission is not supported");

    passes.run(*llvm_module);

    result_.resize(output_buf.size());
    std::memcpy(result_.data(), output_buf.data(), output_buf.size());
}

const std::string &PTXGenerator::get_result() const
{
    return result_;
}

CUJ_NAMESPACE_END(cuj::gen)

#endif // #if CUJ_ENABLE_CUDA
