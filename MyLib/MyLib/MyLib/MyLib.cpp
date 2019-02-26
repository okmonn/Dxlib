#include "MyLib.h"
#include "Descriptor/Descriptor.h"
#include "Window/Window.h"
#include "Queue/Queue.h"
#include "List/List.h"
#include "Fence/Fence.h"
#include "Swap/Swap.h"
#include "Render/Render.h"
#include "Depth/Depth.h"
#include "Root/Root.h"
#include "Pipe/Pipe.h"
#include "etc/Release.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "xaudio2.lib")

std::unordered_map<std::string, std::shared_ptr<Root>> MyLib::root;
std::unordered_map<std::string, std::shared_ptr<Pipe>> MyLib::pipe;

// インプット一覧
const D3D12_INPUT_ELEMENT_DESC inputs[] = {
	//0
	{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//1
	{ "NORMAL",   0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//2
	{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,       0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//3
	{ "BORN",     0, DXGI_FORMAT::DXGI_FORMAT_R16G16_UINT,        0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//4
	{ "WEIGHT",   0, DXGI_FORMAT::DXGI_FORMAT_R8_UINT,            0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
};

// コンストラクタ
MyLib::MyLib(const Vec2& size, const Vec2& pos) : 
	heap(nullptr), rsc(nullptr), constant(nullptr)
{
#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif
	Init();

	constant->winSize = Vec2f(float(size.x), float(size.y));

	Instance(pos);
}

// デストラクタ
MyLib::~MyLib()
{
	Desc.UnMap(rsc);
	Release(rsc);
	Release(heap)
}

// 初期化
void MyLib::Init(void)
{
	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (sizeof(Constant) + 0xff) &~0xff;

	Desc.CreateRsc(&rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	Desc.CBV(heap, rsc);

	Desc.Map(rsc, (void**)(&constant));
}

// ルートのインスタンス
void MyLib::RootSignature(const std::string& name, const std::string& fileName)
{
	if (root.find(name) != root.end())
	{
		return;
	}

	root[name] = std::make_shared<Root>(fileName);
}

// パイプのインスタンス
void MyLib::PipeLine(const std::string & name, const std::string & rootName, 
	const D3D12_PRIMITIVE_TOPOLOGY_TYPE & type, const std::initializer_list<uint>& index, const bool & depth)
{
	if (pipe.find(name) != pipe.end())
	{
		return;
	}

	std::vector<D3D12_INPUT_ELEMENT_DESC>input;
	for (auto& i : index)
	{
		input.push_back(inputs[i]);
	}

	pipe[name] = std::make_shared<Pipe>(root[rootName], *input.data(), input.size(), type, depth);
}

// クラスのインスタンス化
void MyLib::Instance(const Vec2& pos)
{
	win    = std::make_shared<Window>(pos, Vec2(int(constant->winSize.x), int(constant->winSize.y)));
	queue  = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	list   = std::make_shared<List>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	fence  = std::make_unique<Fence>(queue);
	swap   = std::make_shared<Swap>(win, queue, Vec2(int(constant->winSize.x), int(constant->winSize.y)));
	render = std::make_unique<Render>(swap);
	depth  = std::make_unique<Depth>(Vec2(int(constant->winSize.x), int(constant->winSize.y)));

	RootSignature("primitive", "MyLib/Shader/Primitive.hlsl");
	PipeLine("point",    "primitive", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,    { 0 }, false);
	PipeLine("line",     "primitive", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,     { 0 }, false);
	PipeLine("triangle", "primitive", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0 }, false);

	RootSignature("texture", "MyLib/Shader/Texture.hlsl");
	PipeLine("texture", "texture", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0, 2 }, false);
}

// メッセージの確認
bool MyLib::CheckMsg(void) const
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//呼び出し側スレッドが所有しているウィンドウに送信されたメッセージの保留されている物を取得
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//仮想キーメッセージを文字メッセージに変換
		TranslateMessage(&msg);
		//1つのウィドウプロシージャにメッセージを送出する
		DispatchMessage(&msg);
	}

	return true;
}

// クリア
void MyLib::Clear(void) const
{
	list->Reset();

	list->Viewport(Vec2(int(constant->winSize.x), int(constant->winSize.y)));
	list->Scissor(Vec2(int(constant->winSize.x), int(constant->winSize.y)));

	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, render->Get());

	render->Clear(list, depth->Get());

	depth->Clear(list);
}

// プリミティブ描画
void MyLib::Draw(Primitive& primitive, const Vec3f& color, const float& alpha)
{
	primitive.UpData();

	constant->color = color;
	constant->alpha = alpha;

	list->GraphicRoot(root["primitive"]->Get());
	switch (primitive.type)
	{
	case 0:
		break;
	case 1:
		list->Pipeline(pipe["point"]->Get());
		break;
	case 2:
		list->Pipeline(pipe["line"]->Get());
		break;
	default:
		list->Pipeline(pipe["triangle"]->Get());
		break;
	}

	D3D12_VERTEX_BUFFER_VIEW view{};
	view.BufferLocation = primitive.rsc->GetGPUVirtualAddress();
	view.SizeInBytes    = uint(primitive.rsc->GetDesc().Width);
	view.StrideInBytes  = sizeof(primitive.pos[0]);
	list->VertexView(view);

	list->Heap(&heap, 1);
	list->GraphicTable(0, heap);

	list->Topology(D3D12_PRIMITIVE_TOPOLOGY(primitive.type));

	list->DrawVertex(primitive.pos.size());
}

// 画像描画
void MyLib::Draw(Texture& tex, const float& alpha)
{
	tex.vertex[0] = { Vec3f(0.0f),                             Vec2f(0.0f) };
	tex.vertex[1] = { Vec3f(Vec2f(constant->winSize.x, 0.0f)), Vec2f(1.0f, 0.0f) };
	tex.vertex[2] = { Vec3f(Vec2f(0.0f, constant->winSize.y)), Vec2f(0.0f, 1.0f) };
	tex.vertex[3] = { Vec3f(constant->winSize),                Vec2f(1.0f) };
	memcpy(tex.data, tex.vertex.data(), sizeof(tex.vertex[0]) * tex.vertex.size());
	
	constant->alpha = alpha;

	list->GraphicRoot(root["texture"]->Get());
	list->Pipeline(pipe["texture"]->Get());

	DirectX::XMStoreFloat4x4(&tex.constant->matrix, DirectX::XMMatrixAffineTransformation2D(
		DirectX::XMLoadFloat2(&Convert2(tex.size / constant->winSize)),
		DirectX::XMLoadFloat2(&Convert2(tex.size / 2.0f)),
		tex.rotate,
		DirectX::XMLoadFloat3(&Convert3(tex.pos))
	));

	auto index = tex.SetDraw(list);

	list->Heap(&heap, 1);
	list->GraphicTable(index, heap);

	list->Topology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	list->DrawVertex(tex.GetVertexNum());
}

// 実行
void MyLib::Execution(void) const
{
	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, render->Get());

	list->Close();

	ID3D12CommandList* com[] = {
		list->GetList()
	};

	queue->Execution(com, _countof(com));

	swap->Present();

	fence->Wait();
}
