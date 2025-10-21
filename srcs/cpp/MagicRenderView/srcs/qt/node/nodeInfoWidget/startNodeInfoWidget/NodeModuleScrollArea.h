#ifndef NODEMODULESCROLLAREA_H_H_HEAD__FILE__
#define NODEMODULESCROLLAREA_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

#include "../../../../alias/type_alias.h"

class NodeModuleWidget;
class NodeItemInfo;
class NodeModuleScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	NodeModuleWidget* nodeModuleWidget;
public:
	NodeModuleScrollArea( const std_vector< std_vector< NodeItemInfo * > > *run_list, QWidget *parent = nullptr );
	virtual void clear( );
	virtual const std_vector< std_vector< NodeItemInfo * > > * getRunList( ) const;
	virtual void setRunList( const std_vector< std_vector< NodeItemInfo * > > *run_list );
	virtual NodeModuleWidget * getNodeModuleWidget( ) const { return nodeModuleWidget; }
};

#endif // NODEMODULESCROLLAREA_H_H_HEAD__FILE__
