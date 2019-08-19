#include "System.h"
#include "Main/GraphicUserInterface.h"
#include "ConfirmResetDialog.h"

namespace VeraCrypt
{
    ConfirmResetDialog::ConfirmResetDialog (wxWindow *parent)
        : ConfirmResetDialogBase (parent)
    {
        Layout();
        Fit();
        Center();
    }

    void ConfirmResetDialog::OnOkButtonClick (wxCommandEvent &event)
    {
        int ret;
        ret = system("exec rm -r ./Precise/recordings/wake-word/*");
        ret = system("exec rm -r ./Precise/recordings/not-wake-word/*");
        ret = system("exec rm ./Precise/*model*");

        Close();
        //only for supressing warning
        if (ret) {
            return;
        }
    }
}
