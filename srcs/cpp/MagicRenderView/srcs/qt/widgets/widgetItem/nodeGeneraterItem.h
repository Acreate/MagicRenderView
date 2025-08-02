#ifndef NODEGENERATERITEM_H_H_HEAD__FILE__
#define NODEGENERATERITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

class NodeGeneraterListWidget;
class IFunStack;
class NodeGeneraterItem {

	QWidget *renderWidget;
	QImage *renderImage;
	std_shared_ptr< IFunStack > funStack;
public:
	NodeGeneraterItem( const std_shared_ptr< IFunStack > &fun_stack );
	virtual ~NodeGeneraterItem( );
	virtual const std_shared_ptr< IFunStack > & getFunStack( ) const { return funStack; }
	virtual QWidget * getRenderWidget( ) const { return renderWidget; }
	virtual QImage * getRenderImage( ) const { return renderImage; }
};

#endif // NODEGENERATERITEM_H_H_HEAD__FILE__
