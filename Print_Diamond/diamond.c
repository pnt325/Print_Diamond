#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include "diamond.h"


struct diamond_info_s
{
	int size;		// size of diamond
	char** data;	// 2D data data[r][c]
	char render;	// render character
};

static void _print(void* context);
static void _invert(void* context);
static void _fill(void* context);
static void _offset(void* context, int offset);

diamond_t* diamond_create(const int size, const char render_char)
{
	if (size % 2 == 0 || size < 3)
		return NULL;

	diamond_t* d = (diamond_t*)malloc(sizeof(diamond_t));
	if (d == NULL)
	{
		return NULL;
	}

	d->fill = _fill;
	d->invert = _invert;
	d->print = _print;
	d->offset = _offset;
	
	// 2D array
	struct diamond_info_s* info = (struct diamond_info_s*)malloc(sizeof(struct diamond_info_s));
	if (info == NULL)
	{
		return NULL;
	}

	info->size = size;
	info->render = render_char;

	// Pointer to pointer
	info->data = (char**)malloc(size * sizeof(char*));
	if (info->data == NULL)
	{
		return NULL;
	}
	
	// Pointer to data
	for (int i = 0; i < size; i++)
	{
		info->data[i] = (char*)malloc(size * sizeof(char));
		if (info->data[i] == NULL)
		{
			return NULL;
		}
	}

	// int diamond
	d->context = (void*)info;
	d->fill(info);

	printf("Diamond Info: Create diamond %p\r\n", d);
	return d;
}

void diamond_delete(diamond_t* diamond)
{
	if (diamond == NULL)
	{
		return;
	}

	printf("Diamond Info: Delete diamond %p\r\n", diamond);
	if (diamond->context)
	{
		struct diamond_info_s* info = (struct diamond_info_s*)diamond->context;

		if (info->data)
		{
			for (int i = 0; i < info->size; i++)
			{
				free(info->data[i]);
				info->data[i] = NULL;
			}
			free(info->data);
		}
		info->data = NULL;

		free(diamond->context);
		diamond->context = NULL;
	}

	free(diamond);
}


static void _print(void* context)
{
	struct diamond_info_s* info = (struct diamond_info_s*)context;
	printf("Diamond Info: Print\r\n");
	for (int i = 0; i < info->size; i++)
	{
		for (int j = 0; j < info->size; j++)
		{
			printf("%c", info->data[i][j]);
		}
		printf("\r\n");
	}
}
static void _invert(void* context)
{
	printf("Diamond Info: Invert\r\n");
	struct diamond_info_s* info = (struct diamond_info_s*)context;
	for (int i = 0; i < info->size; i++)
	{
		for (int j = 0; j < info->size; j++)
		{
			if (info->data[i][j] == info->render)
			{
				info->data[i][j] = ' ';
			}
			else
			{
				info->data[i][j] = info->render;
			}
		}
	}
}
static void _fill(void* context)
{
	printf("Diamond Info: Fill\r\n");
	struct diamond_info_s* info = (struct diamond_info_s*)context;
	int mid = info->size / 2;

	for (int i = 0; i < info->size; i++)
	{
		for (int c = 0; c < info->size; c++)
		{
			if (i <= mid)
			{
				if (c >= (mid - i) && c <= mid)
				{
					info->data[i][c] = info->render;
					continue;
				}

				if (c <= (mid + i) && c >= mid)
				{
					info->data[i][c] = info->render;
					continue;
				}
			}

			if (i >= mid)
			{
				if (c >= (i - mid) && c <= mid)
				{
					info->data[i][c] = info->render;
					continue;
				}

				if (c <= (info->size - i + mid - 1) && c >= mid)
				{
					info->data[i][c] = info->render;
					continue;
				}
			}
			info->data[i][c] = ' ';
		}
	}
}
static void _offset(void* context, int offset)
{
	struct diamond_info_s* info = (struct diamond_info_s*)context;
	int mid = info->size / 2;

	if (offset == 0)
	{
		printf("Diamond Error: offset could not zeror\r\n");
		return;
	}

	printf("Diamond Info: Offset\r\n");
	for (int i = 0; i < info->size; i++)
	{
		for (int c = 0; c < info->size; c++)
		{
			if (i <= mid)
			{
				if (c >= (mid - i) && c < (mid - i + offset) && c <= mid)
				{
					info->data[i][c] = info->render;
					continue;
				}

				if (c <= (mid + i) && c > (mid + i - offset) && c >= mid)
				{
					info->data[i][c] = info->render;
					continue;
				}
			}

			if (i >= mid)
			{
				if (c >= (i - mid) && c < (i - mid + offset) && c <= mid)
				{
					info->data[i][c] = info->render;
					continue;
				}

				if (c <= (info->size - i + mid - 1) && c > (info->size - i + mid - 1 - offset) && c >= mid)
				{
					info->data[i][c] = info->render;
					continue;
				}
			}
			info->data[i][c] = ' ';
		}
	}
}