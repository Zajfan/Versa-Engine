#include "RenderComponent.h"
#include "Node.h"
#include <wx/graphics.h> // Example using wxWidgets for rendering

void RenderComponent::Render(wxGraphicsContext* gc)
{
    // Assuming you have a Node* m_owner; in your NodeComponent class
    // and properties like Color, Shape, etc. in your Node class

    // Example rendering logic using wxWidgets
    wxPen pen(*wxBLACK, 2); // Example pen for the outline
    wxBrush brush(wxColour(m_owner->Color.x * 255, m_owner->Color.y * 255, m_owner->Color.z * 255));

    gc->SetPen(pen);
    gc->SetBrush(brush);

    switch (m_owner->Shape)
    {
    case Node::NodeShape::Rectangle:
        gc->DrawRoundedRectangle(m_owner->Position.x, m_owner->Position.y, m_owner->Size.x, m_owner->Size.y, 5); // Example rounded rectangle
        break;
    case Node::NodeShape::Circle:
        gc->DrawEllipse(m_owner->Position.x, m_owner->Position.y, m_owner->Size.x, m_owner->Size.y);
        break;
        // ... add cases for other shapes
    default:
        gc->DrawRectangle(m_owner->Position.x, m_owner->Position.y, m_owner->Size.x, m_owner->Size.y);
        break;
    }

    // Draw node name
    gc->DrawText(m_owner->Name, m_owner->Position.x + 10, m_owner->Position.y + 10);

    // Draw icon if available
    if (!m_owner->Icon.empty())
    {
        // TODO: Implement icon loading and drawing
    }
}