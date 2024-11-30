#include "astnode.h"

extern int spaces;
extern std::unique_ptr<LLVMContext> theContext;
extern std::unique_ptr<Module> theModule;
extern std::unique_ptr<IRBuilder<>> builder;
extern std::map<std::string, AllocaInst *> namedValues;
extern std::unique_ptr<legacy::FunctionPassManager> theFPM;
extern int grammererror;
extern std::map<std::string, AllocaInst *> curNamedValues;

extern BasicBlock *continueBasicBlock;
void printspaces()
{
    for (int i = 0; i < spaces; ++i)
        std::cout << " ";
}
void printGrammerInfo(std::string nodeName, int line)
{
    printspaces();
    std::cout << nodeName << " (" << line << ")" << std::endl;
}

void printSemanticError(int type, int line, std::string info = "")
{
    grammererror = 1;
    std::cout << "Error type " << type << " at Line " << line << "."
              << std::endl;
}

int parseNIdentifier(NIdentifier &nIdentifier)
{
    printspaces();
    std::cout << "ID: " << nIdentifier.name << std::endl;
    return 0;
}

Value *LogErrorV(const char *Str)
{
    // std::cout << Str << std::endl;
    return nullptr;
}

void InitializeModuleAndPassManager()
{
    // Open a new module.
    theContext = std::make_unique<LLVMContext>();
    theModule = std::make_unique<Module>("test", *theContext);

    // theModule->setDataLayout(dL);

    // Create a new builder for the module.
    builder = std::make_unique<IRBuilder<>>(*theContext);

    // Create a new pass manager attached to it.
    theFPM = std::make_unique<legacy::FunctionPassManager>(theModule.get());

    // Promote allocas to registers.
    // theFPM->add(createPromoteMemoryToRegisterPass());
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    // theFPM->add(createInstructionCombiningPass());
    // Reassociate expressions.
    // theFPM->add(createReassociatePass());
    // Eliminate Common SubExpressions.
    // theFPM->add(createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    // theFPM->add(createCFGSimplificationPass());

    theFPM->doInitialization();
}

Function *getFunction(std::string Name)
{
    // First, see if the function has already been added to the current module.
    if (auto *F = theModule->getFunction(Name))
        return F;
    return nullptr;
}

/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block
/// of the function.  This is used for mutable variables etc.
static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,
                                          StringRef VarName, Type *varType)
{
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                     TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(varType, nullptr, VarName);
}

