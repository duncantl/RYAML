#include  "yaml.h"

#include <stdio.h>
#include <Rdefines.h>

SEXP processYAMLStream(yaml_parser_t *, int simplify, SEXP nullValue, int simplifyWithNames,  cetype_t charEncoding);

int read_handler(void *ext, unsigned char *buffer, size_t size, size_t *length)
{
    return(0);
}

SEXP
R_readYAML(SEXP stream, SEXP isFile, SEXP simplify, SEXP nullValue, SEXP simplifyWithNames, SEXP encoding)
{
    yaml_parser_t parser;
    FILE *input = NULL;
    SEXP ans = R_NilValue;

    yaml_parser_initialize(&parser);

    if(LOGICAL(isFile)[0]) {
	input = fopen(CHAR(STRING_ELT(stream, 0)), "r");
	yaml_parser_set_input_file(&parser, input);
    } else {
	yaml_parser_set_input(&parser, read_handler, NULL);
    }


    if(input)
	fclose(input);

    ans = processYAMLStream(&parser, INTEGER(simplify)[0], nullValue, INTEGER(simplifyWithNames)[0], INTEGER(encoding)[0]);

    yaml_parser_delete(&parser);

    if(!ans) {
	PROBLEM "failed in yaml"
        ERROR;
    }
	
    return(ans);
}

SEXP
processYAMLStream(yaml_parser_t *parser, int simplify, SEXP nullValue, int simplifyWithNames,  cetype_t charEncoding)
{
    SEXP ans = R_NilValue;
    int done = 0;
    yaml_event_t event;

    while (!done) {

      	         /* Get the next event. */
	if (!yaml_parser_parse(parser, &event)) {
	    return(NULL);
	}

	fprintf(stderr, "type -> %d\n", (int) event.type);

	         /*  Process the event */
	switch(event.type) {

	case YAML_STREAM_START_EVENT:
	    break;
	case YAML_STREAM_END_EVENT:
	    break;
	case YAML_DOCUMENT_START_EVENT:
	    break;
	case YAML_DOCUMENT_END_EVENT:
	    break;
	case YAML_ALIAS_EVENT:
	    break;
	case YAML_SCALAR_EVENT:
	    break;
	case YAML_SEQUENCE_START_EVENT:
	    break;
	case YAML_SEQUENCE_END_EVENT:
	    break;
	case YAML_MAPPING_START_EVENT:
	    break;
	case YAML_MAPPING_END_EVENT:
	    break;
	case YAML_NO_EVENT:
	    break;
	}


	/* Are we finished? */
	done = (event.type == YAML_STREAM_END_EVENT);

	/* The application is responsible for destroying the event object. */
	yaml_event_delete(&event);
    }

    ans = R_NilValue;

    return(ans);
}


