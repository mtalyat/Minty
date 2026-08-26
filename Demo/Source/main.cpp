#include <Minty.hpp>
#include "World/Component/CanvasComponent.hpp"
#include "World/Component/TextComponent.hpp"

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
    ClipResourceHandle const clipResourceHandle = resourceManager.load<ClipResource>("Demo/Assets/test2.clp.minty");
    ImageResourceHandle const imageResourceHandle = resourceManager.load<ImageResource>("Demo/Assets/test.img.minty");
    TextureResourceHandle const textureResourceHandle = resourceManager.load<TextureResource>("Demo/Assets/test.tex.minty");
    ViewportResourceHandle const viewportResourceHandle = resourceManager.load<ViewportResource>("Data/Default/Viewport/default.vpt.minty");
    RenderPassResourceHandle const renderPassResourceHandle = resourceManager.load<RenderPassResource>("Data/Default/RenderPass/default.rpa.minty");
    ShaderResourceHandle const shaderFragResourceHandle = resourceManager.load<ShaderResource>("Data/Default/Shader/default.frag.sha.minty");
    ShaderResourceHandle const shaderVertResourceHandle = resourceManager.load<ShaderResource>("Data/Default/Shader/default.vert.sha.minty");
    PipelineResourceHandle const pipelineResourceHandle = resourceManager.load<PipelineResource>("Data/Default/Pipeline/default.pip.minty");
    MaterialResourceHandle const materialResourceHandle = resourceManager.load<MaterialResource>("Demo/Assets/test.mat.minty");
    MeshResourceHandle const meshResourceHandle = resourceManager.load<MeshResource>("Demo/Assets/test.msh.minty");
    ShaderResourceHandle const spriteVertResourceHandle = resourceManager.load<ShaderResource>("Data/Default/Shader/sprite.vert.sha.minty");
    ShaderResourceHandle const spriteFragResourceHandle = resourceManager.load<ShaderResource>("Data/Default/Shader/sprite.frag.sha.minty");
    ShaderResourceHandle const uiVertResourceHandle = resourceManager.load<ShaderResource>("Data/Default/Shader/ui.vert.sha.minty");
    ShaderResourceHandle const uiFragResourceHandle = resourceManager.load<ShaderResource>("Data/Default/Shader/ui.frag.sha.minty");
    ShaderResourceHandle const uiFontVertResourceHandle = resourceManager.load<ShaderResource>("Data/Default/Shader/ui_font.vert.sha.minty");
    ShaderResourceHandle const uiFontFragResourceHandle = resourceManager.load<ShaderResource>("Data/Default/Shader/ui_font.frag.sha.minty");
    PipelineResourceHandle const spritePipelineResourceHandle = resourceManager.load<PipelineResource>("Data/Default/Pipeline/sprite.pip.minty");
    PipelineResourceHandle const uiPipelineResourceHandle = resourceManager.load<PipelineResource>("Data/Default/Pipeline/ui.pip.minty");
    PipelineResourceHandle const uiFontPipelineResourceHandle = resourceManager.load<PipelineResource>("Data/Default/Pipeline/ui_font.pip.minty");
    MaterialResourceHandle const spriteMaterialResourceHandle = resourceManager.load<MaterialResource>("Data/Default/Material/sprite.mat.minty");
    MaterialResourceHandle const uiMaterialResourceHandle = resourceManager.load<MaterialResource>("Data/Default/Material/ui.mat.minty");
    ImageResourceHandle const defaultFontImageResourceHandle = resourceManager.load<ImageResource>("Data/Default/Image/default_font.img.minty");
    TextureResourceHandle const defaultFontTextureResourceHandle = resourceManager.load<TextureResource>("Data/Default/Texture/default_font.tex.minty");
    MaterialResourceHandle const uiFontMaterialResourceHandle = resourceManager.load<MaterialResource>("Data/Default/Material/ui_font.mat.minty");
    FontResourceHandle const defaultFontResourceHandle = resourceManager.load<FontResource>("Data/Default/Font/default.fnt.minty");
    SpriteResourceHandle const spriteResourceHandle1 = resourceManager.load<SpriteResource>("Demo/Assets/test.spr.minty");
    SpriteResourceHandle const spriteResourceHandle2 = resourceManager.load<SpriteResource>("Demo/Assets/test2.spr.minty");

    (void)defaultFontImageResourceHandle;
    (void)defaultFontTextureResourceHandle;

    // Create render data
    RenderManager& renderManager = app.get_render_manager();
    TextureHandle const textureHandle = renderManager.create(textureResourceHandle);
    RenderPassHandle const renderPassHandle = renderManager.create(renderPassResourceHandle);
    PipelineHandle const pipelineHandle = renderManager.create(pipelineResourceHandle);
    MaterialHandle const materialHandle = renderManager.create(materialResourceHandle);
    GeometryHandle const geometryHandle = renderManager.create(meshResourceHandle);
    PipelineHandle const spritePipelineHandle = renderManager.create(spritePipelineResourceHandle);
    PipelineHandle const uiPipelineHandle = renderManager.create(uiPipelineResourceHandle);
    PipelineHandle const uiFontPipelineHandle = renderManager.create(uiFontPipelineResourceHandle);
    MaterialHandle const spriteMaterialHandle = renderManager.create(spriteMaterialResourceHandle);
    MaterialHandle const uiMaterialHandle = renderManager.create(uiMaterialResourceHandle);
    MaterialHandle const uiFontMaterialHandle = renderManager.create(uiFontMaterialResourceHandle);
    SpriteHandle const spriteHandle1 = renderManager.create(spriteResourceHandle1);
    SpriteHandle const spriteHandle2 = renderManager.create(spriteResourceHandle2);

    // Create Scenes
    SceneManager& sceneManager = app.get_scene_manager();
    SceneInfo sceneInfo{};
    sceneInfo.name = "World Scene";
    SceneHandle const worldSceneHandle = sceneManager.create(sceneInfo);

    SceneInfo uiSceneInfo{};
    uiSceneInfo.name = "UI Scene";
    uiSceneInfo.priority = 1;
    SceneHandle const uiSceneHandle = sceneManager.create(uiSceneInfo);

    // WORLD SCENE
    Scene& worldScene = sceneManager.at(worldSceneHandle);
    SystemManager& worldSystemManager = worldScene.get_system_manager();
    EntityManager& worldEntityManager = worldScene.get_entity_manager();

    // UI SCENE
    Scene& uiScene = sceneManager.at(uiSceneHandle);
    SystemManager& uiSystemManager = uiScene.get_system_manager();
    EntityManager& uiEntityManager = uiScene.get_entity_manager();

    // Add the systems
    worldSystemManager.create_system<RenderSystem>();
    uiSystemManager.create_system<RenderSystem>();

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

    // Create UI scene camera entity so the render view is always bound for UI draws.
    EntityHandle const uiCameraEntity = uiEntityManager.create();
    CameraComponent& uiCameraComponent = uiEntityManager.add<CameraComponent>(uiCameraEntity);
    CameraInfo uiCameraInfo{};
    uiCameraInfo.aspectRatio = static_cast<Float>(applicationInfo.windowInfo.size.x) / static_cast<Float>(applicationInfo.windowInfo.size.y);
    uiCameraComponent.camera = Camera(uiCameraInfo);
    RenderViewInfo uiRenderViewInfo{};
    uiRenderViewInfo.direction = Math::FORWARD;
    uiCameraComponent.renderViewHandle = renderManager.create(uiRenderViewInfo, uiCameraComponent.camera);
    uiEntityManager.add<TransformComponent>(uiCameraEntity, Transform{
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
    worldEntityManager.add<VisibleTag>(modelEntity);

    // Create sprite entity
    EntityHandle const spriteEntity = worldEntityManager.create();
    worldEntityManager.add<TransformComponent>(spriteEntity, Transform{
        Float3{0.0f, 0.0f, 1.0f}
    });
    worldEntityManager.add<SpriteComponent>(spriteEntity, SpriteComponent{
        spriteHandle1,
        spriteMaterialHandle
    });
    worldEntityManager.add<VisibleTag>(spriteEntity);

    // Create child entity
    EntityHandle const childEntity = worldEntityManager.create(spriteEntity);
    worldEntityManager.add<TransformComponent>(childEntity, Transform{
        Float3{1.0f, 0.0f, 1.0f}
    });
    worldEntityManager.add<SpriteComponent>(childEntity, SpriteComponent{
        spriteHandle2,
        spriteMaterialHandle
    });
    worldEntityManager.add<VisibleTag>(childEntity);

    // Create canvas root entity
    EntityHandle const uiCanvasEntity = uiEntityManager.create();
    CanvasComponent& canvasComponent = uiEntityManager.add<CanvasComponent>(uiCanvasEntity);
    canvasComponent.resizeMode = CanvasResizeModeEnum::Dynamic;
    Int2 const initialFramebufferSize = app.get_window().get_framebuffer_size();
    UInt2 const initialCanvasResolution = UInt2(
        static_cast<UInt>(Math::max(initialFramebufferSize.x, 1)),
        static_cast<UInt>(Math::max(initialFramebufferSize.y, 1)));
    canvasComponent.resolution = initialCanvasResolution;
    UITransformComponent& canvasTransformComponent = uiEntityManager.add<UITransformComponent>(uiCanvasEntity);
    canvasTransformComponent.canvas = uiCanvasEntity;
    canvasTransformComponent.transform = UITransform(0.0f, 0.0f,
        static_cast<Float>(initialCanvasResolution.x),
        static_cast<Float>(initialCanvasResolution.y),
        AnchorEnumFlags::TopLeft);

    // Create child UI entity anchored to the canvas
    EntityHandle const uiChildEntity = uiEntityManager.create(uiCanvasEntity);
    UITransformComponent& childTransformComponent = uiEntityManager.add<UITransformComponent>(uiChildEntity);
    childTransformComponent.canvas = uiCanvasEntity;
    childTransformComponent.transform = UITransform(16.0f, -16.0f, 64.0f, 64.0f, AnchorEnumFlags::TopLeft);
    uiEntityManager.add<SpriteComponent>(uiChildEntity, SpriteComponent{
        spriteHandle2,
        uiMaterialHandle
    });
    uiEntityManager.add<VisibleTag>(uiChildEntity);

    EntityHandle const uiChildEntity2 = uiEntityManager.create(uiCanvasEntity);
    UITransformComponent& childTransformComponent2 = uiEntityManager.add<UITransformComponent>(uiChildEntity2);
    childTransformComponent2.canvas = uiCanvasEntity;
    childTransformComponent2.transform = UITransform(-16.0f, 16.0f, 64.0f, 64.0f, AnchorEnumFlags::BottomRight);
    uiEntityManager.add<SpriteComponent>(uiChildEntity2, SpriteComponent{
        spriteHandle1,
        uiMaterialHandle
    });
    uiEntityManager.add<VisibleTag>(uiChildEntity2);

    EntityHandle const uiTextEntity = uiEntityManager.create(uiCanvasEntity);
    UITransformComponent &textTransformComponent = uiEntityManager.add<UITransformComponent>(uiTextEntity);
    textTransformComponent.canvas = uiCanvasEntity;
    textTransformComponent.transform = UITransform(24.0f, -32.0f, 320.0f, 32.0f, AnchorEnumFlags::TopLeft);

    TextComponent &textComponent = uiEntityManager.add<TextComponent>(uiTextEntity);
    textComponent.text = "Hello world!";
    textComponent.color = Color::white();
    textComponent.fontResourceHandle = defaultFontResourceHandle;
    textComponent.materialHandle = uiFontMaterialHandle;
    textComponent.dirty = true;

    uiEntityManager.add<VisibleTag>(uiTextEntity);

    // Enable scene
    sceneManager.enable(worldSceneHandle);
    sceneManager.enable(uiSceneHandle);

    // Run application
    return app.run();
}
