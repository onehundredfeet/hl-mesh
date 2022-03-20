#ifdef EMSCRIPTEN

#include <emscripten.h>
#define HL_PRIM
#define HL_NAME(n)	EMSCRIPTEN_KEEPALIVE eb_##n
#define DEFINE_PRIM(ret, name, args)
#define _OPT(t) t*
#define _GET_OPT(value,t) *value
#define alloc_ref(r, _) r
#define alloc_ref_const(r,_) r
#define _ref(t)			t
#define _unref(v)		v
#define free_ref(v) delete (v)
#define HL_CONST const

#else

#define HL_NAME(x) hmesh_##x
#include <hl.h>

// Need to link in helpers
HL_API hl_type hltx_ui16;
HL_API hl_type hltx_ui8;

#define _IDL _BYTES
#define _OPT(t) vdynamic *
#define _GET_OPT(value,t) (value)->v.t
template <typename T> struct pref {
	void (*finalize)( pref<T> * );
	T *value;
};

#define _ref(t) pref<t>
#define _unref(v) v->value
#define alloc_ref(r,t) _alloc_ref(r,finalize_##t)
#define alloc_ref_const(r, _) _alloc_const(r)
#define HL_CONST

template<typename T> void free_ref( pref<T> *r ) {
	if( !r->finalize ) hl_error("delete() is not allowed on const value.");
	delete r->value;
	r->value = NULL;
	r->finalize = NULL;
}

template<typename T> void free_ref( pref<T> *r, void (*deleteFunc)(T*) ) {
	if( !r->finalize ) hl_error("delete() is not allowed on const value.");
	deleteFunc( r->value );
	r->value = NULL;
	r->finalize = NULL;
}

// Float vector
struct _hl_float2 {
	float x;
	float y;
};

struct _hl_float3 {
	float x;
	float y;
	float z;
};

struct _hl_float4 {
	float x;
	float y;
	float z;
	float w;
};

// int vector
struct _hl_int2 {
	int x;
	int y;
};

struct _hl_int3 {
	int x;
	int y;
	int z;
};

struct _hl_int4 {
	int x;
	int y;
	int z;
	int w;
};

// double vector
struct _hl_double2 {
	double x;
	double y;
};

struct _hl_double3 {
	double x;
	double y;
	double z;
};

struct _hl_double4 {
	double x;
	double y;
	double z;
	double w;
};

inline void testvector(_hl_float3 *v) {
  printf("v: %f %f %f\n", v->x, v->y, v->z);
}
template<typename T> pref<T> *_alloc_ref( T *value, void (*finalize)( pref<T> * ) ) {
	if (value == nullptr) return nullptr;
	pref<T> *r = (pref<T>*)hl_gc_alloc_finalizer(sizeof(pref<T>));
	r->finalize = finalize;
	r->value = value;
	return r;
}

template<typename T> pref<T> *_alloc_const( const T *value ) {
	if (value == nullptr) return nullptr;
	pref<T> *r = (pref<T>*)hl_gc_alloc_noptr(sizeof(pref<T>));
	r->finalize = NULL;
	r->value = (T*)value;
	return r;
}

inline static varray* _idc_alloc_array(float *src, int count) {
	if (src == nullptr) return nullptr;

	varray *a = NULL;
	float *p;
	a = hl_alloc_array(&hlt_f32, count);
	p = hl_aptr(a, float);

	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
	return a;
}
inline static varray* _idc_alloc_array(unsigned char *src, int count) {
	if (src == nullptr) return nullptr;

	varray *a = NULL;
	float *p;
	a = hl_alloc_array(&hltx_ui8, count);
	p = hl_aptr(a, float);

	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
	return a;
}

inline static varray* _idc_alloc_array( char *src, int count) {
	return _idc_alloc_array((unsigned char *)src, count);
}

inline static varray* _idc_alloc_array(int *src, int count) {
	if (src == nullptr) return nullptr;

	varray *a = NULL;
	int *p;
	a = hl_alloc_array(&hlt_i32, count);
	p = hl_aptr(a, int);

	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
	return a;

}

