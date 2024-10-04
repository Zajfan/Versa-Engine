#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory> // for std::unique_ptr

#include "Connection.h" // Include the Connection header

enum class NodeType
{
    Undefined,
    Event,
    Variable,
    Function,
    // ... other node types as needed
};

class Pin
{
public:
    std::string Name;
    std::string DataType; // You might want to use a more specific type for data types later
    // ... other pin-related properties (e.g., connection point location)
};

// Forward declaration of the Event class (assuming you'll have one)
class Event;

// Forward declaration of NodeComponent (we'll define it later)
class NodeComponent;

class Node : public ISelectable // Keep only the ISelectable interface for now
{
public:
    Node(); // Constructor

    // Properties
    std::string Name;
    glm::vec2 Position; // Assuming you're using GLM for vector math
    glm::vec2 Size = glm::vec2(100, 50);
    NodeType Type = NodeType::Undefined;
    std::any Data; // Store node-specific data

    std::vector<std::string> Tags;
    std::map<std::string, std::any> CustomProperties;

    bool IsEnabled = true;
    bool IsVisible = true;

    // ... (Color, Icon, Tooltip, IsCollapsed, ExecutionOrder, Category, IsBreakpoint)

    std::vector<Pin> InputPins;
    std::vector<Pin> OutputPins;
    std::vector<NodeType> AllowedConnectionTypes;

    std::chrono::system_clock::time_point CreationTime;
    std::chrono::system_clock::time_point LastModifiedTime;
    std::map<std::string, std::any> UserDefinedMetadata;

    // Parent-child relationships
    Node* Parent = nullptr;
    std::vector<Node*> Children;

    // Connections
    std::vector<Connection*> Connections;

    // Unique identifier
    int Id;

    std::string Comment;

    // Components
    std::vector<std::unique_ptr<NodeComponent>> Components;

    // Methods
    void AddConnection(Connection* connection);
    void RemoveConnection(Connection* connection);
    std::vector<Node*> GetConnectedNodes();

    // Interface implementations
    virtual bool IsSelected() const override;
    virtual void Select() override;
    virtual void Deselect() override;

    // Node-specific methods
    void Initialize();
    void Terminate();
    void Update(float deltaTime);
    void Render(/* ... graphics context */);
    void HandleEvent(Event event);
    void Execute();

    // Type-safe data access
    template <typename T>
    T GetData() const
    {
        try
        {
            return std::any_cast<T>(Data);
        }
        catch (const std::bad_any_cast& e)
        {
            // Handle type mismatch error
            throw;
        }
    }

    template <typename T>
    void SetData(const T& data)
    {
        Data = data;
    }

    // Connection validation
    bool CanConnectTo(Node* otherNode, Pin* myPin, Pin* otherPin) const;

    // ... (Serialization and Deserialization)
};

#endif // NODE_H