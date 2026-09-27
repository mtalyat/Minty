#include "GUI/GUI/Gui.hpp"

#include "Library/ImGui/ImGui.hpp"

namespace Minty::GUI
{
    Bool begin(String const &title)
    {
        return ImGui::Begin(title.get_data());
    }
    
    void end()
    {
        ImGui::End();
    }
    
    Bool begin_child(String const &title)
    {
        return ImGui::BeginChild(title.get_data());
    }
    
    void end_child()
    {
        ImGui::EndChild();
    }
    
    void text(String const &text)
    {
        ImGui::Text(text.get_data());
    }
    
    Bool button(String const &label)
    {
        return ImGui::Button(label.get_data());
    }
    
    Bool checkbox(String const &label, Bool &value)
    {
        return ImGui::Checkbox(label.get_data(), &value);
    }

    Bool input_text(String const &label, Vector<Char> &value)
    {
        return ImGui::InputText(label.get_data(), value.get_data(), value.get_capacity());
    }

    Bool input_int(String const &label, Int &value)
    {
        return ImGui::InputInt(label.get_data(), &value);
    }
    
    Bool input_float(String const &label, Float &value)
    {
        return ImGui::InputFloat(label.get_data(), &value);
    }
    
    Bool input_bool(String const &label, Bool &value)
    {
        return ImGui::Checkbox(label.get_data(), &value);
    }
    
    Bool input_float2(String const &label, Float2 &value)
    {
        return ImGui::InputFloat2(label.get_data(), &value.x);
    }
    
    Bool input_float3(String const &label, Float3 &value)
    {
        return ImGui::InputFloat3(label.get_data(), &value.x);
    }
    
    Bool input_float4(String const &label, Float4 &value)
    {
        return ImGui::InputFloat4(label.get_data(), &value.x);
    }
    
    Bool slider_int(String const &label, Int &value, Int min, Int max)
    {
        return ImGui::SliderInt(label.get_data(), &value, min, max);
    }
    
    Bool slider_float(String const &label, Float &value, Float min, Float max)
    {
        return ImGui::SliderFloat(label.get_data(), &value, min, max);
    }
    
    Bool begin_combo(String const &label, String const &previewValue)
    {
        return ImGui::BeginCombo(label.get_data(), previewValue.get_data());
    }
    
    void end_combo()
    {
        ImGui::EndCombo();
    }
    
    Bool selectable(String const &label, Bool selected)
    {
        return ImGui::Selectable(label.get_data(), selected);
    }
    
    Bool tree_node(String const &label)
    {
        return ImGui::TreeNode(label.get_data());
    }
    
    void tree_pop()
    {
        ImGui::TreePop();
    }
    
    void same_line()
    {
        ImGui::SameLine();
    }
    
    void new_line()
    {
        ImGui::NewLine();
    }
    
    void separator()
    {
        ImGui::Separator();
    }
    
    void spacing()
    {
        ImGui::Spacing();
    }
    
    Bool begin_popup(String const &strId)
    {
        return ImGui::BeginPopup(strId.get_data());
    }
    
    Bool begin_popup_modal(String const &strId)
    {
        return ImGui::BeginPopupModal(strId.get_data());
    }
    
    void end_popup()
    {
        ImGui::EndPopup();
    }
    Bool begin_menu(String const &label)
    {
        return ImGui::BeginMenu(label.get_data());
    }
    
    void end_menu()
    {
        ImGui::EndMenu();
    }
    
    Bool begin_main_menu_bar()
    {
        return ImGui::BeginMainMenuBar();
    }
    
    void end_main_menu_bar()
    {
        ImGui::EndMainMenuBar();
    }
    
    Bool menu_item(String const &label)
    {
        return ImGui::MenuItem(label.get_data());
    }
    
    void set_tooltip(String const &text)
    {
        ImGui::SetTooltip(text.get_data());
    }
    
    Bool is_item_hovered()
    {
        return ImGui::IsItemHovered();
    }
    
    Bool color_edit3(String const &label, Float3 &value)
    {
        return ImGui::ColorEdit3(label.get_data(), &value.x);
    }
    
    Bool color_edit4(String const &label, Float4 &value)
    {
        return ImGui::ColorEdit4(label.get_data(), &value.x);
    }
    
    Bool begin_table(String const &strId, Int columnCount)
    {
        return ImGui::BeginTable(strId.get_data(), columnCount);
    }
    
    void end_table()
    {
        ImGui::EndTable();
    }
    
    void table_next_row()
    {
        ImGui::TableNextRow();
    }
    
    void table_next_column()
    {
        ImGui::TableNextColumn();
    }
    
    void render()
    {
        ImGui::Render();
    }
}