// Node.h

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory>

#include "Connection.h"
#include "NodeComponent.h"

// ... (NodeDataType enum, Pin class)

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

    // Visual Representation and Editor Interaction
    enum class NodeShape { Rectangle, RoundedRectangle, Circle, Custom };
    NodeShape Shape = NodeShape::Rectangle;
    glm::vec3 Color = glm::vec3(1.0f); // Using vec3 for RGB color
    std::string Icon; // Path or ID for the icon image
    std::string Tooltip;
    bool IsCollapsed = false;
    float BorderThickness = 2.0f; // Add border thickness property
    bool ShowLabel = true;  // Add option to show/hide the node's label

    // Execution and Logic
    int ExecutionPriority = 0;
    bool IsBreakpoint = false;
    std::string Condition; // String to store a conditional expression
    enum class ExecutionMode { Default, Conditional, Loop }; // Add execution mode
    ExecutionMode ExecMode = ExecutionMode::Default;
    int LoopCount = 1; // Add loop count for loop mode
    // ... (Properties or methods for state management)

    // Node Relationships and Connections
    enum class ConnectionType { Data, Event, Control };
    std::vector<ConnectionType> AllowedConnectionTypes;
    bool AllowMultipleConnections = true; // Add flag for multiple connections to a pin
    // ... (Properties or methods for dynamic ports)

    // Data and Metadata
    std::string Version;
    std::map<std::string, std::string> UserDefinedMetadata;

    std::vector<Pin> InputPins;
    std::vector<Pin> OutputPins;

    std::chrono::system_clock::time_point CreationTime;
    std::chrono::system_clock::time_point LastModifiedTime;

    Node* Parent = nullptr;
    std::vector<Node*> Children;
    std::vector<Connection*> Connections;

    int Id;
    std::string Comment;

    // Components (using unique_ptr for ownership)
    std::vector<std::unique_ptr<NodeComponent>> Components;

    // Methods
    void AddComponent(std::unique_ptr<NodeComponent> component);

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

    // Type-safe data access methods
    template <typename T>
    T GetData() const;

    template <typename T>
    void SetData(const T& data);

    // ... (Serialization and Deserialization - declarations will be in NodeSerialization.h)
};

#endif // NODE_H