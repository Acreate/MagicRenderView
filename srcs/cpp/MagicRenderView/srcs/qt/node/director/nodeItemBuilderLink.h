#ifndef NODEITEMBUILDERLINK_H_H_HEAD__FILE__
#define NODEITEMBUILDERLINK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class NodePort;
class NodeOutputPort;
class NodeInputPort;
class NodePortLinkInfo;
class NodeItemInfo;
class NodeItemBuilderLink : public QObject {
	Q_OBJECT;
	friend class NodeDirector;
	friend class Application;
protected:
	NodeItemInfo *nodeItemInfo;
public:
	NodeItemBuilderLink( NodeItemInfo *node_item_info );
	~NodeItemBuilderLink( ) override;
	virtual bool generateBuilderInfo( );
	virtual bool next( );
	virtual bool isRun( ) const;
	virtual bool run( );
	virtual bool getRunNodeItem( NodeItemInfo * &result_current_run_info );
Q_SIGNALS:
	void releaseThisSignal( NodeItemBuilderLink *release_ptr );
	void start( NodeItemBuilderLink *node_item_builder_link );
	void finish( NodeItemBuilderLink *node_item_builder_link );
	void startNodeItem( NodeItemInfo *node_item_info );
	void finishNodeItem( NodeItemInfo *node_item_info );
	void requestInputPortConver( const NodePort *target_input_port, NodePort * &source_output_port );
};

#endif // NODEITEMBUILDERLINK_H_H_HEAD__FILE__
