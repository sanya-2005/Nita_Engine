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
        Vec3_float = 6,
        Vec2_float = 16,
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

    enum CPUAccess
    {
        NoAccess = 0,

    };

    enum DepthStencilFunction
    {
        LessFunction
    };
}