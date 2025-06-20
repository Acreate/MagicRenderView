#ifndef BASENODESTACK_H_H_HEAD__FILE__
#define BASENODESTACK_H_H_HEAD__FILE__
#pragma once
#include "qt/stack/nodeStack/INodeStack.h"

class IFunctionDeclaration;
class BaseNodeStack : public INodeStack {
	Q_OBJECT;
protected:
	using aliasVector = std_pairt< QString, std_vector< QString > >;
	using generateFcuntion = std_function< INodeWidget*( ) >;
	using generateNodePairt = std_pairt< aliasVector, generateFcuntion >;
	std_shared_ptr< std_vector< generateNodePairt > > nodeGenerate;
public:
	BaseNodeStack( const std_function< std_shared_ptr< INodeStack >( ) > &get_stack_function );
protected:
	INodeWidget * _newNode( const QString &type_name ) const;
public:
	INodeWidget * generateNode( const QString &type_name, QWidget *parnet = nullptr ) const override;
	 std_vector< std_pairt< QString, std_vector< QString > > > permissionNodeType( ) const override;
};

#endif // BASENODESTACK_H_H_HEAD__FILE__