int NInteger::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "INT"
              << ": " << value << std::endl;
    spaces -= 2;
    return 0;
}
int NFloat::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "FLOAT"
              << ": " << value << std::endl;
    spaces -= 2;
    return 0;
}
int NChar::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "CHAR"
              << ": " << value << std::endl;
    spaces -= 2;
    return 0;
}
int NIdentifier::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "ID"
              << ": " << name << std::endl;
    spaces -= 2;
    return 0;
}
int NDotOperator::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    exp.parse();
    printspaces();
    std::cout << "DOT" << std::endl;
    parseNIdentifier(id);
    // id.parse();
    spaces -= 2;
    return 0;
}
int NListOperator::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    lhs.parse();
    printspaces();
    std::cout << "LB" << std::endl;
    rhs.parse();
    printspaces();
    std::cout << "RB" << std::endl;
    spaces -= 2;
    return 0;
}
int NArgs::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    exp.parse();
    if (nArgs)
    {
        printspaces();
        std::cout << "COMMA" << std::endl;
        nArgs->parse();
    }
    spaces -= 2;
    return 0;
}
int NMethodCall::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    parseNIdentifier(id);
    // id.parse();
    printspaces();
    std::cout << "LP" << std::endl;
    if (nargs)
    {
        nargs->parse();
    }
    printspaces();
    std::cout << "RP" << std::endl;
    spaces -= 2;
    return 0;
}
int NParenOperator::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "LP" << std::endl;
    printspaces();
    exp.parse();
    printspaces();
    std::cout << "RP" << std::endl;
    spaces -= 2;
    return 0;
}
int NSingleOperator::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << name << std::endl;
    hs.parse();
    spaces -= 2;
    return 0;
}
int NBinaryOperator::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    lhs.parse();
    printspaces();
    if (name.substr(0, 5) == "RELOP")
        std::cout << "RELOP" << std::endl;
    else
        std::cout << name << std::endl;
    rhs.parse();
    spaces -= 2;
    return 0;
}
int NAssignment::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    lhs.parse();
    printspaces();
    std::cout << name << std::endl;
    rhs.parse();
    spaces -= 2;
    return 0;
}
int NSpecifier::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "TYPE: " << type << std::endl;
    spaces -= 2;
    return 0;
}
int NVarDec::parse()
{
    printGrammerInfo(getNodeName(), line);

    if (v.size())
    {
        spaces += 2;
        for (int i = 0; i < v.size(); ++i)
        {
            printGrammerInfo(getNodeName(), line);

            spaces += 2;
        }
        parseNIdentifier(Id);
        // Id.parse();
        spaces -= 2;
        for (int i = 0; i < v.size(); ++i)
        {
            printspaces();
            std::cout << "LB" << std::endl;
            printspaces();
            std::cout << "INT: " << v[i] << std::endl;
            printspaces();
            std::cout << "RB" << std::endl;
            spaces -= 2;
        }
    }
    else
    {
        spaces += 2;
        parseNIdentifier(Id);
        // Id.parse();
        spaces -= 2;
    }
    return 0;
}
int NParamDec::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nSpecifier.parse();
    varDec.parse();
    spaces -= 2;
    return 0;
}
int NVarList::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nParamDec.parse();
    if (nVarList)
    {
        printspaces();
        std::cout << "COMMA" << std::endl;
        nVarList->parse();
    }
    spaces -= 2;
    return 0;
}
int NFunDec::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    parseNIdentifier(Id);
    // Id.parse();
    printspaces();
    std::cout << "LP" << std::endl;
    if (arguments)
        arguments->parse();
    printspaces();
    std::cout << "RP" << std::endl;
    spaces -= 2;
    return 0;
}
int NDec::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    vardec.parse();
    if (exp)
    {
        printspaces();
        std::cout << "ASSIGNOP" << std::endl;
        exp->parse();
    }
    spaces -= 2;
    return 0;
}
int NDecList::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    dec.parse();
    if (nDecList)
    {
        printspaces();
        std::cout << "COMMA" << std::endl;
        nDecList->parse();
    }
    spaces -= 2;
    return 0;
}
int NDef::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nSpecifier.parse();
    if (nDecList)
        nDecList->parse();
    printspaces();
    std::cout << "SEMI" << std::endl;
    spaces -= 2;
    return 0;
}
int NDefList::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nDef.parse();
    if (nDefList)
    {
        nDefList->parse();
    }
    spaces -= 2;
    return 0;
}
int NStructSpecifier::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printGrammerInfo("StructSpecifier", line);

    spaces += 2;
    printspaces();
    std::cout << "STRUCT" << std::endl;
    if (deflist)
    {
        if (tag)
        {
            printGrammerInfo("OptTag", line);
            spaces += 2;
            parseNIdentifier(*tag);
            spaces -= 2;
            printspaces();
            std::cout << "LC" << std::endl;
            deflist->parse();
            printspaces();
            std::cout << "RC" << std::endl;
        }
        else
        {
            deflist->parse();
        }
    }
    else if (tag)
    {
        printGrammerInfo("Tag", line);

        spaces += 2;
        parseNIdentifier(*tag);
        spaces -= 2;
    }
    spaces -= 2;
    spaces -= 2;
    return 0;
}
int NStmtList::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nStmt.parse();
    if (nStmtList)
        nStmtList->parse();
    spaces -= 2;
    return 0;
}

