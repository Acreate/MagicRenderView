#ifndef IMAGECREATEARRAYNODE_H_H_HEAD__FILE__
#define IMAGECREATEARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

#include "../../../../../node/createNode.h"
class ImageVectorOutputPort;
class ImageCreateArrayNode : public CreateNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ImageCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // IMAGECREATEARRAYNODE_H_H_HEAD__FILE__
