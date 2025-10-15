#ifndef TOOLS_H_H_HEAD__FILE__
#define TOOLS_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>

#include <alias/type_alias.h>

namespace tools {
	namespace qstr {
		using qstring_t = QString;
		qstring_t removeSpace( const qstring_t &string );
	}

	namespace ui {
		/// @brief 窗口移动到指定显示器当中
		/// @param move_target 移动的窗口
		/// @param display_target 移动的目标显示器
		/// @return 返回 0 表示成功
		int moveDisplayCenter( QWidget *move_target, size_t display_target );
		/// @brief 窗口移动到指定显示器当中
		/// @param move_target 移动的窗口
		/// @param display_target 移动的目标显示器
		/// @return 返回 0 表示成功
		int moveDisplayCenter( QWindow *move_target, size_t display_target );
	}
	namespace debug {
		/// @brief 获取层级调用信息
		/// @param start 开始
		/// @param leven 层级
		/// @param result_pairt 返回，与该函数返回一致
		/// @return 返回指定层级上的所有层级与行号
		std_vector< std_pairt< QString, size_t > > & getFunctionName( size_t start, size_t leven, std_vector< std_pairt< QString, size_t > > &result_pairt );

		/// @brief 获取层级调用信息
		/// @param start 开始
		/// @param leven 层级
		/// @return 返回指定层级上的所有层级与行号
		inline std_vector< std_pairt< QString, size_t > > getFunctionName( size_t start, size_t leven ) {
			std_vector< std_pairt< QString, size_t > > result;
			return getFunctionName( start + 1, leven, result );
		}

		/// @brief 获取层级调用信息
		/// @param leven 层级
		/// @return 返回指定层级上的所有层级与行号
		inline std_vector< std_pairt< QString, size_t > > getFunctionName( size_t leven ) {
			std_vector< std_pairt< QString, size_t > > result;
			return getFunctionName( 1, leven, result );
		}

		/// @brief 返回调用函数的层级信息
		/// @param leven 上层次数
		/// @param result_pairt 返回引用
		/// @return 同 result_pairt
		inline std_vector< std_pairt< QString, size_t > > & getFunctionName( size_t leven, std_vector< std_pairt< QString, size_t > > &result_pairt ) {
			return getFunctionName( 1, leven, result_pairt );
		}
		/// @brief 返回调用函数信息
		/// @return 调用函数的信息
		inline std_vector< std_pairt< QString, size_t > > getFunctionName( ) {
			std_vector< std_pairt< QString, size_t > > result;
			return getFunctionName( 1, 1, result );
		}
		/// @brief 获取层级调用信息
		/// @param result_pairt 返回，与该函数返回一致
		/// @return 返回指定层级上的所有层级与行号
		inline std_vector< std_pairt< QString, size_t > > & getFunctionName( std_vector< std_pairt< QString, size_t > > &result_pairt ) {
			return getFunctionName( 1, 1, result_pairt );
		}
		/// @brief 输出错误信息
		/// @param msg 信息
		/// @param start_index 堆栈-0 为本函数调用
		/// @param last_remove_count 末尾移除个数
		void printError( const std::wstring &msg, size_t start_index = 1, size_t last_remove_count = 0 );
		/// @brief 输出错误信息
		/// @param msg 信息
		/// @param start_index 堆栈-0 为本函数调用
		/// @param last_remove_count 末尾移除个数
		inline void printError( const QString &msg, size_t start_index = 2, size_t last_remove_count = 0 ) {
			printError( msg.toStdWString( ), start_index, last_remove_count );
		}
		/// @brief 返回调用函数信息
		/// @return 调用函数的信息
		void printInfo( const QString& info_msg);
		/// @brief 格式化到 qt 字符串
		/// @param str 格式化的字符串
		/// @param  ... 参数列表
		/// @return 格式化后的字符串
		QString formQString( const char *str, ... );
	}
	namespace vector {

		/// @brief 遍历序列，根据函数返回决定是否结束遍历
		/// @brief 在临时构成 find_unity_function 当中，使用该方式调用
		/// @code tools::vector::forInVector<int>( { 1, 2, 3, 4 }, [] ( int &p ) {		return true;	} ); @endcode 
		/// @tparam TUnity 遍历元素
		/// @param vector 被遍历的迭代器
		/// @param find_unity_function 结束决定函数
		template< typename TUnity >
		void forInVector( std_vector< TUnity > &vector, const std_function< bool( TUnity & ) > &find_unity_function ) {
			size_t count = vector.size( ), index = 0;
			TUnity *data = vector.data( );
			for( ; index < count; ++index )
				if( find_unity_function( data[ index ] ) )
					break;
		}

