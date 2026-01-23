#ifndef IMAGEINFONODE_H_H_HEAD__FILE__
#define IMAGEINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
class UIntOutputPort;
class ImageInputPort;
class ImageInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	ImageInputPort *imageInputPortPtr;
	UIntOutputPort *widthOutputPortPtr;
	UIntOutputPort *heightOutputPortPtr;
	StringOutputPort *fromatOutputPortPtr;
	uint64_t *width;
	uint64_t *height;
	QString *fromat;
public:
	ImageInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // IMAGEINFONODE_H_H_HEAD__FILE__
