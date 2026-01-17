#ifndef PUBLICSHAREPATHINFONODE_H_H_HEAD__FILE__
#define PUBLICSHAREPATHINFONODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>

class StringOutputPort;

/// @brief 返回一个目录位置，用户特定的公开共享文件和目录可以存储于此。
/// 这是一个通用值。
/// 请注意，如果系统没有公开共享位置的概念，返回的路径可能会为空。
class PublicSharePathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	PublicSharePathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/用户特定的公开共享目录" ) );
};
#endif // PUBLICSHAREPATHINFONODE_H_H_HEAD__FILE__
