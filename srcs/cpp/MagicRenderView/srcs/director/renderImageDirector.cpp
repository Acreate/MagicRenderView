#include "renderImageDirector.h"

#include <app/application.h>
#include <qfont.h>
#include <QImage>
#include <QFontMetrics>
#include <QPainter>
#include <QWidget>
RenderImageDirector::RenderImageDirector( ) {
	font = new QFont( );
}
RenderImageDirector::~RenderImageDirector( ) {
	delete font;
}
bool RenderImageDirector::init( ) {

	application = Application::getInstancePtr( );
	*font = application->font( );
	return true;
}
bool RenderImageDirector::renderText( QPainter &painter, const QString &render_target_text, QImage &result_render_target ) {
	if( painter.isActive( ) == true ) {
		if( painter.end( ) == false )
			return false;
	}
	qint64 length = render_target_text.length( );
	if( length == 0 )
		return false;
	QFontMetrics *fontMetrics;
	fontMetrics = new QFontMetrics( *font );
	int horizontalAdvance = fontMetrics->horizontalAdvance( render_target_text );

	int height = fontMetrics->height( );
	if( horizontalAdvance == 0 || height == 0 ) {
		delete fontMetrics;
		return false;
	}

	QImage *buffImage;
	buffImage = new QImage( horizontalAdvance, height, QImage::Format_RGBA8888 );
	if( painter.begin( &result_render_target ) == false ) {
		delete buffImage;
		delete fontMetrics;
		return false;
	}
	buffImage->fill( 0 );//清空背景
	// 原始图像复制到当前缓存
	if( result_render_target.isNull( ) == false )
		painter.drawImage( 0, 0, result_render_target );
	// 绘制文字
	QRect renderRect = result_render_target.rect( );
	painter.drawText( renderRect, render_target_text );
	// 覆盖原始图像
	result_render_target = *buffImage;
	delete buffImage;
	delete fontMetrics;
	return true;
}
bool RenderImageDirector::renderText( const QString &render_target_text, QImage &result_render_target ) {
	return renderText( render_target_text, Qt::GlobalColor::black, result_render_target );
}
bool RenderImageDirector::renderText( const QString &render_target_text, const QColor &draw_text_color, QImage &result_render_target ) {
	qint64 length = render_target_text.length( );
	if( length == 0 )
		return false;
	QFontMetrics *fontMetrics;
	fontMetrics = new QFontMetrics( *font );
	int horizontalAdvance = fontMetrics->horizontalAdvance( render_target_text );

	int height = fontMetrics->height( );
	if( horizontalAdvance == 0 || height == 0 ) {
		delete fontMetrics;
		return false;
	}

	QImage *buffImage;
	buffImage = new QImage( horizontalAdvance, height, QImage::Format_RGBA8888 );
	buffImage->fill( 0 );//清空背景
	QPainter *painter;
	painter = new QPainter( buffImage );
	// 原始图像复制到当前缓存
	if( result_render_target.isNull( ) == false )
		painter->drawImage( 0, 0, result_render_target );
	// 绘制文字
	painter->setPen( draw_text_color );
	QRect renderRect = result_render_target.rect( );
	painter->drawText( renderRect, render_target_text );
	// 覆盖原始图像
	result_render_target = *buffImage;
	delete buffImage;
	delete painter;
	delete fontMetrics;
	return true;
}
const QFont & RenderImageDirector::getFont( ) const {
	return *font;
}

void RenderImageDirector::setFont( const QFont &font ) {
	*this->font = font;
}
bool RenderImageDirector::renderWidget( QWidget *render_target_widget, QImage &resul_render_target ) {
	if( render_target_widget == nullptr )
		return false;
	resul_render_target = QImage( render_target_widget->size( ), QImage::Format_RGBA8888 );
	QPainter imageTargetPainter( &resul_render_target );
	render_target_widget->render( &imageTargetPainter );
	if( resul_render_target.isNull( ) )
		return false;
	return true;
}
