#include "nodeStyleTypePen.h"

#include <QPainter>

#include "../../enums/nodeEnum.h"
NodeStyleTypePen::NodeStyleTypePen( ) {
	setPenInfo( nonePen, Qt::GlobalColor::black, 4 );
	setPenInfo( createPen, 0x009cff, 4 );
	
	setPenInfo( currentRunPen, 0x008B8B, 4 );
	setPenInfo( oldRunPen, 0x2E8B57, 4 );
	
	setPenInfo( selectActivePen, 0xff8400, 4 );
	setPenInfo( selectOldPen, 0xd191ff, 4 );
	setPenInfo( selectOutputRefPen, 0xaaffa3, 4 );
	setPenInfo( selectInputRefPen, 0x12ff11, 4 );
	
	setPenInfo( warningPen, 0xff7559, 4 );
	setPenInfo( errorPen, 0xff0000, 4 );
	setPenInfo( advisPen, 0xff9c65, 4 );
}
void NodeStyleTypePen::renderPainter( QPainter &painter, const NodeEnum::NodeStatusType &node_render_style, const qint64 &node_width, const qint64 &node_height ) {
	int doubleWidth;
	int penWidth;

	switch( node_render_style ) {
		case NodeEnum::NodeStatusType::None :
			painter.setPen( nonePen );
			penWidth = nonePen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStatusType::Current_Run :
			painter.setPen( currentRunPen );
			penWidth = currentRunPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStatusType::Create :
			painter.setPen( createPen );
			penWidth = createPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStatusType::Warning :
			painter.setPen( warningPen );
			penWidth = warningPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStatusType::Error :
			painter.setPen( errorPen );
			penWidth = errorPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStatusType::Advise :
			painter.setPen( advisPen );
			penWidth = advisPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
	}
}
