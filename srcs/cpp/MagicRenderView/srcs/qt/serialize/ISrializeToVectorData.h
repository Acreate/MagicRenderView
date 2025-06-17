#ifndef ISRIALIZETOVECTORDATA_H_H_HEAD__FILE__
#define ISRIALIZETOVECTORDATA_H_H_HEAD__FILE__
#pragma once
#include "ISerialize.h"

class ISrializeToVectorData : public ISerialize {
public:
	/// @brief 数据序列化到参数
	/// @param result_data_vector 返回被序列化后的数据
	/// @return 失败返回 false
	virtual bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const = 0;
};

#endif // ISRIALIZETOVECTORDATA_H_H_HEAD__FILE__
