#ifndef GENERICDATAPATHINFONODE_H_H_HEAD__FILE__
#define GENERICDATAPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回一个目录位置，用于存储跨应用程序共享的持久数据。
/// 这是一个通用值。返回的路径永远不会为空。
class GenericDataPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	GenericDataPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // GENERICDATAPATHINFONODE_H_H_HEAD__FILE__
