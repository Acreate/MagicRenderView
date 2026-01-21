#ifndef STRINGREPLACEALLSUBSTRINGNODE_H_H_HEAD__FILE__
#define STRINGREPLACEALLSUBSTRINGNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringInputPort;
class StringOutputPort;
class StringReplaceAllSubStringNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringInputPort *orgStringInputPortPtr;
	StringInputPort *replaceSourceSubStringInputPortPtr;
	StringInputPort *replaceTargetSubStringInputPortPtr;
	StringOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	StringReplaceAllSubStringNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // STRINGREPLACEALLSUBSTRINGNODE_H_H_HEAD__FILE__
