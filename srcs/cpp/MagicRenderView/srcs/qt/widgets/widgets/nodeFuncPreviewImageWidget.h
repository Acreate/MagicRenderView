#ifndef NODEFUNCPREVIEWIMAGEWIDGET_H_H_HEAD__FILE__
#define NODEFUNCPREVIEWIMAGEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QLabel>
#include <QWidget>
#include "../../../alias/type_alias.h"

class IFunctionDeclaration;
class NodeFuncPreviewImageWidget : public QWidget {
	Q_OBJECT;
protected:
	QLabel *label;
	std_shared_ptr< IFunctionDeclaration > functionDeclaration;
public:
	NodeFuncPreviewImageWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	virtual const std_shared_ptr< IFunctionDeclaration > & getFunctionDeclaration( ) const { return functionDeclaration; }
	virtual bool setFunctionDeclaration( const std_shared_ptr< IFunctionDeclaration > &function_declaration );
protected:
	void showEvent( QShowEvent *event ) override;
	
};

#endif // NODEFUNCPREVIEWIMAGEWIDGET_H_H_HEAD__FILE__
