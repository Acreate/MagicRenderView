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
public:
	NodeModuleWidget( const std_vector< std_vector< NodeItemInfo * > > *run_list, QWidget *parent = nullptr );

	virtual void clear( ) {
		runList = nullptr;
	}
	virtual const std_vector< std_vector< NodeItemInfo * > > * getRunList( ) const;
	virtual void setRunList( const std_vector< std_vector< NodeItemInfo * > > *run_list );
	
	
};

#endif // NODEMODULEWIDGET_H_H_HEAD__FILE__
