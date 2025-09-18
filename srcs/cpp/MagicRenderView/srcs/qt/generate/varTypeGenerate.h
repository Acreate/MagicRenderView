#ifndef VARTYPEGENERATE_H_H_HEAD__FILE__
#define VARTYPEGENERATE_H_H_HEAD__FILE__
#pragma once
#include <alias/type_alias.h>

#include <qt/varType/varType.h>

class QString;
class QObject;
class VarTypeGenerate final {
public:
	static bool isLittleEndian( );
	/// @brief 获取数据当中的类名称信息{内名称信息长度(size_t 类型),类名称信息内容(QByteArray 类型-utf8编码)}
	/// @param result_type_info 类名称信息
	/// @param source_data_ptr 源
	/// @param source_count 源数据上限
	/// @return 数据使用量
	static size_t getMetaInfo( QString *result_type_info, const uint8_t *source_data_ptr, const size_t &source_count );
	static size_t toVectorUInt8Data( const void *source_ptr, const size_t &source_ptr_count, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const QString &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const uint8_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const uint16_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const uint32_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const uint64_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const float_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const double_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const std::string &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const std::wstring &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const int8_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const int16_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const int32_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toVectorUInt8Data( const int64_t &var_type, std_vector< uint8_t > &result_bin_data_vector );
	static size_t toObj( QString *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( uint8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( uint16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( uint32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( uint64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( float_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( double_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( std::string *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( std::wstring *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( int8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( int16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( int32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
	static size_t toObj( int64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count );
private:
	static VarType * templateVarType( QObject *parent, const QString &type_name );
	static std_vector< VarType * > vars;
public:
	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 填充内容
	/// @param result_bin_data_vector 返回的二进制数据
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toVectortBin( const TBaseType &var_type, std_vector< uint8_t > &result_bin_data_vector ) {
		/*
		 * 对象类型信息
		 */
		QString typeName = typeid( TBaseType ).name( );
		std_vector< uint8_t > typeNameVector;
		size_t dataCount = VarTypeGenerate::toVectorUInt8Data( typeName, typeNameVector );
		std_vector< uint8_t > typeNameVectorCountVector;
		VarTypeGenerate::toVectorUInt8Data( dataCount, typeNameVectorCountVector );
		/*
		 * 对象存储信息
		 */
		std_vector< uint8_t > varDataVector;
		dataCount = VarTypeGenerate::toVectorUInt8Data( var_type, varDataVector );
		std_vector< uint8_t > varDataVectorCountVector;
		VarTypeGenerate::toVectorUInt8Data( dataCount, varDataVectorCountVector );
		/*
		 * 总长度 = 对象类型信息长度+对象存储信息长度
		 */
		dataCount = typeNameVectorCountVector.size( ) + typeNameVector.size( ) + varDataVectorCountVector.size( ) + varDataVector.size( );
		std_vector< uint8_t > dataCountVector;
		VarTypeGenerate::toVectorUInt8Data( dataCount, dataCountVector );
		/*
		* 存储到返回
		*/
		result_bin_data_vector.clear( );
		// 总长
		result_bin_data_vector.append_range( dataCountVector );
		// 变量类型信息长度
		result_bin_data_vector.append_range( typeNameVectorCountVector );
		// 变量类型信息内容
		result_bin_data_vector.append_range( typeNameVector );
		// 变量存储信息长度
		result_bin_data_vector.append_range( varDataVectorCountVector );
		// 变量存储信息内容
		result_bin_data_vector.append_range( varDataVector );
		return true;
	}
	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t fillObjPtr( TBaseType *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		/*
		 * 总数量
		 */
		// 从数据当中获取长度
		size_t minCount = *( size_t * ) source_data_ptr;
		// 长度数据的占用
		size_t size_tTypeSize = sizeof( size_t );
		if( source_data_count < size_tTypeSize )
			return 0;
		// 有效大小
		size_t validSourceDataCount = source_data_count - size_tTypeSize;
		if( minCount > validSourceDataCount )
			return 0;// 无法满足数据需求
		// 移动到对象类型信息起始位置
		source_data_ptr += size_tTypeSize;
		/*
		 * 校对对象类型信息
		 */
		// 获取对象类型信息长度
		size_t typeNameSize = *( size_t * ) source_data_ptr;
		// 指向类型信息起始位置
		source_data_ptr += size_tTypeSize;
		QByteArray array( ( const char * ) source_data_ptr, typeNameSize );
		QString typeName = QString::fromUtf8( array );
		// 获取参数当中的类型
		QString paramTypeName = typeid( TBaseType ).name( );
		if( paramTypeName != typeName )
			return 0; // 类型名称不匹配
		// 指向对象存储信息
		source_data_ptr += typeNameSize;
		/*
		 * 校对对象存储信息
		 */
		validSourceDataCount = *( size_t * ) source_data_ptr;
		source_data_ptr += size_tTypeSize;
		VarTypeGenerate::toObj( var_type, source_data_ptr, validSourceDataCount );

		return minCount;
	}
public:
	template< typename TType_Name >
	static VarType * templateVarType( QObject *parent ) {
		VarType *varType = templateVarType( parent, typeid( TType_Name ).name( ) );
		if( varType->init< TType_Name >( ) == false ) {
			delete varType;
			return nullptr;
		}
		varType->unitySer = [] ( const void *p, std::vector< uint8_t > &vector ) ->size_t {
			return VarTypeGenerate::toVectortBin< TType_Name >( *( ( const TType_Name * ) p ), vector );
		};
		varType->unitySerRes = [] ( const uint8_t *source_data_ptr, const size_t &source_data_count, size_t &result_use_data_count ) ->void * {
			TType_Name *result = new TType_Name( );
			result_use_data_count = VarTypeGenerate::fillObjPtr< TType_Name >( result, source_data_ptr, source_data_count );
			if( result_use_data_count != 0 )
				return result;
			delete result;
			return nullptr;
		};
		return varType;
	}

};

#endif // VARTYPEGENERATE_H_H_HEAD__FILE__
