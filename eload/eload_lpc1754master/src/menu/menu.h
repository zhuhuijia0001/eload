#ifndef _MENU_H_
#define _MENU_H_


extern void switch_to_menu(MENU_ID id);

extern MENU_ID get_cur_menu_id(void);
extern void process_cur_menu_msg(MSG_ID id, void *msg);

extern void init_menu(void);

#endif
