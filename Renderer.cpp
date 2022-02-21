#include "Renderer.h"
#include "Device.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "ThirdParty/tiny_obj_loader.h"
#include "Buffer.h"
#include "Shader.h"

void Renderer::Init(Window* pWindow)
{
	pWindow->SetOnWindowResizeCallback([&](int width, int height) -> void
	{
			//this->Resize(width, height);
	});
	pWindow->SetOnWindowMoveCallback([](RECT rect) -> void {

	});
	::CreateDevice(&m_pDevice, &m_pDeviceContext);
	m_pDevice->CreateSwapChain(&m_pSwapChain, pWindow);
	RECT rect = pWindow->GetWindowRect();
	Resize(rect.right - rect.left, rect.bottom - rect.top);

    LoadCube();
}

void Renderer::Tick(float deltaTime)
{
}

void Renderer::Render()
{
	m_pSwapChain->Present();
}

void Renderer::Resize(int width, int height)
{
	m_pSwapChain->ResizeBuffers(width, height);
}

void Renderer::LoadCube()
{
    VertexAttributes cubeVertices[8] = 
    {
        { Vector3f(-1.0f, -1.0f, -1.0f), Vector4f(0.0f, 0.0f, 0.0f, 1.0f) },
        { Vector3f(-1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f) },
        { Vector3f(1.0f, 1.0f, -1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f) },
        { Vector3f(1.0f, -1.0f, -1.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f) },
        { Vector3f(-1.0f, -1.0f, 1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f) },
        { Vector3f(-1.0f, 1.0f, 1.0f), Vector4f(1.0f, 0.0f, 1.0f, 1.0f) },
        { Vector3f(1.0f, 1.0f, 1.0f), Vector4f(1.0f, 1.0f, 1.0f, 1.0f) },
        { Vector3f(1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f) }
    };

    BUFFER_DESC desc;
    desc.ByteWidth = sizeof cubeVertices;
    m_pCubeVertexBuffer = new Buffer(desc, cubeVertices);

    unsigned int indices[] = {
        // 正面
        0, 1, 2,
        2, 3, 0,
        // 左面
        4, 5, 1,
        1, 0, 4,
        // 顶面
        1, 5, 6,
        6, 2, 1,
        // 背面
        7, 6, 5,
        5, 4, 7,
        // 右面
        3, 2, 6,
        6, 7, 3,
        // 底面
        4, 0, 3,
        3, 7, 4

    };

    BUFFER_DESC desc;
    desc.ByteWidth = sizeof indices;
    m_pCubeIndexBuffer = new Buffer(desc, indices);
}

void Renderer::LoadSword()
{
    std::string inputfile = "Assets/GladiusSword.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());
    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                }
                // Optional: vertex colors
                // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
            }
            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }
}
