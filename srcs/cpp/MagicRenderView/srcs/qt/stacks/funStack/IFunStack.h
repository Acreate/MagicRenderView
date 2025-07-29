#ifndef IFUNSTACK_H_H_HEAD__FILE__
#define IFUNSTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

class IFunctionDeclaration;
class IFunStack : public QObject {
	Q_OBJECT;
protected:
	std_vector< std_shared_ptr< IFunctionDeclaration > > functionList;
	QString name;
public:
	IFunStack( ) { }
	static bool init();
	virtual const QString & getName( ) const { return name; }
	/// @brief 获取函数对象
	/// @return 函数对象列表
	virtual std_vector< std_shared_ptr< IFunctionDeclaration > > getGenerFunctions( ) {
		return functionList;
	}
	/// @brief 追加一个函数对象
	/// @param append 函数对象
	virtual bool append( const std_shared_ptr< IFunctionDeclaration > &append ) {
		auto removeExtent = append.get( );
		for( auto &item : functionList )
			if( item.get( ) == removeExtent )
				return false;
		functionList.emplace_back( append );
		return true;
	}
	virtual std_shared_ptr< IFunctionDeclaration > remove( const std_shared_ptr< IFunctionDeclaration > &append ) {
		std_shared_ptr< IFunctionDeclaration > result( nullptr );
		auto iterator = functionList.begin( );
		auto end = functionList.end( );
		for( ; iterator != end; ++iterator )
			if( iterator->get( ) == append.get( ) ) {
				result = *iterator;
				functionList.erase( iterator );
				return result;
			}
		return result;
	}
};

#endif // IFUNSTACK_H_H_HEAD__FILE__
