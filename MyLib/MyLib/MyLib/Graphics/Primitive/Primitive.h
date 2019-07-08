#pragma once
#include "../../etc/Vector3.h"
#include <wrl.h>
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class List;

namespace okmonn
{
	// プリミティブ
	enum class PrimType {
		POINT    = 1,
		LINE     = 2,
		TRIANGLE = 3,
		BOX      = 4
	};

	// 色情報
	struct Color {
		float r;
		float g;
		float b;
		float a;

		Color() {
			r = g = b = a = 0.0f;
		}
		Color(const float& r, const float& g, const float& b, const float& a):
		r(r), g(g), b(b), a(a){}
	};
}

class Primitive
{
public:
	// コンストラクタ
	Primitive(std::weak_ptr<List>list, const okmonn::PrimType& type);
	// デストラクタ
	~Primitive();

	// ポイント描画
	void DrawPoint(const Vec2f& pos, const okmonn::Color& color);

	// ライン描画
	void DrawLine(const Vec2f& pos1, const Vec2f& pos2, const okmonn::Color& color);

	// トライアングル描画
	void DrawTriangle(const Vec2f& pos1, const Vec2f& pos2, const Vec2f& pos3, const okmonn::Color& color);

	// ボックス描画
	void DrawBox(const Vec2f& pos, const Vec2f& size, const okmonn::Color& color);

	// 描画
	void Draw(void);

private:
	// 頂点リソース生成
	void CreateVRsc(void);

	// 定数リソース生成
	void CreateCRsc(void);

	// 初期化
	void Init(void);


	// リスト
	std::weak_ptr<List>list;

	// ヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>heap;

	// 頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource>vRsc;

	// 定数リソース
	Microsoft::WRL::ComPtr<ID3D12Resource>cRsc;

	// 色情報
	okmonn::Color* color;

	// 頂点
	std::vector<Vec3f>vertex;
};
