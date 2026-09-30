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
#include "Core/Type/Float2.hpp"
#include "Core/Type/Function.hpp"
#include "Input/Key/Key.hpp"
#include "Input/Key/KeyModifier.hpp"
#include "Input/Mouse/MouseButton.hpp"
#include "Render/Type/Handle.hpp"

#include "GUI/GUI/ButtonFlags.hpp"
#include "GUI/GUI/ChildFlags.hpp"
#include "GUI/GUI/ColorEditFlags.hpp"
#include "GUI/GUI/ComboFlags.hpp"
#include "GUI/GUI/GuiConfigFlags.hpp"
#include "GUI/GUI/HoveredFlags.hpp"
#include "GUI/GUI/InputFlags.hpp"
#include "GUI/GUI/InputTextFlags.hpp"
#include "GUI/GUI/SelectableFlags.hpp"
#include "GUI/GUI/SliderFlags.hpp"
#include "GUI/GUI/TabBarFlags.hpp"
#include "GUI/GUI/TabItemFlags.hpp"
#include "GUI/GUI/TableFlags.hpp"
#include "GUI/GUI/TableRowFlags.hpp"
#include "GUI/GUI/WindowFlags.hpp"

namespace Minty
{
    class RenderManager;
}

namespace Minty::GUI
{
    constexpr Str DEFAULT_FORMAT_I = "%d";
    constexpr Str DEFAULT_FORMAT_F = "%.3f";
    
    //      Core GUI functions
    void initialize(RenderManager& renderManager);
    void shutdown();
    void begin_frame();
    void end_frame();

    //      Configuration functions
    void set_config_flags(GuiConfigFlagsEnum const flags);
    void set_config_flag(GuiConfigFlagsEnum const flag, Bool const enabled);
    GuiConfigFlagsEnum get_config_flags();

    //      Viewport functions
    void dock_main();

    //      Accessor functions
    RenderPassHandle get_render_pass();

    //      Window functions
    Bool begin(Str const title, Bool* isOpen = nullptr, WindowFlagsEnum flags = WindowFlagsEnum::Default);
    void end();

    //      Child window functions
    Bool child_begin(Str const title, Float2 const size = Float2(0.0f, 0.0f), ChildFlagsEnum flags = ChildFlagsEnum::Default, WindowFlagsEnum windowFlags = WindowFlagsEnum::Default);
    void child_end();

    //      Text functions
    void text(Str const text);
    void bullet();
    Bool text_link(Str const label);
    Bool text_url(Str const label, Str const url = nullptr);

    //      Button functions
    Bool button(Str const label, Float2 const size = Float2(0.0f, 0.0f));
    Bool button_small(Str const label);
    Bool button_invisible(Str const label, Float2 const size = Float2(0.0f, 0.0f), ButtonFlagsEnum flags = ButtonFlagsEnum::Default);

    //      Checkbox functions
    Bool checkbox(Str const label, Bool& value);

    //      Input functions
    Bool input_text(Str const label, Span<Char> const buffer, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);
    Bool input_int(Str const label, Int& value, Int const step = 1, Int const step_fast = 10, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);
    Bool input_int2(Str const label, Int2& value, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);
    Bool input_int3(Str const label, Int3& value, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);
    Bool input_int4(Str const label, Int4& value, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);
    Bool input_float(Str const label, Float& value, Str const format = DEFAULT_FORMAT_F, Float const step = 0.1f, Float const step_fast = 1.0f, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);
    Bool input_float2(Str const label, Float2& value, Str const format = DEFAULT_FORMAT_F, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);
    Bool input_float3(Str const label, Float3& value, Str const format = DEFAULT_FORMAT_F, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);
    Bool input_float4(Str const label, Float4& value, Str const format = DEFAULT_FORMAT_F, InputTextFlagsEnum flags = InputTextFlagsEnum::Default);

