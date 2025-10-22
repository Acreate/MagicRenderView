#ifndef NODEMODULEWIDGET_H_H_HEAD__FILE__
#define NODEMODULEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

#include <alias/type_alias.h>

class QVBoxLayout;
class NodeModuleItemWidget;
class NodeItem;
class NodeItemInfo;
class NodeModuleWidget : public QWidget {
	Q_OBJECT;
protected:
	const std_vector< std_vector< NodeItemInfo * > > *runList;
	std_vector< NodeModuleItemWidget * > subItemWidget;
	QVBoxLayout *mainLayout;
	size_t currentIndex;
public:
	NodeModuleWidget( QWidget *parent = nullptr );
	virtual void clear( );
	virtual const std_vector< std_vector< NodeItemInfo * > > * getRunList( ) const;
	virtual void setRunList( const std_vector< std_vector< NodeItemInfo * > > *run_list );
	virtual size_t getCurrentRunNodeItemInfoVector( std_vector< NodeItemInfo * > &result_list ) const;
	virtual bool findNodeItemInfoAtIndex( const NodeItemInfo *node_item_info, size_t &result_index ) const;
	virtual bool findNodeItemInfoAtIndex( const NodeItem *node_item, size_t &result_index ) const;
	virtual bool jump( const size_t &jump_target_index ) {
		if( runList->size( ) <= jump_target_index )
			return false;
		currentIndex = jump_target_index;
		return true;
	}
	virtual bool next( ) {
		if( runList->size( ) == currentIndex )
			return false;
		++currentIndex;
		return true;
	}
	virtual bool toBegin( ) {
		if( runList->size( ) == 0 )
			return false;
		currentIndex = 0;
		return true;
	}
	virtual bool toEnd( ) {
		currentIndex = runList->size( );
		return true;
	}
	virtual bool isEnd( ) {
		return currentIndex == runList->size( );
	}
	virtual size_t getCurrentIndex( ) const { return currentIndex; }
	virtual size_t getCurrentCount( ) const { return runList->size( ); }
	virtual const std_vector< std_vector< NodeItemInfo * > > * getData( ) const { return runList; }
};

#endif // NODEMODULEWIDGET_H_H_HEAD__FILE__
