#include "NodeConnections.h"
#include "Node.h"
#include <algorithm>

void Node::AddConnection(Connection* connection)
{
    Connections.push_back(connection);
}

void Node::RemoveConnection(Connection* connection)
{
    auto it = std::find(Connections.begin(), Connections.end(), connection);
    if (it != Connections.end())
    {
        Connections.erase(it);
    }
}

std::vector<Node*> Node::GetConnectedNodes() const
{
    std::vector<Node*> connectedNodes;
    for (const auto* connection : Connections)
    {
        if (connection->Source == this)
        {
            connectedNodes.push_back(connection->Target);
        }
        else if (connection->Target == this)
        {
            connectedNodes.push_back(connection->Source);
        }
    }
    return connectedNodes;
}

bool Node::CanConnectTo(Node* otherNode, Pin* myPin, Pin* otherPin) const
{
    if (std::find(AllowedConnectionTypes.begin(), AllowedConnectionTypes.end(), otherNode->Type) == AllowedConnectionTypes.end())
    {
        return false;
    }

    if (myPin->DataType != otherPin->DataType)
    {
        return false;
    }

    return true;
}