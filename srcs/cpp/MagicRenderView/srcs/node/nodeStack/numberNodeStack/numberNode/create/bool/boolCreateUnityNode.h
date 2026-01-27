#ifndef BOOLCREATEUNITYNODE_H_H_HEAD__FILE__
#define BOOLCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class BoolCreateUnityNodeEditorWidget;
class BoolOutputPort;
class BoolCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = bool;
protected:
	BoolOutputPort *outputPort;
	NodeType *outputVarPtr;
	BoolCreateUnityNodeEditorWidget* editorWidget;
public:
	BoolCreateUnityNode( const QString &node_name );
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
#endif // BOOLCREATEUNITYNODE_H_H_HEAD__FILE__
