#include "Workspace.h"

/*
Function to parse the workspace configuration
*/
WorkspaceInfo* ParseWorkspaceConfig(char* configurationFile);

/*
Free the workspace configuration
*/
void FreeWorkspaceInfo(WorkspaceInfo* info);
