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
	std_vector< std_pairt< NodeGeneraterItem *, QWidget * > > funStackItemS;
protected:
	virtual const NodeGeneraterItem * setCurrentIndex( const size_t &fun_stack_index );
	virtual std_pairt<NodeGeneraterItem *, QWidget *> generaterItemWidget( NodeGeneraterItem *node_item );
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
	virtual std_vector< NodeGeneraterItem * > getFunStackItemS( ) const {
		std_vector< NodeGeneraterItem * > result;
		for( auto &[ item, widget ] : funStackItemS )
			result.emplace_back( item );
		return result;
	}
	virtual NodeGeneraterItem * getCurrentItem( ) const { return currentItem; }
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // NODEGENERATERLISTWIDGET_H_H_HEAD__FILE__
