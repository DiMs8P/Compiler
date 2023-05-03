#pragma once
#include "../ExpressionNode.h"
#include "../../Token.h"

class BinaryOperationNode : public ExpressionNode
{
public:
    BinaryOperationNode(const Token& token, ExpressionNode* left_node, ExpressionNode* right_node);

private:
    Token _operation;
    ExpressionNode* _leftNode;
    ExpressionNode* _rightNode;
};
