#include "normalGenerateNodeMenu.h"

#include "../../node/stack/baseNodeStack/baseNodeStack.h"
#include "../../node/stack/contrlNodeStack/contrlNodeStack.h"
#include "../../node/stack/dateTimeNodeStack/dateTimeNodeStack.h"
#include "../../node/stack/fileNodeStack/fileNodeStack.h"
#include "../../node/stack/imageNodeStack/imageNodeStack.h"
#include "../../node/stack/stringNodeStack/stringNodeStack.h"
#include "../../node/stack/systemNodeStack/systemNodeStack.h"
#include "../../tools/path.h"

void NormalGenerateNodeMenu::releaseObjResource( ) {

	if( createCount != 0 ) {
		createIndex = 0;
		for( ; createIndex < createCount; ++createIndex )
			delete createArrayPtr[ createIndex ].first;
		createVector.clear( );
		createCount = 0;
		createArrayPtr = nullptr;
	}
}
void NormalGenerateNodeMenu::actionSlots( QAction *action ) {
	if( createCount == 0 )
		return;
	for( createIndex = 0; createIndex < createCount; ++createIndex )
		if( action == createArrayPtr[ createIndex ].first ) {
			emit create_node_signal( this, createArrayPtr[ createIndex ].first, createArrayPtr[ createIndex ].second.first, createArrayPtr[ createIndex ].second.second );
			break;
		}
}
NormalGenerateNodeMenu::NormalGenerateNodeMenu( ) : QMenu( ) {
	createCount = 0;
	createArrayPtr = nullptr;
	connect( this, &QMenu::triggered, this, &NormalGenerateNodeMenu::actionSlots );
}
bool NormalGenerateNodeMenu::initNormalGenerateNodeMenu( ) {
	releaseObjResource( );
	// 这里加入节点窗口创建函数
	appendCreateSubMenuAtNodeStack< BaseNodeStack >( );
	appendCreateSubMenuAtNodeStack< ContrlNodeStack >( );
	appendCreateSubMenuAtNodeStack< DateTimeNodeStack >( );
	appendCreateSubMenuAtNodeStack< FileNodeStack >( );
	appendCreateSubMenuAtNodeStack< ImageNodeStack >( );
	appendCreateSubMenuAtNodeStack< StringNodeStack >( );
	appendCreateSubMenuAtNodeStack< SystemNodeStack >( );
	createCount = createVector.size( );
	createArrayPtr = createVector.data( );
	return createCount != 0;
}
Node * NormalGenerateNodeMenu::getCreateResultNode( const QString &node_name ) {
	if( createCount == 0 )
		return nullptr;
	for( createIndex = 0; createIndex < createCount; ++createIndex )
		if( createArrayPtr[ createIndex ].second.first == node_name ) {

			return createArrayPtr[ createIndex ].second.second( node_name );
		}
	return nullptr;
}
NormalGenerateNodeMenu::~NormalGenerateNodeMenu( ) {
	emit release_menu_signal( this );
	releaseObjResource( );
}
void NormalGenerateNodeMenu::createNode( const QString &node_name ) {
	if( createCount == 0 )
		return;
	for( createIndex = 0; createIndex < createCount; ++createIndex )
		if( createArrayPtr[ createIndex ].second.first == node_name ) {
			emit create_node_signal( this, createArrayPtr[ createIndex ].first, createArrayPtr[ createIndex ].second.first, createArrayPtr[ createIndex ].second.second );
			return;
		}
	return;
}

QMenu * NormalGenerateNodeMenu::formNodeStack( NodeStack *create_node_stack ) {
	QMenu *nodeGenerateCreateMenu = nullptr;
	if( create_node_stack == nullptr || create_node_stack->init( ) == false )
		return nodeGenerateCreateMenu;
	nodeGenerateCreateMenu = fromNodeGenerateCreateMenu( create_node_stack );
	if( nodeGenerateCreateMenu )
		addMenu( nodeGenerateCreateMenu );
	return nodeGenerateCreateMenu;
}
void NormalGenerateNodeMenu::appendCareateItem( QAction *create_node_item, const QString &create_node_name, const NormalGenerateNodeMenuType::TCreateNodeFunction &create_node_function ) {
	NormalGenerateNodeMenuType::TCreateUintyType unity = std::pair( create_node_item, NormalGenerateNodeMenuType::TCreateNodeInfo( create_node_name, create_node_function ) );
	createVector.emplace_back( unity );
}

QMenu * NormalGenerateNodeMenu::fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr ) {
	auto nodeStackName = node_stack_ptr->objectName( );
	size_t count = node_stack_ptr->nodeGenerate.size( );
	auto data = node_stack_ptr->nodeGenerate.data( );
	size_t index = 0;
	path::pathTree pathTree( nodeStackName );
	for( ; index < count; ++index )
		pathTree.appSubPath( data[ index ].first );
	if( pathTree.getSubPath( ).size( ) == 0 )
		return nullptr;
	nodeStackName = pathTree.getName( );
	QMenu *resultMenu = new QMenu( nodeStackName );
	if( fromPathTreeGenerateCreateaAction( nodeStackName + "/", &pathTree, resultMenu, data, count ) == true )
		return resultMenu;
	delete resultMenu;
	return nullptr;
}
bool NormalGenerateNodeMenu::fromPathTreeGenerateCreateaAction( const QString &top_name, path::pathTree *path_tree, QMenu *parent_menu, std::pair< QString, std::function< Node *( const QString & ) > > *node_create_stack_array_ptr, const size_t &node_create_stack_array_count ) {
	auto pathTreeSubPath = path_tree->getSubPath( );
	size_t subPathCount = pathTreeSubPath.size( );
	if( subPathCount == 0 )
		return false;

	auto pathTreeSubPathTree = pathTreeSubPath.data( );
	size_t subPathIndex = 0;
	QString name;
	size_t index;
	QString absolutePathName;
	std::list< path::pathTree * > subPathTree;
	for( ; subPathIndex < subPathCount; ++subPathIndex )
		if( pathTreeSubPathTree[ subPathIndex ]->getSubPath( ).size( ) == 0 ) {
			name = pathTreeSubPathTree[ subPathIndex ]->getName( );
			pathTreeSubPathTree[ subPathIndex ]->getAbsolutePath( absolutePathName );
			if( absolutePathName.startsWith( top_name ) == false )
				return false;
			absolutePathName = absolutePathName.mid( top_name.length( ) );
			for( index = 0; index < node_create_stack_array_count; ++index )
				if( node_create_stack_array_ptr[ index ].first == absolutePathName )
					break;
			if( index == node_create_stack_array_count )
				return false;
			appendCareateItem( parent_menu->addAction( name ), absolutePathName, node_create_stack_array_ptr[ index ].second );
		} else
			subPathTree.emplace_back( pathTreeSubPathTree[ subPathIndex ] );
	for( auto &forreachPathTree : subPathTree ) {
		name = forreachPathTree->getName( );
		auto topMenu = parent_menu->addMenu( name );
		if( fromPathTreeGenerateCreateaAction( top_name, forreachPathTree, topMenu, node_create_stack_array_ptr, node_create_stack_array_count ) == false )
			return false;
	}
	return true;
}
