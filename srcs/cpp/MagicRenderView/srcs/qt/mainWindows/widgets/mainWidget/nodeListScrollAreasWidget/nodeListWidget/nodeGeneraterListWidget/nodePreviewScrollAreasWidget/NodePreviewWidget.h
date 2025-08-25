#ifndef NODEPREVIEWWIDGET_H_H_HEAD__FILE__
#define NODEPREVIEWWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
#include <QLabel>

#include <alias/type_alias.h>
class QGridLayout;
class NodeFuncPreviewImageWidget;
class IFunStack;
class NodePreviewWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< IFunStack > funStack;
	std_vector< NodeFuncPreviewImageWidget * > imageVector;
	QSize imageSize;
	QGridLayout *mainLayout;
public:
	NodePreviewWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodePreviewWidget( ) override;
protected:
	virtual void shortFunctionNodeWidget( );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
public:
	virtual const std_shared_ptr< IFunStack > & getFunStack( ) const { return funStack; }
	virtual bool setFunStack( const std_shared_ptr< IFunStack > &fun_stack );
	virtual const QSize & getImageSize( ) const { return imageSize; }
};

#endif // NODEPREVIEWWIDGET_H_H_HEAD__FILE__
