#ifndef BINGENERATE_H_H_HEAD__FILE__
#define BINGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "../tools/tools.h"

class BinGenerate final {
public:
	class BinGenerateItem;
	class Serialization final {
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
	};

	class BinGenerateItem {
	public:
		friend class BinGenerate;

		class Unity {
		public:
			friend class BinGenerate;
		private:
			QString unityTypeName;
			void *ptr = nullptr;
			bool isConst;
		public:
			virtual void clear( ) {
				unityTypeName.clear( );
				ptr = nullptr;
			}
			template< typename TClassName >
			void init( TClassName &unity ) {
				unityTypeName = typeid( TClassName ).name( );
				ptr = ( void * ) &unity;
				isConst = true;
			}
			template< typename TClassName >
			void init( const TClassName &unity ) {
				unityTypeName = typeid( const TClassName ).name( );
				ptr = ( void * ) &unity;
				isConst = true;
			}
			template< typename TClassName >
			void init( TClassName *unity ) {
				unityTypeName = typeid( TClassName ).name( );
				ptr = ( void * ) unity;
				isConst = true;
			}
			template< typename TClassName >
			void init( const TClassName *unity ) {
				unityTypeName = typeid( const TClassName ).name( );
				ptr = ( void * ) unity;
				isConst = true;
			}
			template< typename TClassName >
			TClassName * get( bool &is_const ) const {
				if( unityTypeName != typeid( TClassName ).name( ) )
					return nullptr;
				is_const = isConst;
				return ( TClassName * ) ptr;

			}

			virtual ~Unity( ) = default;
		};

