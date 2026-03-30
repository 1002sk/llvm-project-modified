# このプロジェクトについて
forked from https://github.com/llvm/llvm-project

関数単位で最適化を効かせる目的でLLVMを改変しています。現在制作途中なので随時更新されます/テスト用の出力があります

```
clang SOURCE_CODE.c -c -emit-llvm -o IR_NO_OPT.bc
opt IR_NO_OPT.bc -o IR_OPT.bc -passes='default<O2>,function-opt<"...">'
(or clang IR_NO_OPT.bc --mllvm -funcion-opt-pass-option="..." -o IR_OPT.bc)
clang IR_OPT -o a.out
```

効果を確かめたい時は`-O0 -Xclang -disable-O0-optnone`を使うとO0に指定した最適化のみを有効にできる

https://compilergym.com/llvm/index.html に記載されているパスのうち、function, loop-nest, loopのものに対応。

パスの内容はpass_data.csvに記載、表計算とかのソフトで見てください。LLMを使って情報をまとめているため、内容に誤りがある可能性があります。

## 実装方法
llvm/lib/Transforms/FunctionOpt にパスの形で実装
内部でFunctionPassManagerを生成して呼び出している

# The LLVM Compiler Infrastructure

[![OpenSSF Scorecard](https://api.securityscorecards.dev/projects/github.com/llvm/llvm-project/badge)](https://securityscorecards.dev/viewer/?uri=github.com/llvm/llvm-project)
[![OpenSSF Best Practices](https://www.bestpractices.dev/projects/8273/badge)](https://www.bestpractices.dev/projects/8273)
[![libc++](https://github.com/llvm/llvm-project/actions/workflows/libcxx-build-and-test.yaml/badge.svg?branch=main&event=schedule)](https://github.com/llvm/llvm-project/actions/workflows/libcxx-build-and-test.yaml?query=event%3Aschedule)

Welcome to the LLVM project!

This repository contains the source code for LLVM, a toolkit for the
construction of highly optimized compilers, optimizers, and run-time
environments.

The LLVM project has multiple components. The core of the project is
itself called "LLVM". This contains all of the tools, libraries, and header
files needed to process intermediate representations and convert them into
object files. Tools include an assembler, disassembler, bitcode analyzer, and
bitcode optimizer.

C-like languages use the [Clang](https://clang.llvm.org/) frontend. This
component compiles C, C++, Objective-C, and Objective-C++ code into LLVM bitcode
-- and from there into object files, using LLVM.

Other components include:
the [libc++ C++ standard library](https://libcxx.llvm.org),
the [LLD linker](https://lld.llvm.org), and more.

## Getting the Source Code and Building LLVM

Consult the
[Getting Started with LLVM](https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm)
page for information on building and running LLVM.

For information on how to contribute to the LLVM project, please take a look at
the [Contributing to LLVM](https://llvm.org/docs/Contributing.html) guide.

## Getting in touch

Join the [LLVM Discourse forums](https://discourse.llvm.org/), [Discord
chat](https://discord.gg/xS7Z362),
[LLVM Office Hours](https://llvm.org/docs/GettingInvolved.html#office-hours) or
[Regular sync-ups](https://llvm.org/docs/GettingInvolved.html#online-sync-ups).

The LLVM project has adopted a [code of conduct](https://llvm.org/docs/CodeOfConduct.html) for
participants to all modes of communication within the project.
