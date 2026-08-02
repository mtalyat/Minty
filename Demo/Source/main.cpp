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
    ViewportResourceHandle const viewportResourceHandle = resourceManager.load<ViewportResource>("../Data/Default/Viewport/default.vpt.minty");
    RenderPassResourceHandle const renderPassResourceHandle = resourceManager.load<RenderPassResource>("../Data/Default/RenderPass/default.rpa.minty");
    ShaderResourceHandle const shaderFragResourceHandle = resourceManager.load<ShaderResource>("../Data/Default/Shader/default.frag.sha.minty");
    ShaderResourceHandle const shaderVertResourceHandle = resourceManager.load<ShaderResource>("../Data/Default/Shader/default.vert.sha.minty");
    PipelineResourceHandle const pipelineResourceHandle = resourceManager.load<PipelineResource>("../Data/Default/Pipeline/default.pip.minty");
    MaterialResourceHandle const materialResourceHandle = resourceManager.load<MaterialResource>("Assets/test.mat.minty");
    MeshResourceHandle const meshResourceHandle = resourceManager.load<MeshResource>("Assets/test.msh.minty");
    ShaderResourceHandle const spriteVertResourceHandle = resourceManager.load<ShaderResource>("../Data/Default/Shader/sprite.vert.sha.minty");
    ShaderResourceHandle const spriteFragResourceHandle = resourceManager.load<ShaderResource>("../Data/Default/Shader/sprite.frag.sha.minty");
    PipelineResourceHandle const spritePipelineResourceHandle = resourceManager.load<PipelineResource>("../Data/Default/Pipeline/sprite.pip.minty");
    MaterialResourceHandle const spriteMaterialResourceHandle = resourceManager.load<MaterialResource>("../Data/Default/Material/sprite.mat.minty");
    SpriteResourceHandle const spriteResourceHandle = resourceManager.load<SpriteResource>("Assets/test.spr.minty");

    // Create render data
    RenderManager& renderManager = app.get_render_manager();
    TextureHandle const textureHandle = renderManager.create(textureResourceHandle);
    RenderPassHandle const renderPassHandle = renderManager.create(renderPassResourceHandle);
    PipelineHandle const pipelineHandle = renderManager.create(pipelineResourceHandle);
    MaterialHandle const materialHandle = renderManager.create(materialResourceHandle);
    GeometryHandle const geometryHandle = renderManager.create(meshResourceHandle);
    PipelineHandle const spritePipelineHandle = renderManager.create(spritePipelineResourceHandle);
    MaterialHandle const spriteMaterialHandle = renderManager.create(spriteMaterialResourceHandle);
    SpriteHandle const spriteHandle = renderManager.create(spriteResourceHandle);

    // Create Scenes
    SceneManager& sceneManager = app.get_scene_manager();
    SceneInfo sceneInfo{};
    sceneInfo.name = "World Scene";
    SceneHandle const worldSceneHandle = sceneManager.create(sceneInfo);
    sceneInfo.name = "UI Scene";
    SceneHandle const uiSceneHandle = sceneManager.create(sceneInfo);

    // WORLD SCENE
    Scene& worldScene = sceneManager.at(worldSceneHandle);
    SystemManager& worldSystemManager = worldScene.get_system_manager();
    EntityManager& worldEntityManager = worldScene.get_entity_manager();

    // Add the systems
    worldSystemManager.create_system<RenderSystem>();

    // Create camera entity
    EntityHandle const cameraEntity = worldEntityManager.create();
    CameraComponent& cameraComponent = worldEntityManager.add<CameraComponent>(cameraEntity);
    CameraInfo cameraInfo{};
    cameraInfo.aspectRatio = static_cast<Float>(applicationInfo.windowInfo.size.x) / static_cast<Float>(applicationInfo.windowInfo.size.y);
    cameraComponent.camera = Camera(cameraInfo);
    RenderViewInfo renderViewInfo{};
    renderViewInfo.direction = Math::FORWARD;
    cameraComponent.renderViewHandle = renderManager.create(renderViewInfo, cameraComponent.camera);
    worldEntityManager.add<TransformComponent>(cameraEntity, Transform{
        Float3{0.0f, 0.0f, 0.0f}
    });

    // Create model entity
    EntityHandle const modelEntity = worldEntityManager.create();
    worldEntityManager.add<TransformComponent>(modelEntity, Transform{
        Float3{-5.0f, 0.0f, 5.0f}
    });
    worldEntityManager.add<MeshComponent>(modelEntity, MeshComponent{
        geometryHandle,
        materialHandle
    });
    // worldEntityManager.add<VisibleTag>(modelEntity);

    // Create sprite entity
    EntityHandle const spriteEntity = worldEntityManager.create();
    worldEntityManager.add<TransformComponent>(spriteEntity, Transform{
        Float3{0.0f, 0.0f, 1.0f}
    });
    worldEntityManager.add<SpriteComponent>(spriteEntity, SpriteComponent{
        spriteHandle,
        spriteMaterialHandle
    });
    worldEntityManager.add<VisibleTag>(spriteEntity);

    // Enable scene
    sceneManager.enable(worldSceneHandle);

    // UI SCENE
    // Scene& uiScene = sceneManager.at(uiSceneHandle);
    // SystemManager& uiSystemManager = uiScene.get_system_manager();
    // EntityManager& uiEntityManager = uiScene.get_entity_manager();

    // // Add the systems
    // uiSystemManager.create_system<RenderSystem>();

    // // Create camera entity
    // EntityHandle const uiCameraEntity = uiEntityManager.create();
    // CameraComponent& uiCameraComponent = uiEntityManager.add<CameraComponent>(uiCameraEntity);
    // RenderViewInfo uiRenderViewInfo{};
    // uiRenderViewInfo.direction = Math::FORWARD;
    // uiCameraComponent.renderViewHandle = renderManager.create(uiRenderViewInfo, uiCameraComponent.camera);
    // uiEntityManager.add<TransformComponent>(uiCameraEntity);

    // // Create canvas entity
    // EntityHandle const canvasEntity = uiEntityManager.create();

    // // Create sprite entity
    // EntityHandle const spriteEntity = uiEntityManager.create();
    // uiEntityManager.add<UITransformComponent>(spriteEntity, INVALID_ENTITY,
    //     UITransform{0.0f, 0.0f, 100.0f, 100.0f, AnchorEnumFlags::Center
    //     });
    // uiEntityManager.add<SpriteComponent>(spriteEntity, spriteHandle);

    // // Enable scene
    // sceneManager.enable(uiSceneHandle);

    // Run application
    return app.run();
}
