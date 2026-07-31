#include <Minty.hpp>

using namespace Minty;

static Logger* sp_eventLogger = nullptr;

static void on_event(Event& event)
{
    sp_eventLogger->log(SeverityFlagsEnum::Info, F("Event: State={}, Type={}", event.get_state(), event.get_type()));
}

int main()
{
    // DEBUG
    DebugInfo debugInfo{};
    debugInfo.loggerInfo.path = "debug.log";
    Debug::initialize(debugInfo);

    // TODO: move into application...
    SystemManager::register_system<RenderSystem>("Render");

    // APPLICATION
    ApplicationInfo applicationInfo{};
    applicationInfo.windowInfo.title = "Minty Engine - Demo";
    applicationInfo.windowInfo.size.x = 800;
    applicationInfo.windowInfo.size.y = 600;
    Application app(applicationInfo);

    // Load data
    ResourceManager& resourceManager = app.get_resource_manager();
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

    // Create render data
    RenderManager& renderManager = app.get_render_manager();
    TextureHandle const textureHandle = renderManager.create(textureResourceHandle);
    RenderPassHandle const renderPassHandle = renderManager.create(renderPassResourceHandle);
    ShaderHandle const shaderFragHandle = renderManager.create(shaderFragResourceHandle);
    ShaderHandle const shaderVertHandle = renderManager.create(shaderVertResourceHandle);
    PipelineHandle const pipelineHandle = renderManager.create(pipelineResourceHandle);
    MaterialHandle const materialHandle = renderManager.create(materialResourceHandle);
    GeometryHandle const geometryHandle = renderManager.create(meshResourceHandle);

    // Create Scene
    SceneManager& sceneManager = app.get_scene_manager();
    SceneInfo sceneInfo{};
    sceneInfo.name = "Demo Scene";
    SceneHandle const sceneHandle = sceneManager.create(sceneInfo);

    // Modify the scene
    Scene& scene = sceneManager.at(sceneHandle);
    SystemManager& systemManager = scene.get_system_manager();
    EntityManager& entityManager = scene.get_entity_manager();

    // Add the systems
    systemManager.create_system<RenderSystem>();

    // Create camera entity
    EntityHandle const cameraEntity = entityManager.create();
    CameraComponent& cameraComponent = entityManager.add<CameraComponent>(cameraEntity);
    RenderViewInfo renderViewInfo{};
    renderViewInfo.direction = Math::FORWARD;
    cameraComponent.renderViewHandle = renderManager.create(renderViewInfo, cameraComponent.camera);
    entityManager.add<TransformComponent>(cameraEntity, Transform{
        Float3{0.0f, 0.0f, 0.0f}
    });

    // Create model entity
    EntityHandle const modelEntity = entityManager.create();
    entityManager.add<TransformComponent>(modelEntity, Transform{
        Float3{-5.0f, 0.0f, 5.0f}
    });
    entityManager.add<MeshComponent>(modelEntity, MeshComponent{
        geometryHandle,
        materialHandle
    });
    entityManager.add<VisibleTag>(modelEntity);

    // Enable scene
    sceneManager.enable(sceneHandle);

    // Run application
    return app.run();
}

// int main_old()
// {
//     // DEBUG
//     DebugInfo debugInfo{};
//     debugInfo.loggerInfo.path = "debug.log";
//     Debug::initialize(debugInfo);

//     // EVENTS
//     LoggerInfo loggerInfo{};
//     loggerInfo.logMode = LogModeEnum::File;
//     loggerInfo.path = "events.log";
//     Logger eventLogger(loggerInfo);
//     sp_eventLogger = &eventLogger;

//     // RESOURCE
//     ResourceManagerInfo info{};
//     ResourceManager resourceManager(info);

