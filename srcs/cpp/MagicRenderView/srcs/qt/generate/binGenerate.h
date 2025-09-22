#ifndef BINGENERATE_H_H_HEAD__FILE__
#define BINGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "../tools/tools.h"
#define ConverPtr(left, right, __type) __type left = (__type)right
class BinGenerate final {
public:
	class Serialization;
	class BinGenerateItem {
	public:
		friend class BinGenerate;
	protected:
		static Serialization serialization;
	protected:
		QString typeName;
		size_t typeHasCode;
	public:
		virtual size_t fillUnityBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) = 0;
		virtual size_t fillUnityObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) = 0;
		virtual size_t fillVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) = 0;
		virtual size_t fillVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) = 0;
		virtual size_t fillPtrVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) = 0;
		virtual size_t fillPtrVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) = 0;
		virtual bool getNewObj( void **new_set_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) =0;
		virtual bool removeNewObj( void *new_set_ptr ) = 0;
		virtual bool isSerializationType( const QString &check_type_name, const size_t &type_has_code = 0 ) const {
			bool cond = typeName == check_type_name;
			if( cond && typeHasCode != 0 )
				return type_has_code == typeHasCode;
			return cond;
		}
		template< typename TType >
		bool isSerializationType( ) const {
			auto &typeInfo = typeid( TType );
			return isSerializationType( typeInfo.name( ), typeInfo.hash_code( ) );
		}
	public:
		BinGenerateItem( ) : typeName( "" ), typeHasCode( 0 ) {

		}
		virtual ~BinGenerateItem( ) { }
	protected:
	};
	class Serialization {
		friend class BinGenerate::BinGenerateItem;
		Serialization( ) = default;
		Serialization( const Serialization &other ) = delete;
		Serialization & operator=( const Serialization &other ) = delete;
	private:
		virtual ~Serialization( ) { }
	public:
		/// @brief 二进制填充数组
		/// @param source_ptr 获取源
		/// @param source_ptr_count 获取个数 
		/// @param result_mirror_image_bin_vector 填充目标
		/// @return 填充个数
		size_t fillBinVector( const void *source_ptr, const size_t &source_ptr_count, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			result_mirror_image_bin_vector.resize( source_ptr_count );
			auto pasteTargetDataPtr = result_mirror_image_bin_vector.data( );
			auto copyTargetDataPtr = ( const uint8_t * ) source_ptr;
			for( size_t index = 0; index < source_ptr_count; ++index )
				pasteTargetDataPtr[ index ] = copyTargetDataPtr[ index ];
			return source_ptr_count;
		}
		size_t fillBinVector( const QString &var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
			std_vector< uint8_t > buff;
			auto byteArray = var_type.toUtf8( );
			fillBinVector( byteArray.data( ), byteArray.size( ), buff );
			fillBinVector( buff.size( ), result_bin_data_vector );
			result_bin_data_vector.append_range( buff );
			return result_bin_data_vector.size( );
		}
		size_t fillBinVector( const uint8_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( &var_type, sizeof uint8_t, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const uint16_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( &var_type, sizeof uint16_t, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const uint32_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( &var_type, sizeof uint32_t, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const uint64_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( &var_type, sizeof uint64_t, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const float_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( &var_type, sizeof float_t, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const double_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( &var_type, sizeof double_t, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const std::string &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			QString fromStdString = QString::fromStdString( var_type );
			return fillBinVector( fromStdString, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const std::wstring &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			QString fromStdString = QString::fromStdWString( var_type );
			return fillBinVector( fromStdString, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const int8_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( ( const uint8_t ) var_type, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const int16_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( ( const uint16_t ) var_type, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const int32_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( ( const uint32_t ) var_type, result_mirror_image_bin_vector );
		}
		size_t fillBinVector( const int64_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
			return fillBinVector( ( const uint64_t ) var_type, result_mirror_image_bin_vector );
		}
		size_t fillObjVector( QString *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t count;
			auto add = fillObjVector( &count, source_ptr, source_ptr_count );
			const char *sourcePtr = ( const char * ) source_ptr + add;
			if( count > source_ptr_count - add )
				return 0;
			QByteArray array( sourcePtr, count );
			*target_var_ptr = QString::fromUtf8( array );
			return count + add;
		}
		size_t fillObjVector( uint8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( uint8_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		size_t fillObjVector( uint16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( uint16_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		size_t fillObjVector( uint32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( uint32_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		size_t fillObjVector( uint64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( uint64_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		size_t fillObjVector( float_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( float_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		size_t fillObjVector( double_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( double_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}

		size_t fillObjVector( std::string *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			QString buff;
			auto count = fillObjVector( &buff, source_ptr, source_ptr_count );
			if( count == 0 )
				return 0;
			*target_var_ptr = buff.toStdString( );
			return count;
		}

		size_t fillObjVector( std::wstring *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			QString buff;
			auto count = fillObjVector( &buff, source_ptr, source_ptr_count );
			if( count == 0 )
				return 0;
			*target_var_ptr = buff.toStdWString( );
			return count;
		}
		size_t fillObjVector( int8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( int8_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		size_t fillObjVector( int16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( int16_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		size_t fillObjVector( int32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( int32_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		size_t fillObjVector( int64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			size_t checkCount = sizeof( int64_t );
			if( checkCount > source_ptr_count )
				return 0;
			memcpy( target_var_ptr, source_ptr, checkCount );
			return checkCount;
		}
		/// @brief 平台是否小端
		/// @return true 表示小端
		bool isLittleEndian( ) const {
			union {
				int i;
				char c;
			} un;	// 匿名联合体
			un.i = 1;
			// 小端：返回 1，说明数据的低字节在内存的低地址存放
			return un.c == 1;
		}
		template< typename TPtrType >
		size_t fillUnityBin( BinGenerateItem *bin_generate_item, const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
			if( var_type == nullptr )
				return 0;
			ConverPtr( dataPtr, var_type, const TPtrType * );
			std_vector< uint8_t > resultBuff;
			std_vector< uint8_t > countBuff;
			std_vector< uint8_t > nameBuff;
			fillBinVector( bin_generate_item->typeName, nameBuff );
			resultBuff.append_range( nameBuff );
			size_t count = fillBinVector( *dataPtr, nameBuff );
			fillBinVector( count, countBuff );
			resultBuff.append_range( countBuff );
			resultBuff.append_range( nameBuff );
			count = resultBuff.size( );
			fillBinVector( count, countBuff );
			result_bin_data_vector.clear( );
			result_bin_data_vector.append_range( countBuff );
			result_bin_data_vector.append_range( resultBuff );
			return result_bin_data_vector.size( );
		}
		template< typename TPtrType >
		size_t fillVectorBin( BinGenerateItem *bin_generate_item, const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
			if( var_type == nullptr )
				return 0;
			ConverPtr( dataPtr, var_type, const std_vector< TPtrType > * );
			std_vector< uint8_t > resultBuff;
			std_vector< uint8_t > nameBuff;
			size_t count = fillBinVector( bin_generate_item->typeName, nameBuff );
			resultBuff.append_range( nameBuff );
			count = dataPtr->size( );
			fillBinVector( count, nameBuff );
			resultBuff.append_range( nameBuff );
			size_t index = 0;
			auto data = dataPtr->data( );
			for( ; index < count; ++index ) {
				bin_generate_item->fillUnityBin( data + index, nameBuff );
				resultBuff.append_range( nameBuff );
			}
			count = resultBuff.size( );
			fillBinVector( count, nameBuff );
			result_bin_data_vector.clear( );
			result_bin_data_vector.append_range( nameBuff );
			result_bin_data_vector.append_range( resultBuff );
			return result_bin_data_vector.size( );
		}
		template< typename TPtrType >
		size_t fillPtrVectorBin( BinGenerateItem *bin_generate_item, const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
			if( var_type == nullptr )
				return 0;
			ConverPtr( dataPtr, var_type, const std_vector< TPtrType * > * );
			std_vector< uint8_t > resultBuff;
			std_vector< uint8_t > nameBuff;
			size_t count = fillBinVector( bin_generate_item->typeName, nameBuff );
			resultBuff.append_range( nameBuff );
			count = dataPtr->size( );
			fillBinVector( count, nameBuff );
			resultBuff.append_range( nameBuff );
			size_t index = 0;
			auto data = dataPtr->data( );
			for( ; index < count; ++index ) {
				bin_generate_item->fillUnityBin( *( data + index ), nameBuff );
				resultBuff.append_range( nameBuff );
			}
			count = resultBuff.size( );
			fillBinVector( count, nameBuff );
			result_bin_data_vector.clear( );
			result_bin_data_vector.append_range( nameBuff );
			result_bin_data_vector.append_range( resultBuff );
			return result_bin_data_vector.size( );
		}
		template< typename TPtrType >
		size_t fillUnityObj( BinGenerateItem *bin_generate_item, void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			if( var_type == nullptr || source_ptr == nullptr || source_ptr_count == 0 )
				return 0;
			ConverPtr( dataPtr, var_type, TPtrType * );
			size_t menorySize;
			size_t count = fillObjVector( &menorySize, source_ptr, source_ptr_count );
			auto mod = source_ptr_count - count;
			if( menorySize > mod )
				return 0;
			auto offset = source_ptr + count;
			QString converTypeName;
			count = fillObjVector( &converTypeName, offset, mod );
			if( converTypeName != bin_generate_item->typeName )
				return 0;
			mod -= count;
			offset += count;
			count = fillObjVector( &menorySize, offset, mod );
			mod -= count;
			offset += count;
			count = fillObjVector( dataPtr, offset, mod );
			return offset - source_ptr + count;
		}
		template< typename TPtrType >
		size_t fillVectorObj( BinGenerateItem *bin_generate_item, void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			if( var_type == nullptr || source_ptr == nullptr || source_ptr_count == 0 )
				return 0;
			ConverPtr( dataPtr, var_type, std_vector< TPtrType > * );
			size_t menorySize;
			size_t count = fillObjVector( &menorySize, source_ptr, source_ptr_count );
			auto mod = source_ptr_count - count;
			if( mod < menorySize )
				return 0;
			auto offset = source_ptr + count;
			QString converTypeName;
			count = fillObjVector( &converTypeName, offset, mod );
			if( converTypeName != bin_generate_item->typeName )
				return 0;

			mod -= count;
			offset += count;
			size_t vectorCount;
			count = fillObjVector( &vectorCount, offset, mod );
			mod -= count;
			offset += count;
			dataPtr->resize( vectorCount );
			auto data = dataPtr->data( );
			size_t index = 0;
			for( ; index < vectorCount; ++index ) {
				count = bin_generate_item->fillUnityObj( data + index, offset, mod );
				mod -= count;
				offset += count;
			}
			return offset - source_ptr;
		}
		template< typename TPtrType >
		size_t fillPtrVectorObj( BinGenerateItem *bin_generate_item, void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			if( var_type == nullptr || source_ptr == nullptr || source_ptr_count == 0 )
				return 0;
			ConverPtr( dataPtr, var_type, std_vector< TPtrType * > * );
			size_t menorySize;
			size_t count = fillObjVector( &menorySize, source_ptr, source_ptr_count );
			auto mod = source_ptr_count - count;
			if( mod < menorySize )
				return 0;
			auto offset = source_ptr + count;
			QString converTypeName;
			count = fillObjVector( &converTypeName, offset, mod );
			if( converTypeName != bin_generate_item->typeName )
				return 0;
			mod -= count;
			offset += count;
			size_t vectorCount;
			count = fillObjVector( &vectorCount, offset, mod );
			mod -= count;
			offset += count;
			dataPtr->resize( vectorCount );
			TPtrType **data = dataPtr->data( );
			size_t index = 0;
			for( ; index < vectorCount; ++index ) {
				bin_generate_item->getNewObj( ( void ** ) ( data + index ), offset, mod );
				auto varType = *( data + index );
				count = bin_generate_item->fillUnityObj( varType, offset, mod );
				if( count == 0 ) {
					for( ; count < index; ++count )
						bin_generate_item->removeNewObj( *( data + index ) );
					dataPtr->clear( );
					return 0;
				}
				mod -= count;
				offset += count;
			}
			return offset - source_ptr;
		}
	};
protected:
	static std_vector< std_shared_ptr< BinGenerateItem > > binGenerateItems;
public:
	template< typename TType >
		requires requires ( BinGenerateItem *ptr, TType *org_ptr ) {
			typeid( TType ) != typeid( BinGenerateItem );
			ptr = org_ptr;
		}
	static bool appendBinGenerateItem( ) {

		BinGenerateItem *ptr = new TType( );
		if( ptr->typeName.isEmpty( ) ) {
			delete ptr;
			return false;
		}

		size_t count = binGenerateItems.size( );
		auto data = binGenerateItems.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].get( )->isSerializationType( ptr->typeName ) ) {
				data[ index ] = std_shared_ptr< BinGenerateItem >( ptr );
				return true;
			}
		binGenerateItems.emplace_back( std_shared_ptr< BinGenerateItem >( ptr ) );
		return true;
	}
public:
	/// @brief 检索匹配类型名称，返回匹配的序列化项
	/// @param check_type_name 类型名称
	/// @param type_has_code 类型哈希
	/// @return 匹配的序列化项
	static BinGenerateItem * getBinGenerateItemPtr( const QString &check_type_name, const size_t &type_has_code ) {
		size_t count = binGenerateItems.size( );
		auto data = binGenerateItems.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].get( )->isSerializationType( check_type_name, type_has_code ) )
				return data[ index ].get( );
		return nullptr;
	}
	/// @brief 检索匹配类型名称，返回匹配的序列化项
	/// @tparam TBaseType 填充类型
	/// @return 失败返回 nullptr
	template< typename TBaseType >
	static BinGenerateItem * getBinGenerateItemPtr( ) {
		auto &typeInfo = typeid( TBaseType );
		QString typeName = typeInfo.name( );
		size_t hashCode = typeInfo.hash_code( );
		BinGenerateItem *binGenerateItem = getBinGenerateItemPtr( typeName, hashCode );
		if( binGenerateItem == nullptr )
			tools::debug::printError( QString( "[%1]{%2} 类未实现匹配的序列化功能" ).arg( typeName ).arg( hashCode ) );
		return binGenerateItem;
	}

	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 填充内容
	/// @param result_bin_data_vector 返回的二进制数据
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toBin( TBaseType *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
		BinGenerateItem *binGenerateItem = getBinGenerateItemPtr< TBaseType >( );
		if( binGenerateItem == nullptr )
			return 0;
		binGenerateItem->fillUnityBin( var_type, result_bin_data_vector );
		return result_bin_data_vector.size( );
	}

	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 填充内容
	/// @param result_bin_data_vector 返回的二进制数据
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toBin( const TBaseType &var_type, std_vector< uint8_t > &result_bin_data_vector ) {
		BinGenerateItem *binGenerateItem = getBinGenerateItemPtr< TBaseType >( );
		if( binGenerateItem == nullptr )
			return 0;
		binGenerateItem->fillUnityBin( &var_type, result_bin_data_vector );
		return result_bin_data_vector.size( );
	}

	/// @brief 数组转换到二进制序列
	/// @tparam TVectorIteratorType 数组元素类型
	/// @param obj 转换的数组
	/// @param result_bin 返回的二进制序列
	/// @return 序列个数
	template< typename TVectorIteratorType >
	static size_t toBin( const std_vector< TVectorIteratorType > &obj, std_vector< uint8_t > &result_bin ) {
		BinGenerateItem *binGenerateItem = getBinGenerateItemPtr< TVectorIteratorType >( );
		if( binGenerateItem == nullptr )
			return 0;
		binGenerateItem->fillVectorBin( &obj, result_bin );
		return result_bin.size( );
	}
	/// @brief 数组转换到二进制序列
	/// @tparam TVectorIteratorType 数组元素类型
	/// @param obj 转换的数组
	/// @param result_bin 返回的二进制序列
	/// @return 序列个数
	template< typename TVectorIteratorType >
	static size_t toBin( const std_vector< TVectorIteratorType * > &obj, std_vector< uint8_t > &result_bin ) {
		BinGenerateItem *binGenerateItem = getBinGenerateItemPtr< TVectorIteratorType >( );
		if( binGenerateItem == nullptr )
			return 0;
		binGenerateItem->fillPtrVectorBin( &obj, result_bin );
		return result_bin.size( );
	}
	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toObj( TBaseType *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		BinGenerateItem *binGenerateItem = getBinGenerateItemPtr< TBaseType >( );
		if( binGenerateItem == nullptr )
			return 0;
		return binGenerateItem->fillUnityObj( var_type, source_data_ptr, source_data_count );
	}

	/// @brief 对象直接填充二进制-数组
	/// @tparam TVectorIteratorType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TVectorIteratorType >
	static size_t toObj( std_vector< TVectorIteratorType > *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		BinGenerateItem *binGenerateItem = getBinGenerateItemPtr< TVectorIteratorType >( );
		if( binGenerateItem == nullptr )
			return 0;

		return binGenerateItem->fillVectorObj( var_type, source_data_ptr, source_data_count );
	}

	/// @brief 对象直接填充二进制-数组
	/// @tparam TVectorIteratorType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TVectorIteratorType >
	static size_t toObj( std_vector< TVectorIteratorType * > *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {

		BinGenerateItem *binGenerateItem = getBinGenerateItemPtr< TVectorIteratorType >( );
		if( binGenerateItem == nullptr )
			return 0;
		return binGenerateItem->fillPtrVectorObj( var_type, source_data_ptr, source_data_count );
	}
};

#endif // BINGENERATE_H_H_HEAD__FILE__
