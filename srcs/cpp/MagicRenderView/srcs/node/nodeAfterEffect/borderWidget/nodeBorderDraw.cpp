#include "nodeBorderDraw.h"
#include <QPen>
#include <enums/nodeEnum.h>
#include <QPainter>

#include "nodeBorderAfterEffect.h"
NodeBorderDraw::StatusTypePen::StatusTypePen( ) {
	this->errorPen = new QPen( Qt::GlobalColor::red, 4 );
	this->advisePen = new QPen( Qt::GlobalColor::green, 2, Qt::DashLine );
	this->currentRunPen = new QPen( Qt::GlobalColor::yellow, 4 );
	this->nonePen = new QPen( Qt::GlobalColor::black, 1 );
	this->warningPen = new QPen( Qt::GlobalColor::blue, 4, Qt::DashLine );
	this->createPen = new QPen( Qt::GlobalColor::black, 4 );
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
	this->nonePen = new QPen( QColor( 0, 0, 0, 0 ), 0 );
	this->selectActivePen = new QPen( QColor( 0xd8b85b ), 4 );
	this->selectOldPen = new QPen( QColor( 0x55461d ), 4 );
	this->selectOutputRefPen = new QPen( QColor( 0xb649d4 ), 4 );
	this->selectInputRefPen = new QPen( QColor( 0x15c524 ), 4 );
}
NodeBorderDraw::SelectTypePen::~SelectTypePen( ) {
	delete this->nonePen;
	delete this->selectActivePen;
	delete this->selectOldPen;
	delete this->selectOutputRefPen;
	delete this->selectInputRefPen;
}
void NodeBorderDraw::drawRectBorder( QPainter *painter_ptr, QPen *pen_ptr, const QPoint &start_point_ref, const QSize &end_size_ref ) {
	int width = pen_ptr->width( );
	int startX = width + start_point_ref.x( );
	int startY = width + start_point_ref.y( );
	width = width + width;
	int endX = end_size_ref.width( ) - width;
	int endY = end_size_ref.height( ) - width;
	painter_ptr->setPen( *pen_ptr );
	painter_ptr->drawRect( startX, startY, endX, endY );
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
	switch( nodeSelctType ) {
		case NodeEnum::NodeSelctType::Select_Active :
			drawRectBorder( &painter, selectTypePen->getSelectActivePen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		case NodeEnum::NodeSelctType::Select_Old :
			drawRectBorder( &painter, selectTypePen->getSelectOldPen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		case NodeEnum::NodeSelctType::Select_Output_Ref :
			drawRectBorder( &painter, selectTypePen->getSelectOutputRefPen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		case NodeEnum::NodeSelctType::Select_Input_Ref :
			drawRectBorder( &painter, selectTypePen->getSelectInputRefPen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		// 不处理
		case NodeEnum::NodeSelctType::None :
		default :
			drawRectBorder( &painter, selectTypePen->getNonePen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			return true;
	}
	// 未处理
	return false;
}
bool NodeBorderDraw::drawStatusType( ) {
	if( nodeBorderAfterEffect == nullptr )
		return false;
	QPainter painter( nodeBorderAfterEffect );
	auto nodeStatusType = nodeBorderAfterEffect->getNodeStatusType( );
	switch( nodeStatusType ) {
		case NodeEnum::NodeStatusType::Create :
			drawRectBorder( &painter, statusTypePen->getCreatePen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		case NodeEnum::NodeStatusType::Current_Run :
			drawRectBorder( &painter, statusTypePen->getCurrentRunPen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		case NodeEnum::NodeStatusType::Warning :
			drawRectBorder( &painter, statusTypePen->getWarningPen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		case NodeEnum::NodeStatusType::Error :
			drawRectBorder( &painter, statusTypePen->getErrorPen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		case NodeEnum::NodeStatusType::Advise :
			drawRectBorder( &painter, statusTypePen->getAdvisePen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			break;
		// 不处理
		case NodeEnum::NodeStatusType::None :
		default :
			drawRectBorder( &painter, statusTypePen->getNonePen( ), QPoint( 0, 0 ), nodeBorderAfterEffect->size( ) );
			return true;
	}
	// 未处理
	return false;
}
