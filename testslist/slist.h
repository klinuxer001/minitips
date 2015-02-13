#define	BUF_LEN 128
typedef struct _slist{
	struct _slist *next;
	char *context;
}slist;

slist *head, *pos;
