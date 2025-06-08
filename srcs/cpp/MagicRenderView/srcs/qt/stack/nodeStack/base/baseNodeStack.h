#ifndef BASENODESTACK_H_H_HEAD__FILE__
#define BASENODESTACK_H_H_HEAD__FILE__
#pragma once
#include "qt/stack/nodeStack/INodeStack.h"

class IFunctionDeclaration;
class BaseNodeStack : public INodeStack {
	Q_OBJECT;
protected:
	using aliasVector = std_pairt< QString, std_vector< QString > >;
	using generateFcuntion = std_function< INodeWidget*( const std_shared_ptr< IFunctionDeclaration > & ) >;
	using generateNodePairt = std_pairt< aliasVector, generateFcuntion >;
	std_shared_ptr< std_vector< generateNodePairt > > nodeGenerate;
public:
	BaseNodeStack( );
protected:
	INodeWidget * _newNode( const QString &type_name, const std_shared_ptr< IFunctionDeclaration > &function_declarction ) const;
public:
	INodeWidget * generateNode( const QString &type_name, QWidget *parnet = nullptr, const std_shared_ptr<IFunctionDeclaration> &function_declaration = { } ) const override;
	std_vector< std_pairt< std_pairt< QString, std_vector< QString > >, std_function< void( ) > > > permissionNodeType( ) const override;
};

#endif // BASENODESTACK_H_H_HEAD__FILE__
