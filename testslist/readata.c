#include "common.h"
#include "slist.h"

int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[1], "r");
	assert(fp!=NULL);
	char buf[128];
	while(!feof(fp))
	{
		memset(buf, 0, sizeof(buf));
		fread(buf, 1, sizeof(buf), fp);
		slist *tmp = (slist *)malloc(sizeof(slist));
		assign_node(tmp, buf, sizeof(buf));
		if(head == NULL)
		{
			head = tmp;
			pos = head;
		}else{
			add_to_list(tmp, pos);
		}
	}
	slist *each = head;
	while(each!=NULL)
	{
		printf("%s", each->context);	
		each = each->next;
	}
	while(head!=NULL)
	{
		del_list_head(head);
	}
	
	return 0;
}
