#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory> // for std::unique_ptr

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
    std::string DataType; // You might want to use a more specific type for data types later
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
    glm::vec2 Position; // Assuming you're using GLM for vector math
    glm::vec2 Size = glm::vec2(100, 50);
    NodeType Type = NodeType::Undefined;
    std::any Data; // Can be used to store any type of data

    std::vector<std::string> Tags; // For categorization and filtering
    std::map<std::string, std::any> CustomProperties; // Flexible custom data storage

    bool IsEnabled = true; // Control node activity
    bool IsVisible = true; // Control node visibility

    // Additional properties for visual representation and editor interaction
    // ... (Color, Icon, Tooltip, IsCollapsed, etc.)

    std::vector<Pin> InputPins;
    std::vector<Pin> OutputPins;
    std::vector<NodeType> AllowedConnectionTypes;

    std::chrono::system_clock::time_point CreationTime;
    std::chrono::system_clock::time_point LastModifiedTime;
    std::map<std::string, std::any> UserDefinedMetadata;

    Node* Parent = nullptr;
    std::vector<Node*> Children;
    std::vector<Connection*> Connections;

    int Id; // Unique identifier for the node
    std::string Comment; // User-defined comment or description

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

    // Node-specific methods (examples)
    virtual void Initialize();
    virtual void Terminate();
    virtual void HandleEvent(Event event);
    virtual void Execute(); // If the node represents executable logic

    // Type-safe data access methods
    template <typename T>
    T GetData() const
    {
        if (Data.type() == typeid(T))
        {
            return std::any_cast<T>(Data);
        }
        else
        {
            // Handle the case where the type does not match (e.g., throw an exception or return a default value)
            throw std::bad_any_cast();
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