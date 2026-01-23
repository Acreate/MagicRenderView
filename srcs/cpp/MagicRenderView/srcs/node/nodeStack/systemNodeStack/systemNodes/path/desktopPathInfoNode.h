#ifndef DESKTOPPATHINFONODE_H_H_HEAD__FILE__
#define DESKTOPPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回用户的桌面目录。
/// 这是一个通用值。
/// 在没有桌面概念的系统中，此值与QStandardPaths:HomeLocation相同。
class DesktopPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	DesktopPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // DESKTOPPATHINFONODE_H_H_HEAD__FILE__
