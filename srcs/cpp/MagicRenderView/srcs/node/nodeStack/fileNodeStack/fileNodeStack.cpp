#include "fileNodeStack.h"

#include "fileNodes/info/fileAbsoluteDirPathNode.h"
#include "fileNodes/info/fileAbsoluteNamePathNode.h"
#include "fileNodes/info/fileAuthorNameNode.h"
#include "fileNodes/info/fileBaseNameNode.h"
#include "fileNodes/info/fileCreateTimeNode.h"
#include "fileNodes/info/fileDirNameNode.h"
#include "fileNodes/info/fileIsFileNode.h"
#include "fileNodes/info/fileLastChangeTimeNode.h"
#include "fileNodes/info/fileLastReadTimeNode.h"
#include "fileNodes/info/fileOnlyIsReadNode.h"
#include "fileNodes/info/fileSizeNode.h"
#include "fileNodes/info/pathGetInPathInfoArrayNode.h"
#include "fileNodes/info/pathGetOnPathInfoArrayNode.h"
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
	Def_EmaplaceBackNode( PathGetOnPathInfoArrayNode );
	Def_EmaplaceBackNode( PathGetInPathInfoArrayNode );

	Def_EmaplaceBackNode( FileBaseNameNode );
	Def_EmaplaceBackNode( FileDirNameNode );
	Def_EmaplaceBackNode( FileAbsoluteNamePathNode );
	Def_EmaplaceBackNode( FileAbsoluteDirPathNode );
	Def_EmaplaceBackNode( FileCreateTimeNode );
	Def_EmaplaceBackNode( FileLastChangeTimeNode );
	Def_EmaplaceBackNode( FileLastReadTimeNode );
	Def_EmaplaceBackNode( FileAuthorNameNode );
	Def_EmaplaceBackNode( FileOnlyIsReadNode );
	Def_EmaplaceBackNode( FileIsFileNode );
	Def_EmaplaceBackNode( FileSizeNode );

	return true;
}

FileNodeStack::FileNodeStack( QObject *parent ) : NodeStack( parent ) {

}