		/// @brief 遍历序列，根据函数返回决定是否结束遍历
		/// @brief 在临时构成 find_unity_function 当中，使用该方式调用
		/// @code tools::vector::forInVector<int>( { 1, 2, 3, 4 }, [] (const int &p ) {		return true;	} ); @endcode 
		/// @tparam TUnity 遍历元素
		/// @param vector 被遍历的迭代器
		/// @param find_unity_function 结束决定函数
		template< typename TUnity >
		void forInVector( const std_vector< TUnity > &vector, const std_function< bool( const TUnity & ) > &find_unity_function ) {
			size_t count = vector.size( ), index = 0;
			const TUnity *data = vector.data( );
			for( ; index < count; ++index )
				if( find_unity_function( data[ index ] ) )
					break;
		}

		/// @brief 在序列中查找匹配的元素，并且返回该迭代器
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param begin 序列开始位置
		/// @param end 序列结束位置
		/// @param find_unity_function 匹配元素的函数调用
		/// @return 失败返回序列结束位置
		template< typename TUnity >
		typename std_vector< TUnity >::iterator find( typename std_vector< TUnity >::iterator &begin, const typename std_vector< TUnity >::iterator &end, const std_function< bool( TUnity & ) > &find_unity_function ) {
			for( ; begin != end; ++begin )
				if( find_unity_function( *begin ) )
					break;
			return begin;
		}
		/// @brief 在序列中查找匹配的元素，并且返回该迭代器
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param find_unity_function 匹配元素的函数调用
		/// @return 失败返回序列结束位置
		template< typename TUnity >
		typename std_vector< TUnity >::iterator find( const std_vector< TUnity > &source_vector, const std_function< bool( TUnity & ) > &find_unity_function ) {
			auto begin = source_vector.begin( );
			auto end = source_vector.end( );
			return find( begin, end, find_unity_function );
		}
		/// @brief 在序列当中查找匹配元素，存在返回 true
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param find_unity_function 匹配元素的函数调用
		/// @return 存在返回 true
		template< typename TUnity >
		bool has( const std_vector< TUnity > &source_vector, const std_function< bool( TUnity & ) > &find_unity_function ) {
			auto count = source_vector.size( );
			if( count == 0 )
				return false;
			auto data = source_vector.data( );
			for( size_t index = 0; index < count; ++index )
				if( find_unity_function( data[ index ] ) )
					return true;
			return false;
		}
		/// @brief 在序列当中查找匹配元素，并且删除该元素
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param find_unity_function 匹配元素的函数调用
		/// @return 删除成功返回 true
		template< typename TUnity >
		bool remove( std_vector< TUnity > &source_vector, const std_function< bool( TUnity & ) > &find_unity_function ) {
			auto begin = source_vector.begin( );
			auto end = source_vector.end( );
			for( ; begin != end; ++begin )
				if( find_unity_function( *begin ) ) {
					source_vector.erase( begin );
					return true;
				}
			return false;
		}

		/// @brief 在序列当中查找匹配元素，存在则返回 true，并且该位置信息存储在 result_index
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param find_unity_function 匹配元素的函数调用
		/// @param result_index 返回位置
		/// @return 存在元素时，返回 true
		template< typename TUnity >
		bool findIndex( const std_vector< TUnity > &source_vector, size_t *result_index, const std_function< bool( TUnity & ) > &find_unity_function ) {
			*result_index = 0;
			auto count = source_vector.size( );
			if( count == 0 )
				return false;
			auto data = source_vector.data( );
			for( ; *result_index < count; *result_index += 1 )
				if( find_unity_function( data[ *result_index ] ) )
					return true;
			*result_index = 0;
			return false;
		}
		/// @brief 在序列中查找匹配的元素，并且返回该迭代器
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param begin 序列开始位置
		/// @param end 序列结束位置
		/// @param find_unity 匹配元素
		/// @return 失败返回序列结束位置
		template< typename TUnity >
		typename std_vector< TUnity >::iterator find( typename std_vector< TUnity >::iterator &begin, const typename std_vector< TUnity >::iterator &end, const TUnity &find_unity ) {
			for( ; begin != end; ++begin )
				if( *begin == find_unity )
					break;
			return begin;
		}

