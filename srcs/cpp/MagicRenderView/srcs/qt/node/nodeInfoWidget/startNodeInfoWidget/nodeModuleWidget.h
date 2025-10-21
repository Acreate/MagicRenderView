#ifndef NODEMODULEWIDGET_H_H_HEAD__FILE__
#define NODEMODULEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

#include <alias/type_alias.h>

class NodeItemInfo;
class NodeModuleWidget : public QWidget {
	Q_OBJECT;
protected:
	const std_vector< std_vector< NodeItemInfo * > > *runList;
	size_t currentIndex;
public:
	NodeModuleWidget( QWidget *parent = nullptr );
	virtual void clear( ) {
		runList = nullptr;
	}
	virtual const std_vector< std_vector< NodeItemInfo * > > * getRunList( ) const;
	virtual void setRunList( const std_vector< std_vector< NodeItemInfo * > > *run_list );
	virtual size_t getCurrentRunNodeItemInfoVector( std_vector< NodeItemInfo * > &result_list ) const;
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
};

#endif // NODEMODULEWIDGET_H_H_HEAD__FILE__
