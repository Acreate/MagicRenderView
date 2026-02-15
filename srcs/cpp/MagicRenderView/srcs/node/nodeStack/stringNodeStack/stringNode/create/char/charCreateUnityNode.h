#ifndef CHARCREATEUNITYNODE_H_H_HEAD__FILE__
#define CHARCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

#include "../../../../../node/createNode.h"
class CharCreateUnityNodeEditorWidget;
class CharOutputPort;
class CharCreateUnityNode : public CreateNode {
	Q_OBJECT;
private:
	using NodeType = QChar;
protected:
	CharOutputPort *outputPort;
	NodeType *outputVarPtr;
	CharCreateUnityNodeEditorWidget *editorWidget;
protected:
	bool initNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	NodeInfoWidget * getNodeInfoWidget( ) override;
public:
	CharCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // CHARCREATEUNITYNODE_H_H_HEAD__FILE__
