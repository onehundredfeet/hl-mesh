#include "hl_string_helpers.h"

//SUPER SKETCHY

static  hl_type *strType = nullptr;
void hl_cache_string_type( vstring *str) {
   strType = str->t;

   printf("SYSTEM PREAMBLE -- NEEX TO REMOVE THIS HACK: string type is %s, kind %d\n", hl_to_utf8(hl_type_str(str->t)), str->t->kind);
}

vstring * hl_utf8_to_hlstr( const char *str) {
    int strLen = (int)strlen( str );
    uchar * ubuf = (uchar*)hl_gc_alloc_noptr((strLen + 1) << 1);
    hl_from_utf8( ubuf, strLen, str );

    vstring* vstr = (vstring *)hl_gc_alloc_raw(sizeof(vstring));

    vstr->bytes = ubuf;
    vstr->length = strLen;
    vstr->t = strType;
    return vstr;
}

vdynamic * hl_vstr_to_dyn( vstring *str) {
    return (vdynamic *)(str);
}
/*

inline vdynamic * _idc_utf8_to_dyn_str( const char *str ) {

	int len = strlen(str);
	int size = (len + 1) << 1;
	vbyte *bytes = hl_alloc_bytes(size);
	uchar *out = (uchar*)bytes;

	int p = 0;
	unsigned int c, c2, c3;
	while( p++ < len ) {
		c = *(unsigned char *)str++;
		if( c < 0x80 ) {
			if( c == 0 ) break;
			// nothing
		} else if( c < 0xE0 ) {
			c = ((c & 0x3F) << 6) | ((*str++)&0x7F);
		} else if( c < 0xF0 ) {
			c2 = (unsigned)*str++;
			c = ((c & 0x1F) << 12) | ((c2 & 0x7F) << 6) | ((*str++) & 0x7F);
		} else {
			c2 = (unsigned)*str++;
			c3 = (unsigned)*str++;
			c = (((c & 0x0F) << 18) | ((c2 & 0x7F) << 12) | ((c3 & 0x7F) << 6) | ((*str++) & 0x7F)) - 0x10000;
			// surrogate pair
			if( p++ == outLen ) break;
			*out++ = (uchar)((c >> 10) + 0xD800);
			*out++ = (uchar)((c & 0x3FF) | 0xDC00);
			continue;
		}
		*out++ = (uchar)c;
	}
	*out = 0;

	vdynamic *d;
	d = hl_alloc_dynamic(&hlt_bytes);
	d->v.ptr = bytes;
	return d;
}

*/