#include "astnode.h"

extern int spaces;

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

int parseNIdentifier(NIdentifier &nIdentifier)
{
    printspaces();
    std::cout << "ID: " << nIdentifier.name << std::endl;
    return 0;
}

int NInteger::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "INT" << ": " << value << std::endl;
    spaces -= 2;
    return 0;
}

int NFloat::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "FLOAT" << ": " << value << std::endl;
    spaces -= 2;
    return 0;
}

int NChar::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "CHAR" << ": " << value << std::endl;
    spaces -= 2;
    return 0;
}

int NIdentifier::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "ID" << ": " << name << std::endl;
    spaces -= 2;
    return 0;
}

int NDotOperator::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->exp.parse();
    printspaces();
    std::cout << "DOT" << std::endl;
    printspaces();
    std::cout << "ID" << ": " << this->id.name << std::endl;
    spaces -= 2;
    return 0;
}

int NListOperator::parse()
{

    return 0;
}

int NArgs::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->exp.parse();
    if(this->nArgs != nullptr)
    {
        this->nArgs->parse();
    }
    spaces -= 2;
    return 0;
}

int NMethodCall::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    printspaces();
    std::cout << "ID" << ": " << this->id.name << std::endl;
    printspaces();
    std::cout << "LP" << std::endl;
    if (this->nargs != nullptr)
    {
        this->nargs->parse();
    }
    printspaces();
    std::cout << "RP" << std::endl;
    spaces -= 2;
    return 0;
}

int NParenOperator::parse()
{

    return 0;
}

int NSingleOperator::parse()
{

    return 0;
}

int NBinaryOperator::parse()
{

    return 0;
}

int NAssignment::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->lhs.parse();
    printspaces();
    std::cout << this->name << std::endl;
    this->rhs.parse();
    spaces -= 2;
    return 0;
}

int NSpecifier::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    if (this->nStructSpecifier != nullptr)
    {
        this->nStructSpecifier->parse();
    }
    else
    {
        printspaces();
        std::cout << "TYPE: " << type << std::endl;
    }
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
    this->nSpecifier.parse();
    this->varDec.parse();
    spaces -= 2;
    return 0;
}

int NVarList::parse()
{
    printGrammerInfo(getNodeName(), line);
    spaces += 2;
    this->nParamDec.parse();
    if (this->nVarList != nullptr)
    {
        this->nVarList->parse();
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
    printspaces();
    std::cout << "STRUCT" << std::endl;
    this->tag->parse();
    if (this->deflist != nullptr)
    {
        printspaces();
        std::cout << "LC" << std::endl;
        this->deflist->parse();
        printspaces();
        std::cout << "RC" << std::endl;
    }
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
    this->compst.parse();
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
