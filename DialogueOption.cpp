//3DNomad LLC


#include "DialogueOption.h"

UDialogueOption::UDialogueOption()
{
	DialogueCategory = EDialogueCategory::General;
}

UDialogueOption::~UDialogueOption()
{
}

void UDialogueOption::AddDialogueChoice(FDialogueChoices DialogueChoice)
{
	DialogueChoices.Add(DialogueChoice);
}

void UDialogueOption::RemoveDialogueChoice(FDialogueChoices DialogueChoice)
{
	DialogueChoices.Remove(DialogueChoice);
}

void UDialogueOption::AddDialogueName(FString DialogueName)
{
	DialogueNames.Add(DialogueName);
}

void UDialogueOption::RemoveDialogueName(FString DialogueName)
{
	DialogueNames.Remove(DialogueName);
}
