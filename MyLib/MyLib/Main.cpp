#include "MyLib/MyLib.h"
#include "MyLib/Func/Func.h"

int main()
{
	okmonn::Init(640);
	int imag = okmonn::LoadImg("test.png");

	float a = 0.0f;
	while (okmonn::CheckMsg() && !okmonn::CheckKey(okmonn::KeyCode::Escape))
	{
		okmonn::Clear();
		okmonn::DrawImg(imag, 0, okmonn::Rad(a++));
		//okmonn::DrawImgDivide(imag, 0, 320, 0, { 160, 320 });
		okmonn::Execution();
		okmonn::DeletePrim();
	}
}
