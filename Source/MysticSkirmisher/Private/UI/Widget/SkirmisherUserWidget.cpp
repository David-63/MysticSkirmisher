// Copyright David-6


#include "UI/Widget/SkirmisherUserWidget.h"


void USkirmisherUserWidget::SetWidgetController(UObject* InWidgetController)
{
    WidgetController = InWidgetController;
    WidgetControllerSet();
}