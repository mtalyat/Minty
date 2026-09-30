#include "GUI/GUI/Gui.hpp"
#include "Independence/ImGui/ImGui_Convert.hpp"

#include <cmath>

#include "Library/Vulkan/Vulkan.hpp"
#include "Library/ImGui/ImGui.hpp"

#include "Render/Manager/RenderManager.hpp"
#include "Independence/Vulkan/Vulkan_RenderManager.hpp"
#include "Render/RenderPass/RenderPassInfo.hpp"
#include "Window/Window/Window.hpp"

namespace Minty::GUI
{
    static RenderManager *sp_renderManager = nullptr;
    static Bool s_initialized = false;
    static Bool s_showDemoWindow = true;
    static RenderPassHandle s_renderPass = INVALID_HANDLE;
    static Map<TextureHandle, ImTextureID> s_textures;

    static ImTextureID get_or_register_texture(RenderManager &renderManager, TextureHandle const textureHandle)
    {
        if (s_textures.contains(textureHandle))
        {
            return s_textures.at(textureHandle);
        }

        VkImageView const imageView = renderManager.get_impl().get_texture_view(textureHandle);
        VkSampler const sampler = renderManager.get_impl().get_texture_sampler(textureHandle);
        VkDescriptorSet const descriptorSet = ImGui_ImplVulkan_AddTexture(sampler, imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        ImTextureID const textureId = reinterpret_cast<ImTextureID>(descriptorSet);
        s_textures.add(textureHandle, textureId);
        return textureId;
    }

    static Float srgb_to_linear(Float value)
    {
        return (value <= 0.04045f) ? (value / 12.92f) : static_cast<Float>(std::pow((value + 0.055f) / 1.055f, 2.4f));
    }

    static void apply_linear_style_colors()
    {
        ImGuiStyle &style = ImGui::GetStyle();
        for (Int i = 0; i < ImGuiCol_COUNT; ++i)
        {
            ImVec4 &color = style.Colors[i];
            color.x = srgb_to_linear(color.x);
            color.y = srgb_to_linear(color.y);
            color.z = srgb_to_linear(color.z);
        }
    }

    void initialize(RenderManager &renderManager)
    {
        MINTY_ASSERT(!s_initialized, ErrorCodeEnum::GUI_AlreadyInitialized);

        sp_renderManager = &renderManager;

        // Create ImGui context
        ImGui::CreateContext();

        // Enable controls
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

        ImGui::StyleColorsDark();
        apply_linear_style_colors();

        // Init GLFW for ImGui
        Window &window = renderManager.get_window();
        ImGui_ImplGlfw_InitForVulkan(static_cast<GLFWwindow *>(window.get_native()), true);

        // Init Vulkan for ImGui
        RenderManager::Impl &impl = renderManager.get_impl();

        RenderAttachment colorAttachment{};
        colorAttachment.aspect = ImageAspectFlagsEnum::Color;
        colorAttachment.loadOperation = LoadOperationEnum::Load;
        colorAttachment.storeOperation = StoreOperationEnum::Store;
        colorAttachment.initialLayout = ImageLayoutEnum::Presentation;
        colorAttachment.finalLayout = ImageLayoutEnum::Presentation;

        RenderPassInfo renderPassInfo{};
        Vector<RenderAttachment> attachments;
        attachments.add(colorAttachment);
        renderPassInfo.attachments = attachments;

        s_renderPass = renderManager.create(renderPassInfo);

        ImGui_ImplVulkan_InitInfo init_info{};
        init_info.Instance = impl.get_instance();
        init_info.Device = impl.get_device();
        init_info.PhysicalDevice = impl.get_physical_device();
        init_info.Queue = impl.get_graphics_queue();
        init_info.QueueFamily = impl.get_graphics_queue_family_index();

        init_info.DescriptorPool = VK_NULL_HANDLE;
        init_info.DescriptorPoolSize = 64;
        init_info.PipelineInfoMain.RenderPass = impl.get_render_pass(s_renderPass);
        init_info.PipelineInfoMain.Subpass = 0;
        init_info.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

        init_info.ApiVersion = VK_API_VERSION_1_3;

        init_info.Allocator = VK_NULL_HANDLE;
        init_info.PipelineCache = VK_NULL_HANDLE;
        init_info.CheckVkResultFn = nullptr;
        init_info.ImageCount = FRAMES_PER_FLIGHT;
        init_info.MinAllocationSize = 1024 * 1024;
        init_info.MinImageCount = FRAMES_PER_FLIGHT;
        init_info.UseDynamicRendering = VK_FALSE;

        MINTY_ASSERT(ImGui_ImplVulkan_Init(&init_info), ErrorCodeEnum::GUI_InitializationFailed);

        s_initialized = true;

        // DEFAULT SETUP

        // Set default config flags
        set_config_flags(GuiConfigFlagsEnum::Default);
    }

    void shutdown()
    {
        MINTY_ASSERT(s_initialized, ErrorCodeEnum::GUI_NotInitialized);

        if (sp_renderManager != nullptr)
        {
            sp_renderManager->get_impl().sync();
        }

        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (sp_renderManager != nullptr && s_renderPass != INVALID_HANDLE)
        {
            sp_renderManager->destroy(s_renderPass);
        }

        s_initialized = false;
        sp_renderManager = nullptr;
        s_renderPass = INVALID_HANDLE;
        s_showDemoWindow = true;
    }

    void begin_frame()
    {
        MINTY_ASSERT(s_initialized, ErrorCodeEnum::GUI_NotInitialized);

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void end_frame()
    {
        MINTY_ASSERT(s_initialized, ErrorCodeEnum::GUI_NotInitialized);
        MINTY_ASSERT(sp_renderManager != nullptr, ErrorCodeEnum::GUI_NotInitialized);

        if (!sp_renderManager->begin_pass(s_renderPass))
        {
            return;
        }

        ImGui::Render();

        VkCommandBuffer const commandBuffer = sp_renderManager->get_impl().get_current_command_buffer();
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);

        sp_renderManager->end_pass();
    }

    void set_config_flags(GuiConfigFlagsEnum const flags)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags = Converter<GuiConfigFlagsEnum, ImGuiConfigFlags>::from_minty(flags);
    }

