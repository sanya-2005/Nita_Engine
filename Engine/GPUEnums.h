#pragma once

namespace GPU
{
	enum ConstantBufferTarget
	{
		VSTarget,
		PSTarget
	};

	enum TopologyType
	{
		TriangleList = 4
	};

	enum GPUFormat
	{
		UShort = 57,
		ZBuffer_32Bit = 45,
		InvalidFormat = 1488
	};

	enum BufferUsage
	{
		DefaultUsage = 0,
		DynamicUsage = 2
	};

	enum TextureBindMode
	{
		DepthStencilMode = 0x40L,
		ShaderResourceMode = 0x8L
	};

	enum PerVertexElementMode
	{
		PerVertex,
		PerInstance
	};
}