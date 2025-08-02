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
	NodeGeneraterItem *currentContentFunStack;
	std_vector< NodeGeneraterItem * > funStackItemS;
public:
	NodeGeneraterListWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	virtual bool setCurrentItem( const NodeGeneraterItem *fun_stack );
	virtual bool appendItem( NodeGeneraterItem *fun_stack );
	virtual NodeGeneraterItem * appendFunStack( const std_shared_ptr< IFunStack > &fun_stack );
	virtual bool setCurrentFunStackIndex( const size_t &fun_stack_index );
	virtual std_shared_ptr< IFunStack > getCurrentFunStack( ) const;
	virtual size_t getCurrentFunStackIndex( ) const;
	virtual size_t getCurrentFunStackCount( ) const {
		return funStackItemS.size( );
	}
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // NODEGENERATERLISTWIDGET_H_H_HEAD__FILE__
