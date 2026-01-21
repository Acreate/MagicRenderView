#ifndef HOMEPATHINFONODE_H_H_HEAD__FILE__
#define HOMEPATHINFONODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>



class StringOutputPort;
/// @brief 返回用户的主目录（与QDir:homePath()相同）。
/// 在Unix系统中，这与HOME环境变量的值相同。
/// 此值可能是通用的，也可能是特定于应用程序的，但返回的路径永远不会为空
class HomePathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	HomePathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function(  );
};
#endif // HOMEPATHINFONODE_H_H_HEAD__FILE__
