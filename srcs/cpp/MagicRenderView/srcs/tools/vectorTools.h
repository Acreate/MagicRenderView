#ifndef VECTORTOOLS_H_H_HEAD__FILE__
#define VECTORTOOLS_H_H_HEAD__FILE__

#include <vector>

namespace VectorTools {

	/// @brief 序列当中匹配元素
	/// @tparam TVectorUnityType 
	/// @param find_source_vector 查找的序列
	/// @param find_target 在序列当中匹配的元素
	/// @param result_index 匹配下标
	/// @return 成功匹配时，返回 true
	template< typename TVectorUnityType >
	bool findIndex( const std::vector< TVectorUnityType > &find_source_vector, const TVectorUnityType &find_target, size_t &result_index ) {
		auto count = find_source_vector.size( );
		if( count == 0 )
			return false;
		auto data = find_source_vector.data( );
		for( result_index = 0; result_index < count; result_index += 1 )
			if( data[ result_index ] == find_target )
				return true;
		return false;
	}
	/// @brief 比较两个序列，优先比较大小，
	/// @tparam TVectorUnityType 
	/// @param left_vector 
	/// @param right_vector 
	/// @param result_index 
	/// @return left_vector 较大者，返回 1,相等返回 0。下标相同时 left_vector 较大者，返回 1,相等返回 0。
	template< typename TVectorUnityType >
	int compVectorUnity( const std::vector< TVectorUnityType > &left_vector, const std::vector< TVectorUnityType > &right_vector, size_t &result_index ) {
		auto leftCount = left_vector.size( );
		auto rightCount = right_vector.size( );
		if( left_vector > rightCount )
			return 1;
		else if( rightCount > leftCount )
			return -1;
		auto leftArrayPtr = left_vector.data( );
		auto rightArrayPtr = right_vector.data( );
		result_index = 0;
		for( ; result_index < leftCount; ++result_index )
			if( leftArrayPtr[ result_index ] != rightArrayPtr[ result_index ] )
				break;
		if( result_index == leftCount )
			return 0; // 相等
		if( leftArrayPtr[ result_index ] > rightArrayPtr[ result_index ] )
			return 1;
		else if( rightArrayPtr[ result_index ] > leftArrayPtr[ result_index ] )
			return -1;
		return 0; // 相等
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
	/// @brief 去除序列当中重复元素
	/// @tparam TVectorUnityType 
	/// @param remove_target 目标
	/// @param result_std_vector 返回非重复序列
	template< typename TVectorUnityType >
	bool removeRepeat( const std::vector< TVectorUnityType > &remove_target, std::vector< TVectorUnityType > &result_std_vector ) {
		if( &remove_target == &result_std_vector )
			return false;
		auto count = remove_target.size( );
		if( count == 0 )
			return false;
		result_std_vector.clear( );
		auto data = remove_target.data( );
		size_t index = 0;
		size_t resultIndex;
		for( ; index < count; index += 1 )
			if( findIndex( result_std_vector, data[ index ], resultIndex ) == true )
				continue;
			else
				result_std_vector.emplace_back( data[ index ] );

		return true;
	}
}

#endif // VECTORTOOLS_H_H_HEAD__FILE__
