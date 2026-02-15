#ifndef IMAGECREATEUNITYNODE_H_H_HEAD__FILE__
#define IMAGECREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

#include "../../../../../node/createNode.h"
class ImageCreateUnityNodeEditorWidget;
class ImageOutputPort;
class ImageCreateUnityNode : public CreateNode {
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
	bool formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) override;
	bool toUint8VectorData( std::vector<uint8_t> &result_vector_data ) override;
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // IMAGECREATEUNITYNODE_H_H_HEAD__FILE__
