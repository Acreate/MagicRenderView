#ifndef NODEGENERATERITEM_H_H_HEAD__FILE__
#define NODEGENERATERITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class NodeGeneraterListWidget;
class IFunStack;
class NodeGeneraterItem {
	friend class NodeGeneraterItemGenerater;
	QWidget *renderWidget;
	QImage *renderImage;
	std_shared_ptr< IFunStack > funStack;
public:
	virtual ~NodeGeneraterItem( );
	virtual const IFunStack * getFunStack( ) const { return funStack.get( ); }
protected:
	NodeGeneraterItem( const std_shared_ptr< IFunStack > &fun_stack );
};
class NodeGeneraterItemGenerater {
	friend class NodeGeneraterListWidget;
	static NodeGeneraterItem * generaterItem( const std_shared_ptr< IFunStack > &fun_stack ) {
		return new NodeGeneraterItem( fun_stack );
	}

	static void setRenderWidget( NodeGeneraterItem *node_generater_item, QWidget *render_widget ) { node_generater_item->renderWidget = render_widget; }
	static void setRenderImage( NodeGeneraterItem *node_generater_item, QImage *render_image ) { node_generater_item->renderImage = render_image; }
	static QWidget * getRenderWidget( const NodeGeneraterItem *node_generater_item ) { return node_generater_item->renderWidget; }
	static QImage * getRenderImage( const NodeGeneraterItem *node_generater_item ) { return node_generater_item->renderImage; }
	static std_shared_ptr< IFunStack > getFunStack( const NodeGeneraterItem *node_generater_item ) { return node_generater_item->funStack; }
public:
	static const QWidget * getConstRenderWidget( const NodeGeneraterItem *node_generater_item ) { return node_generater_item->renderWidget; }
	static const QImage * getConstRenderImage( const NodeGeneraterItem *node_generater_item ) { return node_generater_item->renderImage; }
	static const std_shared_ptr< IFunStack > & getConstFunStack( const NodeGeneraterItem *node_generater_item ) { return node_generater_item->funStack; }

};
#endif // NODEGENERATERITEM_H_H_HEAD__FILE__
