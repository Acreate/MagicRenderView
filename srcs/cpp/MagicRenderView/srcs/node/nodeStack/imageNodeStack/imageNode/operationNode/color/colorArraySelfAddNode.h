#ifndef COLORARRAYSELFADDNODE_H_H_HEAD__FILE__
#define COLORARRAYSELFADDNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ColorVectorInputPort;
class ColorOutputPort;
class ColorArraySelfAddNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorInputPort *firstInputPort;
	ColorOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ColorArraySelfAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // COLORARRAYSELFADDNODE_H_H_HEAD__FILE__
