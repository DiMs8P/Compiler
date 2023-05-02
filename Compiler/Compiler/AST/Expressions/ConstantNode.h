#pragma once
#include "../ExpressionNode.h"
#include "../../Token.h"


class ConstantNode : public ExpressionNode
{
public:
    ConstantNode(const Token& token);
private:
    Token _token;
};
