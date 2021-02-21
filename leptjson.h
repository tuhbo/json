#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h> /*size_t*/ 
typedef enum{
	LEPT_NULL, LEPT_FALSE, LEPT_TRUE,
	LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY,LEPT_OBJECT
} lept_type;

typedef struct lept_value lept_value;
typedef struct lept_member lept_member; 
struct lept_value{
	union {
		struct {lept_member *m;size_t size;}o;/* object: members, member count */
		struct {lept_value *e;size_t size;}a;/* array:  elements, element count */
		struct{char *s;size_t len;}s; /*string:null-terminated string, string length*/
		double n; /*number*/
	}u;
	lept_type type;
};

struct lept_member
{
	char *k;
	size_t klen; /*member key string, key string length*/	
	lept_value v; /*member value*/
};
enum {
    LEPT_PARSE_OK = 0, //无错误
	LEPT_PARSE_EXPECT_VALUE, //一个json只包含空白
	LEPT_PARSE_INVALID_VALUE, //值非法
	LEPT_PARSE_ROOT_NOT_SINGULAR, //一个值之后，在空白符之后还有其他字符
	LEPT_PARSE_NUMBER_TOO_BIG, //数值太大
	LEPT_PARSE_MISS_QUOTATION_MARK,//解析字符串确实
	LEPT_PARSE_INVALID_STRING_ESCAPE,//不合法的转义字符
	LEPT_PARSE_INVALID_STRING_CHAR, //不合法的字符
    LEPT_PARSE_INVALID_UNICODE_HEX, //只有高代理项而欠缺低代理项，或是低代理项不在合法码点范围
    LEPT_PARSE_INVALID_UNICODE_SURROGATE,//\u 后不是 4 位十六进位数字
    LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
    LEPT_PARSE_MISS_KEY, //对象没有键 
    LEPT_PARSE_MISS_COLON, //对象缺失冒号 
    LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET //对象缺少'}'
};

#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)

int lept_parse(lept_value* v, const char* json);
char* lept_stringify(const lept_value* v, size_t* length);

void lept_free(lept_value* v);

lept_type lept_get_type(const lept_value* v);

#define lept_set_null(v) lept_free(v)

int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);

size_t lept_get_array_size(const lept_value* v);
lept_value* lept_get_array_element(const lept_value* v, size_t index);

size_t lept_get_object_size(const lept_value* v);
const char* lept_get_object_key(const lept_value* v, size_t index);
size_t lept_get_object_key_length(const lept_value* v, size_t index);
lept_value* lept_get_object_value(const lept_value* v, size_t index);
#endif /*LEPTJSON_H__*/
