#ifndef NODEFUNCPREVIEWIMAGEWIDGET_H_H_HEAD__FILE__
#define NODEFUNCPREVIEWIMAGEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QLabel>
#include <QWidget>

#include <alias/type_alias.h>

class Application;
class IFunctionDeclaration;
class NodeFuncPreviewImageWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< IFunctionDeclaration > functionDeclaration;
	QImage renderImage;
	Application *applicationInstancePtr;
	bool isPreeMouse;
public:
	NodeFuncPreviewImageWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	virtual const std_shared_ptr< IFunctionDeclaration > & getFunctionDeclaration( ) const { return functionDeclaration; }
	virtual bool setFunctionDeclaration( const std_shared_ptr< IFunctionDeclaration > &function_declaration );
	virtual QImage getRenderImage( ) const { return renderImage; }
protected:
	void showEvent( QShowEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // NODEFUNCPREVIEWIMAGEWIDGET_H_H_HEAD__FILE__
