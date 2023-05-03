#include "BinaryOperationNode.h"

BinaryOperationNode::BinaryOperationNode(const Token& token, ExpressionNode* left_node, ExpressionNode* right_node) :
    _operation(token),
    _leftNode(left_node),
    _rightNode(right_node)
{
}
