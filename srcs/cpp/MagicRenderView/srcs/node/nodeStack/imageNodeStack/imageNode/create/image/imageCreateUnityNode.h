#ifndef IMAGECREATEUNITYNODE_H_H_HEAD__FILE__
#define IMAGECREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ImageCreateUnityNodeEditorWidget;
class ImageOutputPort;
class ImageCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageOutputPort *outputPort;
	NodeType *outputVarPtr;
	ImageCreateUnityNodeEditorWidget *editorWidget;
public:
	ImageCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
protected:
	NodeInfoWidget * getNodeInfoWidget( ) override;
	bool initNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // IMAGECREATEUNITYNODE_H_H_HEAD__FILE__
