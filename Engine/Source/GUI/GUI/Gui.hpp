#pragma once

/**
 * @file Gui.hpp
 * @brief GUI header file for the Minty engine.
 * @note This file contains the declaration of the GUI namespace for the Minty engine. 
 * All functions should be implementation specific to the backend GUI system.
 */

#include "Core/Data/String.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Type/Float2.hpp"
#include "Core/Type/Float3.hpp"
#include "Core/Type/Float4.hpp"
#include "Core/Type/Int2.hpp"
#include "Core/Type/Int3.hpp"
#include "Core/Type/Int4.hpp"
#include "Core/Type/UInt2.hpp"
#include "Core/Type/UInt3.hpp"
#include "Core/Type/UInt4.hpp"

namespace Minty::GUI
{
    //      Core GUI functions
    Bool begin(String const& title);
    void end();

    Bool begin_child(String const& title);
    void end_child();

    //      Text functions
    void text(String const& text);

    //      Button functions
    Bool button(String const& label);

    //      Checkbox functions
    Bool checkbox(String const& label, Bool& value);

    //      Input functions
    Bool input_text(String const& label, Vector<Char>& value);
    Bool input_int(String const& label, Int& value);
    Bool input_float(String const& label, Float& value);
    Bool input_bool(String const& label, Bool& value);
    Bool input_float2(String const& label, Float2& value);
    Bool input_float3(String const& label, Float3& value);
    Bool input_float4(String const& label, Float4& value);

    //      Slider functions
    Bool slider_int(String const& label, Int& value, Int min, Int max);
    Bool slider_float(String const& label, Float& value, Float min, Float max);

    //      Combo functions
    Bool begin_combo(String const& label, String const& previewValue);
    void end_combo();

    //      Selectable functions
    Bool selectable(String const& label, Bool selected = false);

    //      Tree functions
    Bool tree_node(String const& label);
    void tree_pop();

    //      Layout functions
    void same_line();
    void new_line();
    void separator();
    void spacing();

    //      Image functions
    // TODO

    //      Popup functions
    Bool begin_popup(String const& strId);
    Bool begin_popup_modal(String const& strId);
    void end_popup();

    //      Menu functions
    Bool begin_menu(String const& label);
    void end_menu();
    Bool begin_main_menu_bar();
    void end_main_menu_bar();
    Bool menu_item(String const& label);

    //      Tooltip functions
    void set_tooltip(String const& text);

    //      Query functions
    Bool is_item_hovered();

    //      Color functions
    Bool color_edit3(String const& label, Float3& value);
    Bool color_edit4(String const& label, Float4& value);

    //      Table functions
    Bool begin_table(String const& strId, Int columnCount);
    void end_table();
    void table_next_row();
    void table_next_column();

    // Rendering
    void render();
}