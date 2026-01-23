#ifndef BINCREATEUNITYNODE__H_H_HEAD__FILE__
#define BINCREATEUNITYNODE__H_H_HEAD__FILE__

#include <node/node/processNode.h>

class BinCreateUnityNodeEditorWidget;
class BinOutputPort;
class BinCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint8_t;
protected:
	BinOutputPort *outputPort;
	NodeType *outputVarPtr;
	BinCreateUnityNodeEditorWidget *editorWidget;
public:
	BinCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
protected:
	bool initNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	NodeInfoWidget * getNodeEditorWidget( ) override;
public:
	bool formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) override;
	bool toUint8VectorData( std::vector< uint8_t > &result_vector_data ) override;
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // BINCREATEUNITYNODE__H_H_HEAD__FILE__
