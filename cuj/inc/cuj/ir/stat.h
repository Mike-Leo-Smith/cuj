#pragma once

#include <optional>

#include <cuj/ir/op.h>

CUJ_NAMESPACE_BEGIN(cuj::ir)

struct Store;
struct Assign;
struct Break;
struct Continue;
struct Block;
struct If;
struct While;
struct Return;
struct ReturnArray;
struct ReturnClass;
struct Call;

using Statement = Variant<
    Store, Assign,
    Break, Continue,
    Block, If, While,
    Return, ReturnArray, ReturnClass,
    Call>;

struct Store
{
    BasicValue dst_ptr;
    BasicValue src_val;
};

struct Assign
{
    BasicTempValue lhs;
    Value          rhs;
};

struct Break
{
    
};

struct Continue
{
    
};

struct Block
{
    std::vector<RC<Statement>> stats;
};

struct If
{
    BasicValue cond;
    RC<Block>  then_block;
    RC<Block>  else_block;
};

struct While
{
    RC<Block>  calculate_cond;
    BasicValue cond;
    RC<Block>  body;
};

struct Return
{
    std::optional<BasicValue> value;
};

struct ReturnClass
{
    BasicValue class_ptr;
};

struct ReturnArray
{
    BasicValue array_ptr;
};

struct Call
{
    CallOp op;
};

CUJ_NAMESPACE_END(cuj::ir)
