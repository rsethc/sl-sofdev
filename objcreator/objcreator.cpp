#include <stdio.h>
#include <stdlib.h>
char* getstring ()
{
	char* out = NULL;
	size_t len = 0;
	size_t chunksize = 0;
	while (true)
	{
		char cc = getchar();
		if (cc == '\n') break;
		if (len + 2 > chunksize)
		{
			chunksize += 16;
			out = realloc(out,chunksize);
		};
		*(out + len) = cc;
		len++;
	};
	if (out) *(out + len) = '\0';
	return out;
};
#include <stdint.h>
#include <slice.h>
float AskNumber_float (char* prompt)
{
	RETRY:
	printf(prompt);
	char* str = getstring();
	if (!str) goto RETRY;
	slScalar n;
	bool n_result = slScanDecF(str,&n);
	free(str);
	if (n_result)
	{
		printf("Invalid number!\n");
		goto RETRY;
	};
	return n;
};
uint32_t AskNumber_uint32 (char* prompt)
{
	RETRY:
	printf(prompt);
	char* str = getstring();
	if (!str) goto RETRY;
	slBU n;
	bool n_result = slScanDecU(str,&n);
	free(str);
	if (n_result)
	{
		printf("Invalid number!\n");
		goto RETRY;
	};
	return n;
};
int main ()
{
	RETRY_OUTPATH:
	printf("Path to object file?\n>>> ");
	char* outpath = getstring();
	FILE* outfile = fopen(outpath,"wb");
	free(outpath);
	if (!outfile)
	{
		printf("Could not open '%s' for writing!\n");
		goto RETRY_OUTPATH;
	};

	putchar('\n');

	RETRY_NAME:
	printf("Friendly name for object?\n>>> ");
	char* name = getstring();
	if (!name) goto RETRY_NAME;
	uint32_t name_len = strlen(name);
	fwrite(&name_len,sizeof(uint32_t),file);
	fwrite(name,name_len,file);
	free(name);

	putchar('\n');

	RETRY_TEXPATH:
	printf("Path to texture file?\n>>> ");
	char* texpath = getstring();
	if (!texpath) goto RETRY_TEXPATH;
	uint32_t texpath_len = strlen(texpath);
	fwrite(&texpath_len,sizeof(uint32_t),outfile);
	fwrite(texpath,texpath_len,outfile);
	free(texpath);

	putchar('\n');

	float w = AskNumber_float("Width?\n>>> ");
	fwrite(&w,sizeof(float),outfile);

	putchar('\n');

	float h = AskNumber_float("Height?\n>>> ");
	fwrite(&h,sizeof(float),outfile);

	putchar('\n');

	uint32_t nodecount = AskNumber_uint32("Number of nodes?\n>>> ");
	fwrite(&nodecount,sizeof(float),outfile);

	putchar('\n');

	for (uint32_t node = 0; node < nodecount; node++)
	{
		printf("Node #%u out of %u:\n",(unsigned int)(node + 1),(unsigned int)nodecount);

		putchar('\n');

		float x = AskNumber_float("\tNode X?\n\t>>> ");
		fwrite(&x,sizeof(float),outfile);

		putchar('\n');

		float y = AskNumber_float("\tNode Y?\n\t>>> ");
		fwrite(&y,sizeof(float),outfile);

		putchar('\n');
	};
	fclose(outfile);
};
