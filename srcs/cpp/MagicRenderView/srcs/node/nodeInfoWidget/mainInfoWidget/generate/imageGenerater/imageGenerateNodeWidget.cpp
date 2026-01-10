#include "imageGenerateNodeWidget.h"

#include <enums/nodeEnum.h>
#include <node/node/node.h>

#include "../../../../node/imp/generateNodes/imageGenerateNode.h"
#include "imageGenerateNodeEditor.h"

ImageGenerateNodeWidget::ImageGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = charGenerateNodeEditor = new ImageGenerateNodeEditor( this );
	//setMinimumSize( 100, 200 );
}
bool ImageGenerateNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	ImageGenerateNode *charGenerateNodePtr = qobject_cast< ImageGenerateNode * >( check_node_ptr );
	if( charGenerateNodePtr == nullptr )
		return false;
	return true;
}
bool ImageGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	ImageGenerateNode *charGenerateNodePtr = qobject_cast< ImageGenerateNode * >( check_node_ptr );
	if( charGenerateNodePtr == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	charGenerateNodeEditor->setBindGenerateVector( charGenerateNodePtr->getGenerateVarPtr( ) );
	if( charGenerateNodeEditor->updateGenerateItemInfo( ) == false )
		return false;
	return true;
}
void ImageGenerateNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
void ImageGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void ImageGenerateNodeWidget::okButtonEvent( ) {
	charGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
