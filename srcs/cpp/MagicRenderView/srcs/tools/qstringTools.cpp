#include "qstringTools.h"
#include <qstring.h>
void QStringTools::replace( const QString &org_string, const QString &find_replace_string, const QString &full_replace_string, QString &result_over_string ) {
	// 保存匹配元素的位置
	std::vector< size_t > indexVector;
	// 原始字符串长度
	size_t orgStringLength = org_string.size( );
	// 原始字符串数据
	const QChar *orgStringDataArray = org_string.data( );
	// 查找字符串长度
	qsizetype findStringLen = find_replace_string.length( );
	// 查找字符串数据
	auto findStringDataArray = find_replace_string.data( );
	// 遍历下标
	size_t foreachIndex;
	// 查找下标
	size_t findIndex;
	size_t findNextIndex = findStringLen - 1;
	// 替换次数
	size_t replaceIndexCount = 0;
	for( foreachIndex = 0; foreachIndex < orgStringLength; ++foreachIndex ) {
		findIndex = orgStringLength - foreachIndex;
		if( findIndex < findStringLen )
			break; // 比较数据不足
		if( findStringDataArray[ 0 ] != orgStringDataArray[ foreachIndex ] )
			continue; // 元素不匹配，则跳过这个元素
		for( findIndex = 1; findIndex < findStringLen; ++findIndex )
			if( findStringDataArray[ findIndex ] != orgStringDataArray[ foreachIndex + findIndex ] )
				break; // 元素不匹配，则跳出
		if( findIndex < findStringLen )
			continue; // 元素不匹配，则跳过这个元素
		// 元素匹配，保存下标
		indexVector.emplace_back( foreachIndex );
		foreachIndex += findNextIndex;
		replaceIndexCount += 1;
	}
	if( replaceIndexCount == 0 ) { // 匹配不到，则返回原本字符串
		if( &result_over_string != &org_string )
			result_over_string = org_string;
		return;
	}
	// 替换长度
	size_t fillStringLen = full_replace_string.length( );
	// 替换数据
	auto fillStringDataArray = full_replace_string.data( );
	size_t expansionSize;
	if( findStringLen > fillStringLen )
		expansionSize = findStringLen - fillStringLen;
	else
		expansionSize = fillStringLen - findStringLen;
	// 缓存大小
	size_t buffSize = replaceIndexCount * expansionSize + orgStringLength;
	result_over_string.resize( buffSize );
	auto fillTarget = result_over_string.data( );
	size_t buffIndex = 0;
	auto replaceIndexDataArray = indexVector.data( );
	size_t replaceIndexDataArrayIndex = 0;
	for( foreachIndex = 0; foreachIndex < orgStringLength; ) {
		if( foreachIndex == replaceIndexDataArray[ replaceIndexDataArrayIndex ] ) {
			// 填充替换字符串
			for( findIndex = 0; findIndex < fillStringLen; ++findIndex ) {
				fillTarget[ buffIndex ] = fillStringDataArray[ findIndex ];
				++buffIndex;
			}
			++replaceIndexDataArrayIndex;
			// 跳过匹配查找的字符串
			foreachIndex += findStringLen;
			continue;
		} else// 填充原始字符
			fillTarget[ buffIndex ] = orgStringDataArray[ foreachIndex ];
		++foreachIndex;
		++buffIndex;
	}

}
void QStringTools::replace( const QString &org_string, const QString &find_replace_string, const QString &full_replace_string, const size_t &replace_count, QString &result_over_string ) {
	if( replace_count == 0 ) {
		result_over_string = org_string;
		return;
	}
	// 原始字符串长度
	size_t orgStringLength = org_string.size( );
	if( orgStringLength <= replace_count ) {
		QStringTools::replace( org_string, find_replace_string, full_replace_string, result_over_string );
		return;
	}
	// 保存匹配元素的位置
	std::vector< size_t > indexVector;
	// 原始字符串数据
	const QChar *orgStringDataArray = org_string.data( );
	// 查找字符串长度
	qsizetype findStringLen = find_replace_string.length( );
	// 查找字符串数据
	auto findStringDataArray = find_replace_string.data( );
	// 遍历下标
	size_t foreachIndex;
	// 查找下标
	size_t findIndex;
	size_t findNextIndex = findStringLen - 1;
	// 替换次数
	size_t replaceIndexCount = 0;
	for( foreachIndex = 0; foreachIndex < orgStringLength; ++foreachIndex ) {
		findIndex = orgStringLength - foreachIndex;
		if( findIndex < findStringLen )
			break; // 比较数据不足
		if( findStringDataArray[ 0 ] != orgStringDataArray[ foreachIndex ] )
			continue; // 元素不匹配，则跳过这个元素
		for( findIndex = 1; findIndex < findStringLen; ++findIndex )
			if( findStringDataArray[ findIndex ] != orgStringDataArray[ foreachIndex + findIndex ] )
				break; // 元素不匹配，则跳出
		if( findIndex < findStringLen )
			continue; // 元素不匹配，则跳过这个元素
		// 元素匹配，保存下标
		indexVector.emplace_back( foreachIndex );
		foreachIndex += findNextIndex;
		replaceIndexCount += 1;
		if( replaceIndexCount == replace_count )
			break;
	}
	if( replaceIndexCount == 0 ) { // 匹配不到，则返回原本字符串
		if( &result_over_string != &org_string )
			result_over_string = org_string;
		return;
	}
	// 替换长度
	size_t fillStringLen = full_replace_string.length( );
	// 替换数据
	auto fillStringDataArray = full_replace_string.data( );
	size_t expansionSize;
	if( findStringLen > fillStringLen )
		expansionSize = findStringLen - fillStringLen;
	else
		expansionSize = fillStringLen - findStringLen;
	// 缓存大小
	size_t buffSize = replaceIndexCount * expansionSize + orgStringLength;
	result_over_string.resize( buffSize );
	auto fillTarget = result_over_string.data( );
	size_t buffIndex = 0;
	auto replaceIndexDataArray = indexVector.data( );
	size_t replaceIndexDataArrayIndex = 0;
	for( foreachIndex = 0; foreachIndex < orgStringLength; ) {
		if( foreachIndex == replaceIndexDataArray[ replaceIndexDataArrayIndex ] ) {
			// 填充替换字符串
			for( findIndex = 0; findIndex < fillStringLen; ++findIndex ) {
				fillTarget[ buffIndex ] = fillStringDataArray[ findIndex ];
				++buffIndex;
			}
			++replaceIndexDataArrayIndex;
			// 跳过匹配查找的字符串
			foreachIndex += findStringLen;
			continue;
		} else// 填充原始字符
			fillTarget[ buffIndex ] = orgStringDataArray[ foreachIndex ];
		++foreachIndex;
		++buffIndex;
	}
}
