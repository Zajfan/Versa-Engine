#include "Node.h"
#include <algorithm>

// Constructor
Node::Node(const std::string& name) : Name(name),
CreationTime(std::chrono::system_clock::now()),
LastModifiedTime(std::chrono::system_clock::now())
{
    // You might want to initialize other properties here if needed
    // For example, you could assign a unique ID to the node here
}

Node::~Node()
{
    // You might want to add cleanup logic here in the future
    // For example, releasing resources held by the node
}

// Methods for managing connections
void Node::AddConnection(Connection* connection)
{
    Connections.push_back(connection);
}

void Node::RemoveConnection(Connection* connection)
{
    // Find and remove the connection from the vector
    auto it = std::find(Connections.begin(), Connections.end(), connection);
    if (it != Connections.end())
    {
        Connections.erase(it);
    }
}

std::vector<Node*> Node::GetConnectedNodes()
{
    std::vector<Node*> connectedNodes;
    for (auto connection : Connections)
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

// Interface implementations
void Node::Render(/* ... graphics context */)
{
    if (IsVisible)
    {
        for (auto& component : Components)
        {
            if (auto* renderable = dynamic_cast<IRenderable*>(component.get()))
            {
                renderable->Render(/* ... graphics context */);
            }
        }
    }
}

bool Node::IsSelected() const
{
    // TODO: Implement selection logic (e.g., check if the node is in a selected state)
    return false;
}

void Node::Select()
{
    // TODO: Implement selection logic (e.g., set a flag to indicate selection, update visual appearance)
}

void Node::Deselect()
{
    // TODO: Implement deselection logic (e.g., clear the selection flag, update visual appearance)
}

void Node::Update(float deltaTime)
{
    if (IsEnabled)
    {
        for (auto& component : Components)
        {
            component->Update(deltaTime);
        }
    }
}

// Node-specific methods
void Node::Initialize()
{
    for (auto& component : Components)
    {
        component->Initialize();
    }
}

void Node::Terminate()
{
    for (auto& component : Components)
    {
        component->Terminate();
    }
}

void Node::HandleEvent(Event event)
{
    for (auto& component : Components)
    {
        // You might need a more specific event handling mechanism here
        // depending on your event system design
        component->HandleEvent(event);
    }
}

void Node::Execute()
{
    for (auto& component : Components)
    {
        // You might need a more specific execution mechanism here
        // depending on your visual scripting design
        component->Execute();
    }
}

bool Node::CanConnectTo(Node* otherNode, Pin* myPin, Pin* otherPin) const
{
    // Check if connection types are compatible
    if (std::find(AllowedConnectionTypes.begin(), AllowedConnectionTypes.end(), otherNode->Type) == AllowedConnectionTypes.end())
    {
        return false;
    }

    // Check if pin data types are compatible
    if (myPin->DataType != otherPin->DataType)
    {
        return false;
    }

    // ... other connection validation logic (e.g., prevent circular connections)

    return true;
}

// Serialization and Deserialization 
// (You'll need to implement these using your chosen XML serialization library)
std::string Node::Serialize() const
{
    // TODO: Implement serialization logic using TinyXML2 or your preferred library
    return ""; // Placeholder
}

void Node::Deserialize(const std::string& xmlData)
{
    // TODO: Implement deserialization logic using TinyXML2 or your preferred library
}

// Method to add components
void Node::AddComponent(std::unique_ptr<NodeComponent> component)
{
    Components.push_back(std::move(component));
}

// ... (You'll likely need to implement serialization and deserialization methods here
//      using your chosen XML serialization library)