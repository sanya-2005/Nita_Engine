#include "GPUShader.h"
#include "Log.h"
#include "D3D11Utils.h"

#include <d3d11.h>
#include <d3dcompiler.h>

using namespace D3D11Utils;

namespace GPU
{
    ShaderByteñode* Compile(ShaderCreateInfo& info)
    {
        ID3DBlob* shaderBlob;
        ID3DBlob* errorBlob;

        HRESULT hr = D3DCompileFromFile(info.path.c_str(), nullptr, nullptr, info.entryPoint.c_str(), info.profile.c_str(),
                                        D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderBlob, &errorBlob);

        if (FAILED(hr))
        {
            logger->WriteLine("Error compiling Shader", "GPU");

            std::string error = "";

            if (errorBlob)
            {
                error = (char*)errorBlob->GetBufferPointer();
                logger->WriteLine(error, "");
            }

            SafeRelease(errorBlob);

            return nullptr;
        }

        SafeRelease(errorBlob);

        ShaderByteñode* byteñode = new ShaderByteñode();

        byteñode->data = shaderBlob->GetBufferPointer();
        byteñode->size = shaderBlob->GetBufferSize();
        byteñode->shaderBlob = shaderBlob;

        return byteñode;
    }
}


