#ifndef ISERIALIZETOOBJECTDATA_H_H_HEAD__FILE__
#define ISERIALIZETOOBJECTDATA_H_H_HEAD__FILE__
#pragma once
#include "ISerialize.h"

class ISerializeToObjectData : public ISerialize {
public:
	/// @brief 从数据当中获取信息，并且重新初始化对象
	/// @param read_data_vector 源数据序列
	/// @param data_count
	/// @return 使用数据的个数
	virtual size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) = 0;
};

#endif // ISERIALIZETOOBJECTDATA_H_H_HEAD__FILE__