int NCompSt::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "LC" << std::endl;
    if (ndeflist)
        ndeflist->parse();
    if (nstmtlist)
        nstmtlist->parse();
    printspaces();
    std::cout << "RC" << std::endl;
    spaces -= 2;
    return 0;
}
int NExpStmt::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    this->exp.parse();
    printspaces();
    std::cout << "SEMI" << std::endl;
    spaces -= 2;
    return 0;
}
int NCompStStmt::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    compst.parse();
    spaces -= 2;
    return 0;
}
int NRetutnStmt::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "RETURN" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "SEMI" << std::endl;
    spaces -= 2;
    return 0;
}
int NIfStmt::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "IF" << std::endl;
    printspaces();
    std::cout << "LP" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "RP" << std::endl;
    this->stmt.parse();
    spaces -= 2;
    return 0;
}
int NIfElseStmt::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "IF" << std::endl;
    printspaces();
    std::cout << "LP" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "RP" << std::endl;
    this->stmt.parse();
    printspaces();
    std::cout << "ELSE" << std::endl;
    this->stmt_else.parse();
    spaces -= 2;
    return 0;
}
int NWhileStmt::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "WHILE" << std::endl;
    printspaces();
    std::cout << "LP" << std::endl;
    this->exp.parse();
    printspaces();
    std::cout << "RP" << std::endl;
    this->stmt.parse();
    spaces -= 2;
    return 0;
}
int NBreakStmt::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    printspaces();
    std::cout << "BREAK" << std::endl;
    printspaces();
    std::cout << "SEMI" << std::endl;
    spaces -= 2;
    return 0;
}
int NExtDecList::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nVarDec.parse();
    if (nExtDecList)
    {
        printspaces();
        std::cout << "COMMA" << std::endl;
        nExtDecList->parse();
    }
    spaces -= 2;
    return 0;
}
int NExtDef::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    specifier.parse();
    if (fundec)
    {
        fundec->parse();
        if (compst)
        {
            compst->parse();
        }
    }
    else
    {
        if (nextdeclist)
        {
            nextdeclist->parse();
        }
        printspaces();
        std::cout << "SEMI" << std::endl;
    }

    spaces -= 2;
    return 0;
}
int NExtDefList::parse()
{
    printGrammerInfo(getNodeName(), line);

    spaces += 2;
    nExtDef.parse();
    if (nExtDefList)
        nExtDefList->parse();
    spaces -= 2;
    return 0;
}
int NProgram::parse()
{
    printGrammerInfo("Program", line);
    spaces += 2;
    if (nextdeflist)
        nextdeflist->parse();
    spaces -= 2;
    return 0;
}

