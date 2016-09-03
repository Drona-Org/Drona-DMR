/**********************************************
Helper functions to make zing more efficient
***********************************************/


static model fun Seal() [invokescheduler = seal]
{}


static model fun Unseal() [invokescheduler = unseal]
{}

static model fun PRINT(a:any) [print=a]{}