    void set_config_flag(GuiConfigFlagsEnum const flag, Bool const enabled)
    {
        ImGuiIO &io = ImGui::GetIO();
        if (enabled)
        {
            io.ConfigFlags |= Converter<GuiConfigFlagsEnum, ImGuiConfigFlags>::from_minty(flag);
        }
        else
        {
            io.ConfigFlags &= ~Converter<GuiConfigFlagsEnum, ImGuiConfigFlags>::from_minty(flag);
        }
    }

    GuiConfigFlagsEnum get_config_flags()
    {
        ImGuiIO &io = ImGui::GetIO();
        return Converter<GuiConfigFlagsEnum, ImGuiConfigFlags>::to_minty(io.ConfigFlags);
    }

    void dock_main()
    {
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    }

    RenderPassHandle get_render_pass()
    {
        return s_renderPass;
    }

    Bool begin(Str const title, Bool *isOpen, WindowFlagsEnum flags)
    {
        return ImGui::Begin(title, isOpen, Converter<WindowFlagsEnum, ImGuiWindowFlags>::from_minty(flags));
    }

    void end()
    {
        ImGui::End();
    }

    Bool child_begin(Str const title, Float2 const size, ChildFlagsEnum flags, WindowFlagsEnum windowFlags)
    {
        return ImGui::BeginChild(title, Converter<Float2, ImVec2>::from_minty(size), Converter<ChildFlagsEnum, ImGuiWindowFlags>::from_minty(flags), Converter<WindowFlagsEnum, ImGuiWindowFlags>::from_minty(windowFlags));
    }

