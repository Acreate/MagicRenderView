#ifndef UINTCREATEUNITYNODE_H_H_HEAD__FILE__
#define UINTCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntCreateUnityNodeEditorWidget;
class UIntOutputPort;
class UIntCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntOutputPort *outputPort;
	NodeType *outputVarPtr;
	UIntCreateUnityNodeEditorWidget *editorWidget;
public:
	UIntCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
protected:
	bool initNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	NodeInfoWidget * getNodeEditorWidget( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // UINTCREATEUNITYNODE_H_H_HEAD__FILE__
