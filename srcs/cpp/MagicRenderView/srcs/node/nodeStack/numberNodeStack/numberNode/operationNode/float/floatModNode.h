#ifndef FLOATMODNODE_H_H_HEAD__FILE__
#define FLOATMODNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class FloatOutputPort;
class FloatInputPort;
class FloatModNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	FloatModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // FLOATMODNODE_H_H_HEAD__FILE__
