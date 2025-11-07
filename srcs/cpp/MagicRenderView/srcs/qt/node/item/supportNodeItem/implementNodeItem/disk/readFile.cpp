#include "./readFile.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/bin/binOutputPort.h"

Imp_StaticMetaInfo( ReadFile, QObject::tr( "读文件" ), QObject::tr( "磁盘" ) );
ReadFile::ReadFile( ) {

}
bool ReadFile::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< StringInputPort >( "文件路径", false );
			// 初始化输出端口
			addOutputProt< BinOutputPort >( "二进制" );
			return true;
		} );
}
