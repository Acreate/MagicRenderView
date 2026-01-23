#ifndef ARRAYTOOLS_H_H_HEAD__FILE__
#define ARRAYTOOLS_H_H_HEAD__FILE__

#include <QDebug>

namespace ArrayTools {
	/// @brief 匹配数组，返回第一个同下标相等的元素
	/// @tparam TVectorUnityType 比较元素类型
	/// @param start_index 开始下标
	/// @param count 最大下标
	/// @param left 左比较数
	/// @param find_target_unity 查找元素
	/// @return true 表示存在，start_index 返回下标
	template< typename TVectorUnityType >
	bool findIndex( const TVectorUnityType *left, const size_t &count, const TVectorUnityType &find_target_unity, size_t &start_index ) {
		if( left == nullptr || count == 0 || start_index == count || start_index > count )
			return false;
		for( ; start_index < count; ++start_index )
			if( left[ start_index ] == find_target_unity )
				return true;
		return false;
	}
	/// @brief 数组进行 nullptr 排序，会把 nullptr 排序到末尾，其他元素不变
	/// @tparam TVectorUnityType 
	/// @param sort_target 排序目标
	/// @param count 排序个数
	template< typename TVectorUnityType >
	void sortNullptr( TVectorUnityType *sort_target, const size_t &count ) {
		size_t index = 0;
		size_t notNullptrIndex = 0;
		for( ; index < count; index += 1 )
			if( sort_target[ index ] == nullptr ) {
				// 匹配第一个非 nullptr
				for( notNullptrIndex = index + 1; notNullptrIndex < count; notNullptrIndex += 1 )
					if( sort_target[ notNullptrIndex ] != nullptr )
						break;
				if( notNullptrIndex == count )
					return; // 已经不存在非 nullptr
				sort_target[ index ] = sort_target[ notNullptrIndex ]; // 当前接受非 nullptr
				sort_target[ notNullptrIndex ] = nullptr; // 值赋予为 nullptr，避免检测
				//index = notNullptrIndex - 1; // 配置检查非 nullptr
			}
	}
	/// @brief 数组转换到序列
	/// @tparam TVectorUnityType 
	/// @param conver_target 转换目标
	/// @param count 转换个数
	/// @param result_conver_std_vector 转换的返回序列
	template< typename TVectorUnityType >
	void toStdVector( TVectorUnityType *conver_target, const size_t &count, std::vector< TVectorUnityType > &result_conver_std_vector ) {
		result_conver_std_vector.resize( count );
		if( count == 0 )
			return;
		auto data = result_conver_std_vector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			data[ index ] = conver_target[ index ];
	}

	/// @brief 去除序列当中重复元素
	/// @tparam TVectorUnityType 
	/// @param remove_target 匹配元素数组
	/// @param remove_target_count 匹配元素个数
	/// @param result_array_ptr 返回数组
	/// @param result_array_count 返回长度
	/// @return 失败返回 false
	template< typename TVectorUnityType >
	bool removeRepeat( const TVectorUnityType *remove_target, const size_t &remove_target_count, TVectorUnityType * &result_array_ptr, size_t &result_array_count ) {
		if( remove_target_count == 0 )
			return false;
		result_array_count = remove_target_count;
		TVectorUnityType *resultBuffPtr = new TVectorUnityType[ result_array_count ];
		size_t resultIndex; // 实际长度
		size_t findResultIndex; // 查找返回
		size_t index = 0;
		for( findResultIndex = 0, resultIndex = 0; index < remove_target_count; index += 1, findResultIndex = 0 )
			if( ArrayTools::findIndex( resultBuffPtr, resultIndex, remove_target[ index ], findResultIndex ) == false ) {
				resultBuffPtr[ resultIndex ] = remove_target[ index ];
				resultIndex += 1;
			}

		if( resultIndex == 0 ) {
			delete[] resultBuffPtr;
			result_array_count = 0;
			return false;
		}
		result_array_count = resultIndex;
		result_array_ptr = new TVectorUnityType[ result_array_count ];
		for( index = 0; index < result_array_count; ++index )
			result_array_ptr[ index ] = resultBuffPtr[ index ];
		delete[] resultBuffPtr;
		return true;
	}
}
#endif // ARRAYTOOLS_H_H_HEAD__FILE__
