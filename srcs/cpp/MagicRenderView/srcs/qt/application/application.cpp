#include "application.h"

#include <QFontDatabase>
#include <QMouseEvent>
#include <QProcess>
#include <QSettings>
#include <qboxlayout.h>
#include <qfile.h>
#include <qfileinfo.h>

#include <qt/generate/varGenerate.h>
#include <qt/node/director/nodeDirector.h>
#include <qt/node/item/app/appInfo.h>
#include <qt/node/item/app/endNode.h>
#include <qt/node/item/app/startNode.h>
#include <qt/node/item/calculate/varAdd.h>
#include <qt/node/item/calculate/varDiv.h>
#include <qt/node/item/calculate/varMod.h>
#include <qt/node/item/calculate/varMul.h>
#include <qt/node/item/calculate/varSub.h>
#include <qt/node/item/disk/readFile.h>
#include <qt/node/item/disk/readImage.h>
#include <qt/node/item/disk/writeFile.h>
#include <qt/node/item/disk/writeImage.h>
#include <qt/node/item/generate/genBinTypes.h>
#include <qt/node/item/generate/genColorTypes.h>
#include <qt/node/item/generate/genFloatTypes.h>
#include <qt/node/item/generate/genIntTypes.h>
#include <qt/node/item/generate/genStringTypes.h>
#include <qt/node/item/generate/genUIntTypes.h>
#include <qt/node/item/info/networkInfo.h>
#include <qt/node/item/info/pathInfo.h>
#include <qt/node/item/info/systemInfo.h>
#include <qt/node/item/logic/ifLogic.h>
#include <qt/node/item/str/strAppend.h>
#include <qt/node/item/str/strInsert.h>
#include <qt/node/item/str/strRemove.h>
#include <qt/node/item/str/strReplace.h>
#include <qt/node/item/str/strSplit.h>
#include <qt/node/item/str/strSub.h>
#include <qt/node/item/struct/array.h>
#include <qt/node/item/time/timeDataConver.h>
#include <qt/node/item/time/timeDataInfo.h>
#include <qt/node/item/time/timeInfo.h>
#include <qt/tools/tools.h>
#include <qt/varType/convers/anyConvers/anyToAny.h>
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
#include <qt/varType/isTypes/isColorType.h>
#include <qt/varType/isTypes/isFloat32Type.h>
#include <qt/varType/isTypes/isFloat64Type.h>
#include <qt/varType/isTypes/isInt16Type.h>
#include <qt/varType/isTypes/isInt32Type.h>
#include <qt/varType/isTypes/isInt64Type.h>
#include <qt/varType/isTypes/isInt8Type.h>
#include <qt/varType/isTypes/isNodeItemType.h>
#include <qt/varType/isTypes/isQStringType.h>
#include <qt/varType/isTypes/isStdStringType.h>
#include <qt/varType/isTypes/isStdWStringType.h>
#include <qt/varType/isTypes/isUint16Type.h>
#include <qt/varType/isTypes/isUint32Type.h>
#include <qt/varType/isTypes/isUint64Type.h>
#include <qt/varType/isTypes/isUint8Type.h>
#include <qt/varType/stacks/base/float32Stack.h>
#include <qt/varType/stacks/base/float64Stack.h>
#include <qt/varType/stacks/base/int16Stack.h>
#include <qt/varType/stacks/base/int32Stack.h>
#include <qt/varType/stacks/base/int64Stack.h>
#include <qt/varType/stacks/base/int8Stack.h>
#include <qt/varType/stacks/base/uInt16Stack.h>
#include <qt/varType/stacks/base/uInt32Stack.h>
#include <qt/varType/stacks/base/uInt64Stack.h>
#include <qt/varType/stacks/base/uInt8Stack.h>
#include <qt/varType/stacks/cpp/stdStringStack.h>
#include <qt/varType/stacks/cpp/stdWStringStack.h>
#include <qt/varType/stacks/qt/qColorStack.h>
#include <qt/varType/stacks/qt/qStringStack.h>

#include "../node/item/jump/jumpGenerate.h"
#include "../node/item/jump/jumpMark.h"
#include "../node/item/mark/markPoint.h"

