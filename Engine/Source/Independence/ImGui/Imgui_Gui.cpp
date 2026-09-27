#include "GUI/GUI/Gui.hpp"

#include <cmath>

#include "Library/Vulkan/Vulkan.hpp"
#include "Library/ImGui/ImGui.hpp"

#include "Render/Manager/RenderManager.hpp"
#include "Independence/Vulkan/Vulkan_RenderManager.hpp"
#include "Render/RenderPass/RenderPassInfo.hpp"
#include "Window/Window/Window.hpp"

namespace Minty::GUI
{
    static RenderManager* sp_renderManager = nullptr;
    static Bool s_initialized = false;
    static Bool s_showDemoWindow = true;
    static RenderPassHandle s_renderPass = INVALID_HANDLE;

    static Float srgb_to_linear(Float value)
    {
        return (value <= 0.04045f) ? (value / 12.92f) : static_cast<Float>(std::pow((value + 0.055f) / 1.055f, 2.4f));
    }

    static void apply_linear_style_colors()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        for (Int i = 0; i < ImGuiCol_COUNT; ++i)
        {
            ImVec4& color = style.Colors[i];
            color.x = srgb_to_linear(color.x);
            color.y = srgb_to_linear(color.y);
            color.z = srgb_to_linear(color.z);
        }
    }

    static void initialize_impl(RenderManager& renderManager)
    {
        if (s_initialized)
        {
            return;
        }

        sp_renderManager = &renderManager;

        // Create ImGui context
        ImGui::CreateContext();

        // Enable controls
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

        ImGui::StyleColorsDark();
        apply_linear_style_colors();

        // Init GLFW for ImGui
        Window& window = renderManager.get_window();
        ImGui_ImplGlfw_InitForVulkan(static_cast<GLFWwindow*>(window.get_native()), true);

        // Init Vulkan for ImGui
        RenderManager::Impl& impl = renderManager.get_impl();

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
    }

    void initialize(RenderManager& renderManager)
    {
        initialize_impl(renderManager);
    }

    void shutdown()
    {
        if (!s_initialized)
        {
            return;
        }

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
        MINTY_ASSERT(s_initialized, ErrorCodeEnum::Library_NotInitialized);

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (s_showDemoWindow)
        {
            ImGui::ShowDemoWindow(&s_showDemoWindow);
        }
    }

    void end_frame()
    {
        MINTY_ASSERT(s_initialized, ErrorCodeEnum::Library_NotInitialized);
        MINTY_ASSERT(sp_renderManager != nullptr, ErrorCodeEnum::Library_NotInitialized);

        if (!sp_renderManager->begin_pass(s_renderPass))
        {
            return;
        }

        ImGui::Render();

        VkCommandBuffer const commandBuffer = sp_renderManager->get_impl().get_current_command_buffer();
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);

        sp_renderManager->end_pass();
    }

    RenderPassHandle get_render_pass()
    {
        return s_renderPass;
    }

    Bool begin(Str const title)
    {
        return ImGui::Begin(title);
    }
    
    void end()
    {
        ImGui::End();
    }
    
    Bool child_begin(Str const title)
    {
        return ImGui::BeginChild(title);
    }
    
    void child_end()
    {
        ImGui::EndChild();
    }
    
    void text(Str const text)
    {
        ImGui::Text(text);
    }
    
    Bool button(Str const label)
    {
        return ImGui::Button(label);
    }

    Bool button_small(Str const label)
    {
        return ImGui::SmallButton(label);
    }

    Bool checkbox(Str const label, Bool &value)
    {
        return ImGui::Checkbox(label, &value);
    }

    Bool input_text(Str const label, Vector<Char> &value)
    {
        return ImGui::InputText(label, value.get_data(), value.get_capacity());
    }

    Bool input_int(Str const label, Int &value)
    {
        return ImGui::InputInt(label, &value);
    }
    
    Bool input_float(Str const label, Float &value)
    {
        return ImGui::InputFloat(label, &value);
    }
    
    Bool input_bool(Str const label, Bool &value)
    {
        return ImGui::Checkbox(label, &value);
    }
    
    Bool input_float2(Str const label, Float2 &value)
    {
        return ImGui::InputFloat2(label, &value.x);
    }
    
    Bool input_float3(Str const label, Float3 &value)
    {
        return ImGui::InputFloat3(label, &value.x);
    }
    
    Bool input_float4(Str const label, Float4 &value)
    {
        return ImGui::InputFloat4(label, &value.x);
    }
    
    Bool slider_int(Str const label, Int &value, Int min, Int max)
    {
        return ImGui::SliderInt(label, &value, min, max);
    }
    
    Bool slider_float(Str const label, Float &value, Float min, Float max)
    {
        return ImGui::SliderFloat(label, &value, min, max);
    }
    
    Bool combo_begin(Str const label, Str const previewValue)
    {
        return ImGui::BeginCombo(label, previewValue);
    }
    
    void combo_end()
    {
        ImGui::EndCombo();
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
    
    Bool menu_begin(Str const label)
    {
        return ImGui::BeginMenu(label);
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
    
    Bool menu_item(Str const label, Str const shortcut, Bool selected)
    {
        return ImGui::MenuItem(label, shortcut, selected);
    }
    
    void tooltip_set(Str const text)
    {
        ImGui::SetTooltip(text);
    }
    
    Bool query_is_item_hovered()
    {
        return ImGui::IsItemHovered();
    }
    
    Bool color_edit3(Str const label, Float3 &value)
    {
        return ImGui::ColorEdit3(label, &value.x);
    }
    
    Bool color_edit4(Str const label, Float4 &value)
    {
        return ImGui::ColorEdit4(label, &value.x);
    }
    
    Bool table_begin(Str const strId, Int columnCount)
    {
        return ImGui::BeginTable(strId, columnCount);
    }
    
    void table_end()
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
}