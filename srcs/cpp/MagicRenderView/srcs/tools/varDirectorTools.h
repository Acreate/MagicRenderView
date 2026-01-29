#ifndef VARDIRECTORTOOLS_H_H_HEAD__FILE__
#define VARDIRECTORTOOLS_H_H_HEAD__FILE__
#include <cstdint>
#include <vector>

class QString;
class VarDirector;
namespace VarDirectorTools {
	/// @brief 判定 *var_ptr 值是否为 true
	/// @param varDirectorPtr var_ptr 所在管理对象
	/// @param var_ptr 指向判定对象值的指针
	/// @return *var_ptr 值是否为 true
	bool isTrue( const VarDirector *varDirectorPtr, const void *var_ptr );
	/// @brief conver_var_ptr 指向对象转换为字符串
	/// @param var_director_ptr conver_var_ptr 所在管理对象
	/// @param conver_var_ptr 指向转换对象的指针
	/// @param result_string 返回转换
	/// @return 失败返回 false
	bool toString( const VarDirector *var_director_ptr, void const *conver_var_ptr, QString &result_string );

	/// @brief 从数据中返回实现对象
	/// @param varDirectorPtr 管理 var_ptr 指向对象的管理对象
	/// @param var_ptr 指向存储目标指针
	/// @param result_use_count 返回使用数据量
	/// @param source_array_ptr 数据起始位置
	/// @param source_array_count 数据数量
	/// @return 失败返回 false
	bool formUint8ArrayData( VarDirector *varDirectorPtr, void *&var_ptr, size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count );
	/// @brief 对象转换到数据
	/// @param varDirectorPtr 管理 var_ptr 指向对象的管理对象
	/// @param var_ptr 指向存储目标指针
	/// @param result_vector_data 返回的数据
	/// @return 失败返回 false
	bool toUint8VectorData( VarDirector *varDirectorPtr, void *&var_ptr, std::vector< uint8_t > &result_vector_data );
}

#endif // VARDIRECTORTOOLS_H_H_HEAD__FILE__