inline static varray* _idc_alloc_array(double *src, int count) {
	if (src == nullptr) return nullptr;

	varray *a = NULL;
	double *p;
	a = hl_alloc_array(&hlt_f64, count);
	p = hl_aptr(a, double);

	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
	return a;
}


inline static varray* _idc_alloc_array(const unsigned short *src, int count) {
	if (src == nullptr) return nullptr;

	varray *a = NULL;
	unsigned short *p;
	a = hl_alloc_array(&hltx_ui16, count);
	p = hl_aptr(a, unsigned short);

	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
	return a;
}

inline static varray* _idc_alloc_array(unsigned short *src, int count) {
	if (src == nullptr) return nullptr;

	varray *a = NULL;
	unsigned short *p;
	a = hl_alloc_array(&hltx_ui16, count);
	p = hl_aptr(a, unsigned short);

	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
	return a;
}

inline static void _idc_copy_array( float *dst, varray *src, int count) {
	float *p = hl_aptr(src, float);
	for (int i = 0; i < count; i++) {
		dst[i] = p[i];
	}
}

inline static void _idc_copy_array( varray *dst, float *src,  int count) {
	float *p = hl_aptr(dst, float);
	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
}


inline static void _idc_copy_array( int *dst, varray *src, int count) {
	int *p = hl_aptr(src, int);
	for (int i = 0; i < count; i++) {
		dst[i] = p[i];
	}
}

inline static void _idc_copy_array( unsigned short *dst, varray *src) {
	unsigned short *p = hl_aptr(src, unsigned short);
	for (int i = 0; i < src->size; i++) {
		dst[i] = p[i];
	}
}

inline static void _idc_copy_array( const unsigned short *cdst, varray *src) {
	unsigned short *p = hl_aptr(src, unsigned short);
	unsigned short *dst = (unsigned short *)cdst;
	for (int i = 0; i < src->size; i++) {
		dst[i] = p[i];
	}
}

inline static void _idc_copy_array( varray *dst, int *src,  int count) {
	int *p = hl_aptr(dst, int);
	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
}


inline static void _idc_copy_array( double *dst, varray *src, int count) {
	double *p = hl_aptr(src, double);
	for (int i = 0; i < count; i++) {
		dst[i] = p[i];
	}
}

inline static void _idc_copy_array( varray *dst, double *src,  int count) {
	double *p = hl_aptr(dst, double);
	for (int i = 0; i < count; i++) {
		p[i] = src[i];
	}
}

#endif

#ifdef _WIN32
#pragma warning(disable:4305)
#pragma warning(disable:4244)
#pragma warning(disable:4316)
#endif


//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "tiny_gltf.h"

#include "hl_string_helpers.h"
#include "hmesh_impl.h"





