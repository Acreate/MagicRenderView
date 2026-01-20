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
	width = width - penWidth;
	height = height - penWidth;
	penWidth = penWidth / 2;
	x = penWidth + x;
	y = penWidth + y;
	painter_ptr->setPen( *pen_ptr );
	painter_ptr->drawRect( x, y, width, height );
}
NodeBorderDraw::NodeBorderDraw( NodeBorderAfterEffect *node_border_after_effect ) : nodeBorderAfterEffect( node_border_after_effect ) {
	this->statusTypePen = new StatusTypePen;
	this->selectTypePen = new SelectTypePen;
	statusPenPtr = nullptr;
	selectPenPtr = nullptr;
}
NodeBorderDraw::~NodeBorderDraw( ) {
	delete this->statusTypePen;
	delete this->selectTypePen;
}
void NodeBorderDraw::draw( ) {
	if( nodeBorderAfterEffect == nullptr )
		return;
	QPainter *painter;
	selectSelectTypePen( );
	selectStatusTypePen( );
	if( statusPenPtr == nullptr && selectPenPtr == nullptr )
		return;
	painter = new QPainter( nodeBorderAfterEffect );
	nodeBorderAfterEffectWidth = nodeBorderAfterEffect->width( );
	nodeBorderAfterEffectHeight = nodeBorderAfterEffect->height( );
	if( statusPenPtr != nullptr && selectPenPtr == nullptr ) {
		drawRectBorder( painter, statusPenPtr, 0, 0, nodeBorderAfterEffectWidth, nodeBorderAfterEffectHeight );
	} else if( statusPenPtr == nullptr && selectPenPtr != nullptr ) {
		drawRectBorder( painter, selectPenPtr, 0, 0, nodeBorderAfterEffectWidth, nodeBorderAfterEffectHeight );
	} else {
		int borderWidth;
		int doubleBorderWidth;
		borderWidth = statusPenPtr->width( );
		doubleBorderWidth = borderWidth + borderWidth;
		drawRectBorder( painter, statusPenPtr, 0, 0, nodeBorderAfterEffectWidth, nodeBorderAfterEffectHeight );
		drawRectBorder( painter, selectPenPtr, borderWidth, borderWidth, nodeBorderAfterEffectWidth - doubleBorderWidth, nodeBorderAfterEffectHeight - doubleBorderWidth );
	}
	delete painter;
}
bool NodeBorderDraw::selectSelectTypePen( ) {
	QPainter painter( nodeBorderAfterEffect );
	auto nodeSelctType = nodeBorderAfterEffect->getNodeSelctType( );
	switch( nodeSelctType ) {
		case NodeEnum::NodeSelctType::Select_Active :
			selectPenPtr = selectTypePen->getSelectActivePen( );
			break;
		case NodeEnum::NodeSelctType::Select_Old :
			selectPenPtr = selectTypePen->getSelectOldPen( );
			break;
		case NodeEnum::NodeSelctType::Select_Output_Ref :
			selectPenPtr = selectTypePen->getSelectOutputRefPen( );
			break;
		case NodeEnum::NodeSelctType::Select_Input_Ref :
			selectPenPtr = selectTypePen->getSelectInputRefPen( );
			break;
		case NodeEnum::NodeSelctType::None :
			selectPenPtr = selectTypePen->getNonePen( );
			break;
		default :
			selectPenPtr = nullptr;
			return false; // 未处理
	}
	return true;
}
bool NodeBorderDraw::selectStatusTypePen( ) {
	if( nodeBorderAfterEffect == nullptr )
		return false;
	QPainter painter( nodeBorderAfterEffect );
	auto nodeStatusType = nodeBorderAfterEffect->getNodeStatusType( );
	switch( nodeStatusType ) {
		case NodeEnum::NodeStatusType::Create :
			statusPenPtr = statusTypePen->getCreatePen( );
			break;
		case NodeEnum::NodeStatusType::Current_Run :
			statusPenPtr = statusTypePen->getCurrentRunPen( );
			break;
		case NodeEnum::NodeStatusType::Warning :
			statusPenPtr = statusTypePen->getWarningPen( );
			break;
		case NodeEnum::NodeStatusType::Error :
			statusPenPtr = statusTypePen->getErrorPen( );
			break;
		case NodeEnum::NodeStatusType::Advise :
			statusPenPtr = statusTypePen->getAdvisePen( );
			break;
		case NodeEnum::NodeStatusType::None :
			statusPenPtr = statusTypePen->getNonePen( );
			break;
		default :
			statusPenPtr = nullptr;
			return false; // 未处理
	}
	return true;
}
