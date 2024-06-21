  //3DNomad LLC


#include "SPPlayuurController.h"
#include "Blueprint/UserWidget.h"

void ASPPlayuurController::BeginPlay()
{
    Super::BeginPlay();

    if (CrosshairWidgetClass)
    {
        CrosshairWidget = CreateWidget<USPCrosshairWidget>(this, CrosshairWidgetClass);
        if (CrosshairWidget)
        {
            CrosshairWidget->AddToViewport();
        }
    }
}
