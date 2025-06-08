#ifndef BASENODESTACK_H_H_HEAD__FILE__
#define BASENODESTACK_H_H_HEAD__FILE__
#pragma once
#include "qt/stack/nodeStack/INodeStack.h"

class BaseNodeStack : public INodeStack {
	Q_OBJECT;
protected:
	INodeWidget * _newNode( const QString &type_name ) const;
public:
	INodeWidget * generateNode( const QString &type_name, QWidget *parnet = nullptr ) const override;
	INodeWidget * setStorageNode( INodeWidget *storage_obj, const QString &storage_name ) override;
	INodeWidget * getStorageNode( const QString &storage_name ) const override;
	INodeWidget * removeStorageNode( const QString &storage_name ) override;
	std_vector< std_pairt< QString, std_vector< QString > > > permissionNodeType( ) const override;
};

#endif // BASENODESTACK_H_H_HEAD__FILE__
