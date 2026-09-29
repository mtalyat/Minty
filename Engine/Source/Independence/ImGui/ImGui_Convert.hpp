#pragma once

#include "Library/ImGui/ImGui.hpp"
#include "Core/Convert/Converter.hpp"

#include "Core/Type/Float2.hpp"
#include "Input/Key/Key.hpp"
#include "Input/Key/KeyModifier.hpp"
#include "Input/Mouse/MouseButton.hpp"
#include "GUI/GUI/ButtonFlags.hpp"
#include "GUI/GUI/ChildFlags.hpp"
#include "GUI/GUI/ColorEditFlags.hpp"
#include "GUI/GUI/ComboFlags.hpp"
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
    template<>
    struct Converter<Float2, ImVec2>
    {
        inline static Float2 to_minty(ImVec2 const value) { return Float2(value.x, value.y); }
        inline static ImVec2 from_minty(Float2 const value) { return ImVec2(value.x, value.y); }
    };

    template<>
    struct Converter<Key, ImGuiKey>
    {
        static Key to_minty(ImGuiKey const value);
        static ImGuiKey from_minty(Key const value);
    };

    template<>
    struct Converter<KeyModifier, ImGuiKey>
    {
        static KeyModifier to_minty(ImGuiKey const value);
        static ImGuiKey from_minty(KeyModifier const value);
    };

    template<>
    struct Converter<MouseButtonEnum, ImGuiMouseButton>
    {
        static MouseButtonEnum to_minty(ImGuiMouseButton const value);
        static ImGuiMouseButton from_minty(MouseButtonEnum const value);
    };

    template<>
    struct Converter<ButtonFlagsEnum, ImGuiButtonFlags>
    {
        inline static ButtonFlagsEnum to_minty(ImGuiButtonFlags const value) { return static_cast<ButtonFlagsEnum>(value); }
        inline static ImGuiButtonFlags from_minty(ButtonFlagsEnum const value) { return static_cast<ImGuiButtonFlags>(value); }
    };

    template<>
    struct Converter<ChildFlagsEnum, ImGuiChildFlags>
    {
        inline static ChildFlagsEnum to_minty(ImGuiChildFlags const value) { return static_cast<ChildFlagsEnum>(value); }
        inline static ImGuiChildFlags from_minty(ChildFlagsEnum const value) { return static_cast<ImGuiChildFlags>(value); }
    };

    template<>
    struct Converter<ColorEditFlagsEnum, ImGuiColorEditFlags>
    {
        inline static ColorEditFlagsEnum to_minty(ImGuiColorEditFlags const value) { return static_cast<ColorEditFlagsEnum>(value); }
        inline static ImGuiColorEditFlags from_minty(ColorEditFlagsEnum const value) { return static_cast<ImGuiColorEditFlags>(value); }
    };

    template<>
    struct Converter<ComboFlagsEnum, ImGuiComboFlags>
    {
        inline static ComboFlagsEnum to_minty(ImGuiComboFlags const value) { return static_cast<ComboFlagsEnum>(value); }
        inline static ImGuiComboFlags from_minty(ComboFlagsEnum const value) { return static_cast<ImGuiComboFlags>(value); }
    };

    template<>
    struct Converter<HoveredFlagsEnum, ImGuiHoveredFlags>
    {
        inline static HoveredFlagsEnum to_minty(ImGuiHoveredFlags const value) { return static_cast<HoveredFlagsEnum>(value); }
        inline static ImGuiHoveredFlags from_minty(HoveredFlagsEnum const value) { return static_cast<ImGuiHoveredFlags>(value); }
    };

    template<>
    struct Converter<InputFlagsEnum, ImGuiInputFlags>
    {
        inline static InputFlagsEnum to_minty(ImGuiInputFlags const value) { return static_cast<InputFlagsEnum>(value); }
        inline static ImGuiInputFlags from_minty(InputFlagsEnum const value) { return static_cast<ImGuiInputFlags>(value); }
    };

    template<>
    struct Converter<InputTextFlagsEnum, ImGuiInputTextFlags>
    {
        inline static InputTextFlagsEnum to_minty(ImGuiInputTextFlags const value) { return static_cast<InputTextFlagsEnum>(value); }
        inline static ImGuiInputTextFlags from_minty(InputTextFlagsEnum const value) { return static_cast<ImGuiInputTextFlags>(value); }
    };

    template<>
    struct Converter<SelectableFlagsEnum, ImGuiSelectableFlags>
    {
        inline static SelectableFlagsEnum to_minty(ImGuiSelectableFlags const value) { return static_cast<SelectableFlagsEnum>(value); }
        inline static ImGuiSelectableFlags from_minty(SelectableFlagsEnum const value) { return static_cast<ImGuiSelectableFlags>(value); }
    };

    template<>
    struct Converter<SliderFlagsEnum, ImGuiSliderFlags>
    {
        inline static SliderFlagsEnum to_minty(ImGuiSliderFlags const value) { return static_cast<SliderFlagsEnum>(value); }
        inline static ImGuiSliderFlags from_minty(SliderFlagsEnum const value) { return static_cast<ImGuiSliderFlags>(value); }
    };

    template<>
    struct Converter<TabBarFlagsEnum, ImGuiTabBarFlags>
    {
        inline static TabBarFlagsEnum to_minty(ImGuiTabBarFlags const value) { return static_cast<TabBarFlagsEnum>(value); }
        inline static ImGuiTabBarFlags from_minty(TabBarFlagsEnum const value) { return static_cast<ImGuiTabBarFlags>(value); }
    };

    template<>
    struct Converter<TabItemFlagsEnum, ImGuiTabItemFlags>
    {
        inline static TabItemFlagsEnum to_minty(ImGuiTabItemFlags const value) { return static_cast<TabItemFlagsEnum>(value); }
        inline static ImGuiTabItemFlags from_minty(TabItemFlagsEnum const value) { return static_cast<ImGuiTabItemFlags>(value); }
    };

    template<>
    struct Converter<TableFlagsEnum, ImGuiTableFlags>
    {
        inline static TableFlagsEnum to_minty(ImGuiTableFlags const value) { return static_cast<TableFlagsEnum>(value); }
        inline static ImGuiTableFlags from_minty(TableFlagsEnum const value) { return static_cast<ImGuiTableFlags>(value); }
    };

    template<>
    struct Converter<TableRowFlagsEnum, ImGuiTableRowFlags>
    {
        inline static TableRowFlagsEnum to_minty(ImGuiTableRowFlags const value) { return static_cast<TableRowFlagsEnum>(value); }
        inline static ImGuiTableRowFlags from_minty(TableRowFlagsEnum const value) { return static_cast<ImGuiTableRowFlags>(value); }
    };

    template<>
    struct Converter<WindowFlagsEnum, ImGuiWindowFlags>
    {
        inline static WindowFlagsEnum to_minty(ImGuiWindowFlags const value) { return static_cast<WindowFlagsEnum>(value); }
        inline static ImGuiWindowFlags from_minty(WindowFlagsEnum const value) { return static_cast<ImGuiWindowFlags>(value); }
    };
}