#ifndef DOCUMENTSPATHINFONODE_H_H_HEAD__FILE__
#define DOCUMENTSPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringOutputPort;
/// @brief 返回包含用户文档文件的目录。
/// 这是一个通用值。返回的路径永远不会为空。
class DocumentsPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	DocumentsPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // DOCUMENTSPATHINFONODE_H_H_HEAD__FILE__
