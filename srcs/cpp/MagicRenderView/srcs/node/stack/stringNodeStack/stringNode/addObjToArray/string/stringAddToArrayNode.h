#ifndef STRINGADDTOARRAYNODE_H_H_HEAD__FILE__
#define STRINGADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringVectorInputPort;
class StringVectorOutputPort;
class StringInputPort;
class StringAddToArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringVectorInputPort *firstInputPort;
	StringInputPort *secondInputPort;
	StringVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	StringAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // STRINGADDTOARRAYNODE_H_H_HEAD__FILE__
