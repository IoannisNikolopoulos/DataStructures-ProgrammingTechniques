#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

typedef struct node *CircularList;

CircularList createCircularList();
CircularList circularListAdd(CircularList cursor, int data);
int circularListRemove (CircularList *cursor);
CircularList advanceCursor(CircularList cursor);

#endif /* CIRCULARLIST_H */