		class UnityVector {
		public:
			friend class BinGenerate;
		private:
			QString unityTypeName;
			void *ptr = nullptr;
			bool isConst;
		public:
			virtual void clear( ) {
				unityTypeName.clear( );
				ptr = nullptr;
			}
			template< typename TClassName >
			void init( std_vector< TClassName > &vector ) {
				unityTypeName = typeid( std_vector< TClassName > ).name( );
				ptr = ( void * ) &vector;
				isConst = false;
			}
			template< typename TClassName >
			void init( const std_vector< TClassName > &vector ) {
				unityTypeName = typeid( const std_vector< TClassName > ).name( );
				ptr = ( void * ) &vector;
				isConst = true;
			}
			template< typename TClassName >
			void init( std_vector< TClassName > *vector ) {
				unityTypeName = typeid( std_vector< TClassName > ).name( );
				ptr = ( void * ) vector;
				isConst = false;
			}
			template< typename TClassName >
			void init( const std_vector< TClassName > *vector ) {
				unityTypeName = typeid( const std_vector< TClassName > ).name( );
				ptr = ( void * ) vector;
				isConst = true;
			}
			template< typename TClassName >
			std_vector< TClassName > * get( bool &is_const ) const {
				if( unityTypeName != typeid( std_vector< TClassName > ).name( ) )
					return nullptr;
				is_const = isConst;
				return ( std_vector< TClassName > * ) ptr;

			}
			virtual ~UnityVector( ) = default;
		};
		class UnityPtrVector {
		public:
			friend class BinGenerate;
		protected:
			QString unityTypeName;
			void *ptr = nullptr;
			bool isConst;
		public:
			virtual void clear( ) {
				unityTypeName.clear( );
				ptr = nullptr;
				isConst = false;
			}
			template< typename TClassName >
			void init( std_vector< TClassName * > &vector ) {
				unityTypeName = typeid( std_vector< TClassName * > ).name( );
				ptr = ( void * ) &vector;
				isConst = false;
			}
			template< typename TClassName >
			void init( const std_vector< TClassName * > &vector ) {
				unityTypeName = typeid( std_vector< TClassName * > ).name( );
				ptr = ( void * ) &vector;
				isConst = true;
			}
			template< typename TClassName >
			void init( std_vector< TClassName * > *vector ) {
				unityTypeName = typeid( std_vector< TClassName * > ).name( );
				ptr = ( void * ) vector;
				isConst = false;
			}
			template< typename TClassName >
			void init( const std_vector< TClassName * > *vector ) {
				unityTypeName = typeid( const std_vector< TClassName * > ).name( );
				ptr = ( void * ) vector;
				isConst = true;
			}
			template< typename TClassName >
			std_vector< TClassName * > * get( bool &is_const ) const {
				if( unityTypeName != typeid( std_vector< TClassName * > ).name( ) )
					return nullptr;
				is_const = isConst;
				return ( std_vector< TClassName * > * ) ptr;
			}
			virtual ~UnityPtrVector( ) = default;
		};
	protected:
		static Serialization serialization;
	protected:
		QString typeName;
		std_shared_ptr< Unity > unitySharedPtr;
	public:
		virtual size_t fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const = 0;
		virtual size_t fillObj( Unity *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const = 0;
		virtual size_t fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const = 0;
		virtual size_t fillObj( UnityVector *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const = 0;
		virtual size_t fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const = 0;
		virtual size_t fillObj( UnityPtrVector *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const = 0;
	public:
		BinGenerateItem( ) : unitySharedPtr( new Unity ) {

		}
		virtual ~BinGenerateItem( ) { }
	protected:
		template< typename TPtrType >
		size_t fillBinTemplate( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
			bool isConst;
			auto dataPtr = var_type->get< TPtrType >( isConst );
			if( dataPtr == nullptr )
				return 0;
			std_vector< uint8_t > resultBuff;
			std_vector< uint8_t > countBuff;
			std_vector< uint8_t > nameBuff;
			size_t count = serialization.fillBinVector( typeName, nameBuff );
			serialization.fillBinVector( count, countBuff );
			resultBuff.append_range( countBuff );
			resultBuff.append_range( nameBuff );
			count = serialization.fillBinVector( *dataPtr, nameBuff );
			serialization.fillBinVector( count, countBuff );
			resultBuff.append_range( countBuff );
			resultBuff.append_range( nameBuff );
			count = resultBuff.size( );
			serialization.fillBinVector( count, countBuff );
			result_bin_data_vector.clear( );
			result_bin_data_vector.append_range( countBuff );
			result_bin_data_vector.append_range( resultBuff );
			return result_bin_data_vector.size( );
		}
		template< typename TPtrType >
		size_t fillObjTemplate( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			bool isConst;
			auto dataPtr = var_type->get< TPtrType >( isConst );
			if( dataPtr == nullptr )
				return 0;
			size_t menorySize;
			size_t count = serialization.fillObjVector( &menorySize, source_ptr, source_ptr_count );
			auto mod = source_ptr_count - count;
			if( menorySize > mod )
				return 0;
			auto offset = source_ptr + count;
			count = serialization.fillObjVector( &menorySize, offset, mod );
			offset = offset + count;
			mod -= count;
			if( menorySize > mod )
				return 0;
			QString converTypeName;
			count = serialization.fillObjVector( &converTypeName, offset, menorySize );
			if( converTypeName != typeName )
				return 0;
			mod -= count;
			offset += count;
			count = serialization.fillObjVector( &menorySize, offset, mod );
			mod -= count;
			offset += count;
			count = serialization.fillObjVector( dataPtr, offset, mod );
			return offset - source_ptr + count;
		}
		template< typename TPtrType >
		size_t fillBinTemplate( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
			bool isConst;
			auto dataPtr = var_type->get< TPtrType >( isConst );
			if( dataPtr == nullptr )
				return 0;
			std_vector< uint8_t > resultBuff;
			std_vector< uint8_t > countBuff;
			std_vector< uint8_t > nameBuff;
			size_t count = serialization.fillBinVector( typeName, nameBuff );
			serialization.fillBinVector( count, countBuff );
			resultBuff.append_range( countBuff );
			resultBuff.append_range( nameBuff );
			count = dataPtr->size( );
			serialization.fillBinVector( count, countBuff );
			resultBuff.append_range( countBuff );
			size_t index = 0;
			auto data = dataPtr->data( );
			auto unity = unitySharedPtr.get( );
			for( ; index < count; ++index ) {
				unity->init( data[ index ] );
				this->fillBin( unity, nameBuff );
				resultBuff.append_range( nameBuff );
			}
			count = resultBuff.size( );
			serialization.fillBinVector( count, countBuff );
			result_bin_data_vector.clear( );
			result_bin_data_vector.append_range( countBuff );
			result_bin_data_vector.append_range( resultBuff );
			return 0;
		}
		template< typename TPtrType >
		size_t fillObjTemplate( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			bool isConst;
			auto dataPtr = var_type->get< TPtrType >( isConst );
			if( dataPtr == nullptr )
				return 0;
			size_t menorySize;
			size_t count = serialization.fillObjVector( &menorySize, source_ptr, source_ptr_count );
			auto mod = source_ptr_count - count;
			if( mod < menorySize )
				return 0;
			auto offset = source_ptr + count;
			count = serialization.fillObjVector( &menorySize, offset, mod );
			offset = offset + count;
			mod -= count;
			if( menorySize > mod )
				return 0;
			QString converTypeName;
			count = serialization.fillObjVector( &converTypeName, offset, menorySize );
			if( converTypeName != typeName )
				return 0;
			mod -= count;
			offset += count;
			size_t vectorCount;
			count = serialization.fillObjVector( &vectorCount, offset, mod );
			mod -= count;
			offset += count;
			dataPtr->resize( vectorCount );
			auto data = dataPtr->data( );
			size_t index = 0;
			auto unity = unitySharedPtr.get( );
			for( ; index < vectorCount; ++index ) {
				TPtrType var;
				unitySharedPtr->init( var );
				count = this->fillObj( unity, offset, mod );
				mod -= count;
				offset += count;
				data[ index ] = var;
			}
			return offset - source_ptr;
		}
		template< typename TPtrType >
		size_t fillBinTemplate( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
			bool isConst;
			auto dataPtr = var_type->get< TPtrType >( isConst );
			if( dataPtr == nullptr )
				return 0;
			std_vector< uint8_t > resultBuff;
			std_vector< uint8_t > countBuff;
			std_vector< uint8_t > nameBuff;
			size_t count = serialization.fillBinVector( typeName, nameBuff );
			serialization.fillBinVector( count, countBuff );
			resultBuff.append_range( countBuff );
			resultBuff.append_range( nameBuff );
			count = dataPtr->size( );
			serialization.fillBinVector( count, countBuff );
			resultBuff.append_range( countBuff );
			size_t index = 0;
			auto data = dataPtr->data( );
			auto unity = unitySharedPtr.get( );
			for( ; index < count; ++index ) {
				unity->init( *data[ index ] );
				this->fillBin( unity, nameBuff );
				resultBuff.append_range( nameBuff );
			}
			count = resultBuff.size( );
			serialization.fillBinVector( count, countBuff );
			result_bin_data_vector.clear( );
			result_bin_data_vector.append_range( countBuff );
			result_bin_data_vector.append_range( resultBuff );
			return 0;
		}
		template< typename TPtrType >
		size_t fillObjTemplate( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
			bool isConst;
			auto dataPtr = var_type->get< TPtrType >( isConst );
			if( dataPtr == nullptr )
				return 0;
			size_t menorySize;
			size_t count = serialization.fillObjVector( &menorySize, source_ptr, source_ptr_count );
			auto mod = source_ptr_count - count;
			if( mod < menorySize )
				return 0;
			auto offset = source_ptr + count;
			count = serialization.fillObjVector( &menorySize, offset, mod );
			offset = offset + count;
			mod -= count;
			if( menorySize > mod )
				return 0;
			QString converTypeName;
			count = serialization.fillObjVector( &converTypeName, offset, menorySize );
			if( converTypeName != typeName )
				return 0;
			mod -= count;
			offset += count;
			size_t vectorCount;
			count = serialization.fillObjVector( &vectorCount, offset, mod );
			mod -= count;
			offset += count;
			size_t index = 0;
			count = dataPtr->size( );
			auto data = dataPtr->data( );
			for( ; index < count; ++index ) delete data[ index ];
			dataPtr->resize( vectorCount );
			data = dataPtr->data( );
			auto unity = unitySharedPtr.get( );
			for( ; index < vectorCount; ++index ) {
				auto var = new TPtrType;
				unity->init( var );
				count = this->fillObj( unity, offset, mod );
				mod -= count;
				offset += count;
				data[ index ] = var;
			}
			return offset - source_ptr;
		}
	};
protected:
	static std_vector< std_pairt< QString, std_shared_ptr< BinGenerateItem > > > binGenerateItems;
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
			if( data[ index ].first == ptr->typeName ) {
				data[ index ].second = std_shared_ptr< BinGenerateItem >( ptr );
				return true;
			}
		binGenerateItems.emplace_back( ptr->typeName, std_shared_ptr< BinGenerateItem >( ptr ) );
		return true;
	}
public:
	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 填充内容
	/// @param result_bin_data_vector 返回的二进制数据
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toBin( const TBaseType &var_type, std_vector< uint8_t > &result_bin_data_vector ) {
		QString typeName = typeid( TBaseType ).name( );
		size_t count = binGenerateItems.size( );
		auto data = binGenerateItems.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].first == typeName ) {
				BinGenerateItem *binGenerateItem = data[ index ].second.get( );
				BinGenerateItem::Unity unity;
				unity.init( var_type );
				binGenerateItem->fillBin( &unity, result_bin_data_vector );
				return result_bin_data_vector.size( );
			}
		tools::debug::printError( QString( "[%1] 类未实现匹配的序列化功能" ).arg( typeName ) );
		return 0;
	}

