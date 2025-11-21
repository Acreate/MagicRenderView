#include "./pathInfo.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/bin/binOutputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( PathInfo, QObject::tr( "路径" ), QObject::tr( "信息" ) );

PathInfo::PathInfo( ) {
}
bool PathInfo::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {

			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< StringInputPort >( "文件路径", false );
			// 初始化输出端口
			addOutputProt< StringOutputPort >( "全路径" );
			addOutputProt< StringOutputPort >( "目录" );
			addOutputProt< StringOutputPort >( "文件名" );
			addOutputProt< StringOutputPort >( "基本名" );
			addOutputProt< StringOutputPort >( "后缀名" );
			addOutputProt< StringOutputPort >( "拥有者" );
			addOutputProt< StringOutputPort >( "创建日期" );
			addOutputProt< StringOutputPort >( "最后修改日期" );
			addOutputProt< BinOutputPort >( "是否文件" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};

			return true;
		} );
}
