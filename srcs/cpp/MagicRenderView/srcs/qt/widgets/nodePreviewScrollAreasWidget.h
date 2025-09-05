#ifndef NODEPREVIEWSCROLLAREASWIDGET_H_H_HEAD__FILE__
#define NODEPREVIEWSCROLLAREASWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>

#include <alias/type_alias.h>

class IFunStack;
class NodePreviewWidget;
class NodePreviewScrollAreasWidget : public QScrollArea {
	Q_OBJECT;
protected:
	NodePreviewWidget *nodePreviewWidget;
public:
	NodePreviewScrollAreasWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodePreviewScrollAreasWidget( ) override;
	virtual NodePreviewWidget * getNodeListWidget( ) const { return nodePreviewWidget; }
	virtual const std_shared_ptr< IFunStack > & getFunStack( ) const ;
	virtual bool setFunStack( const std_shared_ptr< IFunStack > &fun_stack );
};
#endif // NODEPREVIEWSCROLLAREASWIDGET_H_H_HEAD__FILE__
