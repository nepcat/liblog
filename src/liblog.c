/*
 * liblog.c - Personal C99 logging library.
 * See: https://github.com/8dcc/liblog
 * Copyright (C) 2024 8dcc
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include <time.h>

/* NOTE: Remember to change the path if you move the header */
#include "liblog.h"

/*----------------------------------------------------------------------------*/
/* Private macros */

#define IGNORE_UNUSED(VAR) (void)(VAR)

/*----------------------------------------------------------------------------*/
/* Private variables */

static const char *log_tags[LOG_TAGS] = {[LOG_TAG_DEBUG] = "DEBUG",
                                         [LOG_TAG_INFO] = "INFO ",
                                         [LOG_TAG_WARN] = "WARN ",
                                         [LOG_TAG_ERROR] = "ERROR",
                                         [LOG_TAG_FATAL] = "FATAL"};

#ifdef LOG_USE_COLOR
#define LOG_COLOR_RESET "\x1b[0m"

#ifndef LOG_COLOR_DIM
#define LOG_COLOR_DIM "\x1b[37m"
#endif /* LOG_COLOR_DIM */

static const char *log_colors[LOG_TAGS] = {[LOG_TAG_DEBUG] = "\x1b[32m",
                                           [LOG_TAG_INFO] = "\x1b[36m",
                                           [LOG_TAG_WARN] = "\x1b[33m",
                                           [LOG_TAG_ERROR] = "\x1b[1;31m",
                                           [LOG_TAG_FATAL] = "\x1b[1;31m"};
#else
#define LOG_COLOR_RESET ""
#define LOG_COLOR_DIM ""
static const char *log_colors[LOG_TAGS] = {[LOG_TAG_DEBUG] = "",
                                           [LOG_TAG_INFO] = "",
                                           [LOG_TAG_WARN] = "",
                                           [LOG_TAG_ERROR] = "",
                                           [LOG_TAG_FATAL] = ""};
#endif /* LOG_USE_COLOR */

/*----------------------------------------------------------------------------*/
/* Private functions */

static void log_write_fp(FILE *fp, enum ELogTag tag, const char *func,
                         const char *fmt, va_list va) {
#if defined(LOG_DATE) || defined(LOG_TIME)
  time_t now;
  struct tm *tm;

  time(&now);
#ifdef LOG_UTC
  tm = gmtime(&now);
#else
  tm = localtime(&now);
#endif

#endif

  /* Avoid -Wunused-variable */
  IGNORE_UNUSED(log_tags);
  IGNORE_UNUSED(log_colors);
  IGNORE_UNUSED(tag);
  IGNORE_UNUSED(func);

#if defined(LOG_DATE) || defined(LOG_TIME) || defined(LOG_TAG) ||              \
    defined(LOG_FUNC)
  fputc('[', fp);
  bool printed_before = false;
#endif

#ifdef LOG_DATE
  /* Draw the date */
  fprintf(fp, "%04d-%02d-%02d", 1900 + tm->tm_year, tm->tm_mon, tm->tm_mday);
  printed_before = true;
#endif

#ifdef LOG_TIME
  /* Draw the time */
  if (printed_before) {
    fputc(' ', fp);
  }
  fprintf(fp, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
  printed_before = true;
#endif

#ifdef LOG_TAG
  if (printed_before) {
    fputc(' ', fp);
  }
  /* Draw the tag (ERROR, WARNING, etc.) */
  fprintf(fp, "%s%s%s", log_colors[tag], log_tags[tag], LOG_COLOR_RESET);
  printed_before = true;
#endif

#ifdef LOG_FUNC
  if (printed_before) {
    fputc(' ', fp);
  }
  /* Draw the function name */
  fprintf(fp, "%s%s()%s", LOG_COLOR_DIM, func, LOG_COLOR_RESET);
  printed_before = true;
#endif

#if defined(LOG_DATE) || defined(LOG_TIME) || defined(LOG_TAG) ||              \
    defined(LOG_FUNC)
  fputc(']', fp);
  fputc(' ', fp);
#endif

  /* Draw the user message */
  vfprintf(fp, fmt, va);
  fputc('\n', fp);
  fflush(fp);
}

/*----------------------------------------------------------------------------*/
/* Public functions */

void log_write(enum ELogTag tag, const char *func, const char *fmt, ...) {
  va_list va;
  va_start(va, fmt);

  /* TODO: Iterate private list of FILE pointers */
  log_write_fp(LOG_FP, tag, func, fmt, va);

  va_end(va);
}
