#include "testDirector.h"

#include <app/application.h>
#include <srack/srackInfo.h>

#include "menuDirector.h"
#include "nodeDirector.h"
#include "printerDirector.h"
bool TestDirector::testAllNodeCreate( ) {
	std::vector< NormalGenerateNodeMenuType::TCreateUintyType > resultNodeCreateVector;
	Application *instancePtr = Application::getInstancePtr( );
	auto printerDirector = instancePtr->getPrinterDirector( );
	NodeDirector *nodeDirector = instancePtr->getNodeDirector( );
	if( nodeDirector->getCreateNodeVector( resultNodeCreateVector ) == false ) {
		printerDirector->info( tr( "获取节点创建序列失败" ), Create_SrackInfo( ) );
		return false;
	}
	size_t count = resultNodeCreateVector.size( );
	auto data = resultNodeCreateVector.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		Node *node = nodeDirector->createNode( data[ index ].second.first );
		if( node == nullptr ) {
			printerDirector->info( tr( "获取节点[%1]创建失败" ).arg( data[ index ].second.first ), Create_SrackInfo( ) );
			return false;
		}
		printerDirector->info( tr( "节点[%1]创建失成功(数量:%2)" ).arg( data[ index ].second.first ).arg( index + 1 ), Create_SrackInfo( ) );
	}

	return true;
}
