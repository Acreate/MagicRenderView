#include "nodeRunInfoData.h"

#include "../../enums/nodeEnum.h"

#include "../node/node.h"
#include <QDateTime>

NodeRunInfoData::NodeRunInfoData( ) : QObject( ), builderDataTime( new QDateTime ), brforeRunDataTime( new QDateTime ), currentRunDataTime( new QDateTime ), oldNode( nullptr ), currentNode( nullptr ) {
}
NodeRunInfoData::~NodeRunInfoData( ) {
	delete builderDataTime;
	delete brforeRunDataTime;
	delete currentRunDataTime;
}

bool NodeRunInfoData::copyNodeRunInfoDataToThis( const NodeRunInfoData *const copy_target_ptr ) {
	if( copy_target_ptr == nullptr )
		return false;
	if( this == copy_target_ptr )
		return true;
	currentFrame = copy_target_ptr->currentFrame;
	maxFrame = copy_target_ptr->maxFrame;
	runStop = copy_target_ptr->runStop;
	ready = copy_target_ptr->ready;
	nextRunNodeTime = copy_target_ptr->nextRunNodeTime;
	*builderDataTime = *copy_target_ptr->builderDataTime;
	*brforeRunDataTime = *copy_target_ptr->brforeRunDataTime;
	*currentRunDataTime = *copy_target_ptr->currentRunDataTime;
	buffNode = copy_target_ptr->buffNode;
	currentNode = copy_target_ptr->currentNode;
	oldNode = copy_target_ptr->oldNode;
	builderNodeVector = copy_target_ptr->builderNodeVector;
	builderBeginVector = copy_target_ptr->builderBeginVector;
	runOverNodeVector = copy_target_ptr->runOverNodeVector;
	return true;
}
bool NodeRunInfoData::copyNodeRunInfoDataToThis( const NodeRunInfoData &copy_target_instance ) {
	return copyNodeRunInfoDataToThis( &copy_target_instance );
}
void NodeRunInfoData::clear( ) {
	ready = false;
	runStop = true;
	currentFrame = 0;
	buffNode = currentNode = oldNode = nullptr;
	builderNodeVector.clear( );
	builderBeginVector.clear( );
	runOverNodeVector.clear( );
	jumpNodeList.clear( );
	createNodeList.clear( );
	functionNodeList.clear( );
	awaitNodeList.clear( );
}