extern "C" {

static void finalize_GLTFModel( _ref(tinygltf::Model)* _this ) { free_ref(_this ); }
HL_PRIM void HL_NAME(GLTFModel_delete)( _ref(tinygltf::Model)* _this ) {
	free_ref(_this );
}
DEFINE_PRIM(_VOID, GLTFModel_delete, _IDL);
static void finalize_GLTFLoader( _ref(tinygltf::TinyGLTF)* _this ) { free_ref(_this ); }
HL_PRIM void HL_NAME(GLTFLoader_delete)( _ref(tinygltf::TinyGLTF)* _this ) {
	free_ref(_this );
}
DEFINE_PRIM(_VOID, GLTFLoader_delete, _IDL);
static void finalize_EditablePolymesh( _ref(hmesh::EditableMesh)* _this ) { free_ref(_this ); }
HL_PRIM void HL_NAME(EditablePolymesh_delete)( _ref(hmesh::EditableMesh)* _this ) {
	free_ref(_this );
}
DEFINE_PRIM(_VOID, EditablePolymesh_delete, _IDL);
static void finalize_EditablePolymeshIt( _ref(hmesh::EditableMesh::Iterator)* _this ) { free_ref(_this ); }
HL_PRIM void HL_NAME(EditablePolymeshIt_delete)( _ref(hmesh::EditableMesh::Iterator)* _this ) {
	free_ref(_this );
}
DEFINE_PRIM(_VOID, EditablePolymeshIt_delete, _IDL);
HL_PRIM _ref(tinygltf::Model)* HL_NAME(GLTFModel_new0)() {
	return alloc_ref((new tinygltf::Model()),GLTFModel);
}
DEFINE_PRIM(_IDL, GLTFModel_new0,);

HL_PRIM int HL_NAME(GLTFModel_get_defaultScene)( _ref(tinygltf::Model)* _this ) {
	return _unref(_this)->defaultScene;
}
DEFINE_PRIM(_I32,GLTFModel_get_defaultScene,_IDL);
HL_PRIM int HL_NAME(GLTFModel_set_defaultScene)( _ref(tinygltf::Model)* _this, int value ) {
	_unref(_this)->defaultScene = (value);
	return value;
}
DEFINE_PRIM(_I32,GLTFModel_set_defaultScene,_IDL _I32);

HL_PRIM _ref(tinygltf::TinyGLTF)* HL_NAME(GLTFLoader_new0)() {
	return alloc_ref((new tinygltf::TinyGLTF()),GLTFLoader);
}
DEFINE_PRIM(_IDL, GLTFLoader_new0,);

HL_PRIM bool HL_NAME(GLTFLoader_LoadASCIIFromFile4)(_ref(tinygltf::TinyGLTF)* _this, _ref(tinygltf::Model)* model, vstring * path) {
	std::string error__cstr;
std::string warning__cstr;
std::string path__cstr = (path == nullptr) ? "" : hl_to_utf8( path->bytes ); // Should be garbage collected
	auto ___retvalue = (_unref(_this)->LoadASCIIFromFile(_unref(model), &error__cstr, &warning__cstr, path__cstr));
if (___retvalue != true) hl_throw(hl_vstr_to_dyn(hl_utf8_to_hlstr(error__cstr.c_str())));	return ___retvalue;
}
DEFINE_PRIM(_BOOL, GLTFLoader_LoadASCIIFromFile4, _IDL _IDL _STRING);

HL_PRIM bool HL_NAME(GLTFLoader_LoadBinaryFromFile4)(_ref(tinygltf::TinyGLTF)* _this, _ref(tinygltf::Model)* model, vstring * path) {
	std::string error__cstr;
std::string warning__cstr;
std::string path__cstr = (path == nullptr) ? "" : hl_to_utf8( path->bytes ); // Should be garbage collected
	auto ___retvalue = (_unref(_this)->LoadBinaryFromFile(_unref(model), &error__cstr, &warning__cstr, path__cstr));
if (___retvalue != true) hl_throw(hl_vstr_to_dyn(hl_utf8_to_hlstr(error__cstr.c_str())));	return ___retvalue;
}
DEFINE_PRIM(_BOOL, GLTFLoader_LoadBinaryFromFile4, _IDL _IDL _STRING);

HL_PRIM _ref(hmesh::EditableMesh)* HL_NAME(EditablePolymesh_new0)() {
	return alloc_ref((new hmesh::EditableMesh()),EditablePolymesh);
}
DEFINE_PRIM(_IDL, EditablePolymesh_new0,);

HL_PRIM void HL_NAME(EditablePolymesh_load1)(_ref(hmesh::EditableMesh)* _this, vstring * path) {
	const char* path__cstr = (path == nullptr) ? "" : hl_to_utf8( path->bytes ); // Should be garbage collected
	(_unref(_this)->Load(path__cstr));
}
DEFINE_PRIM(_VOID, EditablePolymesh_load1, _IDL _STRING);

HL_PRIM _ref(hmesh::EditableMesh::Iterator)* HL_NAME(EditablePolymesh_iterate0)(_ref(hmesh::EditableMesh)* _this) {
	return alloc_ref((_unref(_this)->NewIterator()),EditablePolymeshIt);
}
DEFINE_PRIM(_IDL, EditablePolymesh_iterate0, _IDL);

}
