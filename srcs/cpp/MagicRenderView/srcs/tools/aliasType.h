#ifndef ALIASTYPE_H_H_HEAD__FILE__
#define ALIASTYPE_H_H_HEAD__FILE__
#pragma once
#include <QString>
#include <utility>

using portInfo = std::pair< uint64_t, QString >;
using InputportLinkOutputPortInfoMap = std::pair< portInfo, std::vector< portInfo > >;

#endif // ALIASTYPE_H_H_HEAD__FILE__
