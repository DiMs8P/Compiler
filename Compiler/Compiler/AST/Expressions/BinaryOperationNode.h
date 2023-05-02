#pragma once
#include "../ExpressionNode.h"
#include "../../Token.h"

class BinaryOperationNode : public ExpressionNode
{
public:
    BinaryOperationNode(const Token& token, const ExpressionNode& left_node, const ExpressionNode& right_node);

private:
    Token _token;
    ExpressionNode _leftNode;
    ExpressionNode _rightNode;
};
