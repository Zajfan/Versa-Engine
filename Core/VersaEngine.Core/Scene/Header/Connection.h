#ifndef CONNECTION_H
#define CONNECTION_H

#include <map>
#include <any>

#include "Node.h" 

enum class ConnectionType
{
    Data,
    Execution,
    Event,
    // ... other connection types as needed
};

class Connection
{
public:
    Node* Source = nullptr;
    Node* Target = nullptr;

    Pin* SourcePin = nullptr;
    Pin* TargetPin = nullptr;
    // ... (Color)

    ConnectionType Type = ConnectionType::Data;
    std::map<std::string, std::any> CustomProperties;

    bool IsValid() const;

private:
    bool IsCircularConnection() const;
};

#endif // CONNECTION_H