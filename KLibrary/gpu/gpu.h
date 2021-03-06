#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>

#include "libspec/using.h"
#include "gpu/gpu.h"
#include "math/int2.h"
#include "math/float4.h"
#include "geometry/vertex.h"
#include "graphics/image.h"

#pragma comment (lib, "d3d11.lib")


namespace kl {
	class gpu {
	private:
		// DirectX pointers
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* devcon = nullptr;
		IDXGISwapChain* chain = nullptr;

		// Internal buffers
		ID3D11RenderTargetView* interFrameBuff = nullptr;
		ID3D11DepthStencilView* interDepthBuff = nullptr;

		// Buffers
		std::set<IUnknown*> children;

		// Predefined constant buffers
		bool cbuffsPredefined = false;
		ID3D11Buffer* vertCBuffs[32] = {};
		ID3D11Buffer* pixlCBuffs[32] = {};

	public:
		gpu(HWND hwnd, bool predefineCBuffs = true);
		gpu(const kl::gpu&) = delete;
		void operator=(const kl::gpu&) = delete;
		~gpu();

		// Getters
		ID3D11Device* dev();
		ID3D11DeviceContext* con();

		// Sets the viewport
		void viewport(const kl::int2& pos, const kl::int2& size);

		// Regenerates the buffers
		void regenBuffers(const kl::int2& size);

		// Binds the internal render targets
		void bindInternal(const std::vector<ID3D11RenderTargetView*> targets = {}, ID3D11DepthStencilView* depthView = nullptr);

		// Binds given render target
		void bindTargets(const std::vector<ID3D11RenderTargetView*> targets, ID3D11DepthStencilView* depthView = nullptr);

		// Clears the buffer
		void clearColor(const kl::float4& color);
		void clearDepth();
		void clear(const kl::float4& color);

		// Swaps the buffers
		void swap(bool vSync);

		// Raster state
		ID3D11RasterizerState* newRasterState(D3D11_RASTERIZER_DESC* desc);
		ID3D11RasterizerState* newRasterState(bool wireframe, bool cull, bool cullBack = true);
		void bind(ID3D11RasterizerState* state);

		// Depth stenicl state
		ID3D11DepthStencilState* newDepthState(D3D11_DEPTH_STENCIL_DESC* desc);
		ID3D11DepthStencilState* newDepthState(bool depth, bool stencil, bool mask);
		void bind(ID3D11DepthStencilState* state);

		// Shaders
		ID3D11VertexShader* newVertexShader(const String& source, ID3D11InputLayout** outLayout = nullptr, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc = {});
		ID3D11PixelShader* newPixelShader(const String& source);
		void bind(ID3D11VertexShader* sha);
		void bind(ID3D11PixelShader* sha);
		void bind(ID3D11InputLayout* layout);

		// Buffer
		ID3D11Buffer* newBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* subData = nullptr);

		// Constant buffer
		ID3D11Buffer* newConstBuffer(int byteSize);
		void setBuffData(ID3D11Buffer* buff, const void* data);
		void bindVertCBuff(ID3D11Buffer* buff, int slot);
		void bindPixlCBuff(ID3D11Buffer* buff, int slot);
		template<typename T> inline bool autoSetVertBuff(const T& data) {
			const size_t dataSize = sizeof(T);
			if (!cbuffsPredefined || dataSize > 512 || dataSize % 16) {
				return false;
			}
			ID3D11Buffer* approBuffer = vertCBuffs[dataSize / 16 - 1];
			bindVertCBuff(approBuffer, 0);
			setBuffData(approBuffer, &data);
			return true;
		}
		template<typename T> inline bool autoSetPixlBuff(const T& data) {
			const size_t dataSize = sizeof(T);
			if (!cbuffsPredefined || dataSize > 512 || dataSize % 16) {
				return false;
			}
			ID3D11Buffer* approBuffer = pixlCBuffs[dataSize / 16 - 1];
			bindPixlCBuff(approBuffer, 0);
			setBuffData(approBuffer, &data);
			return true;
		}

		// Mesh
		ID3D11Buffer* newVertBuffer(const std::vector<kl::vertex>& vertexData);
		ID3D11Buffer* newVertBuffer(const String& filePath, bool flipZ = true);
		void draw(ID3D11Buffer* mesh);

		// Sampler
		ID3D11SamplerState* newSamplerState(D3D11_SAMPLER_DESC* desc);
		ID3D11SamplerState* newSamplerState(bool linear, bool mirror);
		void bind(ID3D11SamplerState* sampState, int slot);

		// Texture
		ID3D11Texture2D* newTextureBB();
		ID3D11Texture2D* newTexture(D3D11_TEXTURE2D_DESC* desc, D3D11_SUBRESOURCE_DATA* subData = nullptr);
		ID3D11Texture2D* newTexture(const kl::image& img);
		ID3D11Texture2D* newTexture(const kl::image& front, const kl::image& back, const kl::image& left, const kl::image& right, const kl::image& top, const kl::image& bottom);
		ID3D11Texture2D* newTextureST(ID3D11Texture2D* tex, const kl::int2& size = {});

		// Render target view
		ID3D11RenderTargetView* newTargetView(ID3D11Texture2D* tex, D3D11_RENDER_TARGET_VIEW_DESC* desc = nullptr);
		void clear(ID3D11RenderTargetView* view, const kl::float4& color);

		// Depth stencil view
		ID3D11DepthStencilView* newDepthView(ID3D11Texture2D* tex, D3D11_DEPTH_STENCIL_VIEW_DESC* desc = nullptr);
		void clear(ID3D11DepthStencilView* view, float depth = 1.0f, byte stencil = 0);

		// Shader resource view
		ID3D11ShaderResourceView* newShaderView(ID3D11Texture2D* tex, D3D11_SHADER_RESOURCE_VIEW_DESC* desc = nullptr);
		void bindPixlTex(ID3D11ShaderResourceView* buff, int slot);

		// Deletes child instance
		bool destroy(IUnknown* child);
	};
}
