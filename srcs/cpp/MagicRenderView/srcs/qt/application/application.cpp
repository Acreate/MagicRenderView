#include "application.h"

#include <QMouseEvent>
#include <QProcess>
#include <QFontDatabase>
#include <QSettings>
#include <qboxlayout.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qt/stack/stack.h>
#include <qt/widgets/mainWidget.h>

#include "../generate/nodeItemGenerate.h"
#include "../generate/varTypeGenerate.h"

#include "../node/item/calculate/varAdd.h"
#include "../node/item/calculate/varDiv.h"
#include "../node/item/calculate/varMod.h"
#include "../node/item/calculate/varMul.h"
#include "../node/item/calculate/varSub.h"
#include "../node/item/disk/readFile.h"
#include "../node/item/disk/readImage.h"
#include "../node/item/disk/writeFile.h"
#include "../node/item/disk/writeImage.h"
#include "../node/item/info/pathInfo.h"
#include "../node/item/info/systemInfo.h"
#include "../node/item/str/strAppend.h"
#include "../node/item/str/strInsert.h"
#include "../node/item/str/strRemove.h"
#include "../node/item/str/strReplace.h"
#include "../node/item/str/strSplit.h"
#include "../node/item/str/strSub.h"

#include "../serialization/float32Serialization.h"
#include "../serialization/float64Serialization.h"
#include "../serialization/int16Serialization.h"
#include "../serialization/int32Serialization.h"
#include "../serialization/int64Serialization.h"
#include "../serialization/qstringSerialization.h"
#include "../serialization/stdStringSerialization.h"
#include "../serialization/stdWStringSerialization.h"
#include "../serialization/uint16Serialization.h"
#include "../serialization/uint32Serialization.h"
#include "../serialization/uint64Serialization.h"
#include "../serialization/uint8Serialization.h"

#include "qt/tools/tools.h"

Application::Application( int &argc, char **argv, int i ) : QApplication( argc, argv, i ) {
	QString displayName = applicationDisplayName( );
	writeSettingPath = applicationDirPath( ) + "/" + displayName + "/progress/";
	QString fileName = writeSettingPath + displayName + "/" + displayName + ".ini";
	settings = new QSettings( fileName, QSettings::IniFormat );
	QFileInfo fileInfo( fileName );
	if( fileInfo.exists( ) == false ) {
		auto key = "settings";
		settings->setValue( key, 0 );
		settings->sync( );
		settings->remove( key );
		if( fileInfo.exists( ) == false )
			qDebug( ) << "无法创建匹配的 ini 文件";
		else
			settings->sync( );
	}
	/*
	 * 锁
	 */
	stdMutex_p.reset( new std_mutex );
	stdMutexWidgetSelectLock.reset( new std_mutex );
	/*
	 * 堆栈
	 */
	stack = new Stack( );

	/*
	 * 字体
	 */
	int fontId = QFontDatabase::addApplicationFont( ":/fonts/Alibaba-PuHuiTi-Regular.ttf" );
	if( fontId != -1 ) {
		QString family = QFontDatabase::applicationFontFamilies( fontId ).at( 0 );
		QApplication::setFont( QFont( family ) );
		font.reset( new QFont( family ) );
		font->setItalic( true );
		font->setBold( true );
	} else
		font.reset( new QFont( "" ) );
	/*
	 * 初始化节点
	 */
	// todo : 磁盘节点
	NodeItemGenerate::appendNodeItemInfo< WriteFile >( );
	NodeItemGenerate::appendNodeItemInfo< WriteImage >( );
	NodeItemGenerate::appendNodeItemInfo< ReadFile >( );
	NodeItemGenerate::appendNodeItemInfo< ReadImage >( );
	// todo : 信息节点
	NodeItemGenerate::appendNodeItemInfo< PathInfo >( );
	NodeItemGenerate::appendNodeItemInfo< SystemInfo >( );
	// todo : 计算节点
	NodeItemGenerate::appendNodeItemInfo< VarAdd >( );
	NodeItemGenerate::appendNodeItemInfo< VarSub >( );
	NodeItemGenerate::appendNodeItemInfo< VarMul >( );
	NodeItemGenerate::appendNodeItemInfo< VarDiv >( );
	NodeItemGenerate::appendNodeItemInfo< VarMod >( );
	// todo : 字符串节点
	NodeItemGenerate::appendNodeItemInfo< StrAppend >( );
	NodeItemGenerate::appendNodeItemInfo< StrRemove >( );
	NodeItemGenerate::appendNodeItemInfo< StrReplace >( );
	NodeItemGenerate::appendNodeItemInfo< StrInsert >( );
	NodeItemGenerate::appendNodeItemInfo< StrSplit >( );
	NodeItemGenerate::appendNodeItemInfo< StrSub >( );
	// todo : 图片特效节点

	// todo : 视频操作节点

	// todo : 视频特效节点

	// todo : 音乐操作节点

	// todo : 音乐特效节点

	// todo : VarType 支持变量
	VarTypeGenerate::appendType< QString >( );
	VarTypeGenerate::appendType< uint8_t >( );
	VarTypeGenerate::appendType< uint16_t >( );
	VarTypeGenerate::appendType< uint32_t >( );
	VarTypeGenerate::appendType< uint64_t >( );
	VarTypeGenerate::appendType< int8_t >( );
	VarTypeGenerate::appendType< int16_t >( );
	VarTypeGenerate::appendType< int32_t >( );
	VarTypeGenerate::appendType< int64_t >( );
	VarTypeGenerate::appendType< float_t >( );
	VarTypeGenerate::appendType< double_t >( );
	VarTypeGenerate::appendType< QString >( );
	// todo : 序列化支持
	BinGenerate::appendBinGenerateItem< Int16Serialization >( );
	BinGenerate::appendBinGenerateItem< Int32Serialization >( );
	BinGenerate::appendBinGenerateItem< Int64Serialization >( );
	BinGenerate::appendBinGenerateItem< Uint8Serialization >( );
	BinGenerate::appendBinGenerateItem< Uint16Serialization >( );
	BinGenerate::appendBinGenerateItem< Uint32Serialization >( );
	BinGenerate::appendBinGenerateItem< Uint64Serialization >( );
	BinGenerate::appendBinGenerateItem< Float32Serialization >( );
	BinGenerate::appendBinGenerateItem< Float64Serialization >( );
	BinGenerate::appendBinGenerateItem< QStringSerialization >( );
	BinGenerate::appendBinGenerateItem< StdStringSerialization >( );
	BinGenerate::appendBinGenerateItem< StdWStringSerialization >( );
}
Application::~Application( ) {
	settings->sync( );
	delete settings;
}
void Application::setAppIniValue( const QAnyStringView &key, const QVariant &value ) {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	settings->setValue( key, value );
}
QVariant Application::getAppIniValue( const QAnyStringView &key, const QVariant &defaultValue ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	return settings->value( key, defaultValue );
}
QVariant Application::getAppIniValue( const QAnyStringView &key ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	return settings->value( key );
}
void Application::syncAppValueIniFile( ) const {
	std_lock_grad_mutex lock( *stdMutex_p.get( ) );
	settings->sync( );
}

