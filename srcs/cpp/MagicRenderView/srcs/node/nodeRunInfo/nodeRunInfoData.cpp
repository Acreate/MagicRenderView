#include "nodeRunInfoData.h"

#include "../../enums/nodeEnum.h"

#include "../node/node.h"

NodeRunInfoData::NodeRunInfoData( ) : QObject( ), builderDataTime( nullptr ), brforeRunDataTime( nullptr ), currentRunDataTime( nullptr ), oldNode( nullptr ), currentNode( nullptr ) {
}
NodeRunInfoData::~NodeRunInfoData( ) {
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
	builderDataTime = copy_target_ptr->builderDataTime;
	brforeRunDataTime = copy_target_ptr->brforeRunDataTime;
	currentRunDataTime = copy_target_ptr->currentRunDataTime;
	buffNode = copy_target_ptr->buffNode;
	currentNode = copy_target_ptr->currentNode;
	oldNode = copy_target_ptr->oldNode;
	builderNodeVector = copy_target_ptr->builderNodeVector;
	builderBeginList = copy_target_ptr->builderBeginList;
	builderReferenceSortVector = copy_target_ptr->builderReferenceSortVector;
	runOverNodeVector = copy_target_ptr->runOverNodeVector;
	return true;
}
