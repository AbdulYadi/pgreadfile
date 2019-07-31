#include <postgres.h>
#include <fmgr.h>
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif
#include <lib/stringinfo.h>
#include <utils/builtins.h>
#include <libpq/pqformat.h>

#define BUFFSIZE 5120

PG_FUNCTION_INFO_V1(pgreadfile);
Datum pgreadfile(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pgwritefile);
Datum pgwritefile(PG_FUNCTION_ARGS);

Datum
pgreadfile(PG_FUNCTION_ARGS)
{
	char* path;
	FILE* f;
	StringInfoData fileBytea;
	char buf[BUFFSIZE];
	size_t readlen;

	if(PG_NARGS()!=1) {
		elog(ERROR, "argument count must be 1");
	}
	
	if(PG_ARGISNULL(0)) {
		elog(ERROR, "filepath must be defined");
	}

	path = TextDatumGetCString(PG_GETARG_DATUM(0));
	f = fopen(path, "rb");
	if(f) {
		pq_begintypsend(&fileBytea);
		while(!feof(f)){
			readlen = fread(buf, 1, BUFFSIZE, f);
			appendBinaryStringInfo(&fileBytea, buf, readlen);
		}	
		fclose(f);
	} else {
		PG_RETURN_NULL();
	}

	PG_RETURN_BYTEA_P(pq_endtypsend(&fileBytea));
}

Datum
pgwritefile(PG_FUNCTION_ARGS)
{
	char* path;
	bytea* bytes;
	unsigned char* data;
	int32 len;	
	FILE* f;

	if(PG_NARGS()!=2) {
		elog(ERROR, "argument count must be 2");
	}
	
	if(PG_ARGISNULL(0)) {
		elog(ERROR, "filepath must be defined");
	}
	
	if(PG_ARGISNULL(1)) {
		elog(ERROR, "data must be defined");
	}

	path = TextDatumGetCString(PG_GETARG_DATUM(0));
	bytes = PG_GETARG_BYTEA_PP(1);
	data = (unsigned char*)VARDATA_ANY(bytes);
	len = VARSIZE_ANY_EXHDR(bytes);	
	
	f = fopen(path, "wb");
	if(f) {
		fwrite((const void *)data, 1, len, f);
		fclose(f);
	} else {
		PG_RETURN_VOID();
	}

	PG_RETURN_VOID();
}