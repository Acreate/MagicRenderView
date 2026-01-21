#ifndef CHARCREATEARRAYNODE_H_H_HEAD__FILE__
#define CHARCREATEARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class CharVectorOutputPort;
class CharCreateArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QChar;
protected:
	CharVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	CharCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // CHARCREATEARRAYNODE_H_H_HEAD__FILE__
