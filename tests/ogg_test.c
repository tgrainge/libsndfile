/*
** Copyright (C) 2007 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include "sfconfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include	<sndfile.h>

#include	"utils.h"
#include	"generate.h"

#define	SAMPLE_RATE			44100
#define	DATA_LENGTH			(SAMPLE_RATE / 8)

typedef union
{	double d [DATA_LENGTH] ;
	float f [DATA_LENGTH] ;
	int i [DATA_LENGTH] ;
	short s [DATA_LENGTH] ;
} BUFFER ;

static BUFFER data_out ;
static BUFFER data_in ;

static void
ogg_short_test (void)
{	const char * filename = "vorbis_short.oga" ;

	SNDFILE * file ;
	SF_INFO sfinfo ;
	unsigned k ;

	print_test_name ("ogg_short_test", filename) ;

	/* Generate float data. */
	gen_windowed_sine_float (data_out.f, ARRAY_LEN (data_out.f), 1.0 * 0x7F00) ;

	/* Convert to shorteger. */
	for (k = 0 ; k < ARRAY_LEN (data_out.s) ; k++)
		data_out.s [k] = lrintf (data_out.f [k]) ;

	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	/* Set up output file type. */
	sfinfo.format = SF_FORMAT_OGG | SF_FORMAT_VORBIS ;
	sfinfo.channels = 1 ;
	sfinfo.samplerate = SAMPLE_RATE ;

	/* Write the output file. */
	file = test_open_file_or_die (filename, SFM_WRITE, &sfinfo, SF_FALSE, __LINE__) ;
	test_write_short_or_die (file, 0, data_out.s, ARRAY_LEN (data_out.s), __LINE__) ;
	sf_close (file) ;

	/* Read the file in again. */
	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	file = test_open_file_or_die (filename, SFM_READ, &sfinfo, SF_FALSE, __LINE__) ;
	test_read_short_or_die (file, 0, data_in.s, ARRAY_LEN (data_in.s), __LINE__) ;
	sf_close (file) ;

	puts ("ok") ;
	/*-unlink (filename) ;-*/
} /* ogg_short_test */

static void
ogg_int_test (void)
{	const char * filename = "vorbis_int.oga" ;

	SNDFILE * file ;
	SF_INFO sfinfo ;
	unsigned k ;

	print_test_name ("ogg_int_test", filename) ;

	/* Generate float data. */
	gen_windowed_sine_float (data_out.f, ARRAY_LEN (data_out.f), 1.0 * 0x7FFF0000) ;

	/* Convert to integer. */
	for (k = 0 ; k < ARRAY_LEN (data_out.i) ; k++)
		data_out.i [k] = lrintf (data_out.f [k]) ;

	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	/* Set up output file type. */
	sfinfo.format = SF_FORMAT_OGG | SF_FORMAT_VORBIS ;
	sfinfo.channels = 1 ;
	sfinfo.samplerate = SAMPLE_RATE ;

	/* Write the output file. */
	file = test_open_file_or_die (filename, SFM_WRITE, &sfinfo, SF_FALSE, __LINE__) ;
	test_write_int_or_die (file, 0, data_out.i, ARRAY_LEN (data_out.i), __LINE__) ;
	sf_close (file) ;

	/* Read the file in again. */
	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	file = test_open_file_or_die (filename, SFM_READ, &sfinfo, SF_FALSE, __LINE__) ;
	test_read_int_or_die (file, 0, data_in.i, ARRAY_LEN (data_in.i), __LINE__) ;
	sf_close (file) ;

	puts ("ok") ;
	/*-unlink (filename) ;-*/
} /* ogg_int_test */

static void
ogg_float_test (void)
{	const char * filename = "vorbis_float.oga" ;

	SNDFILE * file ;
	SF_INFO sfinfo ;

	print_test_name ("ogg_float_test", filename) ;

	gen_windowed_sine_float (data_out.f, ARRAY_LEN (data_out.f), 0.95) ;

	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	/* Set up output file type. */
	sfinfo.format = SF_FORMAT_OGG | SF_FORMAT_VORBIS ;
	sfinfo.channels = 1 ;
	sfinfo.samplerate = SAMPLE_RATE ;

	/* Write the output file. */
	file = test_open_file_or_die (filename, SFM_WRITE, &sfinfo, SF_FALSE, __LINE__) ;
	test_write_float_or_die (file, 0, data_out.f, ARRAY_LEN (data_out.f), __LINE__) ;
	sf_close (file) ;

	/* Read the file in again. */
	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	file = test_open_file_or_die (filename, SFM_READ, &sfinfo, SF_FALSE, __LINE__) ;
	test_read_float_or_die (file, 0, data_in.f, ARRAY_LEN (data_in.f), __LINE__) ;
	sf_close (file) ;

	puts ("ok") ;

	/* Test seeking. */
	print_test_name ("ogg_seek_test", filename) ;

	file = test_open_file_or_die (filename, SFM_READ, &sfinfo, SF_FALSE, __LINE__) ;
	test_seek_or_die (file, 10, SEEK_SET, 10, sfinfo.channels, __LINE__) ;
	sf_close (file) ;

	puts ("ok") ;

	/*-unlink (filename) ;-*/
} /* ogg_float_test */

static void
ogg_double_test (void)
{	const char * filename = "vorbis_double.oga" ;

	SNDFILE * file ;
	SF_INFO sfinfo ;

	print_test_name ("ogg_double_test", filename) ;

	gen_windowed_sine_double (data_out.d, ARRAY_LEN (data_out.d), 0.95) ;

	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	/* Set up output file type. */
	sfinfo.format = SF_FORMAT_OGG | SF_FORMAT_VORBIS ;
	sfinfo.channels = 1 ;
	sfinfo.samplerate = SAMPLE_RATE ;

	/* Write the output file. */
	file = test_open_file_or_die (filename, SFM_WRITE, &sfinfo, SF_FALSE, __LINE__) ;
	test_write_double_or_die (file, 0, data_out.d, ARRAY_LEN (data_out.d), __LINE__) ;
	sf_close (file) ;

	/* Read the file in again. */
	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	file = test_open_file_or_die (filename, SFM_READ, &sfinfo, SF_FALSE, __LINE__) ;
	test_read_double_or_die (file, 0, data_in.d, ARRAY_LEN (data_in.d), __LINE__) ;
	sf_close (file) ;

	puts ("ok") ;

	/* Test seeking. */
	print_test_name ("ogg_seek_test", filename) ;

	file = test_open_file_or_die (filename, SFM_READ, &sfinfo, SF_FALSE, __LINE__) ;
	test_seek_or_die (file, 10, SEEK_SET, 10, sfinfo.channels, __LINE__) ;
	sf_close (file) ;

	puts ("ok") ;

	/*-unlink (filename) ;-*/
} /* ogg_double_test */

int
main (void)
{
	ogg_short_test () ;
	ogg_int_test () ;
	ogg_float_test () ;
	ogg_double_test () ;

	return 0 ;
} /* main */
