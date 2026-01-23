#ifndef IMAGEARRAYMULNODE_H_H_HEAD__FILE__
#define IMAGEARRAYMULNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ImageVectorInputPort;
class ImageInputPort;
class ImageVectorOutputPort;
class ImageArrayMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageVectorInputPort *firstInputPort;
	ImageInputPort *secondInputPort;
	ImageVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ImageArrayMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // IMAGEARRAYMULNODE_H_H_HEAD__FILE__
