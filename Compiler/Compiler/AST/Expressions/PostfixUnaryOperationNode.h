#pragma once
#include "../ExpressionNode.h"
#include "../../Token.h"

class PostfixUnaryOperationNode : public ExpressionNode
{
public:
    PostfixUnaryOperationNode(const Token& token, ExpressionNode* operand)
        : _token(token),
          _operand(operand)
    {
    }

private:
    Token _token;
    ExpressionNode* _operand;
};
