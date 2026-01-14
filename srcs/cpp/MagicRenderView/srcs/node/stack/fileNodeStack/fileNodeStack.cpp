#include "fileNodeStack.h"

#include "fileNodes/info/fileInfoNode.h"
#include "fileNodes/read/readFileBinDataNode.h"
#include "fileNodes/read/readFileImageNode.h"
#include "fileNodes/read/readFileTextNode.h"
#include "fileNodes/write/writeFileBinDataNode.h"
#include "fileNodes/write/writeFileImageNode.h"
#include "fileNodes/write/writeFileTextNode.h"

bool FileNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "文件节点" );
	setObjectName( name );
	Def_EmaplaceBackNode( ReadFileBinDataNode );
	Def_EmaplaceBackNode( ReadFileImageNode );
	Def_EmaplaceBackNode( ReadFileTextNode );
	Def_EmaplaceBackNode( WriteFileBinDataNode );
	Def_EmaplaceBackNode( WriteFileImageNode );
	Def_EmaplaceBackNode( WriteFileTextNode );
	Def_EmaplaceBackNode( FileInfoNode );
	return true;
}

FileNodeStack::FileNodeStack( QObject *parent ) : NodeStack( parent ) {

}
