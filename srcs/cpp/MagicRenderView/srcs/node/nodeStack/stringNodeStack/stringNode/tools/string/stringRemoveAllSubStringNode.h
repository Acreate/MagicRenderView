#ifndef STRINGREMOVEALLSUBSTRINGNODE_H_H_HEAD__FILE__
#define STRINGREMOVEALLSUBSTRINGNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringInputPort;
class StringOutputPort;
class StringRemoveAllSubStringNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringInputPort *orgStringInputPortPtr;
	StringInputPort *removeSubStringInputPortPtr;
	StringOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	StringRemoveAllSubStringNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // STRINGREMOVEALLSUBSTRINGNODE_H_H_HEAD__FILE__
