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
        ret = system("exec rm -r ./Precise/Wakeword/*");
        ret = system("exec rm -r ./Precise/Notwakeword/*");

        Close();
        //only for supressing warning
        if (ret) {
            return;
        }
    }
}
