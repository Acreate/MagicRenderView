#include "colorEditor.h"

#include <define/castMacro.h>
#include <qcoreevent.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <qpushbutton.h>
void ColorEditor::affirmBtenClick( ) {

}
void ColorEditor::cancelBtenClick( ) {
}
ColorEditor::ColorEditor( QWidget *parent ) : QWidget( parent ) {
	alphaScrollButton = new QLabel( tr( "透" ), this );
	affirmBtn = new QLabel( tr( "确定" ), this );
	cancelBen = new QLabel( tr( "取消" ), this );
	selectPoint = new QLabel( this );
	QImage image( ":/imageIco/color_picking.png" );
	QPixmap fromImage = QPixmap::fromImage( image );
	selectPoint->setPixmap( fromImage );
	selectPointBackground = new QImage( );
	alphaScrollBackground = new QImage( );
}
ColorEditor::~ColorEditor( ) {
	delete selectPointBackground;
	delete alphaScrollBackground;
}

void ColorEditor::setCurrentColor( const QColor &current_color ) {
	currentColor = current_color;
	repaint( ); // 属性面板
}
bool ColorEditor::affirmButtonRelease( ) {
	emit selectorColor( currentColor );
	hide( );
	return true;
}
bool ColorEditor::cancelButtonRelease( ) {
	hide( );
	return true;
}
bool ColorEditor::alphaScrollButtonRelease( ) {
	return true;
}
bool ColorEditor::alphaScrollButtonPaint( ) {
	QPainter *painter;
	int drawXPos;
	int height;
	int width;
	double value;
	// 高度
	height = alphaScrollButton->height( );
	// 宽度
	width = alphaScrollButton->width( );
	// 角度
	value = 45;
	// 因子
	value = value * ( M_PI / 180.0 );
	// tan 值
	value = std::tan( value );
	// 相差像素
	value = height / value;
	// 间隔
	nextInterval = 4;
	painter = new QPainter( alphaScrollButton );
	painter->setPen( Qt::GlobalColor::red );
	drawXPos = 0;
	width += width; // 增加底部宽度
	while( true ) {
		painter->drawLine( drawXPos, 0, drawXPos - value, height );
		if( drawXPos > width )
			break;
		drawXPos += nextInterval;
	}
	delete painter;
	return true;
}
bool ColorEditor::eventFilter( QObject *watched, QEvent *event ) {
	auto type = event->type( );
	QMouseEvent *mouseEventPtr;
	switch( type ) {
		case QEvent::MouseButtonRelease :
			Reinterpret_Cast( mouseEventPtr, event );
			if( watched == affirmBtn )
				return affirmButtonRelease( );
			else if( watched == cancelBen )
				return cancelButtonRelease( );
			else if( watched == alphaScrollButton )
				return alphaScrollButtonRelease( ); // 滑动窗口
			return true; // 已经处理的即返回
		case QEvent::Paint :
			if( alphaScrollButton != watched || alphaScrollButtonPaint( ) == false )
				return false;
			return false;
	}
	return QWidget::eventFilter( watched, event );
}
bool ColorEditor::updateLayout( ) {
	int width = currentSize.width( );
	int height = currentSize.height( );
	int affirmHeight = affirmBtn->height( );
	int affirmWidth = affirmBtn->width( );
	int falfWidth = width / 2;
	falfWidth = falfWidth - affirmWidth;
	height = height - affirmHeight; // 剩余高度
	affirmBtn->move( falfWidth, height );
	cancelBen->move( falfWidth + 5, height );
	height = height - alphaScrollButton->height( );// 剩余高度
	double alphaXPos = alphaScrollButton->x( ); // 未移动的 x
	alphaXPos = alphaXPos / oldSize.width( ); // 旧 x 位置百分比
	alphaXPos = alphaXPos * currentSize.width( ); // 新 x 位置百分比
	alphaScrollButton->move( alphaXPos, height ); // 移动到匹配位置

	return true;
}
bool ColorEditor::updateColorInfo( ) {
	return true;
}
bool ColorEditor::clearColorInfo( ) {
	return true;
}
bool ColorEditor::reDrawWidget( ) {
	return true;
}
bool ColorEditor::hideEventCall( ) {
	if( clearColorInfo( ) == false )
		return false;
	return true;
}
bool ColorEditor::showEventCall( ) {
	if( updateLayout( ) == false )
		return false;
	if( updateColorInfo( ) == false )
		return false;
	return true;
}
bool ColorEditor::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::Show :
			if( showEventCall( ) == false )
				return false;
			return true;
		case QEvent::Hide :
			if( hideEventCall( ) == false )
				return false;
			return true;
		case QEvent::Paint :
			if( reDrawWidget( ) == false )
				return false;
			return true;
		case QEvent::Resize :
			if( updateLayout( ) == false )
				return false;
			return true;
	}
	return QWidget::event( event );
}
