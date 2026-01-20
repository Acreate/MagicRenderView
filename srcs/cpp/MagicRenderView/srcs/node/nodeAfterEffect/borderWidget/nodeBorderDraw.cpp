#include "nodeBorderDraw.h"
#include <QPen>
#include <enums/nodeEnum.h>
#include <QPainter>

#include "nodeBorderAfterEffect.h"
NodeBorderDraw::StatusTypePen::StatusTypePen( ) {
	this->errorPen = new QPen( );
	errorPen->setColor( Qt::GlobalColor::red );
	errorPen->setWidth( 2 );

	this->advisePen = new QPen( );
	advisePen->setColor( Qt::GlobalColor::green );
	advisePen->setWidth( 4 );
	advisePen->setStyle( Qt::DashLine );

	this->currentRunPen = new QPen( );
	currentRunPen->setColor( Qt::GlobalColor::yellow );
	currentRunPen->setWidth( 4 );

	this->nonePen = new QPen( );
	nonePen->setColor( Qt::GlobalColor::black );
	nonePen->setWidth( 2 );

	this->warningPen = new QPen( );
	warningPen->setColor( Qt::GlobalColor::blue );
	warningPen->setWidth( 4 );
	warningPen->setStyle( Qt::DashLine );

	this->createPen = new QPen( );
	createPen->setColor( Qt::GlobalColor::black );
	createPen->setWidth( 4 );
}
NodeBorderDraw::StatusTypePen::~StatusTypePen( ) {
	delete this->errorPen;
	delete this->advisePen;
	delete this->currentRunPen;
	delete this->nonePen;
	delete this->warningPen;
	delete this->createPen;
}
NodeBorderDraw::SelectTypePen::SelectTypePen( ) {
	this->nonePen = new QPen( );
	nonePen->setColor( QColor( 0, 0, 0, 0 ) );
	nonePen->setWidth( 0 );

	this->selectActivePen = new QPen( );
	selectActivePen->setColor( QColor( 0xff9400 ) );
	selectActivePen->setWidth( 4 );

	this->selectOldPen = new QPen( );
	selectOldPen->setColor( QColor( 0x55461d ) );
	selectOldPen->setWidth( 4 );

	this->selectOutputRefPen = new QPen( );
	selectOutputRefPen->setColor( QColor( 0xb649d4 ) );
	selectOutputRefPen->setWidth( 4 );

	this->selectInputRefPen = new QPen( );
	selectInputRefPen->setColor( QColor( 0x15c524 ) );
	selectInputRefPen->setWidth( 4 );
}
NodeBorderDraw::SelectTypePen::~SelectTypePen( ) {
	delete this->nonePen;
	delete this->selectActivePen;
	delete this->selectOldPen;
	delete this->selectOutputRefPen;
	delete this->selectInputRefPen;
}

void NodeBorderDraw::drawRectBorder( QPainter *painter_ptr, QPen *pen_ptr, int x, int y, int width, int height ) {
	int penWidth = pen_ptr->width( );
	if( penWidth == 0 )
		return;
	x = penWidth + x;
	y = penWidth + y;
	penWidth = penWidth + penWidth;
	width = width - penWidth;
	height = height - penWidth;
	painter_ptr->setPen( *pen_ptr );
	painter_ptr->drawRect( x, y, width, height );
}
NodeBorderDraw::NodeBorderDraw( NodeBorderAfterEffect *node_border_after_effect ) : nodeBorderAfterEffect( node_border_after_effect ) {
	this->statusTypePen = new StatusTypePen;
	this->selectTypePen = new SelectTypePen;
}
NodeBorderDraw::~NodeBorderDraw( ) {
	delete this->statusTypePen;
	delete this->selectTypePen;
}
bool NodeBorderDraw::drawSelctType( ) {
	if( nodeBorderAfterEffect == nullptr )
		return false;
	QPainter painter( nodeBorderAfterEffect );
	auto nodeSelctType = nodeBorderAfterEffect->getNodeSelctType( );

	nodeBorderAfterEffectWidth = nodeBorderAfterEffect->width( );
	nodeBorderAfterEffectHeight = nodeBorderAfterEffect->height( );
	penPtr = nullptr;
	switch( nodeSelctType ) {
		case NodeEnum::NodeSelctType::Select_Active :
			penPtr = selectTypePen->getSelectActivePen( );
			break;
		case NodeEnum::NodeSelctType::Select_Old :
			penPtr = selectTypePen->getSelectOldPen( );
			break;
		case NodeEnum::NodeSelctType::Select_Output_Ref :
			penPtr = selectTypePen->getSelectOutputRefPen( );
			break;
		case NodeEnum::NodeSelctType::Select_Input_Ref :
			penPtr = selectTypePen->getSelectInputRefPen( );
			break;
		// 不处理
		case NodeEnum::NodeSelctType::None :
			penPtr = selectTypePen->getNonePen( );
		default :
			break;
	}
	if( penPtr == nullptr )
		return false; // 未处理
	drawRectBorder( &painter, penPtr, 0 + 4, 0 + 4, nodeBorderAfterEffectWidth - 8, nodeBorderAfterEffectHeight - 8 );
	return true;
}
bool NodeBorderDraw::drawStatusType( ) {
	if( nodeBorderAfterEffect == nullptr )
		return false;
	QPainter painter( nodeBorderAfterEffect );
	auto nodeStatusType = nodeBorderAfterEffect->getNodeStatusType( );
	nodeBorderAfterEffectWidth = nodeBorderAfterEffect->width( );
	nodeBorderAfterEffectHeight = nodeBorderAfterEffect->height( );
	penPtr = nullptr;
	switch( nodeStatusType ) {
		case NodeEnum::NodeStatusType::Create :
			penPtr = statusTypePen->getCreatePen( );
			break;
		case NodeEnum::NodeStatusType::Current_Run :
			penPtr = statusTypePen->getCurrentRunPen( );
			break;
		case NodeEnum::NodeStatusType::Warning :
			penPtr = statusTypePen->getWarningPen( );
			break;
		case NodeEnum::NodeStatusType::Error :
			penPtr = statusTypePen->getErrorPen( );
			break;
		case NodeEnum::NodeStatusType::Advise :
			penPtr = statusTypePen->getAdvisePen( );
			break;
		// 不处理
		case NodeEnum::NodeStatusType::None :
			penPtr = statusTypePen->getNonePen( );
		default :
			break;
	}
	if( penPtr == nullptr )
		return false; // 未处理
	drawRectBorder( &painter, penPtr, 0, 0, nodeBorderAfterEffectWidth, nodeBorderAfterEffectHeight );
	return true;
}
