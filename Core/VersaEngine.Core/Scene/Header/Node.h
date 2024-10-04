#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory> 

#include "Connection.h" 
#include "NodeComponent.h" // Include the NodeComponent header

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
    std::string DataType;
    // ... other pin-related properties (e.g., connection point location)
};

// Forward declaration of the Event class
class Event;

class Node : public ISelectable
{
public:
    Node(const std::string& name);
    ~Node();

    // Properties
    std::string Name;
    glm::vec2 Position;
    glm::vec2 Size = glm::vec2(100, 50);
    NodeType Type = NodeType::Undefined;
    std::any Data;

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

    Node* Parent = nullptr;
    std::vector<Node*> Children;

    std::vector<Connection*> Connections;

    int Id;

    std::string Comment;

    // Components (using unique_ptr for ownership)
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
            // Handle type mismatch error (e.g., log an error, return a default value) 
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

    // Method to add components
    void AddComponent(std::unique_ptr<NodeComponent> component);

    // ... (Serialization and Deserialization)
};

#endif // NODE_H