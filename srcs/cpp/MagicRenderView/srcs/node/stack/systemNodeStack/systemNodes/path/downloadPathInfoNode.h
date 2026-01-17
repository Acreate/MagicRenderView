#ifndef DOWNLOADPATHINFONODE_H_H_HEAD__FILE__
#define DOWNLOADPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回用户下载文件的目录。
/// 这是一个通用值。
/// 如果不存在专门用于存储下载文件的目录，则会返回一个合理的备用方案，用于存储用户文档。
class DownloadPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	DownloadPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/用户下载文件目录" ) );
};
#endif // DOWNLOADPATHINFONODE_H_H_HEAD__FILE__