std_vector< QWidget * > Application::getLayoutWidgets( QBoxLayout *main_widget ) {
	std_vector< QWidget * > result;
	int count = main_widget->count( );
	for( int index = 0; index < count; ++count ) {
		auto layoutItem = main_widget->itemAt( index );
		if( layoutItem->isEmpty( ) )
			continue;
		auto widget = layoutItem->widget( );
		if( widget == nullptr )
			continue;
		result.emplace_back( widget );
	}
	return result;
}
void Application::deleteLayoutWidgets( QBoxLayout *main_widget ) {
	int count = main_widget->count( );
	for( int index = 0; index < count; ++index ) {
		auto layoutItem = main_widget->itemAt( index );
		if( layoutItem == nullptr )
			continue;
		auto widget = layoutItem->widget( );
		if( widget == nullptr )
			continue;
		delete widget;
	}
}
Application * Application::getApplicationInstancePtr( ) {
	return qobject_cast< Application * >( qApp );
}
void Application::setWindowToIndexScreenCentre( size_t index ) {
	QWindowList windowList = qGuiApp->allWindows( );
	for( QWindow *&win : windowList )
		tools::ui::moveDisplayCenter( win, index );
}

void Application::resetApp( ) {
	quit( );
	QProcess::startDetached( applicationFilePath( ), arguments( ) );
}
void Application::quitApp( ) {
	quit( );
}
QString Application::normalKey( const QString &key ) {

	QString result;
	std_vector< QChar > charData;

	qsizetype length = key.length( ), index = 0;
	auto data = key.data( );
	for( ; index < length; ++index )
		if( data[ index ] == '/' || data[ index ] == '\\' ) {
			charData.emplace_back( '/' );
			for( ; index < length; ++index )
				if( data[ index ] != '/' && data[ index ] != '\\' ) {
					charData.emplace_back( data[ index ] );
					break;
				}
		} else
			charData.emplace_back( data[ index ] );
	size_t count = charData.size( );

	result = staticMetaObject.className( );
	result.append( "/" );
	if( charData[ count - 1 ] == "/" )
		result.append( QString( charData.data( ), count ) );
	else
		result.append( QString( charData.data( ), count ) ).append( "/" );
	return result;
}
QString Application::normalKey( const QString &key, QWidget *widget ) {
	QString result = normalKey( key );
	QString className = widget->metaObject( )->className( );
	className.append( "/" );
	if( result.endsWith( className ) == false )
		result.append( className );
	return result;
}
QString Application::normalKeyAppendWidgetName( const QString &key, QWidget *widget ) {
	auto appendStr = widget->objectName( );
	if( appendStr.isEmpty( ) )
		return normalKey( key, widget );
	return normalKeyAppendEnd( key, widget, appendStr );
}
bool Application::notify( QObject *object, QEvent *event ) {
	return QApplication::notify( object, event );
}
