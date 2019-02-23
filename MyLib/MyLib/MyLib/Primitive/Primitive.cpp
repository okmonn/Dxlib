#include "Primitive.h"
#include "../etc/Release.h"

// コンストラクタ
Primitive::Primitive() : 
	heap(nullptr), cRsc(nullptr), vRsc(nullptr)
{
}

// デストラクタ
Primitive::~Primitive()
{
	Release(vRsc);
	Release(cRsc);
	Release(heap);
}
