#ifndef FLOATADDNODE_H_H_HEAD__FILE__
#define FLOATADDNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class FloatOutputPort;
class FloatInputPort;
class FloatAddNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	FloatAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // FLOATADDNODE_H_H_HEAD__FILE__