    //      Slider functions
    Bool slider_int(Str const label, Int& value, Int const min, Int const max, Str const format = DEFAULT_FORMAT_I, SliderFlagsEnum flags = SliderFlagsEnum::Default);
    Bool slider_float(Str const label, Float& value, Float const min, Float const max, Str const format = DEFAULT_FORMAT_F, SliderFlagsEnum flags = SliderFlagsEnum::Default);

    //      Combo functions
    Bool combo_begin(Str const label, Str const preview, ComboFlagsEnum flags = ComboFlagsEnum::Default);
    void combo_end();

    //      Selectable functions
    Bool selectable(Str const label, Bool& selected, SelectableFlagsEnum flags = SelectableFlagsEnum::Default, Float2 const size = Float2(0.0f, 0.0f));

    //      Tree functions
    Bool tree_node(Str const label); // "tree_push()" called when returning true
    void tree_pop();

    //      Layout functions
    void layout_same_line();
    void layout_new_line();
    void layout_separator();
    void layout_spacing();
    void layout_dummy(Float2 const size = Float2(0.0f, 0.0f));

    //      Group functions
    void group_begin();
    void group_end();

    //      Image functions
    // TODO

    //      Popup functions
    Bool popup_begin(Str const strId);
    Bool popup_begin_modal(Str const strId);
    void popup_end();

    //      Menu functions
    Bool menu_bar_begin();
    void menu_bar_end();
    Bool menu_begin(Str const label, Bool const enabled = true);
    void menu_end();
    Bool menu_bar_main_begin();
    void menu_bar_main_end();
    Bool menu_item(Str const label, Str const shortcut = nullptr, Bool const selected = false, Bool const enabled = true);
    Bool menu_item(Str const label, Str const shortcut, Bool* const selected, Bool const enabled = true);

    //      Tab functions
    Bool tab_bar_begin(Str const label, TabBarFlagsEnum const flags = TabBarFlagsEnum::Default);
    void tab_bar_end();
    Bool tab_item_begin(Str const label, Bool* const opened = nullptr, TabItemFlagsEnum flags = TabItemFlagsEnum::Default);
    void tab_item_end();

    //      Tooltip functions
    void tooltip_set(Str const text);

    //      Shortcut functions
    Bool shortcut(Str const text, Key const key, KeyModifier const modifier = KeyModifierFlagsEnum::None, InputFlagsEnum const inputFlags = InputFlagsEnum::Default);
    void shortcut_set(Str const text, Key const key, KeyModifier const modifier = KeyModifierFlagsEnum::None, InputFlagsEnum const inputFlags = InputFlagsEnum::Default);

    //      Query functions
    Bool query_is_item_hovered(HoveredFlagsEnum const flags = HoveredFlagsEnum::Default);
    Bool query_is_item_active();
    Bool query_is_item_focused();
    Bool query_is_item_clicked(MouseButtonEnum const button);
    Bool query_is_item_visible();
    Bool query_is_item_edited();
    Bool query_is_item_activated();
    Bool query_is_item_deactivated();
    Bool query_is_item_deactivated_after_edit();
    Bool query_is_item_toggled();
    Bool query_is_any_item_hovered();
    Bool query_is_any_item_active();
    Bool query_is_any_item_focused();

    //      Color functions
    Bool color_edit3(Str const label, Float3& value, ColorEditFlagsEnum const flags = ColorEditFlagsEnum::Default);
    Bool color_edit4(Str const label, Float4& value, ColorEditFlagsEnum const flags = ColorEditFlagsEnum::Default);

    //      Table functions
    Bool table_begin(Str const strId, Int columnCount, TableFlagsEnum const flags = TableFlagsEnum::Default, Float2 const outerSize = Float2(0.0f, 0.0f), Float const innerWidth = 0.0f);
    void table_end();
    void table_next_row(TableRowFlagsEnum const flags = TableRowFlagsEnum::Default, Float const minRowHeight = 0.0f);
    void table_next_column();
}