#ifndef NODEITEMBUILDERLINK_H_H_HEAD__FILE__
#define NODEITEMBUILDERLINK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

class NodePortLinkInfo;
class NodeItemInfo;
class NodeItemBuilderLink : public QObject {
	Q_OBJECT;
	friend class NodeDirector;
	friend class Application;
protected:
	std_vector< NodeItemInfo * > nodeItemInfos;
	std_vector< NodePortLinkInfo * > nodePortLinkInfos;
protected:
	NodeItemBuilderLink( ) { }
public:
	~NodeItemBuilderLink( ) override;
	virtual bool appendNodeItemInfo( NodeItemInfo *append_nodeite_info );
	virtual bool appendNodePortLinkInfo( NodePortLinkInfo *append_node_port_link_info );
	virtual bool appendNodeItemInfoVector( const std_vector< NodeItemInfo * > &append_nodeite_info );
	virtual bool appendNodePortLinkInfoVector( const std_vector< NodePortLinkInfo * > &append_node_port_link_info );
	virtual bool removeNodeItemInfo( NodeItemInfo *remove_nodeite_info );
	virtual bool removeNodePortLinkInfo( NodePortLinkInfo *remove_node_port_link_info );
	virtual bool removeNodeItemInfoVector( const std_vector< NodeItemInfo * > &remove_nodeite_info );
	virtual bool removeNodePortLinkInfoVector( const std_vector< NodePortLinkInfo * > &remove_node_port_link_info );
	virtual void clearNodeItemInfoVector( );
	virtual void clearNodePortLinkInfoVector( );
	virtual void clear( );
	virtual bool generateBuilderInfo( );
	virtual bool next( );
	virtual bool isRun( ) const;
	virtual bool run( );
	virtual bool getRunNodeItems( std_vector< NodeItemInfo * > &result_current_run_info_vector );
Q_SIGNALS:
	void releaseThisSignal( NodeItemBuilderLink *release_ptr );
	void appendNodeItemInfoSignal( NodeItemInfo *append_node_item_ptr );
	void appendNodePortLinkInfoSignal( NodePortLinkInfo *append_node_port_ptr );
	void removeNodeItemInfoSignal( NodeItemInfo *remove_node_item_ptr );
	void removeNodePortLinkInfoSignal( NodePortLinkInfo *remove_node_port_ptr );
};

#endif // NODEITEMBUILDERLINK_H_H_HEAD__FILE__
