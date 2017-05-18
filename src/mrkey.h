/*******************************************************************************
 *
 *                              Delta Chat Core
 *                      Copyright (C) 2017 Björn Petersen
 *                   Contact: r10s@b44t.com, http://b44t.com
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see http://www.gnu.org/licenses/ .
 *
 *******************************************************************************
 *
 * File:    mrkey.h
 * Purpose: Handle keys
 *
 ******************************************************************************/


#ifndef __MRKEY_H__
#define __MRKEY_H__
#ifdef __cplusplus
extern "C" {
#endif


/*** library-private **********************************************************/

#define MR_PUBLIC  0
#define MR_PRIVATE 1


typedef struct mrkey_t
{
	unsigned char* m_binary;
	int            m_bytes;
	int            m_type;
} mrkey_t;


void  mrkey_init          (mrkey_t*); /* for initialing random memory that should be used as a key */
void  mrkey_empty         (mrkey_t*); /* free data needed; for private keys, this also wipes the memory */

int   mrkey_set_from_raw  (mrkey_t*, const unsigned char* data, int bytes, int type);
int   mrkey_set_from_key  (mrkey_t*, const mrkey_t*, int type);
int   mrkey_set_from_stmt (mrkey_t*, sqlite3_stmt*, int index, int type);

int   mrkey_equals        (const mrkey_t*, const mrkey_t*);

int   mrkey_save_keypair__(const mrkey_t* public_key, const mrkey_t* private_key, const char* addr, mrsqlite3_t* sql);
int   mrkey_load_public__ (mrkey_t*, mrsqlite3_t* sql);
int   mrkey_load_private__(mrkey_t*, mrsqlite3_t* sql);

char* mrkey_render_base64(const mrkey_t* ths, int break_every, const char* break_chars); /* the result must be freed */


#ifdef __cplusplus
} /* /extern "C" */
#endif
#endif /* __MRKEY_H__ */
