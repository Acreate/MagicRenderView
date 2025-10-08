#include "./readFile.h"

#include "../../../widgets/nodeItemInfoScrollAreaWidget.h"

#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../prot/outputProt/impOutputPort/bin/binOutputPort.h"
#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( ReadFile, QObject::tr( "ReadFile" ), QObject::tr( "disk" ) );
ReadFile::ReadFile( ) : NodeItem( ) {

}
bool ReadFile::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< StringInputPort >( "文件路径" );
			// 初始化输出端口
			addOutputProt< BinOutputPort >( "二进制" );
			return true;
		} );
}
