#ifndef INTCREATEUNITYNODE_H_H_HEAD__FILE__
#define INTCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

#include "../../../../../node/createNode.h"
class IntCreateUnityNodeEditorWidget;
class IntOutputPort;
class IntCreateUnityNode : public CreateNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntOutputPort *outputPort;
	NodeType *outputVarPtr;
	IntCreateUnityNodeEditorWidget *editorWidget;
public:
	IntCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
protected:
	bool initNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	NodeInfoWidget * getNodeInfoWidget( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // INTCREATEUNITYNODE_H_H_HEAD__FILE__
