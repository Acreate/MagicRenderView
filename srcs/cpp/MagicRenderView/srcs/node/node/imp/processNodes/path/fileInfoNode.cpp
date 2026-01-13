#include "fileInfoNode.h"

#include <app/application.h>
#include <director/printerDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../director/varDirector.h"
#include "../../../../port/inputPort/unity/stringInputPort.h"
#include "../../../../port/outputPort/unity/dateTimeOutputPort.h"
#include "../../../../port/outputPort/unity/intOutputPort.h"
#include "../../../../port/outputPort/unity/uIntOutputPort.h"

FileInfoNode::FileInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	outFilePtahPtr = nullptr;
	outDirNamePtr = nullptr;
	outBaseNamePtr = nullptr;
	outAuthorNamePtr = nullptr;
	outCreateTimePtr = nullptr;
	outLastChangeTimePtr = nullptr;
	outFileSizePtr = nullptr;
	outIsReadPtr = nullptr;
}
bool FileInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "文件路径" ), filePtahInputPortPtr );
		Def_AappendBindVarOutputPortType( tr( "绝对路径" ), filePtahOutputPortPtr, outFilePtahPtr );
		Def_AappendBindVarOutputPortType( tr( "目录路径" ), dirNameOutputPortPtr, outDirNamePtr );
		Def_AappendBindVarOutputPortType( tr( "基本名称" ), baseNameOutputPortPtr, outBaseNamePtr );
		Def_AappendBindVarOutputPortType( tr( "作者" ), authorNameOutputPortPtr, outAuthorNamePtr );
		Def_AappendBindVarOutputPortType( tr( "创建时间" ), createTimeOutputPortPtr, outCreateTimePtr );
		Def_AappendBindVarOutputPortType( tr( "最后时间" ), lastChangeTimeOutputPortPtr, outLastChangeTimePtr );
		Def_AappendBindVarOutputPortType( tr( "大小" ), fileSizeOutputPortPtr, outFileSizePtr );
		Def_AappendBindVarOutputPortType( tr( "只读" ), isReadOutputPortPtr, outIsReadPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool FileInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool FileInfoNode::readyNodeRunData( ) {
	return true;
}
bool FileInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
