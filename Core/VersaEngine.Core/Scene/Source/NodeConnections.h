#ifndef NODECONNECTIONS_H
#define NODECONNECTIONS_H

#include "Node.h"

void Node::AddConnection(Connection* connection);
void Node::RemoveConnection(Connection* connection);
std::vector<Node*> Node::GetConnectedNodes() const;
bool Node::CanConnectTo(Node* otherNode, Pin* myPin, Pin* otherPin) const;

#endif