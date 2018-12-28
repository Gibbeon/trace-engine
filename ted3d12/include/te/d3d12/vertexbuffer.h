#include "te/engine.h"
#include "te/d3d12/global.h"

namespace te {

class D3D12VertexBuffer : public IGfxVertexBuffer {
public:
    D3D12VertexBuffer(ID3D12Resource* buffer, ulong_t size);
    virtual bool_t Write(void* data, ulong_t offset, ulong_t size);

    D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView() { return &_vertexBufferView; }

private:
    ID3D12Resource* _buffer;
    D3D12_VERTEX_BUFFER_VIEW _vertexBufferView;
    long_t _size;
};

}