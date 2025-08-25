#ifndef NODEGENERATERITEM_H_H_HEAD__FILE__
#define NODEGENERATERITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

class NodeGeneraterListWidget;
class IFunStack;
class NodeGeneraterItem {
	friend class NodeGeneraterListWidget;
	QWidget *renderWidget;
	QImage *renderImage;
	std_shared_ptr< IFunStack > funStack;
public:
	virtual ~NodeGeneraterItem( );
protected:
	NodeGeneraterItem( const std_shared_ptr< IFunStack > &fun_stack );
	virtual const std_shared_ptr< IFunStack > & getFunStack( ) const { return funStack; }
	virtual QWidget * getRenderWidget( ) const { return renderWidget; }
	virtual QImage * getRenderImage( ) const { return renderImage; }
	virtual void setRenderWidget( QWidget *const render_widget ) { renderWidget = render_widget; }
	virtual void setRenderImage( QImage *const render_image ) { renderImage = render_image; }
};

#endif // NODEGENERATERITEM_H_H_HEAD__FILE__
