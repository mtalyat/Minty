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
}