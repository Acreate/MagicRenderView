#ifndef NODEGENERATERLISTWIDGET_H_H_HEAD__FILE__
#define NODEGENERATERLISTWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "../../../alias/type_alias.h"
class IFunStack;
class QVBoxLayout;
class NodeGeneraterListWidget : public QWidget {
	Q_OBJECT;
protected:
	QVBoxLayout *mainLayout;
	std_shared_ptr< IFunStack > currentContentFunStack;
	std_vector< std_shared_ptr< IFunStack > > funStacks;
public:
	NodeGeneraterListWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	virtual bool setCurrentFunStack( const std_shared_ptr< IFunStack > &fun_stack );
	virtual bool setCurrentFunStackIndex( const size_t &fun_stack_index );
	virtual std_shared_ptr< IFunStack > getCurrentFunStack( );
	virtual std_shared_ptr< IFunStack > getCurrentFunStackIndex( );
	virtual bool appendCurrentFunStack( const std_shared_ptr< IFunStack > &fun_stack );
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // NODEGENERATERLISTWIDGET_H_H_HEAD__FILE__
