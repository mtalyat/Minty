#include "Test_RenderTarget.h"
#include "Minty.h"

void test_RenderTarget(Test& _test)
{
	CATEGORY(RenderTarget)
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
			RenderTargetBuilder builder{};
			EXPECT_FAILURE(RenderTarget::create(builder));
			
			RenderPassBuilder passBuilder{};
			passBuilder.colorAttachment = &colorAttachment;
			passBuilder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(passBuilder);

			builder.renderPass = renderPass;
			EXPECT_FAILURE(RenderTarget::create(builder));
			
			builder.renderPass = nullptr;
			builder.images = renderManager.get_surface()->get_images();
			EXPECT_FAILURE(RenderTarget::create(builder));
			builder.renderPass = renderPass;
			EXPECT_SUCCESS(RenderTarget::create(builder));
		}

		TEST("Get Render Pass")
		{
			RenderPassBuilder passBuilder{};
			passBuilder.colorAttachment = &colorAttachment;
			passBuilder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(passBuilder);

			RenderTargetBuilder builder{};
			builder.renderPass = renderPass;
			builder.images = renderManager.get_surface()->get_images();
			Owner<RenderTarget> renderTarget = RenderTarget::create(builder);

			EXPECT_EQUAL(renderTarget->get_render_pass(), renderPass);
		}

		TEST("Get Images")
		{
			RenderPassBuilder passBuilder{};
			passBuilder.colorAttachment = &colorAttachment;
			passBuilder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(passBuilder);

			RenderTargetBuilder builder{};
			builder.renderPass = renderPass;
			builder.images = renderManager.get_surface()->get_images();
			Owner<RenderTarget> renderTarget = RenderTarget::create(builder);
			
			EXPECT_EQUAL(renderTarget->get_images().get_size(), renderManager.get_surface()->get_images().get_size());
			for (Size i = 0; i < renderTarget->get_images().get_size(); i++)
			{
				EXPECT_EQUAL(renderTarget->get_images()[i]->get_id(), renderManager.get_surface()->get_images()[i]->get_id());
			}
		}

		TEST("Get Size")
		{
			RenderPassBuilder passBuilder{};
			passBuilder.colorAttachment = &colorAttachment;
			passBuilder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(passBuilder);

			RenderTargetBuilder builder{};
			builder.renderPass = renderPass;
			builder.images = renderManager.get_surface()->get_images();
			Owner<RenderTarget> renderTarget = RenderTarget::create(builder);

			EXPECT_EQUAL(renderTarget->get_size(), renderManager.get_surface()->get_size());
		}

		TEST("Get Asset Type")
		{
			RenderPassBuilder passBuilder{};
			passBuilder.colorAttachment = &colorAttachment;
			passBuilder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(passBuilder);
			
			RenderTargetBuilder builder{};
			builder.renderPass = renderPass;
			builder.images = renderManager.get_surface()->get_images();
			Owner<RenderTarget> renderTarget = RenderTarget::create(builder);

			EXPECT_EQUAL(renderTarget->get_asset_type(), AssetType::RenderTarget);
		}

		TEST("Refresh")
		{
			RenderPassBuilder passBuilder{};
			passBuilder.colorAttachment = &colorAttachment;
			passBuilder.depthAttachment = &depthAttachment;
			Owner<RenderPass> renderPass = RenderPass::create(passBuilder);

			RenderTargetBuilder builder{};
			builder.renderPass = renderPass;
			builder.images = renderManager.get_surface()->get_images();
			Owner<RenderTarget> renderTarget = RenderTarget::create(builder);

			EXPECT_SUCCESS(renderTarget->refresh(builder));
		}
	}
}
