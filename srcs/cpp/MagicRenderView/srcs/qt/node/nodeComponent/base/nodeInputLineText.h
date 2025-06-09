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
	virtual void setTitle( const QString &new_title );
public:
	NodeInputLineText( ): NodeInputLineText( nullptr, Qt::WindowFlags( ) ) { }
	NodeInputLineText( QWidget *parent )
		: NodeInputLineText( parent, Qt::WindowFlags( ) ) { }
	NodeInputLineText( QWidget *parent, Qt::WindowFlags f );
	bool resetOrg( ) override;
	virtual bool setText( const QString &text );
	virtual QString getText( ) const;
	const std_shared_ptr< ITypeObject > getVarObject( ) const override;
	const ITypeObject * getVarObjectPtr( ) const override;
	bool setVar( const std_shared_ptr< ITypeObject > &new_var ) const override;
	bool setVar( const ITypeObject &new_var ) const override;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODEINPUTLINETEXT_H_H_HEAD__FILE__
