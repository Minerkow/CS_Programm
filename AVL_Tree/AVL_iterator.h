#pragma once

//*If iterator is empty return FALSE,
//*else returns TRUE
bool avlEmptyIt (struct Node_t* it);

//*Check iterators for equality
bool avlEqualIt(struct Node_t* it1, struct Node_t* it2);

//*Return Data by iterator
int avlGetDataByIt(struct Node_t* it);
