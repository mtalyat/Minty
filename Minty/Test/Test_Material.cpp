#include "Test_Material.h"
#include "Minty.h"

void test_Material(Test& _test)
{
	CATEGORY(Material)
	{
		Owner<Window> window = Window::create({});
		ContextBuilder contextBuilder{};
		contextBuilder.renderManagerBuilder.window = window;
		contextBuilder.assetManagerBuilder.wraps.add("Assets/test.wrap");
		Context context(contextBuilder);

		// load stuff
		RenderManager& renderManager = context.get_render_manager();
		AssetManager& assetManager = context.get_asset_manager();
		Ref<Viewport> const& viewport = renderManager.get_default_viewport();
		Ref<Texture> const& texture = assetManager.load<Texture>("Defaults/Texture/defaultTexture.png");
		Ref<ShaderModule> const& vertexModule = assetManager.load<ShaderModule>("Defaults/ShaderModule/defaultModule.vert.spv");
		Ref<ShaderModule> const& fragmentModule = assetManager.load<ShaderModule>("Defaults/ShaderModule/defaultModule.frag.spv");
		Ref<RenderPass> const& renderPass = assetManager.load<RenderPass>("Defaults/RenderPass/defaultRenderPass.mrpa");
		Ref<Shader> const& shader = assetManager.load<Shader>("Defaults/Shader/defaultShader.msha");
		Ref<MaterialTemplate> const& materialTemplate = assetManager.load<MaterialTemplate>("Defaults/MaterialTemplate/defaultMaterialTemplate.mmtp");

		TEST("Constructor/Create")
		{
			MaterialBuilder builder{};
			EXPECT_FAILURE(Material::create(builder));
			builder.materialTemplate = materialTemplate;
			EXPECT_SUCCESS(Material::create(builder));
			builder.values.add("xxx", Object());
			EXPECT_FAILURE(Material::create(builder));
			builder.values.remove("xxx");
			builder.values.add("camera", Object());
			EXPECT_SUCCESS(Material::create(builder));
		}

		TEST("Get Material Template")
		{
			MaterialBuilder builder{};
			builder.materialTemplate = materialTemplate;
			Owner<Material> material = Material::create(builder);
			EXPECT_EQUAL(materialTemplate, material->get_material_template());
		}

		TEST("Get Inputs")
		{
			MaterialBuilder builder{};
			builder.materialTemplate = materialTemplate;
			builder.values.add("camera", Object());
			Owner<Material> material = Material::create(builder);
			EXPECT_EQUAL(material->get_inputs().get_size(), 1);
			EXPECT_TRUE(material->get_inputs().contains("camera"));
			EXPECT_FALSE(material->get_inputs().contains("xxx"));
		}

		TEST("Get Asset Type")
		{
			MaterialBuilder builder{};
			builder.materialTemplate = materialTemplate;
			Owner<Material> material = Material::create(builder);
			EXPECT_EQUAL(material->get_asset_type(), AssetType::Material);
		}

		TEST("Set/Get Input")
		{
			MaterialBuilder builder{};
			builder.materialTemplate = materialTemplate;
			
			Owner<Material> material = Material::create(builder);
			EXPECT_FAILURE(material->set_input("xxx", nullptr, 0));
			EXPECT_FAILURE(material->set_input("camera", nullptr, 0));
			Matrix4 matrix = Math::identity<Matrix4>();
			EXPECT_FAILURE(material->set_input("camera", &matrix, 0));
			EXPECT_FAILURE(material->set_input("camera", &matrix, sizeof(Matrix4) + 1));
			EXPECT_FAILURE(material->set_input("camera", nullptr, sizeof(Matrix4)));
			EXPECT_SUCCESS(material->set_input("camera", &matrix, sizeof(Matrix4)));
		}

		TEST("Get Input")
		{

		}
	}
}
