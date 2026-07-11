#include <Minty.h>

using namespace Minty;

int main()
{
    // RESOURCE
    ResourceManagerInfo info{};
    ResourceManager resourceManager(info);

    ClipResourceHandle const clipResourceHandle = resourceManager.load<ClipResource>("Assets/test2.clp.minty");
    ImageResourceHandle const imageResourceHandle = resourceManager.load<ImageResource>("Assets/test.img.minty");
    TextureResourceHandle const textureResourceHandle = resourceManager.load<TextureResource>("Assets/test.tex.minty");
    ViewportResourceHandle const viewportResourceHandle = resourceManager.load<ViewportResource>("Assets/test.vpt.minty");
    RenderPassResourceHandle const renderPassResourceHandle = resourceManager.load<RenderPassResource>("Assets/test.rpa.minty");
    ShaderResourceHandle const shaderFragResourceHandle = resourceManager.load<ShaderResource>("Assets/test.frag.sha.minty");
    ShaderResourceHandle const shaderVertResourceHandle = resourceManager.load<ShaderResource>("Assets/test.vert.sha.minty");
    PipelineResourceHandle const pipelineResourceHandle = resourceManager.load<PipelineResource>("Assets/test.pip.minty");
    MaterialResourceHandle const materialResourceHandle = resourceManager.load<MaterialResource>("Assets/test.mat.minty");
    MeshResourceHandle const meshResourceHandle = resourceManager.load<MeshResource>("Assets/test.msh.minty");

    // AUDIO
    AudioManagerInfo audioInfo{};
    AudioManager audioManager(audioInfo);

    ClipHandle const clipHandle = audioManager.create(clipResourceHandle);

    // WINDOW
    WindowManagerInfo windowManagerInfo{};
    WindowManager windowManager(windowManagerInfo);

    WindowInfo windowInfo{};
    windowInfo.title = "Minty Engine - Demo";
    windowInfo.size.x = 800;
    windowInfo.size.y = 600;
    WindowHandle const window = windowManager.create(windowInfo);

    // RENDER
    RenderManagerInfo renderManagerInfo{};
    renderManagerInfo.window = window;
    RenderManager renderManager(renderManagerInfo);

    TextureHandle const textureHandle = renderManager.create(textureResourceHandle);
    RenderPassHandle const renderPassHandle = renderManager.create(renderPassResourceHandle);
    ShaderHandle const shaderFragHandle = renderManager.create(shaderFragResourceHandle);
    ShaderHandle const shaderVertHandle = renderManager.create(shaderVertResourceHandle);
    PipelineHandle const pipelineHandle = renderManager.create(pipelineResourceHandle);
    MaterialHandle const materialHandle = renderManager.create(materialResourceHandle);
    Camera camera{};
    RenderViewInfo renderViewInfo{};
    RenderViewHandle const renderViewHandle = renderManager.create(renderViewInfo, camera);

    // SETUP
    audioManager.play(clipHandle);

    // MAIN LOOP
    while (windowManager.is_open(window))
    {
        windowManager.process_events();

        if (renderManager.begin_frame())
        {
            if (renderManager.begin_pass(renderPassHandle))
            {
                renderManager.bind(renderViewHandle);
                renderManager.bind(pipelineHandle);
                renderManager.bind(materialHandle);

                renderManager.end_pass();
            }
            renderManager.end_frame();
        }
    }

    return 0;
}
