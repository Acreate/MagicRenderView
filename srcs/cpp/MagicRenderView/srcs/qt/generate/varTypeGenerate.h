#ifndef VARTYPEGENERATE_H_H_HEAD__FILE__
#define VARTYPEGENERATE_H_H_HEAD__FILE__
#pragma once
#include <alias/type_alias.h>

#include <qt/varType/varType.h>

#include "binGenerate.h"

#include "../tools/tools.h"

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
public:
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
	static VarType * templateVarType( QObject *parent ) {
		size_t count = generates.size( );
		if( count == 0 )
			return nullptr;
		QString generateTypeName = typeid( TType_Name ).name( );
		auto data = generates.data( );

		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == generateTypeName ) {
				auto &function = data[ index ].second;
				VarType *varType = function( parent, generateTypeName );
				if( varType == nullptr )
					return nullptr;
				return varType;
			}
		return nullptr;
	}

};

#endif // VARTYPEGENERATE_H_H_HEAD__FILE__