	/// @brief 数组转换到二进制序列
	/// @tparam TVectorIteratorType 数组元素类型
	/// @param obj 转换的数组
	/// @param result_bin 返回的二进制序列
	/// @return 序列个数
	template< typename TVectorIteratorType >
	static size_t toBin( const std_vector< TVectorIteratorType > &obj, std_vector< uint8_t > &result_bin ) {
		QString typeName = typeid( TVectorIteratorType ).name( );
		size_t count = binGenerateItems.size( );
		auto data = binGenerateItems.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].first == typeName ) {
				BinGenerateItem *binGenerateItem = data[ index ].second.get( );
				BinGenerateItem::UnityVector unity;
				unity.init( obj );
				binGenerateItem->fillBin( &unity, result_bin );
				return result_bin.size( );
			}
		tools::debug::printError( QString( "[%1] 类未实现匹配的序列化功能" ).arg( typeName ) );
		return 0;
	}
	/// @brief 数组转换到二进制序列
	/// @tparam TVectorIteratorType 数组元素类型
	/// @param obj 转换的数组
	/// @param result_bin 返回的二进制序列
	/// @return 序列个数
	template< typename TVectorIteratorType >
	static size_t toBin( const std_vector< TVectorIteratorType * > &obj, std_vector< uint8_t > &result_bin ) {
		QString typeName = typeid( TVectorIteratorType ).name( );
		size_t count = binGenerateItems.size( );
		auto data = binGenerateItems.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].first == typeName ) {
				BinGenerateItem *binGenerateItem = data[ index ].second.get( );
				BinGenerateItem::UnityPtrVector unity;
				unity.init( obj );
				binGenerateItem->fillBin( &unity, result_bin );
				return result_bin.size( );
			}
		tools::debug::printError( QString( "[%1] 类未实现匹配的序列化功能" ).arg( typeName ) );
		return 0;
	}
	/// @brief 对象直接填充二进制
	/// @tparam TBaseType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TBaseType >
	static size_t toObj( TBaseType *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
		QString typeName = typeid( TBaseType ).name( );
		size_t count = binGenerateItems.size( );
		auto data = binGenerateItems.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].first == typeName ) {
				BinGenerateItem *binGenerateItem = data[ index ].second.get( );
				BinGenerateItem::Unity unity;
				unity.init( var_type );
				return binGenerateItem->fillObj( &unity, source_data_ptr, source_data_count );
			}
		tools::debug::printError( QString( "[%1] 类未实现匹配的序列化功能" ).arg( typeName ) );
		return 0;
	}

	/// @brief 对象直接填充二进制-数组
	/// @tparam TVectorIteratorType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TVectorIteratorType >
	static size_t toObj( std_vector< TVectorIteratorType > *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {

		QString typeName = typeid( TVectorIteratorType ).name( );
		size_t count = binGenerateItems.size( );
		auto data = binGenerateItems.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].first == typeName ) {
				BinGenerateItem *binGenerateItem = data[ index ].second.get( );
				BinGenerateItem::UnityVector unity;
				unity.init( var_type );
				return binGenerateItem->fillObj( &unity, source_data_ptr, source_data_count );
			}
		tools::debug::printError( QString( "[%1] 类未实现匹配的序列化功能" ).arg( typeName ) );
		return 0;
	}

	/// @brief 对象直接填充二进制-数组
	/// @tparam TVectorIteratorType 填充类型
	/// @param var_type 被填充对象指针
	/// @param source_data_ptr 匹配数据
	/// @param source_data_count 匹配数据的总个数
	/// @return 失败返回 false
	template< typename TVectorIteratorType >
	static size_t toObj( std_vector< TVectorIteratorType * > *var_type, const uint8_t *source_data_ptr, const size_t &source_data_count ) {

		QString typeName = typeid( TVectorIteratorType ).name( );
		size_t count = binGenerateItems.size( );
		auto data = binGenerateItems.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].first == typeName ) {
				BinGenerateItem *binGenerateItem = data[ index ].second.get( );
				BinGenerateItem::UnityPtrVector unity;
				unity.init( var_type );
				return binGenerateItem->fillObj( &unity, source_data_ptr, source_data_count );
			}
		tools::debug::printError( QString( "[%1] 类未实现匹配的序列化功能" ).arg( typeName ) );
		return 0;
	}
};

#endif // BINGENERATE_H_H_HEAD__FILE__
