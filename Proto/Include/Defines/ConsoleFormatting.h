#pragma once
#include "Defines/Platform.h"

#ifdef LINUX_PLATFORM

#define CONSOLE_RESET_FORMAT "\x1b[0m"
//#define CONSOLE_INVERT_FORMAT "\x1b[7m"
#define CONSOLE_BOLD "\x1b[1m"
#define CONSOLE_ITALIC "\x1b[3m"
#define CONSOLE_UNDERLINE "\x1b[4m"
#define CONSOLE_STRIKETHROUGH "\x1b[9m"
// Foreground colours
#define CONSOLE_TEXT_BLACK "\x1b[30m"
#define CONSOLE_TEXT_RED "\x1b[31m"
#define CONSOLE_TEXT_GREEN "\x1b[32m"
#define CONSOLE_TEXT_YELLOW "\x1b[33m"
#define CONSOLE_TEXT_BLUE "\x1b[34m"
#define CONSOLE_TEXT_MAGENTA "\x1b[35m"
#define CONSOLE_TEXT_CYAN "\x1b[36m"
#define CONSOLE_TEXT_WHITE "\x1b[37m"
// Background colours
#define CONSOLE_BACKGROUND_BLACK "\x1b[40m"
#define CONSOLE_BACKGROUND_RED "\x1b[41m"
#define CONSOLE_BACKGROUND_GREEN "\x1b[42m"
#define CONSOLE_BACKGROUND_YELLOW "\x1b[43m"
#define CONSOLE_BACKGROUND_BLUE "\x1b[44m"
#define CONSOLE_BACKGROUND_MAGENTA "\x1b[45m"
#define CONSOLE_BACKGROUND_CYAN "\x1b[46m"
#define CONSOLE_BACKGROUND_WHITE "\x1b[47m"

#else
#ifdef WINDOWS_PLATFORM

#include "Windows/Console/Formatting/DefaultFormat.h"
#include "Windows/Console/Formatting/BoldFormat.h"

#include "Windows/Console/Formatting/Background/BackgroundBlack.h"
#include "Windows/Console/Formatting/Background/BackgroundBlue.h"
#include "Windows/Console/Formatting/Background/BackgroundCyan.h"
#include "Windows/Console/Formatting/Background/BackgroundGreen.h"
#include "Windows/Console/Formatting/Background/BackgroundMagenta.h"
#include "Windows/Console/Formatting/Background/BackgroundRed.h"
#include "Windows/Console/Formatting/Background/BackgroundWhite.h"
#include "Windows/Console/Formatting/Background/BackgroundYellow.h"

#include "Windows/Console/Formatting/Foreground/ForegroundBlack.h"
#include "Windows/Console/Formatting/Foreground/ForegroundBlue.h"
#include "Windows/Console/Formatting/Foreground/ForegroundCyan.h"
#include "Windows/Console/Formatting/Foreground/ForegroundGreen.h"
#include "Windows/Console/Formatting/Foreground/ForegroundMagenta.h"
#include "Windows/Console/Formatting/Foreground/ForegroundRed.h"
#include "Windows/Console/Formatting/Foreground/ForegroundWhite.h"
#include "Windows/Console/Formatting/Foreground/ForegroundYellow.h"

#define CONSOLE_RESET_FORMAT Proto::DefaultFormat()
#define CONSOLE_BOLD Proto::BoldFormat()
#define CONSOLE_ITALIC ""
#define CONSOLE_UNDERLINE ""
#define CONSOLE_STRIKETHROUGH ""
// Foreground colours
#define CONSOLE_TEXT_BLACK Proto::ForegroundBlack()
#define CONSOLE_TEXT_BLUE Proto::ForegroundBlue()
#define CONSOLE_TEXT_CYAN Proto::ForegroundCyan()
#define CONSOLE_TEXT_GREEN Proto::ForegroundGreen()
#define CONSOLE_TEXT_MAGENTA Proto::ForegroundMagenta()
#define CONSOLE_TEXT_RED Proto::ForegroundRed()
#define CONSOLE_TEXT_WHITE Proto::ForegroundWhite()
#define CONSOLE_TEXT_YELLOW Proto::ForegroundYellow()
// Background colours
#define CONSOLE_BACKGROUND_BLACK Proto::BackgroundBlack()
#define CONSOLE_BACKGROUND_BLUE Proto::BackgroundBlue()
#define CONSOLE_BACKGROUND_CYAN Proto::BackgroundCyan()
#define CONSOLE_BACKGROUND_GREEN Proto::BackgroundGreen()
#define CONSOLE_BACKGROUND_MAGENTA Proto::BackgroundMagenta()
#define CONSOLE_BACKGROUND_RED Proto::BackgroundRed()
#define CONSOLE_BACKGROUND_WHITE Proto::BackgroundWhite()
#define CONSOLE_BACKGROUND_YELLOW Proto::BackgroundYellow()

#endif
#endif