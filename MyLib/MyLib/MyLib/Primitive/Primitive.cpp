#include "Primitive.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Primitive::Primitive() : 
	heap(nullptr), cRsc(nullptr), vRsc(nullptr)
{
}

// �f�X�g���N�^
Primitive::~Primitive()
{
	Release(vRsc);
	Release(cRsc);
	Release(heap);
}
