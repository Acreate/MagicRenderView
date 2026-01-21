#ifndef COLORADDTOARRAYNODE_H_H_HEAD__FILE__
#define COLORADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ColorVectorInputPort;
class ColorVectorOutputPort;
class ColorInputPort;
class ColorAddToArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorInputPort *firstInputPort;
	ColorInputPort *secondInputPort;
	ColorVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ColorAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // COLORADDTOARRAYNODE_H_H_HEAD__FILE__
