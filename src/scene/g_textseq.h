
//  g_textseq.c
//  g_textseq
//
//  Created by Andrew Macfarlane on 07/07/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_textseq_h_
#define g_textseq_h_

typedef struct TextSeq
{
	char*  delim;
	int    count;
	int    cur;
	char*  base;
	char** chunks;

} TextSeq;

char*       g_textseq_get(TextSeq* seq);
TextSeq*    g_textseq_create(char* base, char* delim);
void	g_textseq_destroy(TextSeq* seq);
const char* g_textseq_current(TextSeq* seq);

#endif
