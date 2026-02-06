#ifndef RENDERIMAGEDIRECTOR_H_H_HEAD__FILE__
#define RENDERIMAGEDIRECTOR_H_H_HEAD__FILE__
#include <QObject>
class QPainter;
class QImage;
class QString;
class QFont;
class Application;

class RenderImageDirector : public QObject {
	Q_OBJECT;
protected:
	QFont *font;
	Application *application;
public:
	RenderImageDirector( );
	~RenderImageDirector( ) override;
	virtual bool init( );
	virtual bool renderText( QPainter &painter, const QString &render_target_text, QImage &result_render_target );
	virtual bool renderText( const QString &render_target_text, QImage &result_render_target );
	virtual bool renderText( const QString &render_target_text, const QColor &draw_text_color, QImage &result_render_target );
	virtual const QFont & getFont( ) const;
	virtual void setFont( const QFont &font );
	virtual bool renderWidget( QWidget *render_target_widget, QImage &resul_render_target );
};

#endif // RENDERIMAGEDIRECTOR_H_H_HEAD__FILE__
