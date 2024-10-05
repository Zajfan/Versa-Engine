#ifndef NODECOMPONENT_H
#define NODECOMPONENT_H

class Node; // Forward declaration

class NodeComponent
{
public:
    NodeComponent(Node* owner);
    virtual ~NodeComponent() = default;

    virtual void Initialize();
    virtual void Terminate();
    virtual void Update(float deltaTime);
    // ... other virtual methods as needed (e.g., Render, HandleEvent)

protected:
    Node* m_owner; // Pointer to the owning Node
};

#endif // NODECOMPONENT_H