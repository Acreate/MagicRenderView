#ifndef NODEINPUTLINETEXT_H_H_HEAD__FILE__
#define NODEINPUTLINETEXT_H_H_HEAD__FILE__
#pragma once

#include "qt/node/nodeComponent/INodeComponent.h"

class StringTypeObject;
class QLabel;
class QLineEdit;
class QHBoxLayout;
class NodeInputLineText : public INodeComponent {
	Q_OBJECT;
protected:
	std_shared_ptr< StringTypeObject > var;
protected:
	QHBoxLayout *mainLayout;
	QLabel *titile;
public:
	NodeInputLineText( const QString &node_component_name, QWidget *parent, Qt::WindowFlags f );
	NodeInputLineText( const QString &node_component_name, QWidget *parent ): NodeInputLineText( node_component_name, parent, Qt::WindowFlags( ) ) {
	}
	bool resetOrg( ) override;
	virtual bool setText( const QString &text );
	virtual QString getText( ) const;
	const std_shared_ptr< ITypeObject > getVarObject( ) const override;
	const ITypeObject * getVarObjectPtr( ) const override;
	bool setVar( const std_shared_ptr< ITypeObject > &new_var ) const override;
	bool setVar( const ITypeObject &new_var ) const override;
	void setNodeComponentName( const QString &node_component_name ) override;
	INodeComponent * getPosNodeComponent( const QPoint &pos ) const override;
	bool tryLetChangeVar( const ITypeObject *object_ptr ) const override;
	bool tryLetChangeVar( const INodeComponent *component_object_ptr ) const override;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODEINPUTLINETEXT_H_H_HEAD__FILE__
