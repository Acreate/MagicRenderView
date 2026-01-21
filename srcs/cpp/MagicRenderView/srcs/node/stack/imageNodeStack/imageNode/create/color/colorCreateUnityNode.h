#ifndef COLORCREATEUNITYNODE_H_H_HEAD__FILE__
#define COLORCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ColorOutputPort;
class ColorCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ColorCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // COLORCREATEUNITYNODE_H_H_HEAD__FILE__
