#include "aboutApplicationWidget.h"

#include <QDate>
#include <QLabel>
#include <QMessageBox>
#include <qstyle.h>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../app/application.h"
#include "../win/aboutApplicationWindow.h"
AboutApplicationWidget::AboutApplicationWidget( AboutApplicationWindow *parent_window ) : QWidget( parent_window ), parentWindow( parent_window ) {
	Application *application = Application::getInstancePtr( );
	setWindowTitle( tr( "%1 关于" ).arg( application->applicationName( ) ) );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	auto qtIco = new QLabel( this );
	QStyle *stylePtr = style( );
	auto icon = stylePtr->standardPixmap( QStyle::SP_TitleBarMenuButton );
	icon = icon.scaled( 64, 64 );
	qtIco->setPixmap( icon );

	auto pixmap = QPixmap::fromImage( QImage( ":/qt-project.org/qmessagebox/images/qtlogo-64.png" ) );
	qtIco->setPixmap( pixmap );

	mainLayout->addWidget( qtIco, 0, Qt::AlignTop );
	auto textBox = new QTextEdit( this );
	textBox->setReadOnly( true );
	mainLayout->addWidget( textBox );
	textBox->setText( getSoftwareProtocolInfo( ) );
	textBox->setAutoFormatting( QTextEdit::AutoAll );
}

QString AboutApplicationWidget::getSoftwareProtocolInfo( ) {
	QString softInfo;
	// ===== 1. 软件基础信息（自定义）
	softInfo += "<h3 style='color:#2980b9;margin:0;padding:0;'>📄 软件编译&运行协议信息</h3><hr/>";
	softInfo += QString( "<p><b>软件版本：</b>%1</p>" ).arg( "V1.2.0" );

	QDateTime compileDateTime = QDateTime(
		QDate::fromString( __DATE__, "MMM dd yyyy" ),
		QTime::fromString( __TIME__, "hh:mm:ss" )
		);
	softInfo += QString( "<p><b>编译时间：</b>%1</p>" ).arg( compileDateTime.toString( "yyyy年MM月dd日 hh时mm分ss秒.zzz" ) );

	// ===== 2. Qt核心协议/版本信息（重中之重）
	softInfo += "<p><b>▷ Qt 编译协议信息</b></p>";
	softInfo += QString( "<p>Qt库版本：</p><p style='padding-left:20px;'>%1</p>" ).arg( QT_VERSION_STR );
#ifdef QT_DEBUG
	softInfo += "<p>Qt编译模式：</p><p style='padding-left:20px;color:red;'>调试版(Debug)</p>";
#else
	softInfo += "<p>Qt编译模式：</p><p style='padding-left:20px;color:green;'>发布版(Release)</p>";
#endif
	softInfo += QString( "<p>Qt构建架构：</p><p style='padding-left:20px;'>%1 位</p>" ).arg( QSysInfo::WordSize );

	// ===== 3. 编译器协议/版本信息（软件编译核心协议）
	softInfo += "<p><b>▷ 编译器协议信息</b></p>";
#ifdef _MSC_VER
	softInfo += QString( "<p>编译器：</p><p style='padding-left:20px;'>MSVC %1</p>" ).arg( QString::number( _MSC_VER / 100.0, 'f', 1 ) );
	softInfo += "<p>编译协议：</p><p style='padding-left:20px;'>VC++ 运行时协议 (MSVCRT)</p>";
#elif __GNUC__
	softInfo += QString( "<p>编译器：</p><p style='padding-left:20px;'>GCC %1.%2</p>" ).arg( __GNUC__ ).arg( __GNUC_MINOR__ );
	softInfo += "<p>编译协议：</p><p style='padding-left:20px;'>GNU 开源协议 (GPL)</p>";
#elif __clang__
	softInfo += "<p>编译器：</p><p style='padding-left:20px;'>Clang</p>";
	softInfo += "<p>编译协议：</p><p style='padding-left:20px;'>LLVM 开源协议</p>";
#else
	softInfo += "<p>编译器：</p><p style='padding-left:20px;'>未知编译器</p>";
#endif

	// ===== 4. 系统运行协议/环境信息
	softInfo += "<p><b>▷ 系统运行协议信息</b></p>";
	softInfo += QString( "<p>操作系统：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::prettyProductName( ) );
	softInfo += QString( "<p>系统架构：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::currentCpuArchitecture( ) );
	softInfo += QString( "<p>系统内核：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::kernelType( ) + " " + QSysInfo::kernelVersion( ) );
	softInfo += "<p>运行协议：</p><p style='padding-left:20px;'>本地系统原生协议</p>";

	// ===== 5. 软件版权协议（必加）

	QStringList stringList;
	QString pStyle( "style='color:#3c8e51;text-align:center;'" );
	stringList.append( tr( "<p %2 >%1</p>" ).arg( tr( "©2025 本软件包含的贡献均属于其各自所有者的版权。" ) ).arg( pStyle ) );
	stringList.append( tr( "<p %2 >%1</p>" ).arg( tr( "Qt 及其相应标识均为 Qt 公司有限公司在芬兰及其他国家/地区的商标。" ) ).arg( pStyle ) );
	stringList.append( tr( "<p %2 >%1</p>" ).arg( tr( "所提供的 QT 库受 %1 许可证限制。" ).arg( "LGPL 3.0" ) ).arg( pStyle ) );
	stringList.append( tr( "<p %2 >%1</p>" ).arg( tr( "所有其他商标均归其各自所有者所有。" ) ).arg( pStyle ) );
	pStyle = QStringLiteral( "style='color:#0079ff;text-align:center;'" );
	stringList.append( tr( "<p %2 >%1</p>" ).arg( tr( "gitee : <a href='https://gitee.com/ChenYLhuman/MagicRenderView'>https://gitee.com/ChenYLhuman/MagicRenderView</a>" ) ).arg( pStyle ) );
	stringList.append( tr( "<p %2 >%1</p>" ).arg( tr( "github : <a href='https://github.com/Acreate/MagicRenderView'>https://github.com/Acreate/MagicRenderView</a>" ) ).arg( pStyle ) );
	softInfo += tr( "<hr/>" ) + stringList.join( "\n" );

	return softInfo;
}
