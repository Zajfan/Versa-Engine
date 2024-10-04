#ifndef ScriptComponent_H
#define ScriptComponent_H

#include "NodeComponent.h"

class ScriptComponent : public NodeComponent
{
public:
    ScriptComponent(Node* owner);

    // Properties specific to scripting (e.g., script source code, compiled script)
    // ...

    // Methods for executing the script, handling events, etc.
    virtual void Execute() override;
    virtual void HandleEvent(Event event) override;
    // ...
};

#endif // ScriptComponent_H