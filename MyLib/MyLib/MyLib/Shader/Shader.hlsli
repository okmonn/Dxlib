// 平行移動
matrix Translate(float3 vec)
{
    return matrix(1.0f, 0.0f, 0.0f, vec.x,
				  0.0f, 1.0f, 0.0f, vec.y,
				  0.0f, 0.0f, 1.0f, vec.z,
				  0.0f, 0.0f, 0.0f, 1.0f);
}

// X軸回転
matrix RotateX(float angle)
{
    return matrix(1.0f,        0.0f,       0.0f, 0.0f,
				  0.0f,  cos(angle), sin(angle), 0.0f,
				  0.0f, -sin(angle), cos(angle), 0.0f,
				  0.0f,        0.0f,       0.0f, 1.0f);
}

// Y軸回転
matrix RotateY(float angle)
{
    return matrix(cos(angle), 0.0f, sin(angle), 0.0f,
				        0.0f, 1.0f,       0.0f, 0.0f,
				 -sin(angle), 0.0f, cos(angle), 0.0f,
					    0.0f, 0.0f,       0.0f, 1.0f);
}

// Z軸回転
matrix RotateZ(float angle)
{
    return matrix(cos(angle), sin(angle), 0.0f, 0.0f,
				 -sin(angle), cos(angle), 0.0f, 0.0f,
				        0.0f,       0.0f, 1.0f, 0.0f,
				        0.0f,       0.0f, 0.0f, 1.0f);
}

// 任意軸回転
matrix Rotate(float3 axis, float angle)
{
    float3 norm = normalize(axis);
    return matrix(norm.x * norm.x * (1.0f - cos(angle)) + cos(angle),          norm.y * norm.x * (1.0f - cos(angle)) - norm.z * sin(angle), norm.z * norm.x * (1.0f - cos(angle)) + norm.y * sin(angle), 0.0f,
				  norm.x * norm.y * (1.0f - cos(angle)) + norm.z * sin(angle), norm.y * norm.y * (1.0f - cos(angle)) + cos(angle),          norm.z * norm.y * (1.0f - cos(angle)) - norm.x * sin(angle), 0.0f,
				  norm.x * norm.z * (1.0f - cos(angle)) - norm.y * sin(angle), norm.y * norm.z * (1.0f - cos(angle)) + norm.x * sin(angle), norm.z * norm.z * (1.0f - cos(angle)) + cos(angle),          0.0f,
				                                                         0.0f,                                                        0.0f,                                                        0.0f, 1.0f);
}

// クォータニオン
float4 Quaternion(float3 axis, float angle)
{
    float3 norm = normalize(axis);
    return float4(norm * sin(angle * 0.5f), cos(angle * 0.5f));
}

// クォータニオン同士の掛け算
float4 QuaternionMultipli(float4 q1, float4 q2)
{
    return float4(mul(matrix(q2.w, -q2.z,  q2.y, q2.x,
							 q2.z,  q2.w, -q2.x, q2.y,
							-q2.y,  q2.x,  q2.w, q2.z,
							-q2.x, -q2.y, -q2.z, q2.w), q1));
}

// 共役クォータニオン
float4 InverseQuaternion(float4 q)
{
    return float4(-q.xyz, q.w);
}
