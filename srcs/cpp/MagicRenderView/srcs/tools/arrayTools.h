#ifndef ARRAYTOOLS_H_H_HEAD__FILE__
#define ARRAYTOOLS_H_H_HEAD__FILE__
#pragma once

namespace ArrayTools {
	/// @brief 匹配数组，返回第一个同下标相等的元素
	/// @tparam TVectorUnityType 比较元素类型
	/// @param start_index 开始下标
	/// @param count 最大下标
	/// @param left 左比较数
	/// @param find_target_unity 查找元素
	/// @return true 表示存在，start_index 返回下标
	template< typename TVectorUnityType >
	bool findIndexUnity( size_t &start_index, const size_t &count, const TVectorUnityType *left, const TVectorUnityType &find_target_unity ) {
		if( start_index == count || start_index > count )
			return false;
		for( ; start_index < count; ++start_index )
			if( left[ start_index ] == find_target_unity )
				break;
		return true;
	}
}
#endif // ARRAYTOOLS_H_H_HEAD__FILE__
