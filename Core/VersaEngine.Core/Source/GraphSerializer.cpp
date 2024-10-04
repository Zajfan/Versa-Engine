#include "GraphSerializer.h"

// ... (Implementations for Serialize, Deserialize, and helper functions)

// Example implementation for SerializeNode
tinyxml2::XMLElement* GraphSerializer::SerializeNode(tinyxml2::XMLDocument& doc, Node* node)
{
    tinyxml2::XMLElement* nodeElement = doc.NewElement("Node");
    // ... (Set node attributes: Id, Name, Position, Type, etc.)

    // Serialize input and output pins
    // ...

    return nodeElement;
}

// ... (Implementations for other methods)