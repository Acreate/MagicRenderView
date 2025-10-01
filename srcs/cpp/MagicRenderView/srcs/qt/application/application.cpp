#include "application.h"

#include <QFontDatabase>
#include <QMouseEvent>
#include <QProcess>
#include <QSettings>
#include <qboxlayout.h>
#include <qfile.h>
#include <qfileinfo.h>

#include <qt/generate/nodeItemGenerate.h>
#include <qt/generate/varGenerate.h>

#include <qt/varType/convers/floatToConvers/floatToFloat.h>
#include <qt/varType/convers/floatToConvers/floatToInt.h>
#include <qt/varType/convers/floatToConvers/floatToString.h>
#include <qt/varType/convers/floatToConvers/floatToUInt.h>
#include <qt/varType/convers/intToConvers/intToFloat.h>
#include <qt/varType/convers/intToConvers/intToInt.h>
#include <qt/varType/convers/intToConvers/intToString.h>
#include <qt/varType/convers/intToConvers/intToUInt.h>
#include <qt/varType/convers/nullToConver/nullToAny.h>
#include <qt/varType/convers/stringToConvers/stringToFloat.h>
#include <qt/varType/convers/stringToConvers/stringToInt.h>
#include <qt/varType/convers/stringToConvers/stringToString.h>
#include <qt/varType/convers/stringToConvers/stringToUint.h>
#include <qt/varType/convers/uintToConvers/uIntToInt.h>
#include <qt/varType/convers/uintToConvers/uIntToString.h>
#include <qt/varType/convers/uintToConvers/uIntToUInt.h>
#include <qt/varType/convers/uintToConvers/uintToFloat.h>

#include <qt/varType/type/baseType/float32Type.h>
#include <qt/varType/type/baseType/float64Type.h>
#include <qt/varType/type/baseType/int16Type.h>
#include <qt/varType/type/baseType/int32Type.h>
#include <qt/varType/type/baseType/int64Type.h>
#include <qt/varType/type/baseType/int8Type.h>
#include <qt/varType/type/baseType/uInt32Type.h>
#include <qt/varType/type/baseType/uInt64Type.h>
#include <qt/varType/type/baseType/uInt8Type.h>
#include <qt/varType/type/cpp/stdStringType.h>
#include <qt/varType/type/cpp/stdWStringType.h>
#include <qt/varType/type/qt/qStringType.h>
#include "qt/varType/type/baseType/uInt16Type.h"

#include <qt/node/item/calculate/varAdd.h>
#include <qt/node/item/calculate/varDiv.h>
#include <qt/node/item/calculate/varMod.h>
#include <qt/node/item/calculate/varMul.h>
#include <qt/node/item/calculate/varSub.h>
#include <qt/node/item/disk/readFile.h>
#include <qt/node/item/disk/readImage.h>
#include <qt/node/item/disk/writeFile.h>
#include <qt/node/item/disk/writeImage.h>
#include <qt/node/item/info/pathInfo.h>
#include <qt/node/item/info/systemInfo.h>
#include <qt/node/item/str/strAppend.h>
#include <qt/node/item/str/strInsert.h>
#include <qt/node/item/str/strRemove.h>
#include <qt/node/item/str/strReplace.h>
#include <qt/node/item/str/strSplit.h>
#include <qt/node/item/str/strSub.h>

#include <qt/tools/tools.h>

Application::Application( int &argc, char **argv, int i ) : QApplication( argc, argv, i ) {
	QString displayName = applicationDisplayName( );
	writeSettingPath = applicationDirPath( ) + "/" + displayName + "/progress/";
	/*
	 * 锁
	 */
	stdMutex_p.reset( new std_mutex );
	stdMutexWidgetSelectLock.reset( new std_mutex );
	/*
	 * 堆栈
	 */
	varGenerate = new VarGenerate( );
}
Application::~Application( ) {
	settings->sync( );
	delete settings;
	delete varGenerate;
}
bool Application::init( ) {

	QString displayName = applicationDisplayName( );
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
	NodeItemGenerate::appendGenerateNodeItemInfo< WriteFile >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< WriteImage >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< ReadFile >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< ReadImage >( );
	// todo : 信息节点
	NodeItemGenerate::appendGenerateNodeItemInfo< PathInfo >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< SystemInfo >( );
	// todo : 计算节点
	NodeItemGenerate::appendGenerateNodeItemInfo< VarAdd >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< VarSub >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< VarMul >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< VarDiv >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< VarMod >( );
	// todo : 字符串节点
	NodeItemGenerate::appendGenerateNodeItemInfo< StrAppend >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< StrRemove >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< StrReplace >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< StrInsert >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< StrSplit >( );
	NodeItemGenerate::appendGenerateNodeItemInfo< StrSub >( );
	// todo : 图片特效节点

	// todo : 视频操作节点

	// todo : 视频特效节点

	// todo : 音乐操作节点

	// todo : 音乐特效节点

	// todo : VarType 支持变量

	// todo : VarType 类型转换
	varGenerate->appendConverInstance< StringToString >( );
	varGenerate->appendConverInstance< StringToInt >( );
	varGenerate->appendConverInstance< StringToUint >( );
	varGenerate->appendConverInstance< StringToFloat >( );
	varGenerate->appendConverInstance< FloatToFloat >( );
	varGenerate->appendConverInstance< FloatToUInt >( );
	varGenerate->appendConverInstance< FloatToInt >( );
	varGenerate->appendConverInstance< FloatToString >( );
	varGenerate->appendConverInstance< IntToInt >( );
	varGenerate->appendConverInstance< IntToUInt >( );
	varGenerate->appendConverInstance< IntToFloat >( );
	varGenerate->appendConverInstance< IntToString >( );
	varGenerate->appendConverInstance< UIntToInt >( );
	varGenerate->appendConverInstance< UIntToUInt >( );
	varGenerate->appendConverInstance< UintToFloat >( );
	varGenerate->appendConverInstance< UIntToString >( );
	varGenerate->appendConverInstance< NullToAny >( );
	// todo : 序列化支持
	varGenerate->appendStackInstance< Float32Type >( );
	varGenerate->appendStackInstance< Float64Type >( );
	varGenerate->appendStackInstance< Int8Type >( );
	varGenerate->appendStackInstance< Int16Type >( );
	varGenerate->appendStackInstance< Int32Type >( );
	varGenerate->appendStackInstance< Int64Type >( );
	varGenerate->appendStackInstance< UInt8Type >( );
	varGenerate->appendStackInstance< UInt16Type >( );
	varGenerate->appendStackInstance< UInt32Type >( );
	varGenerate->appendStackInstance< UInt64Type >( );
	varGenerate->appendStackInstance< QStringType >( );
	varGenerate->appendStackInstance< StdStringType >( );
	varGenerate->appendStackInstance< StdWStringType >( );

	return true;
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
