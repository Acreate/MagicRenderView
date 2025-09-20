#ifndef VARTYPEGENERATE_H_H_HEAD__FILE__
#define VARTYPEGENERATE_H_H_HEAD__FILE__
#pragma once
#include <alias/type_alias.h>

#include "binGenerate.h"

#include "../tools/tools.h"

#include "../varType/varType.h"

class QString;
class QObject;

class VarTypeGenerate final {
private:
	friend class VarTypeGenerateItem;
	using generate_function = std_function< VarType *( QObject *, const QString & ) >;
private:
	static VarType * templateVarType( QObject *parent, const QString &type_name );
	static std_vector< VarType * > vars;
	static std_vector< std_pairt< QString, generate_function > > generates;
private:
	class VarTypeGenerateItem {
	public:
		template< typename TTBase >
		static VarTypeGenerate::generate_function createVarTypeGenerateFunction( ) {
			return [] ( QObject *parent, const QString &type_name ) ->VarType * {
				VarType *varType = VarTypeGenerate::templateVarType( parent, type_name );
				if( varType->init< TTBase >( ) == true )
					return varType;
				delete varType;
				return nullptr;
			};
		}
	};

	template< typename TTBase >
	static std_pairt< QString, VarTypeGenerate::generate_function > mkVarTypeGeneratePair( ) {
		return { typeid( TTBase ).name( ), VarTypeGenerateItem::createVarTypeGenerateFunction< TTBase >( ) };
	}
	/// @brief 建立信号链接
	/// @param sender_obj 信号对象指针
	static void cnnectSignal( VarType *sender_obj );
public:
	static std_vector< uint8_t > toBin( const VarType *obj_ptr );
	static VarType * toObj( size_t &reseult_use_count, const uint8_t *source_bin_data_ptr, const size_t &source_bin_data_count );

	template< typename TTBase >
	static size_t appendType( ) {
		generates.emplace_back( mkVarTypeGeneratePair< TTBase >( ) );
		generates = tools::vector::removeRepetition< QString, std_pairt< QString, VarTypeGenerate::generate_function > >( generates, [] ( const std::pair< QString, VarTypeGenerate::generate_function > &pair ) {
			return pair.first;
		} );
		return generates.size( );
	}
	/// @brief 获取类型支持列表
	/// @return 列表
	static std_vector< QString > supportTypes( ) {
		size_t count = generates.size( );
		std_vector< QString > result( count );
		if( count == 0 )
			return result;
		auto data = generates.data( );
		auto des = result.data( );
		for( size_t index = 0; index < count; ++index )
			des[ index ] = data[ index ].first;
		return result;
	}
	template< typename TType_Name >
	static VarType * templateVarType( QObject *parent = nullptr ) {
		QString generateTypeName = typeid( TType_Name ).name( );
		return craeteVarType( generateTypeName, parent );
	}
	static VarType * craeteVarType( const QString &generateTypeName, QObject *parent = nullptr );
	/// @brief 获取 var_type_ptr 的原本生成代码
	/// @param var_type_ptr 获取的对象指针
	/// @return 生成代码，失败返回 0
	static size_t genVarTypeCode( const VarType *var_type_ptr );
	/// @brief 获取生成代码指向的对象
	/// @param var_type_generate_code 生成代码
	/// @return 指向对象，失败返回 nullptr
	static VarType * fromGenerateCodeGetVarTypObjPtr( const size_t &var_type_generate_code );
};

#endif // VARTYPEGENERATE_H_H_HEAD__FILE__
