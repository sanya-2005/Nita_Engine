#include "GPUVertexFormat.h"

namespace GPU
{
    D3D11_INPUT_ELEMENT_DESC VertexAttribute::ConvertToD3dInputElement()
    {
        D3D11_INPUT_ELEMENT_DESC decs{};
        decs.InputSlot = slot;
        decs.AlignedByteOffset = offset;
        decs.SemanticName = name.c_str();
        decs.SemanticIndex = semanticIndex;
        decs.InputSlotClass = (D3D11_INPUT_CLASSIFICATION)elementMode;
        decs.InstanceDataStepRate = instanceStep;
        decs.Format = (DXGI_FORMAT)format;

        return decs;
    }
}
