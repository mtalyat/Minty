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
#include "Render/Type/Handle.hpp"
#include "Core/Type/UInt2.hpp"
#include "Core/Type/UInt3.hpp"
#include "Core/Type/UInt4.hpp"

namespace Minty
{
    class RenderManager;
}

namespace Minty::GUI
{
    //      Core GUI functions
    void initialize(RenderManager& renderManager);
    void shutdown();
    void begin_frame();
    void end_frame();

    //      Accessor functions
    RenderPassHandle get_render_pass();

    //      Window functionsq
    Bool begin(Str const title);
    void end();

    //      Child window functions
    Bool child_begin(Str const title);
    void child_end();

    //      Text functions
    void text(Str const text);

    //      Button functions
    Bool button(Str const label);
    Bool button_small(Str const label);

    //      Checkbox functions
    Bool checkbox(Str const label, Bool& value);

    //      Input functions
    Bool input_text(Str const label, Vector<Char>& value);
    Bool input_int(Str const label, Int& value);
    Bool input_float(Str const label, Float& value);
    Bool input_bool(Str const label, Bool& value);
    Bool input_float2(Str const label, Float2& value);
    Bool input_float3(Str const label, Float3& value);
    Bool input_float4(Str const label, Float4& value);

    //      Slider functions
    Bool slider_int(Str const label, Int& value, Int min, Int max);
    Bool slider_float(Str const label, Float& value, Float min, Float max);

    //      Combo functions
    Bool combo_begin(Str const label, Str const previewValue);
    void combo_end();

    //      Selectable functions
    Bool selectable(Str const label, Bool selected = false);

    //      Tree functions
    Bool tree_node(Str const label);
    void tree_pop();

    //      Layout functions
    void layout_same_line();
    void layout_new_line();
    void layout_separator();
    void layout_spacing();

    //      Image functions
    // TODO

    //      Popup functions
    Bool popup_begin(Str const strId);
    Bool popup_begin_modal(Str const strId);
    void popup_end();

    //      Menu functions
    Bool menu_bar_begin();
    void menu_bar_end();
    Bool menu_begin(Str const label);
    void menu_end();
    Bool menu_bar_main_begin();
    void menu_bar_main_end();
    Bool menu_item(Str const label, Str const shortcut = nullptr, Bool selected = false);

    //      Tooltip functions
    void tooltip_set(Str const text);

    //      Query functions
    Bool query_is_item_hovered();

    //      Color functions
    Bool color_edit3(Str const label, Float3& value);
    Bool color_edit4(Str const label, Float4& value);

    //      Table functions
    Bool table_begin(Str const strId, Int columnCount);
    void table_end();
    void table_next_row();
    void table_next_column();
}