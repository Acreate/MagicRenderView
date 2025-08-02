#ifndef NODEGENERATERLISTWIDGET_H_H_HEAD__FILE__
#define NODEGENERATERLISTWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "../../../alias/type_alias.h"
class NodeGeneraterItem;
class IFunStack;
class QVBoxLayout;
class NodeGeneraterListWidget : public QWidget {
	Q_OBJECT;
protected:
	QVBoxLayout *mainLayout;
	NodeGeneraterItem *currentItem;
	std_vector< NodeGeneraterItem * > funStackItemS;
public:
	NodeGeneraterListWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeGeneraterListWidget( ) override;
	virtual bool setCurrentItem( const NodeGeneraterItem *item );
	virtual const NodeGeneraterItem * appendItem( NodeGeneraterItem *item );
	virtual const NodeGeneraterItem * appendFunStack( const std_shared_ptr< IFunStack > &fun_stack );
	virtual const NodeGeneraterItem * setCurrentFunStackIndex( const size_t &fun_stack_index );
	virtual std_shared_ptr< IFunStack > getCurrentFunStack( ) const;
	virtual size_t getCurrentFunStackIndex( ) const;
	virtual size_t getCurrentFunStackCount( ) const {
		return funStackItemS.size( );
	}
	virtual const std_vector< NodeGeneraterItem * > & getFunStackItemS( ) const { return funStackItemS; }
	virtual NodeGeneraterItem * getCurrentItem( ) const { return currentItem; }
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // NODEGENERATERLISTWIDGET_H_H_HEAD__FILE__
