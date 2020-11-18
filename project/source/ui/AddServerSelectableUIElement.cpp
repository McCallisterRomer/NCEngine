#include "AddServerSelectableUIElement.h"

namespace
{
    const auto ELEMENT_SIZE = ImVec2{ 300, 100 };
}

namespace project::ui
{
    AddServerSelectableUIElement::AddServerSelectableUIElement(bool startOpen, std::function<void(ServerSelectable)> callback)
        : nc::ui::UIFixedElement(startOpen, nc::ui::UIPosition::Center, ELEMENT_SIZE),
          AddServerCallback{callback}
    {
        m_nameBuffer[0] = '\0';
        m_ipBuffer[0] = '\0';
    }

    void AddServerSelectableUIElement::Draw()
    {
        if(!isOpen) return;

        nc::ui::UIFixedElement::PositionElement();

        if(ImGui::Begin("Add Server", &(this->isOpen)))
        {
            ImGui::InputText("Nickname", m_nameBuffer, m_bufferSize);
            ImGui::InputText("IP", m_ipBuffer, m_bufferSize);

            if(ImGui::Button("Add"))
            {
                isOpen = false;
                AddServerCallback({std::string{m_nameBuffer}, std::string{m_ipBuffer}, false});
            }
        }
        ImGui::End();
    }
}