// codegen()
Value *Node::codegen()
{
    assert(false); // Never use this function.
    // This is a list.
    return ConstantInt::get(*theContext, APInt(32, 0, true));
}
Value *NExpression::codegen()
{
    return ConstantInt::get(*theContext, APInt(32, 0, true));
}
Value *NInteger::codegen()
{
    return ConstantInt::get(*theContext, APInt(32, value, true));
}
Value *NFloat::codegen()
{
    // begin
    // 返回浮点数常量
    return ConstantFP::get(*theContext, APFloat(value));
    // end
}
Value *NChar::codegen()
{
    // begin
    // 返回字符常量
    return ConstantDataArray::get(*theContext, value);
    // end
}
Value *NIdentifier::codegen()
{
    // begin
    // 标识先查找标识是否存在
    // 获取当前代码所在的函数
    Function *currentFunction = builder->GetInsertBlock()->getParent();
    // 查找变量是否定义过
    // 获取当前函数内的变量
    Value *foundVariable = nullptr;
    for (auto &basicBlock : *currentFunction)
    {
        for (auto &instruction : basicBlock)
        {
            if (instruction.hasName() && instruction.getName() == name)
            {
                foundVariable = &instruction;
                break;
            }
        }
    }
    if (foundVariable == nullptr)
    {
        // 未找到的变量
        printSemanticError(1, line);
        return nullptr;
    }
    // 加载变量并返回
    return builder->CreateLoad(foundVariable->getType()->getPointerElementType(), foundVariable, "");
    // end
}
Value *NArgs::codegen()
{
    return exp.codegen();
}
Value *NMethodCall::codegen()
{
    // begin
    // 找函数是否定义
    Function *foundFunc = theModule->getFunction(id.name);
    if (foundFunc == nullptr)
    {
        printSemanticError(2, line);
        return nullptr;
    }
    return nullptr;
    // end
}
Value *NParenOperator::codegen() { return exp.codegen(); }
Value *NSingleOperator::codegen()
{
    // begin

    return nullptr;
    // end
}
Value *NBinaryOperator::codegen()
{
    // begin
    // 获取左右表达式的值
    Value *lhsValue = lhs.codegen();
    Value *rhsValue = rhs.codegen();
    if (lhsValue == nullptr || rhsValue == nullptr)
    {
        return nullptr;
    }
    // lhs和rhs需要类型相同
    Type *lhsType = lhsValue->getType();
    Type *rhsType = rhsValue->getType();
    if (lhsType->isPointerTy())
    {
        lhsType = lhsType->getPointerElementType();
    }
    if (rhsType->isPointerTy())
    {
        rhsType = rhsType->getPointerElementType();
    }
    if (lhsType != rhsType)
    {
        printSemanticError(5, line);
    }
    // 运算结果
    Value *resultValue = nullptr;
    if (name == "AND")
    {
        resultValue = nullptr;
    }
    else if (name == "OR")
    {
        resultValue = nullptr;
    }
    else if (name == "RELOP")
    {
        resultValue = nullptr;
    }
    else if (name == "PLUS")
    {
        resultValue = builder->CreateAdd(lhsValue, rhsValue, "");
    }
    else if (name == "MINUS")
    {
        resultValue = builder->CreateSub(lhsValue, rhsValue, "");
    }
    else if (name == "STAR")
    {
        resultValue = builder->CreateMul(lhsValue, rhsValue, "");
    }
    else if (name == "DIV")
    {
        resultValue = builder->CreateSDiv(lhsValue, rhsValue, "");
    }
    else if (name == "MOD")
    {
        resultValue = builder->CreateSRem(lhsValue, rhsValue, "");
    }
    else
    {
        return nullptr;
    }
    return resultValue;
    // end
}
Value *NAssignment::codegen()
{
    // Assignment requires the LHS to be an identifier.
    // begin
    // 需要左值为ID
    if (lhs.name == "")
    {
        printSemanticError(6, line);
        return nullptr;
    }
    // 查找标识是否存在
    // 获取当前代码所在的函数
    Function *currentFunction = builder->GetInsertBlock()->getParent();
    // 查找变量是否定义过
    // 获取当前函数内的变量
    Value *lhsValue = nullptr;
    for (auto &basicBlock : *currentFunction)
    {
        for (auto &instruction : basicBlock)
        {
            if (instruction.hasName() && instruction.getName() == lhs.name)
            {
                lhsValue = &instruction;
                break;
            }
        }
    }
    if (lhsValue == nullptr)
    {
        // 未找到的变量
        printSemanticError(1, line);
    }

    // 右侧表达式的值
    Value *rhsValue = rhs.codegen();
    if (rhsValue == nullptr)
    {
        return nullptr;
    }
    // lhs和rhs需要类型相同
    Type *lhsType = lhsValue->getType();
    Type *rhsType = rhsValue->getType();
    if (lhsType->isPointerTy())
    {
        lhsType = lhsType->getPointerElementType();
    }
    if (rhsType->isPointerTy())
    {
        rhsType = rhsType->getPointerElementType();
    }
    if (lhsType != rhsType)
    {
        printSemanticError(5, line);
    }
    if (name == "ASSIGNOP")
    {
        return builder->CreateStore(rhsValue, lhsValue);
    }
    else if (name == "PLUSASS")
    {
        return nullptr;
    }
    else if (name == "MINUSASS")
    {
        return nullptr;
    }
    else if (name == "STARASS")
    {
        return nullptr;
    }
    else if (name == "DIVASS")
    {
        return nullptr;
    }
    else
    {
        return nullptr;
    }
    return nullptr;
    // end
}
Value *NSpecifier::codegen()
{
    // begin

    return nullptr;
    // end
}
Type *NSpecifier::getType()
{
    if (type == "int")
        return Type::getInt32Ty(*theContext);
    if (type == "float")
        return Type::getFloatTy(*theContext);
    if (type == "char")
        return Type::getInt8Ty(*theContext);
    assert(false);
    return Type::getInt32Ty(*theContext);
}
Value *NVarDec::codegen()
{
    // begin

    return nullptr;
    // end
}
Value *NParamDec::codegen()
{
    // begin

    return nullptr;
    // end
}

