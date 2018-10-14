// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IBlissFunctionLibrary.h"



void UIBlissFunctionLibrary::CallInteractionFunction(FInteractionOption Option, AActor* EventInstigator)
{
	struct FInteractionFunctionArgs
	{
		AActor* EventInstigator;

		FInteractionFunctionArgs(AActor* EventInstigator)
			: EventInstigator(EventInstigator)
		{}
	};

	UFunction* Function = Option.Object->FindFunctionChecked(Option.FunctionName);

	FInteractionFunctionArgs Param(EventInstigator);
	Option.Object->ProcessEvent(Function, &Param);
}
