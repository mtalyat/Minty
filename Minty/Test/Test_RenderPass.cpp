#include "Test_RenderPass.h"
#include "Minty.h"

void test_RenderPass(Test& _test)
{
	CATEGORY(RenderPass)
	{
		Owner<Window> window = Window::create();
		ContextBuilder contextBuilder{};
		contextBuilder.renderManagerBuilder.window = window;
		Context context(contextBuilder);

		RenderManager& renderManager = context.get_render_manager();

		RenderAttachment colorAttachment{};
		colorAttachment.type = RenderAttachment::Type::Color;
		colorAttachment.loadOperation = LoadOperation::Clear;
		colorAttachment.storeOperation = StoreOperation::Store;
		colorAttachment.initialLayout = ImageLayout::Undefined;
		colorAttachment.finalLayout = ImageLayout::Presentation;

		RenderAttachment depthAttachment{};
		depthAttachment.type = RenderAttachment::Type::Depth;
		depthAttachment.loadOperation = LoadOperation::Clear;
		depthAttachment.storeOperation = StoreOperation::Store;
		depthAttachment.initialLayout = ImageLayout::Undefined;
		depthAttachment.finalLayout = ImageLayout::DepthStencilAttachment;

		TEST("Constructor/Create")
		{
			RenderPassBuilder builder{};
			builder.colorAttachment = &colorAttachment;
			builder.depthAttachment = &depthAttachment;
			EXPECT_SUCCESS(RenderPass::create(builder));
		}

		TEST("Has Color Attachment")
		{
			RenderPassBuilder builder{};
			builder.colorAttachment = &colorAttachment;
			builder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(builder);
			EXPECT_TRUE(renderPass->has_color_attachment());
			builder.colorAttachment = nullptr;
			renderPass = RenderPass::create(builder);
			EXPECT_FALSE(renderPass->has_color_attachment());
		}

		TEST("Has Depth Attachment")
		{
			RenderPassBuilder builder{};
			builder.colorAttachment = &colorAttachment;
			builder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(builder);
			EXPECT_TRUE(renderPass->has_depth_attachment());
			builder.depthAttachment = nullptr;
			renderPass = RenderPass::create(builder);
			EXPECT_FALSE(renderPass->has_depth_attachment());
		}

		TEST("Get Asset Type")
		{
			RenderPassBuilder builder{};
			builder.colorAttachment = &colorAttachment;
			builder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(builder);
			EXPECT_EQUAL(renderPass->get_asset_type(), AssetType::RenderPass);
		}

		TEST("Get Native")
		{
			RenderPassBuilder builder{};
			builder.colorAttachment = &colorAttachment;
			builder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(builder);
			EXPECT_NOT_EQUAL(renderPass->get_native(), nullptr);
		}

		TEST("Refresh")
		{
			// create pass
			RenderPassBuilder builder{};
			builder.colorAttachment = &colorAttachment;
			builder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(builder);

			// create targets
			RenderTargetBuilder targetBuilder{};
			targetBuilder.renderPass = renderPass;
			targetBuilder.images = renderManager.get_surface()->get_images();
			Size const TARGET_COUNT = 3;
			Vector<Owner<RenderTarget>> renderTargets;
			renderTargets.reserve(TARGET_COUNT);
			for (Size i = 0; i < TARGET_COUNT; i++)
			{
				renderTargets.add(RenderTarget::create(targetBuilder));
			}

			// refresh targets
			EXPECT_SUCCESS(renderPass->refresh(targetBuilder));
		}

		TEST("Register Render Target")
		{
			// TODO: not sure how to test this
		}

		TEST("Unregister Render Target")
		{
			// TODO: not sure how to test this
		}
	}
}
