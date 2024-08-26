/*
 * liblog.h - Personal C99 logging library.
 * See: https://github.com/8dcc/liblog
 * Copyright (C) 2024 8dcc
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBLOG_H_
#define LIBLOG_H_ 1

#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Settings */

/* Default FILE* when logging */
#ifndef LOG_FP
#define LOG_FP stderr
#endif

#if !defined(LOG_NO_DEFAULT)
/* NOTE: Comment to disable ASCII colors when logging */
#define LOG_USE_COLOR

/* NOTE: Uncomment to use UTC time instead of local time */
/* #define LOG_UTC */

/* NOTE: Comment to disable ogging features */
#define LOG_DATE
#define LOG_TIME
#define LOG_TAG
#define LOG_FUNC

#define LOG_PRINT_ALL
#endif /* LOG_NO_DEFAULT */

#ifdef LOG_PRINT_ALL
#define LOG_PRINT_TRACE
#define LOG_PRINT_DEBUG
#define LOG_PRINT_INFO
#define LOG_PRINT_WARN
#define LOG_PRINT_ERROR
#define LOG_PRINT_FATAL
#endif

/*----------------------------------------------------------------------------*/
/* Enums */

enum ELogTag {
  LOG_TAG_TRACE,
  LOG_TAG_DEBUG,
  LOG_TAG_INFO,
  LOG_TAG_WARN,
  LOG_TAG_ERROR,
  LOG_TAG_FATAL,

  LOG_TAGS,
};

/*----------------------------------------------------------------------------*/
/* Functions and callable macros */

void log_write(enum ELogTag tag, const char *func, const char *fmt, ...);

#ifdef LOG_PRINT_TRACE
#define log_trace(...) log_write(LOG_TAG_TRACE, __func__, __VA_ARGS__)
#else
#define log_trace(...)
#endif

#ifdef LOG_PRINT_DEBUG
#define log_debug(...) log_write(LOG_TAG_DEBUG, __func__, __VA_ARGS__)
#else
#define log_debug(...)
#endif

#ifdef LOG_PRINT_INFO
#define log_info(...) log_write(LOG_TAG_INFO, __func__, __VA_ARGS__)
#else
#define log_info(...)
#endif

#ifdef LOG_PRINT_WARN
#define log_warn(...) log_write(LOG_TAG_WARN, __func__, __VA_ARGS__)
#else
#define log_warn(...)
#endif

#ifdef LOG_PRINT_ERROR
#define log_error(...) log_write(LOG_TAG_ERROR, __func__, __VA_ARGS__)
#else
#define log_error(...)
#endif

#ifdef LOG_PRINT_FATAL
#define log_fatal(...) log_write(LOG_TAG_FATAL, __func__, __VA_ARGS__)
#else
#define log_fatal(...)
#endif

#endif /* LIBLOG_H_ */
