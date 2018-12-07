
//  g_textseq.c
//  g_textseq
//
//  Created by Andrew Macfarlane on 07/07/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_textseq.h"

#include <stdlib.h>

#include <strsplit/strsplit.h>
#include <r4/r4.h>

TextSeq* g_textseq_create(char* base, char* delim)
{

	printf("allocing seq\n");
	TextSeq* seq = calloc(1, sizeof(TextSeq));
	seq->chunks  = (char**)calloc(16, sizeof(const char**));
	printf("calloc done.\n");
	char** chunks = calloc(16, sizeof(char) * 256);
	// size_t size = strsplit(path, chunks, "/");

	printf("breaking [%s] into substrings via %s\n", base, delim);

	int count = 0;
	count     = strsplit(base, chunks, delim);

	// printf("split done.\n");

	seq->count  = count;
	seq->chunks = chunks;
	seq->base   = base;
	seq->delim  = delim;
	seq->cur    = 0;

	return seq;
}

void g_textseq_destroy(TextSeq* seq)
{
	if (!seq)
	{
		printf("Tried to destroy a NULL textseq\n");
		return;
	}
	free(seq->chunks);
	// free(seq->base);
	free(seq);
	seq = NULL; // dumb?
}

char* g_textseq_get(TextSeq* seq)
{

	if (seq == NULL)
		return "noooooooooope";

	return (seq->chunks[seq->cur]);
}