#include "../varType/stacks/app/nodeDirectorStack.h"

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
	nodeDirector = new NodeDirector( );
	nodeItemWidgetIco = new QImage( ":/ico/ui_w_font.png" );
	*nodeItemWidgetIco = nodeItemWidgetIco->scaled( 16, 16 );
}
Application::~Application( ) {
	delete nodeDirector;
	delete varGenerate;
	settings->sync( );
	delete settings;
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
	// todo : app
	varGenerate->appendNodeItemGenerateInstance< AppInfo >( );
	varGenerate->appendNodeItemGenerateInstance< EndNode >( );
	varGenerate->appendNodeItemGenerateInstance< StartNode >( );
	// todo : 磁盘节点
	varGenerate->appendNodeItemGenerateInstance< WriteFile >( );
	varGenerate->appendNodeItemGenerateInstance< WriteImage >( );
	varGenerate->appendNodeItemGenerateInstance< ReadFile >( );
	varGenerate->appendNodeItemGenerateInstance< ReadImage >( );
	// todo : 生成

	varGenerate->appendNodeItemGenerateInstance< GenFloatTypes >( );
	varGenerate->appendNodeItemGenerateInstance< GenIntTypes >( );
	varGenerate->appendNodeItemGenerateInstance< GenStringTypes >( );
	varGenerate->appendNodeItemGenerateInstance< GenUIntTypes >( );
	varGenerate->appendNodeItemGenerateInstance< GenColorTypes >( );
	varGenerate->appendNodeItemGenerateInstance< GenBinTypes >( );
	// todo : 信息节点
	varGenerate->appendNodeItemGenerateInstance< PathInfo >( );
	varGenerate->appendNodeItemGenerateInstance< SystemInfo >( );
	varGenerate->appendNodeItemGenerateInstance< NetworkInfo >( );
	// todo : 跳
	varGenerate->appendNodeItemGenerateInstance< MarkPoint >( );
	varGenerate->appendNodeItemGenerateInstance< JumpMark >( );
	varGenerate->appendNodeItemGenerateInstance< JumpGenerate >( );
	// todo : 逻辑节点
	varGenerate->appendNodeItemGenerateInstance< IfLogic >( );
	// todo : 计算节点
	varGenerate->appendNodeItemGenerateInstance< VarAdd >( );
	varGenerate->appendNodeItemGenerateInstance< VarSub >( );
	varGenerate->appendNodeItemGenerateInstance< VarMul >( );
	varGenerate->appendNodeItemGenerateInstance< VarDiv >( );
	varGenerate->appendNodeItemGenerateInstance< VarMod >( );
	// todo : 字符串节点
	varGenerate->appendNodeItemGenerateInstance< StrAppend >( );
	varGenerate->appendNodeItemGenerateInstance< StrRemove >( );
	varGenerate->appendNodeItemGenerateInstance< StrReplace >( );
	varGenerate->appendNodeItemGenerateInstance< StrInsert >( );
	varGenerate->appendNodeItemGenerateInstance< StrSplit >( );
	varGenerate->appendNodeItemGenerateInstance< StrSub >( );
	// todo : 结构体
	varGenerate->appendNodeItemGenerateInstance< Array >( );
	// todo : 时间
	varGenerate->appendNodeItemGenerateInstance< TimeDataConver >( );
	varGenerate->appendNodeItemGenerateInstance< TimeDataInfo >( );
	varGenerate->appendNodeItemGenerateInstance< TimeInfo >( );

	// todo : 图片特效节点

	// todo : 视频操作节点

	// todo : 视频特效节点

	// todo : 音乐操作节点

	// todo : 音乐特效节点
	// todo : 类型识别支持
	varGenerate->appendIsTypeInstance< IsColorType >( );
	varGenerate->appendIsTypeInstance< IsInt8Type >( );
	varGenerate->appendIsTypeInstance< IsInt16Type >( );
	varGenerate->appendIsTypeInstance< IsInt32Type >( );
	varGenerate->appendIsTypeInstance< IsInt64Type >( );
	varGenerate->appendIsTypeInstance< IsUint8Type >( );
	varGenerate->appendIsTypeInstance< IsUint16Type >( );
	varGenerate->appendIsTypeInstance< IsUint32Type >( );
	varGenerate->appendIsTypeInstance< IsUint64Type >( );
	varGenerate->appendIsTypeInstance< IsFloat32Type >( );
	varGenerate->appendIsTypeInstance< IsFloat64Type >( );
	varGenerate->appendIsTypeInstance< IsStdStringType >( );
	varGenerate->appendIsTypeInstance< IsStdWStringType >( );
	varGenerate->appendIsTypeInstance< IsQStringType >( );
	varGenerate->appendIsTypeInstance< IsNodeItemType >( );
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

	varGenerate->appendConverInstance< AnyToAny >( );

	// todo : 序列化支持
	varGenerate->appendStackInstance< Float32Stack >( );
	varGenerate->appendStackInstance< Float64Stack >( );
	varGenerate->appendStackInstance< Int8Stack >( );
	varGenerate->appendStackInstance< Int16Stack >( );
	varGenerate->appendStackInstance< Int32Stack >( );
	varGenerate->appendStackInstance< Int64Stack >( );
	varGenerate->appendStackInstance< UInt8Stack >( );
	varGenerate->appendStackInstance< UInt16Stack >( );
	varGenerate->appendStackInstance< UInt32Stack >( );
	varGenerate->appendStackInstance< UInt64Stack >( );
	varGenerate->appendStackInstance< QStringStack >( );
	varGenerate->appendStackInstance< StdStringStack >( );
	varGenerate->appendStackInstance< StdWStringStack >( );
	varGenerate->appendStackInstance< QColorStack >( );
	varGenerate->appendStackInstance< NodeDirectorStack >( );
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
	switch( event->type( ) ) {
		case QEvent::Quit :
			break;
	}
	return QApplication::notify( object, event );
}
