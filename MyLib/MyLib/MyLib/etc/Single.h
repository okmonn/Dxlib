#pragma once

template <typename T>
class Single
{
public:
	// インスタンス変数の取得
	static T& Get(void)
	{
		static T instance;
		return instance;
	}

protected:
	// コンストラクタ
	Single() {}

	// デストラクタ
	virtual ~Single() {}

private:
	Single(const Single&) = delete;
	void operator=(const Single&) = delete;

};
