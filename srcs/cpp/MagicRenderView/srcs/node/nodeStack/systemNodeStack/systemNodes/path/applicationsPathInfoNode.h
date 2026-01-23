#ifndef APPLICATIONSPATHINFONODE_H_H_HEAD__FILE__
#define APPLICATIONSPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回包含用户应用程序（包括可执行文件、应用程序包或指向它们的快捷方式）的目录。
/// 这是一个通用值。
/// 请注意，安装应用程序可能需要额外的、针对特定平台的操作。
/// 此目录中的文件、文件夹或快捷方式是特定于平台的。
class ApplicationsPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	ApplicationsPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // APPLICATIONSPATHINFONODE_H_H_HEAD__FILE__
