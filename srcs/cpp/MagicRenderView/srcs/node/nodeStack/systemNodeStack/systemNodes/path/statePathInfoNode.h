#ifndef STATEPATHINFONODE_H_H_HEAD__FILE__
#define STATEPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回一个目录位置，用于存放用户特定的应用程序状态数据文件。
/// 这是一个应用程序专用的目录，返回的路径永远不会为空。
class StatePathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	StatePathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // STATEPATHINFONODE_H_H_HEAD__FILE__
