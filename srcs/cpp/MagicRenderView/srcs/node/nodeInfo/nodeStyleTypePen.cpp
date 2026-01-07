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
void NodeStyleTypePen::renderPainter( QPainter &painter, const NodeEnum::NodeStyleType &node_render_style, const qint64 &node_width, const qint64 &node_height ) {
	int doubleWidth;
	int penWidth;

	switch( node_render_style ) {
		case NodeEnum::NodeStyleType::None :
			painter.setPen( nonePen );
			penWidth = nonePen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Current_Run :
			painter.setPen( currentRunPen );
			penWidth = currentRunPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Old_Run :
			painter.setPen( oldRunPen );
			penWidth = oldRunPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Create :
			painter.setPen( createPen );
			penWidth = createPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Select_Active :
			painter.setPen( selectActivePen );
			penWidth = selectActivePen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Select_Old :
			painter.setPen( selectOldPen );
			penWidth = selectOldPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Warning :
			painter.setPen( warningPen );
			penWidth = warningPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Error :
			painter.setPen( errorPen );
			penWidth = errorPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Advise :
			painter.setPen( advisPen );
			penWidth = advisPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Select_Output_Ref :
			painter.setPen( selectOutputRefPen );
			penWidth = selectOutputRefPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Select_Input_Ref :
			painter.setPen( selectInputRefPen );
			penWidth = selectInputRefPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, node_width - doubleWidth, node_height - doubleWidth );
			break;
	}
}