    void child_end()
    {
        ImGui::EndChild();
    }

    void text(Str const text)
    {
        ImGui::Text(text);
    }

    void bullet()
    {
        ImGui::Bullet();
    }

    void image(TextureHandle const textureHandle, Float2 const size, Float2 const uv0, Float2 const uv1)
    {
        MINTY_ASSERT(s_initialized, ErrorCodeEnum::GUI_NotInitialized);
        MINTY_ASSERT(sp_renderManager != nullptr, ErrorCodeEnum::GUI_NotInitialized);
        MINTY_ASSERT(sp_renderManager->is_valid(textureHandle), ErrorCodeEnum::Argument_KeyNotFound);

        ImTextureID const textureId = get_or_register_texture(*sp_renderManager, textureHandle);
        ImGui::Image(textureId,
            Converter<Float2, ImVec2>::from_minty(size),
            Converter<Float2, ImVec2>::from_minty(uv0),
            Converter<Float2, ImVec2>::from_minty(uv1));
    }

    Bool text_link(Str const label)
    {
        return ImGui::TextLink(label);
    }

    Bool text_url(Str const label, Str const url)
    {
        return ImGui::TextLinkOpenURL(label, url);
    }

    Bool button(Str const label, Float2 const size)
    {
        return ImGui::Button(label, Converter<Float2, ImVec2>::from_minty(size));
    }

    Bool button_small(Str const label)
    {
        return ImGui::SmallButton(label);
    }

    Bool button_invisible(Str const label, Float2 const size, ButtonFlagsEnum flags)
    {
        return ImGui::InvisibleButton(label, Converter<Float2, ImVec2>::from_minty(size), Converter<ButtonFlagsEnum, ImGuiButtonFlags>::from_minty(flags));
    }

    Bool checkbox(Str const label, Bool &value)
    {
        return ImGui::Checkbox(label, &value);
    }

    Bool input_text(Str const label, Vector<Char> &value)
    {
        return ImGui::InputText(label, value.get_data(), value.get_capacity());
    }

