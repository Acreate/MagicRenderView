#ifndef DEBUGINFONODE_H_H_HEAD__FILE__
#define DEBUGINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class DebugNodeInfoWidget;
class AnyVarInputPort;
class DebugInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *inputBugPort;
	DebugNodeInfoWidget *debugNodeInfoWidget;
public:
	DebugInfoNode( const QString &node_name )
		: ProcessNode( node_name ) { debugNodeInfoWidget = nullptr; }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
protected:
	void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	NodeInfoWidget * getNodeEditorWidget( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "输出/值" ) );
};
#endif // DEBUGINFONODE_H_H_HEAD__FILE__