std::pair<std::string, Type *> NParamDec::getType()
{
    assert(varDec.v.size() == 0);
    std::pair<std::string, Type *> tmp(varDec.Id.name, nSpecifier.getType());
    return tmp;
}
Value *NVarList::codegen()
{
    assert(false); // Never use this function.
    // This is a list.
    return ConstantInt::get(*theContext, APInt(32, 0, true));
}
Function *NFunDec::funcodegen(Type *retType)
{
    // check if it exists the same name of fun
    if (theModule->getFunction(Id.name))
    {
        printSemanticError(4, line, "Redefined " + Id.name);
        return nullptr;
    }

    std::vector<Type *> argsTypes;
    std::vector<std::string> argNames;
    for (NVarList *item = arguments; item; item = item->nVarList)
    {
        auto tmp = item->nParamDec.getType();
        argNames.push_back(tmp.first);
        argsTypes.push_back(tmp.second);
    }

    FunctionType *ft = FunctionType::get(retType, argsTypes, false);
    Function *f =
        Function::Create(ft, Function::ExternalLinkage, Id.name, theModule.get());
    unsigned idx = 0;
    for (auto &arg : f->args())
    {
        arg.setName(argNames[idx++]);
    }
    return f;
}
Value *NDef::codegen()
{
    // begin
    // 局部变量
    // nSpecifier中储存的是类型
    // 不考虑结构体
    // nextdeclist储存的是变量名
    Type *varType;
    if (nSpecifier.type == "int")
    {
        varType = Type::getInt32Ty(*theContext);
    }
    else if (nSpecifier.type == "float")
    {
        varType = Type::getDoubleTy(*theContext);
    }
    else if (nSpecifier.type == "char")
    {
        varType = Type::getInt8Ty(*theContext);
    }
    else
    {
        // 类型为nullptr 不存在的情况
        return nullptr;
    }
    // 创建变量
    Value *lastCode = nullptr;
    NDecList *decList = nDecList;
    // 获取当前代码所在的函数
    Function *currentFunction = builder->GetInsertBlock()->getParent();
    while (decList != nullptr)
    {
        std::string varName = decList->dec.vardec.Id.name;
        // 查找变量是否定义过
        // 获取当前函数内的变量
        for (auto &basicBlock : *currentFunction)
        {
            for (auto &instruction : basicBlock)
            {
                if (instruction.hasName() && instruction.getName() == varName)
                {
                    printSemanticError(3, line);
                }
            }
        }
        lastCode = builder->CreateAlloca(varType, nullptr, varName);
        // 如果exp不是nullptr,变量定义时，赋值
        if (decList->dec.exp != nullptr)
        {
            Value *lastValue = decList->dec.exp->codegen();
            builder->CreateStore(lastValue, lastCode);
        }
        decList = decList->nDecList;
    }
    return lastCode;
    // end
}
Value *NDefList::codegen()
{
    // begin
    auto *lastCode = nDef.codegen();
    if (nDefList)
        lastCode = nDefList->codegen();
    return lastCode;
    // end
}
Value *NStmtList::codegen()
{
    auto *retVal = nStmt.codegen();
    if (nStmtList)
        retVal = nStmtList->codegen();
    return retVal;
}
Value *NCompSt::codegen()
{
    // 自行处理变量作用域的问题
    Value *retVal = nullptr;
    if (ndeflist)
        retVal = ndeflist->codegen();
    if (nstmtlist)
        retVal = nstmtlist->codegen();
    return retVal;
}
Value *NExpStmt::codegen() { return exp.codegen(); }
Value *NCompStStmt::codegen()
{
    // begin

    return nullptr;
    // end
}
Value *NRetutnStmt::codegen()
{
    Function *theFun = builder->GetInsertBlock()->getParent();
    BasicBlock *bb = BasicBlock::Create(*theContext, "ret", theFun);
    builder->CreateBr(bb);
    builder->SetInsertPoint(bb);
    auto *retVal = exp.codegen();
    // check the return type and fundec type
    // begin

    // end
    builder->CreateRet(retVal);
    return retVal;
}
Value *NIfStmt::codegen()
{
    Function *theFun = builder->GetInsertBlock()->getParent();
    // begin

    return nullptr;
    // end
}
Value *NIfElseStmt::codegen()
{
    Function *theFun = builder->GetInsertBlock()->getParent();
    // begin

    return nullptr;
    // end
}
Value *NWhileStmt::codegen()
{
    Function *theFun = builder->GetInsertBlock()->getParent();
    BasicBlock *condb = BasicBlock::Create(*theContext, "cond", theFun);
    // begin

    return nullptr;
    // end
}
Value *NBreakStmt::codegen()
{
    // begin

    return nullptr;
    // end
}
Value *NExtDefVarDec::codegen()
{
    // begin
    // 全局变量
    return nullptr;
    // end
}
Value *NExtDefFunDec::codegen()
{
    Type *retType = specifier.getType();

    Function *f = fundec->funcodegen(retType);
    if (!f)
    {
        return nullptr;
    }
    assert(compst != nullptr); // Assert compst is not null.
    BasicBlock *bb = BasicBlock::Create(*theContext, "entry", f);
    builder->SetInsertPoint(bb);
    namedValues.clear();
    for (auto &arg : f->args())
    {
        // Create an alloca for this variable.
        AllocaInst *alloca =
            CreateEntryBlockAlloca(f, arg.getName(), arg.getType());

        if (curNamedValues[std::string(arg.getName())])
        {
            printSemanticError(3, line, "Redefined " + arg.getName().str());
            return LogErrorV("Unknown function referenced");
        }
        // Store the initial value into the alloca.
        builder->CreateStore(&arg, alloca);
        // Add arguments to variable symbol table.
        namedValues[std::string(arg.getName())] = alloca;
        curNamedValues[std::string(arg.getName())] = alloca;
    }
    if (Value *retVal = compst->codegen())
    {
        // Finish off the function.

        // Validate the generated code, checking for consistency.
        verifyFunction(*f);

        // Run the optimizer on the function.
        // theFPM->run(*f);
        return f;
    }
    // Error reading body, remove function.
    f->eraseFromParent();

    return nullptr;
}
Value *NExtDefList::codegen()
{
    auto *lastCode = nExtDef.codegen();
    // lastCode->print(errs());
    // assert(nExtDefList == nullptr);
    if (nExtDefList)
        lastCode = nExtDefList->codegen();
    return lastCode;
}
Value *NProgram::codegen()
{

    // 默认输出函数putchar
    std::vector<Type *> putArgs;
    putArgs.push_back(Type::getInt32Ty(*theContext));

    FunctionType *putType =
        FunctionType::get(builder->getInt32Ty(), putArgs, false);
    Function *putFunc = Function::Create(putType, Function::ExternalLinkage,
                                         "putchar", theModule.get());

    // 默认输入函数getchar
    std::vector<Type *> getArgs;
    // getArgs.push_back(Type::getInt32Ty(*theContext));

    FunctionType *getType =
        FunctionType::get(builder->getInt32Ty(), getArgs, false);
    Function *getFunc = Function::Create(getType, Function::ExternalLinkage,
                                         "getchar", theModule.get());

    Value *lastCode = nextdeflist->codegen();
    if (grammererror)
        return nullptr;
    return lastCode;
}
