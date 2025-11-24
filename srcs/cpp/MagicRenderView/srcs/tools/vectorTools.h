#ifndef VECTORTOOLS_H_H_HEAD__FILE__
#define VECTORTOOLS_H_H_HEAD__FILE__
#pragma once
#include <vector>
namespace VectorTools {
	/// @brief 匹配两个数组，返回第一个同下标相等的元素
	/// @tparam TVectorUnityType 比较元素类型
	/// @param start_index 开始下标
	/// @param count 最大下标
	/// @param left 左比较数
	/// @param right 右比较数
	/// @return true 表示合法比较，第一相等下标返回到 start_index
	template< typename TVectorUnityType >
	bool findIndexEquUnity( size_t &start_index, const size_t &count, const typename std::vector< TVectorUnityType >::value_type *left, const typename std::vector< TVectorUnityType >::value_type *right ) {
		if( start_index == count || start_index > count )
			return false;
		for( ; start_index < count; ++start_index )
			if( left[ start_index ] == right[ start_index ] )
				break;
		return true;
	}
	/// @brief 匹配两个数组，返回第一个同下标不相等的元素
	/// @tparam TVectorUnityType 比较元素类型
	/// @param start_index 开始下标
	/// @param count 最大下标
	/// @param left 左比较数
	/// @param right 右比较数
	/// @return true 表示合法比较，第一不相等下标返回到 start_index
	template< typename TVectorUnityType >
	bool findIndexDisEquUnity( size_t &start_index, const size_t &count, const typename std::vector< TVectorUnityType >::value_type *left, const typename std::vector< TVectorUnityType >::value_type *right ) {
		if( start_index == count || start_index > count )
			return false;
		for( ; start_index < count; ++start_index )
			if( left[ start_index ] == right[ start_index ] )
				break;
		return true;
	}

}

#endif // VECTORTOOLS_H_H_HEAD__FILE__
