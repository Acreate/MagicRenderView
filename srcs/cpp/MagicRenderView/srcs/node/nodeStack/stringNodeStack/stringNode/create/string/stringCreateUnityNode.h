#ifndef STRINGCREATEUNITYNODE_H_H_HEAD__FILE__
#define STRINGCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringCreateUnityNodeEditorWidget;
class StringOutputPort;
class StringCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringOutputPort *outputPort;
	NodeType *outputVarPtr;
	StringCreateUnityNodeEditorWidget *editorWidget;
protected:
	bool initNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	NodeInfoWidget * getNodeEditorWidget( ) override;
public:
	StringCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};


#endif // STRINGCREATEUNITYNODE_H_H_HEAD__FILE__
