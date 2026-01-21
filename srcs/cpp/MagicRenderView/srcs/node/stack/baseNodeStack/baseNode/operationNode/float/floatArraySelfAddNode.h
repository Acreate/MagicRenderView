#ifndef FLOATARRAYSELFADDNODE_H_H_HEAD__FILE__
#define FLOATARRAYSELFADDNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class FloatOutputPort;
class FloatVectorInputPort;
class FloatArraySelfAddNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatVectorInputPort *firstInputPort;
	FloatOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	FloatArraySelfAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // FLOATARRAYSELFADDNODE_H_H_HEAD__FILE__
