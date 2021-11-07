#ifndef _DIAMOND_H_
#define _DIAMOND_H_

typedef struct
{
	void* context;
	void(*print)(void* context);
	void(*invert)(void* context);
	void(*fill)(void * context);
	void(*offset)(void* context, int offset);
}diamond_t;

diamond_t* diamond_create(const int size, const char render_char);
void diamond_delete(diamond_t* diamond);

#endif	/*_DIAMOND_H_*/