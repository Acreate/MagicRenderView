#ifndef MOVIESPATHINFONODE_H_H_HEAD__FILE__
#define MOVIESPATHINFONODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>


class StringOutputPort;
/// @brief 返回包含用户电影和视频的目录。
/// 这是一个通用值。
/// 如果不存在专门用于存储电影文件的目录，则会返回一个合理的备用方案，用于存储用户文档。
class MoviesPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	MoviesPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/用户电影和视频的目录" ) );
};
#endif // MOVIESPATHINFONODE_H_H_HEAD__FILE__