		/// @brief 在序列中查找匹配的元素，并且返回该迭代器
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param find_unity 匹配元素
		/// @return 失败返回序列结束位置
		template< typename TUnity >
		typename std_vector< TUnity >::iterator find( const std_vector< TUnity > &source_vector, const TUnity &find_unity ) {
			auto begin = source_vector.begin( );
			auto end = source_vector.end( );
			return find( begin, end, find_unity );
		}
		/// @brief 在序列当中查找匹配元素，存在返回 true
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param find_unity 匹配元素
		/// @return 存在返回 true
		template< typename TUnity >
		bool has( const std_vector< TUnity > &source_vector, const TUnity &find_unity ) {
			auto count = source_vector.size( );
			if( count == 0 )
				return false;
			auto data = source_vector.data( );
			for( size_t index = 0; index < count; ++index )
				if( data[ index ] == find_unity )
					return true;
			return false;
		}
		/// @brief 在序列当中查找匹配元素，并且删除该元素
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param find_unity 匹配元素
		/// @return 删除成功返回 true
		template< typename TUnity >
		bool remove( std_vector< TUnity > &source_vector, const TUnity &find_unity ) {
			auto begin = source_vector.begin( );
			auto end = source_vector.end( );
			for( ; begin != end; ++begin )
				if( *begin == find_unity ) {
					source_vector.erase( begin );
					return true;
				}
			return false;
		}
		/// @brief 在序列当中查找下标元素，并且删除该元素
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param remove_index 删除的洗标
		/// @return 删除成功返回 true
		template< typename TUnity >
		bool removeIndex( std_vector< TUnity > &source_vector, const size_t &remove_index ) {
			auto count = source_vector.size( );
			if( count <= remove_index )
				return false;
			auto begin = source_vector.begin( ) + remove_index;
			source_vector.erase( begin );
			return true;
		}
		/// @brief 在序列当中查找匹配元素，存在则返回 true，并且该位置信息存储在 result_index
		/// @tparam TUnity 序列中的匹配类型的元素
		/// @param source_vector 查找序列
		/// @param find_unity 匹配元素
		/// @param result_index 返回位置
		/// @return 存在元素时，返回 true
		template< typename TUnity >
		bool findIndex( const std_vector< TUnity > &source_vector, const TUnity &find_unity, size_t *result_index ) {
			*result_index = 0;
			auto count = source_vector.size( );
			if( count == 0 )
				return false;
			auto data = source_vector.data( );
			for( ; *result_index < count; *result_index += 1 )
				if( data[ *result_index ] == find_unity )
					return true;
			*result_index = 0;
			return false;
		}
		/// @brief 获取不重复的元素
		/// @tparam TUnity 元素类型
		/// @param source_vector 匹配序列
		/// @return 不重复的序列
		template< typename TUnity >
		std_vector< TUnity > removeRepetition( const std_vector< TUnity > &source_vector ) {
			auto count = source_vector.size( );
			if( count == 0 )
				return source_vector;
			std_vector< TUnity > result;
			size_t index = 0;
			size_t subIndex = 0;
			size_t subCount = 0;
			const TUnity *data = source_vector.data( );
			TUnity *subData;

			for( ; index < count; ++index ) {
				for( ; subIndex < subCount; ++subIndex )
					if( data[ index ] == subData[ subIndex ] )
						break;
				if( subIndex < subCount )
					continue;
				result.emplace_back( data[ index ] );
				subCount = result.size( );
				subIndex = 0;
				subData = result.data( );
			}
			return result;
		}

		/// @brief 获取不重复的元素
		/// @tparam TUnity 元素类型
		/// @param source_vector 匹配序列
		/// @param get_comp_unity 用于获取重复元素的函数调用
		/// @return 不重复的序列
		template< typename TCompUnity, typename TUnity >
		std_vector< TUnity > removeRepetition( const std_vector< TUnity > &source_vector, const std_function< TCompUnity ( const TUnity & ) > &get_comp_unity ) {
			auto count = source_vector.size( );
			if( count == 0 )
				return source_vector;
			std_vector< TUnity > result;
			size_t index = 0;
			size_t subIndex = 0;
			size_t subCount = 0;
			const TUnity *data = source_vector.data( );
			TUnity *subData;

			for( ; index < count; ++index ) {
				TCompUnity compUnity = get_comp_unity( data[ index ] );
				for( ; subIndex < subCount; ++subIndex )
					if( compUnity == get_comp_unity( subData[ subIndex ] ) )
						break;
				if( subIndex < subCount )
					continue;
				result.emplace_back( data[ index ] );
				subCount = result.size( );
				subIndex = 0;
				subData = result.data( );
			}
			return result;
		}
	}
	class Serialize;
}

#endif // TOOLS_H_H_HEAD__FILE__
