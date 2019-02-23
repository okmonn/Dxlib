#include "PipeMane.h"
#include "Pipie.h"
#include "../etc/Release.h"
#include <vector>

// 入力一覧
std::unordered_map<std::string, D3D12_INPUT_ELEMENT_DESC> inputs = {
	{ "POSITION", { "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 } },
	{ "NORMAL",   { "NORMAL",   0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 } },
	{ "TEXCOORD", { "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 } },
};

// コンストラクタ
PipeMane::PipeMane()
{
}

// デストラクタ
PipeMane::~PipeMane()
{
}

// パイプ生成
void PipeMane::Create(const std::string & name, std::weak_ptr<Root> root, const D3D12_PRIMITIVE_TOPOLOGY_TYPE & type, const std::initializer_list<std::string>& input, const bool & depth)
{
	if (pipe.find(name) != pipe.end())
	{
		return;
	}

	std::vector<D3D12_INPUT_ELEMENT_DESC>in;
	for (auto& i : input)
	{
		for (auto itr = inputs.begin(); itr != inputs.end(); ++itr)
		{
			if (i == itr->first)
			{
				in.push_back(itr->second);
				break;
			}
		}
	}

	pipe[name] = std::make_shared<Pipe>(root);
	pipe[name]->Graphic(*in.data(), in.size(), type, depth);
}

// パイプ生成
void PipeMane::Create(const std::string & name, std::weak_ptr<Root> root)
{
	if (pipe.find(name) != pipe.end())
	{
		return;
	}

	pipe[name] = std::make_shared<Pipe>(root);
	pipe[name]->Compute();
}

// パイプ削除
void PipeMane::Delete(const std::string& name)
{
	if (pipe.find(name) != pipe.end())
	{
		pipe.erase(pipe.find(name));
	}
}

// インスタンス変数取得
PipeMane & PipeMane::Get(void)
{
	static PipeMane instance;
	return instance;
}

// パイプ取得
std::shared_ptr<Pipe> PipeMane::GetPipe(const std::string& name)
{
	if (pipe.find(name) == pipe.end())
	{
		return nullptr;
	}

	return pipe[name];
}