    Bool input_text(Str const label, Span<Char> const buffer, InputTextFlagsEnum flags)
    {
        return ImGui::InputText(label, buffer.get_data(), buffer.get_size(), Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool input_int(Str const label, Int &value, Int const step, Int const step_fast, InputTextFlagsEnum flags)
    {
        return ImGui::InputInt(label, &value, step, step_fast, Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool input_int2(Str const label, Int2 &value, InputTextFlagsEnum flags)
    {
        return ImGui::InputInt2(label, &value.x, Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool input_int3(Str const label, Int3 &value, InputTextFlagsEnum flags)
    {
        return ImGui::InputInt3(label, &value.x, Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool input_int4(Str const label, Int4 &value, InputTextFlagsEnum flags)
    {
        return ImGui::InputInt4(label, &value.x, Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool input_float(Str const label, Float &value, Str const format, Float const step, Float const step_fast, InputTextFlagsEnum flags)
    {
        return ImGui::InputFloat(label, &value, step, step_fast, format, Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool input_float2(Str const label, Float2 &value, Str const format, InputTextFlagsEnum flags)
    {
        return ImGui::InputFloat2(label, &value.x, format, Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool input_float3(Str const label, Float3 &value, Str const format, InputTextFlagsEnum flags)
    {
        return ImGui::InputFloat3(label, &value.x, format, Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool input_float4(Str const label, Float4 &value, Str const format, InputTextFlagsEnum flags)
    {
        return ImGui::InputFloat4(label, &value.x, format, Converter<InputTextFlagsEnum, ImGuiInputTextFlags>::from_minty(flags));
    }

    Bool slider_int(Str const label, Int &value, Int const min, Int const max, Str const format, SliderFlagsEnum flags)
    {
        return ImGui::SliderInt(label, &value, min, max, format, Converter<SliderFlagsEnum, ImGuiSliderFlags>::from_minty(flags));
    }

    Bool slider_float(Str const label, Float &value, Float const min, Float const max, Str const format, SliderFlagsEnum flags)
    {
        return ImGui::SliderFloat(label, &value, min, max, format, Converter<SliderFlagsEnum, ImGuiSliderFlags>::from_minty(flags));
    }

    Bool combo_begin(Str const label, Str const preview, ComboFlagsEnum flags)
    {
        return ImGui::BeginCombo(label, preview, Converter<ComboFlagsEnum, ImGuiComboFlags>::from_minty(flags));
    }

    void combo_end()
    {
        ImGui::EndCombo();
    }

    Bool selectable(Str const label, Bool &selected, SelectableFlagsEnum flags, Float2 const size)
    {
        return ImGui::Selectable(label, &selected, Converter<SelectableFlagsEnum, ImGuiSelectableFlags>::from_minty(flags), Converter<Float2, ImVec2>::from_minty(size));
    }

    Bool selectable(Str const label, Bool selected)
    {
        return ImGui::Selectable(label, selected);
    }

    Bool tree_node(Str const label)
    {
        return ImGui::TreeNode(label);
    }

    void tree_pop()
    {
        ImGui::TreePop();
    }

    void layout_same_line()
    {
        ImGui::SameLine();
    }

    void layout_new_line()
    {
        ImGui::NewLine();
    }

    void layout_separator()
    {
        ImGui::Separator();
    }

    void layout_spacing()
    {
        ImGui::Spacing();
    }

    void layout_dummy(Float2 const size)
    {
        ImGui::Dummy(Converter<Float2, ImVec2>::from_minty(size));
    }

    void group_begin()
    {
        ImGui::BeginGroup();
    }

    void group_end()
    {
        ImGui::EndGroup();
    }

    Bool popup_begin(Str const strId)
    {
        return ImGui::BeginPopup(strId);
    }

    Bool popup_begin_modal(Str const strId)
    {
        return ImGui::BeginPopupModal(strId);
    }

    void popup_end()
    {
        ImGui::EndPopup();
    }

    Bool menu_bar_begin()
    {
        return ImGui::BeginMenuBar();
    }

    void menu_bar_end()
    {
        ImGui::EndMenuBar();
    }

    Bool menu_begin(Str const label, Bool const enabled)
    {
        return ImGui::BeginMenu(label, enabled);
    }

    void menu_end()
    {
        ImGui::EndMenu();
    }

    Bool menu_bar_main_begin()
    {
        return ImGui::BeginMainMenuBar();
    }

    void menu_bar_main_end()
    {
        ImGui::EndMainMenuBar();
    }

    Bool menu_item(Str const label, Str const shortcut, Bool const selected, Bool const enabled)
    {
        return ImGui::MenuItem(label, shortcut, selected, enabled);
    }

    Bool menu_item(Str const label, Str const shortcut, Bool *const selected, Bool const enabled)
    {
        return ImGui::MenuItem(label, shortcut, selected, enabled);
    }

    Bool menu_item(Str const label, Str const shortcut, Bool selected)
    {
        return ImGui::MenuItem(label, shortcut, selected);
    }

    Bool tab_bar_begin(Str const label)
    {
        return ImGui::BeginTabBar(label);
    }

    Bool tab_bar_begin(Str const label, TabBarFlagsEnum const flags)
    {
        return ImGui::BeginTabBar(label, Converter<TabBarFlagsEnum, ImGuiTabBarFlags>::from_minty(flags));
    }

    void tab_bar_end()
    {
        ImGui::EndTabBar();
    }

    Bool tab_item_begin(Str const label, Bool *const opened, TabItemFlagsEnum flags)
    {
        return ImGui::BeginTabItem(label, opened, Converter<TabItemFlagsEnum, ImGuiTabItemFlags>::from_minty(flags));
    }

    void tab_item_end()
    {
        ImGui::EndTabItem();
    }

    void tooltip_set(Str const text)
    {
        ImGui::SetTooltip(text);
    }

    static inline ImGuiKeyChord create_key_chord(Key const key, KeyModifier const modifier)
    {
        return Converter<Key, ImGuiKey>::from_minty(key) | Converter<KeyModifier, ImGuiKey>::from_minty(modifier);
    }

    Bool shortcut(Str const text, Key const key, KeyModifier const modifier, InputFlagsEnum const inputFlags)
    {
        return ImGui::Shortcut(create_key_chord(key, modifier), Converter<InputFlagsEnum, ImGuiInputFlags>::from_minty(inputFlags));
    }

    void shortcut_set(Str const text, Key const key, KeyModifier const modifier, InputFlagsEnum const inputFlags)
    {
        return ImGui::SetNextItemShortcut(create_key_chord(key, modifier), Converter<InputFlagsEnum, ImGuiInputFlags>::from_minty(inputFlags));
    }

    Bool query_is_item_hovered(HoveredFlagsEnum const flags)
    {
        return ImGui::IsItemHovered(Converter<HoveredFlagsEnum, ImGuiHoveredFlags>::from_minty(flags));
    }

    Bool query_is_item_active()
    {
        return ImGui::IsItemActive();
    }

    Bool query_is_item_focused()
    {
        return ImGui::IsItemFocused();
    }

    Bool query_is_item_clicked(MouseButtonEnum const button)
    {
        return ImGui::IsItemClicked(Converter<MouseButtonEnum, ImGuiMouseButton>::from_minty(button));
    }

    Bool query_is_item_visible()
    {
        return ImGui::IsItemVisible();
    }

    Bool query_is_item_edited()
    {
        return ImGui::IsItemEdited();
    }

    Bool query_is_item_activated()
    {
        return ImGui::IsItemActivated();
    }

    Bool query_is_item_deactivated()
    {
        return ImGui::IsItemDeactivated();
    }

    Bool query_is_item_deactivated_after_edit()
    {
        return ImGui::IsItemDeactivatedAfterEdit();
    }

    Bool query_is_item_toggled()
    {
        return ImGui::IsItemToggledOpen();
    }

    Bool query_is_any_item_hovered()
    {
        return ImGui::IsAnyItemHovered();
    }

    Bool query_is_any_item_active()
    {
        return ImGui::IsAnyItemActive();
    }

    Bool query_is_any_item_focused()
    {
        return ImGui::IsAnyItemFocused();
    }

    Bool color_edit3(Str const label, Float3 &value, ColorEditFlagsEnum const flags)
    {
        return ImGui::ColorEdit3(label, &value.x, Converter<ColorEditFlagsEnum, ImGuiColorEditFlags>::from_minty(flags));
    }

    Bool color_edit4(Str const label, Float4 &value, ColorEditFlagsEnum const flags)
    {
        return ImGui::ColorEdit4(label, &value.x, Converter<ColorEditFlagsEnum, ImGuiColorEditFlags>::from_minty(flags));
    }

    Bool table_begin(Str const strId, Int columnCount, TableFlagsEnum const flags, Float2 const outerSize, Float const innerWidth)
    {
        return ImGui::BeginTable(strId, columnCount, Converter<TableFlagsEnum, ImGuiTableFlags>::from_minty(flags), Converter<Float2, ImVec2>::from_minty(outerSize), innerWidth);
    }

    void table_end()
    {
        ImGui::EndTable();
    }

    void table_next_row(TableRowFlagsEnum const flags, Float const minRowHeight)
    {
        ImGui::TableNextRow(Converter<TableRowFlagsEnum, ImGuiTableRowFlags>::from_minty(flags), minRowHeight);
    }

    void table_next_column()
    {
        ImGui::TableNextColumn();
    }
}