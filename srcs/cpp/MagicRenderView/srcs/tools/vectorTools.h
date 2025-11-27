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
	/// @brief 填充一个元素指针到末尾，若碰到一个 nullptr 时候，填充到该位置，如果在非 nullptr 前匹配相等，则这个位置被后续元素覆盖，原数据排放到第一个 nullptr 前
	/// @tparam TVectorUnityType 指针指向对象的类型
	/// @param fill_vector 填充序列
	/// @param fill_unity 填充元素
	/// @param result_index 填充位置
	/// @return true 表示填充成功
	template< typename TVectorUnityType >
	bool fillVectorUnityToLast( std::vector< TVectorUnityType * > &fill_vector, TVectorUnityType *fill_unity, size_t &result_index ) {
		auto count = fill_vector.size( );
		auto data = fill_vector.data( );
		result_index = 0;
		for( ; result_index < count; ++result_index )
			if( data[ result_index ] == nullptr ) {
				data[ result_index ] = fill_unity;
				return true;
			} else if( data[ result_index ] == fill_unity ) {
				count -= 1;
				for( ; result_index < count; ++result_index )
					if( data[ result_index ] != nullptr )
						data[ result_index ] = data[ result_index + 1 ];
					else
						break;
				data[ result_index ] = fill_unity;
				return true;
			}
		fill_vector.emplace_back( fill_unity );
		result_index = count;
		return true;
	}

	/// @brief 填充一个 nullptr 指针到匹配指针位置
	/// @tparam TVectorUnityType 指针指向对象的类型
	/// @param fill_vector 填充序列
	/// @param fill_unity 填充元素
	/// @param result_index 填充位置
	/// @return true 表示填充 nullptr 成功，false 表示无法匹配 fill_unity
	template< typename TVectorUnityType >
	bool nullptrUnityVectorToUnity( std::vector< TVectorUnityType * > &fill_vector, TVectorUnityType *fill_unity, size_t &result_index ) {
		auto count = fill_vector.size( );
		auto data = fill_vector.data( );
		result_index = 0;
		for( ; result_index < count; ++result_index )
			if( data[ result_index ] == fill_unity ) {
				size_t index = result_index;
				count -= 1;
				for( ; index < count; ++index )
					data[ index ] = data[ index + 1 ];
				data[ count ] = nullptr;
				return true;
			}
		return false;
	}

	/// @brief 填充一个元素指针到末尾，若碰到一个 nullptr 时候，填充到该位置，如果在非 nullptr 前匹配相等，则这个位置被后续元素覆盖，原数据排放到第一个 nullptr 前
	/// @tparam TVectorUnityType 指针指向对象的类型
	/// @param fill_array_ptr 填充序列起始
	/// @param fill_array_count 填充序列个数
	/// @param fill_unity 填充元素
	/// @param result_index 填充位置
	/// @return true 表示填充成功
	template< typename TVectorUnityType >
	bool fillVectorUnityToLast( const TVectorUnityType **fill_array_ptr, size_t &fill_array_count, TVectorUnityType *fill_unity, size_t &result_index ) {
		result_index = 0;
		for( ; result_index < fill_array_count; ++result_index )
			if( fill_array_ptr[ result_index ] == nullptr ) {
				fill_array_ptr[ result_index ] = fill_unity;
				return true;
			} else if( fill_array_ptr[ result_index ] == fill_unity ) {
				fill_array_count = fill_array_count - 1;
				for( ; result_index < fill_array_count; ++result_index )
					if( fill_array_ptr[ result_index ] != nullptr )
						fill_array_ptr[ result_index ] = fill_array_ptr[ result_index + 1 ];
					else
						break;
				fill_array_ptr[ result_index ] = fill_unity;
				return true;
			}
		return false;
	}

	/// @brief 填充一个 nullptr 指针到匹配指针位置
	/// @tparam TVectorUnityType 指针指向对象的类型
	/// @param fill_array_ptr 填充序列起始
	/// @param fill_array_count 填充序列个数
	/// @param fill_unity 填充元素
	/// @param result_index 填充位置
	/// @return true 表示填充 nullptr 成功，false 表示无法匹配 fill_unity
	template< typename TVectorUnityType >
	bool nullptrUnityVectorToUnity( const TVectorUnityType **fill_array_ptr, size_t &fill_array_count, TVectorUnityType *fill_unity, size_t &result_index ) {
		result_index = 0;
		for( ; result_index < fill_array_count; ++result_index )
			if( fill_array_ptr[ result_index ] == fill_unity ) {
				size_t index = result_index;
				fill_array_count -= 1;
				for( ; index < fill_array_count; ++index )
					fill_array_ptr[ index ] = fill_array_ptr[ index + 1 ];
				fill_array_ptr[ index ] = nullptr;
				return true;
			}
		return false;
	}
}

#endif // VECTORTOOLS_H_H_HEAD__FILE__