//     ClipResourceHandle const clipResourceHandle = resourceManager.load<ClipResource>("Assets/test2.clp.minty");
//     ImageResourceHandle const imageResourceHandle = resourceManager.load<ImageResource>("Assets/test.img.minty");
//     TextureResourceHandle const textureResourceHandle = resourceManager.load<TextureResource>("Assets/test.tex.minty");
//     ViewportResourceHandle const viewportResourceHandle = resourceManager.load<ViewportResource>("Assets/test.vpt.minty");
//     RenderPassResourceHandle const renderPassResourceHandle = resourceManager.load<RenderPassResource>("Assets/test.rpa.minty");
//     ShaderResourceHandle const shaderFragResourceHandle = resourceManager.load<ShaderResource>("Assets/test.frag.sha.minty");
//     ShaderResourceHandle const shaderVertResourceHandle = resourceManager.load<ShaderResource>("Assets/test.vert.sha.minty");
//     PipelineResourceHandle const pipelineResourceHandle = resourceManager.load<PipelineResource>("Assets/test.pip.minty");
//     MaterialResourceHandle const materialResourceHandle = resourceManager.load<MaterialResource>("Assets/test.mat.minty");
//     MeshResourceHandle const meshResourceHandle = resourceManager.load<MeshResource>("Assets/test.msh.minty");

//     // AUDIO
//     AudioManagerInfo audioInfo{};
//     AudioManager audioManager(audioInfo);

//     ClipHandle const clipHandle = audioManager.create(clipResourceHandle);

//     // WINDOW
//     WindowInfo windowInfo{};
//     windowInfo.title = "Minty Engine - Demo";
//     windowInfo.size.x = 800;
//     windowInfo.size.y = 600;
//     Window window(windowInfo);

//     // RENDER
//     RenderManagerInfo renderManagerInfo{};
//     renderManagerInfo.window = &window;
//     RenderManager renderManager(renderManagerInfo);

//     TextureHandle const textureHandle = renderManager.create(textureResourceHandle);
//     RenderPassHandle const renderPassHandle = renderManager.create(renderPassResourceHandle);
//     ShaderHandle const shaderFragHandle = renderManager.create(shaderFragResourceHandle);
//     ShaderHandle const shaderVertHandle = renderManager.create(shaderVertResourceHandle);
//     PipelineHandle const pipelineHandle = renderManager.create(pipelineResourceHandle);
//     MaterialHandle const materialHandle = renderManager.create(materialResourceHandle);
//     GeometryHandle const geometryHandle = renderManager.create(meshResourceHandle);
//     Camera camera{};
//     camera.direction = Float3(0.0f, 0.0f, 1.0f);
//     camera.aspectRatio = static_cast<Float>(windowInfo.size.x) / static_cast<Float>(windowInfo.size.y);
//     RenderViewInfo renderViewInfo{};
//     RenderViewHandle const renderViewHandle = renderManager.create(renderViewInfo, camera);

//     // SCENE
//     SceneManagerInfo sceneManagerInfo{};
//     SceneManager sceneManager(sceneManagerInfo);
//     SceneInfo sceneInfo{};
//     SceneHandle const sceneHandle = sceneManager.create(sceneInfo);
//     Scene &scene = sceneManager.at(sceneHandle);
//     SystemManager &systemManager = scene.get_system_manager();
//     EntityManager &entityManager = scene.get_entity_manager();

//     // SETUP
//     audioManager.play(clipHandle);
//     Transform transform{};
//     transform.set_position(Float3(-5.0f, 0.0f, 5.0f));

//     // MAIN LOOP
//     while (window.is_open())
//     {
//         // Process events...

//         // Begin frame and pass
//         if (!renderManager.begin_frame())
//         {
//             continue;
//         }
//         if (!renderManager.begin_pass(renderPassHandle))
//         {
//             renderManager.end_frame();
//             continue;
//         }

//         // Bind assets
//         renderManager.bind(renderViewHandle);
//         renderManager.bind(pipelineHandle); 
//         renderManager.bind(materialHandle);
//         renderManager.bind(geometryHandle);

//         // Draw scene
//         renderManager.draw(transform);

//         // End pass and frame
//         renderManager.end_pass();
//         renderManager.end_frame();
//     }

//     return 0;
// }
