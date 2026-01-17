#include "systemNodeStack.h"

#include "systemNodes/path/appConfigPathInfoNode.h"
#include "systemNodes/path/appDataPathInfoNode.h"
#include "systemNodes/path/applicationsPathInfoNode.h"
#include "systemNodes/path/appLocalDataPathInfoNode.h"
#include "systemNodes/path/cachePathInfoNode.h"
#include "systemNodes/path/configPathInfoNode.h"
#include "systemNodes/path/desktopPathInfoNode.h"
#include "systemNodes/path/documentsPathInfoNode.h"
#include "systemNodes/path/downloadPathInfoNode.h"
#include "systemNodes/path/fontsPathInfoNode.h"
#include "systemNodes/path/genericCachePathInfoNode.h"
#include "systemNodes/path/genericConfigPathInfoNode.h"
#include "systemNodes/path/genericDataPathInfoNode.h"
#include "systemNodes/path/genericStatePathInfoNode.h"
#include "systemNodes/path/homePathInfoNode.h"
#include "systemNodes/path/moviesPathInfoNode.h"
#include "systemNodes/path/musicPathInfoNode.h"
#include "systemNodes/path/picturesPathInfoNode.h"
#include "systemNodes/path/publicSharePathInfoNode.h"
#include "systemNodes/path/runtimePathInfoNode.h"
#include "systemNodes/path/statePathInfoNode.h"
#include "systemNodes/path/systemSepInfoNode.h"
#include "systemNodes/path/templatesPathInfoNode.h"
#include "systemNodes/path/tempPathInfoNode.h"

bool SystemNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "系统节点" );
	setObjectName( name );
	Def_EmaplaceBackNode( AppConfigPathInfoNode );
	Def_EmaplaceBackNode( AppDataPathInfoNode );
	Def_EmaplaceBackNode( ApplicationsPathInfoNode );
	Def_EmaplaceBackNode( AppLocalDataPathInfoNode );
	Def_EmaplaceBackNode( CachePathInfoNode );
	Def_EmaplaceBackNode( ConfigPathInfoNode );
	Def_EmaplaceBackNode( DesktopPathInfoNode );
	Def_EmaplaceBackNode( DocumentsPathInfoNode );
	Def_EmaplaceBackNode( DownloadPathInfoNode );
	Def_EmaplaceBackNode( FontsPathInfoNode );
	Def_EmaplaceBackNode( GenericCachePathInfoNode );
	Def_EmaplaceBackNode( GenericConfigPathInfoNode );
	Def_EmaplaceBackNode( GenericDataPathInfoNode );
	Def_EmaplaceBackNode( GenericStatePathInfoNode );
	Def_EmaplaceBackNode( HomePathInfoNode );
	Def_EmaplaceBackNode( MoviesPathInfoNode );
	Def_EmaplaceBackNode( MusicPathInfoNode );
	Def_EmaplaceBackNode( PicturesPathInfoNode );
	Def_EmaplaceBackNode( PublicSharePathInfoNode );
	Def_EmaplaceBackNode( RuntimePathInfoNode );
	Def_EmaplaceBackNode( StatePathInfoNode );
	Def_EmaplaceBackNode( SystemSepInfoNode );
	Def_EmaplaceBackNode( TemplatesPathInfoNode );
	Def_EmaplaceBackNode( TempPathInfoNode );

	return true;
}

SystemNodeStack::SystemNodeStack( QObject *parent ) : NodeStack( parent ) {

}
