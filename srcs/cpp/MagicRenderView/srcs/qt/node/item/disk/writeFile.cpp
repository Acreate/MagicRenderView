#include "./writeFile.h"

#include "../../prot/inputProt/inpInputPort/bin/binInputPort.h"
#include "../../prot/inputProt/inpInputPort/string/stringInputPort.h"

Imp_StaticMetaInfo( WriteFile, QObject::tr( "WriteFile" ), QObject::tr( "disk" ) );
WriteFile::WriteFile( ) : NodeItem( ) {
}
bool WriteFile::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< StringInputPort >( "文件路径" );
			addInputProt< BinInputPort >( "二进制" );
			return true;
		} );
}
