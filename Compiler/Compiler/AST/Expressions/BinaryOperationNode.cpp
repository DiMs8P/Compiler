#include "BinaryOperationNode.h"

BinaryOperationNode::BinaryOperationNode(const Token& token, const ExpressionNode& left_node, const ExpressionNode& right_node) :
    _token(token),
    _leftNode(left_node),
    _rightNode(right_node)
{
}
