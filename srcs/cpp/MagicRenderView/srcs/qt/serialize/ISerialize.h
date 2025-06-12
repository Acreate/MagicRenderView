#ifndef ISERIALIZE_H_H_HEAD__FILE__
#define ISERIALIZE_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

class ISerialize {
public:
	/// @brief 数据序列化到参数
	/// @param result_data_vector 返回被序列化后的数据
	/// @return 失败返回 false
	virtual bool serializeToVectorData( std_vector< uchar > *result_data_vector ) const {
		return false;
	}
	/// @brief 从数据当中获取信息，并且重新初始化对象
	/// @param read_data_vector 源数据序列
	/// @return 使用数据的个数
	virtual size_t serializeToObjectData( const std_vector< uchar > &read_data_vector ) const {
		return 0;
	}
	virtual ~ISerialize( ) { }
};

#endif // ISERIALIZE_H_H_HEAD__FILE__
